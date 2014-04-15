#include <unordered_set>
#include <thread>
#include <mutex>

#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <obelisk/obelisk.hpp>

#include "config.hpp"
#include "util.hpp"

#ifdef _WIN32
#include <stdlib.h>
#include <pdcwin.h>
#else
#include <ncurses.h>
#include <unistd.h>
#define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

// warning: this is not good code!
std::mutex broadcast_mutex;
std::vector<bc::transaction_type> tx_broadcast_queue;

class wallet_control;

typedef boost::circular_buffer<std::string> string_buffer;

typedef std::unordered_set<bc::payment_address> unique_address_set;

struct wallet_history_entry
{
    bool is_credit;
    bc::output_point point;
    size_t block_height;
    std::string address;
    uint64_t amount;
};

class wallet_display
{
public:
    string_buffer console_output;
    std::string user_input;

    wallet_display() : console_output(20) {}

    void draw();

    void add_balance(uint64_t balance)
    {
        balance_ += balance;
    }
    void set_receive_address(const std::string& addr)
    {
        receive_address_ = addr;
    }

    void clear_history()
    {
        history_.clear();
    }
    void add(wallet_history_entry&& entry)
    {
        history_.push_back(std::move(entry));
        std::sort(history_.begin(), history_.end(),
            [](const wallet_history_entry& a, const wallet_history_entry& b)
            {
                return a.block_height > b.block_height;
            });
    }

    void select_next()
    {
        if (history_.empty())
            return;
        ++selected_entry_;
        BITCOIN_ASSERT(selected_entry_ <= (int)history_.size());
        if (selected_entry_ == 21 || selected_entry_ == history_.size())
            selected_entry_ = 0;
    }
    void select_previous()
    {
        if (history_.empty())
            return;
        if (selected_entry_ == 0)
            /* Using min macro to avoid macro redefiniton conflict with pdcurses. */
            selected_entry_ = __min(21, (int)history_.size());
        --selected_entry_;
    }

    void set_cursor(size_t y, size_t x)
    {
        cursor_y_ = y;
        cursor_x_ = x;
    }

    bool is_selected()
    {
        return selected_entry_ != -1;
    }
    const wallet_history_entry& selected_entry()
    {
        BITCOIN_ASSERT(selected_entry_ < (int)history_.size());
        return history_[selected_entry_];
    }

private:
    typedef std::vector<wallet_history_entry> wallet_history;

    uint64_t balance_ = 0;
    std::string receive_address_;
    int selected_entry_ = -1;
    wallet_history history_;
    size_t cursor_y_ = 0, cursor_x_ = 0;
};

struct address_cycler
{
    const bc::payment_address address(size_t sequence, bool change)
    {
        bc::payment_address addr;
        bc::set_public_key(addr,
            detwallet.generate_public_key(sequence, change));
        return addr;
    }
    const bc::payment_address address()
    {
        return address(n, false);
    }

    size_t n = 0;
    libwallet::deterministic_wallet detwallet;
};

namespace std
{
    template <>
    struct hash<bc::output_point>
    {
        size_t operator()(const bc::output_point& outpoint) const
        {
            std::string raw;
            raw.resize(hash_digest_size + 4);
            auto serial = bc::make_serializer(raw.begin());
            serial.write_hash(outpoint.hash);
            serial.write_4_bytes(outpoint.index);
            std::hash<std::string> hash_fn;
            return hash_fn(raw);
        }
    };
}

class wallet_control
{
public:
    wallet_control(wallet_display& display, address_cycler& addr_cycler)
      : display_(display), addr_cycler_(addr_cycler)
    {
        display_.set_receive_address(addr_cycler_.address().encoded());
    }

    void next_address()
    {
        ++addr_cycler_.n;
        display_.set_receive_address(addr_cycler_.address().encoded());
    }
    void previous_address()
    {
        if (addr_cycler_.n == 0)
            return;
        --addr_cycler_.n;
        display_.set_receive_address(addr_cycler_.address().encoded());
    }

    void add_address(const bc::payment_address& addr)
    {
        our_addrs_.insert(addr);
    }
    bool is_ours(const bc::payment_address& addr)
    {
        return our_addrs_.find(addr) != our_addrs_.end();
    }

    void add_unspent(const output_point& outpoint,
        const bc::payment_address& addr, uint64_t value)
    {
        unspent_[outpoint] = output_data{addr, value};
    }

    libwallet::select_outputs_result find_unspent(uint64_t value)
    {
        // Generate unspent out list.
        output_info_list outs;
        for (const auto& pair: unspent_)
        {
            outs.push_back({pair.first, pair.second.value});
        }
        return libwallet::select_outputs(outs, value);
    }

    // For finding the right signing key.
    const bc::payment_address& lookup(const output_point& outpoint)
    {
        return unspent_[outpoint].addr;
    }

    const bc::payment_address change_address()
    {
        return addr_cycler_.address(addr_cycler_.n, true);
    }

    void add_key(const bc::payment_address& addr,
        const bc::secret_parameter& secret)
    {
        privkeys_[addr] = secret;
    }
    const bc::secret_parameter lookup(const bc::payment_address& addr)
    {
        return privkeys_[addr];
    }

private:
    struct output_data
    {
        bc::payment_address addr;
        uint64_t value;
    };

    typedef std::unordered_map<output_point, output_data> output_info_map;

    typedef std::unordered_map<bc::payment_address, bc::secret_parameter>
        keys_map;

    wallet_display& display_;
    address_cycler& addr_cycler_;
    unique_address_set our_addrs_;
    output_info_map unspent_;
    keys_map privkeys_;
};

void wallet_display::draw()
{
    int row, col;
    getmaxyx(stdscr, row, col);
    mvaddstr(28, 0, "Command:");
    mvhline(29, 0, ACS_HLINE, 40);
    for (size_t i = 0; i < console_output.size(); ++i)
    {
        std::string clear_line(col, ' ');
        mvaddstr(30 + i, 0, clear_line.c_str());
        mvaddstr(30 + i, 0, console_output[i].c_str());
    }
    std::string render_string(col - 2, ' ');
    attron(A_REVERSE);
    mvaddstr(50, 0, "> ");
    mvaddstr(50, 2, render_string.c_str());
    mvaddstr(50, 2, user_input.c_str());
    attroff(A_REVERSE);

    set_cursor(50, user_input.size() + 2);
    size_t y = 0;
    std::string balance_line =
        "Balance: " + bc::satoshi_to_btc(balance_) + " BTC";
    mvaddstr(y++, 0, balance_line.c_str());
    std::string receive_line = "Receive: " + receive_address_;
    mvaddstr(y++, 0, receive_line.c_str());
    mvhline(y++, 0, ACS_HLINE, 40);
    mvaddstr(y++, 0, "History");
    mvhline(y++, 0, ACS_HLINE, 40);
    size_t offset = 5;
    for (size_t i = 0; i < history_.size(); ++i)
    {
        // Bail...
        if (i > 20)
        {
            mvaddstr(offset + i, 0, "...");
            break;
        }
        const auto& entry = history_[i];
        std::string entry_line;
        if (entry.is_credit)
            entry_line = " To ";
        else
            entry_line = " From ";
        entry_line += std::string(
            entry.address.begin(), entry.address.begin() + 7) + "...";
        std::string amount_str = "[";
        if (entry.is_credit)
            amount_str += "+";
        else
            amount_str += "-";
        amount_str += bc::satoshi_to_btc(entry.amount);
        amount_str += " BTC] ";
        entry_line += std::string(
            40 - entry_line.size() - amount_str.size(), ' ');
        entry_line += amount_str;
        if (i == selected_entry_)
            attron(A_REVERSE);
        mvaddstr(offset + i, 0, entry_line.c_str());
        if (i == selected_entry_)
            attroff(A_REVERSE);
    }
    move(cursor_y_, cursor_x_);
    refresh();
}

void history_fetched(const std::error_code& ec,
    const bc::blockchain::history_list& history,
    wallet_control& control, wallet_display& display,
    const std::string& btc_address)
{
    if (ec)
    {
        //std::cerr << "history: Failed to fetch history: "
        //    << ec.message() << std::endl;
        return;
    }
    uint64_t balance = 0;
    for (const auto& row: history)
    {
        display.add({true, row.output, row.output_height,
            btc_address, row.value});
        if (row.spend.hash == bc::null_hash)
        {
            bc::payment_address addr;
            addr.set_encoded(btc_address);
            control.add_unspent(row.output, addr, row.value);
            balance += row.value;
            continue;
        }
        display.add({false, row.spend, row.spend_height,
            btc_address, row.value});
        //int64_t value = row.value;
        //std::cout << row.output.hash << " " << value << std::endl;
        //if (row.spend.hash != null_hash)
        //    std::cout << row.spend.hash << " " << -value << std::endl;
    }
    display.add_balance(balance);
    display.draw();
}

void subscribed(const std::error_code& ec, const obelisk::worker_uuid& worker,
    obelisk::fullnode_interface& fullnode,
    wallet_control& control, wallet_display& display,
    const bc::payment_address& payaddr)
{
    //std::cout << "Worker: " << worker << std::endl;
    fullnode.address.fetch_history(payaddr,
        std::bind(history_fetched, _1, _2,
            std::ref(control), std::ref(display), payaddr.encoded()),
        0, worker);
}

void new_update(const std::error_code& ec, size_t height,
    const bc::hash_digest& block_hash, const bc::transaction_type& tx)
{
    //std::cout << "Update " << bc::encode_hex(bc::hash_transaction(tx))
    //    << " [ #" << height << " "
    //    << bc::encode_hex(block_hash) << " ]" << std::endl;
}

// omg hacks
bool stopped = false;

// Maybe should also be in libbitcoin too?
script_type build_pubkey_hash_script(const short_hash& pubkey_hash)
{
    script_type result;
    result.push_operation({opcode::dup, data_chunk()});
    result.push_operation({opcode::hash160, data_chunk()});
    result.push_operation({opcode::special,
        data_chunk(pubkey_hash.begin(), pubkey_hash.end())});
    result.push_operation({opcode::equalverify, data_chunk()});
    result.push_operation({opcode::checksig, data_chunk()});
    return result;
}

script_type build_script_hash_script(const short_hash& script_hash)
{
    script_type result;
    result.push_operation({opcode::hash160, data_chunk()});
    result.push_operation({opcode::special,
        data_chunk(script_hash.begin(), script_hash.end())});
    result.push_operation({opcode::equal, data_chunk()});
    return result;
}

bool build_output_script(
    script_type& out_script, const payment_address& payaddr)
{
    switch (payaddr.version())
    {
        case payment_address::pubkey_version:
            out_script = build_pubkey_hash_script(payaddr.hash());
            return true;

        case payment_address::script_version:
            out_script = build_script_hash_script(payaddr.hash());
            return true;
    }
    return false;
}

bool make_signature(transaction_type& tx, size_t input_index,
    const elliptic_curve_key& key, const script_type& script_code)
{
    transaction_input_type& input = tx.inputs[input_index];

    const data_chunk public_key = key.public_key();
    if (public_key.empty())
        return false;
    hash_digest tx_hash =
        script_type::generate_signature_hash(tx, input_index, script_code, 1);
    if (tx_hash == null_hash)
        return false;
    data_chunk signature = key.sign(tx_hash);
    signature.push_back(0x01);
    //std::cout << signature << std::endl;
    script_type& script = tx.inputs[input_index].script;
    // signature
    script.push_operation({opcode::special, signature});
    // public key
    script.push_operation({opcode::special, public_key});
    return true;
}

bc::hash_digest send(wallet_control& control, std::vector<std::string>& strs,
    string_buffer& console_output)
{
    if (strs.size() != 3 && strs.size() != 4)
    {
        console_output.push_back("send: Wrong number of arguments.");
        return null_hash;
    }
    bc::payment_address dest_addr;
    if (!dest_addr.set_encoded(strs[1]))
    {
        console_output.push_back("send: Invalid address.");
        return null_hash;
    }
    uint64_t amount;
    try
    {
        amount = boost::lexical_cast<uint64_t>(strs[2]);
    }
    catch (const boost::bad_lexical_cast&)
    {
        console_output.push_back("send: Invalid amount.");
        return null_hash;
    }
    // Fee of 0.0001 BTC = 10000 Sat
    uint64_t fee = 10000;
    if (strs.size() == 4)
    {
        try
        {
            fee = boost::lexical_cast<uint64_t>(strs[3]);
        }
        catch (const boost::bad_lexical_cast&)
        {
            console_output.push_back("send: Invalid fee.");
            return null_hash;
        }
    }
    console_output.push_back("Sending...");
    libwallet::select_outputs_result unspent =
        control.find_unspent(amount + fee);
    if (unspent.points.empty())
    {
        console_output.push_back("send: Not enough funds.");
        return null_hash;
    }
    // construct transaction now.
    transaction_type tx;
    tx.version = 1;
    tx.locktime = 0;
    // start with outputs.
    // dest addr output first.
    transaction_output_type dest_output;
    dest_output.value = amount;
    if (!build_output_script(dest_output.script, dest_addr))
    {
        console_output.push_back("send: Unsupported address type.");
        return null_hash;
    }
    tx.outputs.push_back(dest_output);
    // add change output also.
    transaction_output_type change_output;
    change_output.value = unspent.change;
    bc::payment_address change_addr = control.change_address();
    bool change_script_success =
        build_output_script(change_output.script, change_addr);
    BITCOIN_ASSERT(change_script_success);
    tx.outputs.push_back(change_output);
    // notice we have left the fee out.
    // now do inputs.
    for (const bc::output_point& prevout: unspent.points)
    {
        transaction_input_type input;
        input.previous_output = prevout;
        input.sequence = 4294967295;
        tx.inputs.push_back(input);
    }
    // now sign inputs
    for (size_t i = 0; i < tx.inputs.size(); ++i)
    {
        bc::transaction_input_type& input = tx.inputs[i];
        const bc::payment_address addr = control.lookup(input.previous_output);
        const bc::secret_parameter secret = control.lookup(addr);
        elliptic_curve_key key;
        bool set_secret_success = key.set_secret(secret);
        BITCOIN_ASSERT(set_secret_success);
        payment_address address;
        set_public_key(address, key.public_key());
        script_type prevout_script_code;
        bool prevout_script_code_success =
            build_output_script(prevout_script_code, address);
        BITCOIN_ASSERT(prevout_script_code_success);
        bool sign_success = make_signature(tx, i, key, prevout_script_code);
    }
    // holy shit! now lets broadcast the tx!
    broadcast_mutex.lock();
    tx_broadcast_queue.push_back(tx);
    broadcast_mutex.unlock();
    return bc::hash_transaction(tx);
}

void showtx(const std::error_code& ec, const transaction_type& tx,
    string_buffer& console_output, wallet_display& display)
{
#define OUTPUT(stuff) \
    { \
    std::ostringstream oss; \
    oss << stuff; \
    console_output.push_back(oss.str()); \
    }

    OUTPUT("version: " << tx.version);
    OUTPUT("locktime: " << tx.locktime);
    for (const transaction_input_type& input: tx.inputs)
    {
        OUTPUT("Input:");
        OUTPUT("  previous output: "
            << input.previous_output.hash << ":"
            << input.previous_output.index);
        OUTPUT("  script: " << pretty(input.script));
        OUTPUT("  sequence: " << input.sequence);
        payment_address addr;
        if (extract(addr, input.script))
            OUTPUT("  address: " << addr.encoded());
    }
    for (const transaction_output_type& output: tx.outputs)
    {
        OUTPUT("Output:");
        OUTPUT("  value: " << output.value);
        OUTPUT("  script: " << pretty(output.script));
        payment_address addr;
        if (extract(addr, output.script))
            OUTPUT("  address: " << addr.encoded());
    }
    display.draw();
}

void run_command(std::string user_input, string_buffer& console_output,
    wallet_control& control, wallet_display& display,
    libwallet::deterministic_wallet& detwallet,
    obelisk::fullnode_interface& fullnode)
{
    boost::trim(user_input);
    if (user_input.empty())
        return;
    std::vector<std::string> strs;
    boost::split(strs, user_input, boost::is_any_of(" \t"));
    if (strs.empty())
        return;
    const std::string& cmd = strs[0];
    console_output.push_back(std::string("> ") + user_input);
    if (cmd == "help" || cmd == "h")
    {
        console_output.push_back("Commands:");
        console_output.push_back("send ADDRESS AMOUNT [FEE]");
        console_output.push_back("info");
    }
    else if (cmd == "send" || cmd == "s")
    {
        bc::hash_digest tx_hash = send(control, strs, console_output);
        if (tx_hash != null_hash)
            console_output.push_back(
                std::string("send: Broadcasting ") + bc::encode_hex(tx_hash));
    }
    else if (cmd == "info" || cmd == "i")
    {
        if (!display.is_selected())
        {
            console_output.push_back(
                "info: Nothing selected.");
            return;
        }
        const wallet_history_entry entry = display.selected_entry();
        console_output.push_back(
            std::string("info: ") +
            (entry.is_credit ? "Output " : "Input ") +
            bc::encode_hex(entry.point.hash) + ":" +
            boost::lexical_cast<std::string>(entry.point.index));
        fullnode.blockchain.fetch_transaction(entry.point.hash,
            std::bind(showtx, _1, _2, std::ref(console_output),
                std::ref(display)));
    }
    else if (cmd == "quit" || cmd == "q")
        stopped = true;
    else
        console_output.push_back(
            std::string("Unknown command: ") + cmd);
}

std::string read_data()
{
    std::istreambuf_iterator<char> it(std::cin);
    std::istreambuf_iterator<char> end;
    return std::string(it, end);
}

void init_curses()
{
    initscr();
    start_color();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
}

void handle_start(const std::error_code& ec)
{
    if (ec)
    {
        mvaddstr(0, 0, "ERROR WITH BROADCASTING SUBSYSTEM!!");
        refresh();
    }
}

void output_to_file(std::ofstream& file, bc::log_level level,
    const std::string& domain, const std::string& body)
{
    if (body.empty())
        return;
    file << bc::level_repr(level);
    if (!domain.empty())
        file << " [" << domain << "]";
    file << ": " << body << std::endl;
}

// warning: this is not good code!
void broadcast_subsystem()
{
    std::ofstream outfile("wallet.log");
    log_debug().set_output_function(
        std::bind(output_to_file, std::ref(outfile), _1, _2, _3));
    log_info().set_output_function(
        std::bind(output_to_file, std::ref(outfile), _1, _2, _3));
    log_warning().set_output_function(
        std::bind(output_to_file, std::ref(outfile), _1, _2, _3));
    log_error().set_output_function(
        std::bind(output_to_file, std::ref(outfile), _1, _2, _3));
    log_fatal().set_output_function(
        std::bind(output_to_file, std::ref(outfile), _1, _2, _3));
    threadpool pool(4);
    // Create dependencies for our protocol object.
    hosts hst(pool);
    handshake hs(pool);
    network net(pool);
    // protocol service.
    protocol prot(pool, hst, hs, net);
    prot.set_max_outbound(4);
    // Perform node discovery if needed and then creating connections.
    prot.start(handle_start);
    // wait
    while (!stopped)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        // if any new shit then broadcast it.
        broadcast_mutex.lock();
        if (tx_broadcast_queue.empty())
        {
            broadcast_mutex.unlock();
            continue;
        }
        transaction_type tx = tx_broadcast_queue.back();
        tx_broadcast_queue.pop_back();
        broadcast_mutex.unlock();
        auto ignore_send = [](const std::error_code&, size_t) {};
        prot.broadcast(tx, ignore_send);
    }
    auto ignore_stop = [](const std::error_code&) {};
    prot.stop(ignore_stop);
    // Safely close down.
    pool.stop();
    pool.join();
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: sx wallet SEED" << std::endl;
        return -1;
    }
    libwallet::deterministic_wallet detwallet;
    std::string user_data = argv[1];
    if (!detwallet.set_seed(user_data))
    {
        data_chunk mpk = decode_hex(user_data);
        if (!detwallet.set_master_public_key(mpk))
        {
            std::cerr << "wallet: No valid master public key, or "
                << "private secret key was passed in." << std::endl;
            return -1;
        }
    }
    init_curses();
    wallet_display display;
    address_cycler cycler;
    cycler.detwallet = detwallet;
    BITCOIN_ASSERT(
        cycler.detwallet.master_public_key() == detwallet.master_public_key());
    wallet_control control(display, cycler);
    // test data
    //display.add({false, bc::output_point{bc::null_hash, 0}, 0,
    //    "1blaablaa", 100020000});
    //display.add({true, bc::output_point{bc::null_hash, 0}, 0,
    //    "1xyzxyzdusd", 817000000});
    //display.add({false, bc::output_point{bc::null_hash, 0}, 0,
    //    "1foobarbar", 610020000});
    //display.add({false, bc::output_point{bc::null_hash, 0}, 0,
    //    "1afgoYY", 1020000});
    config_map_type config;
    load_config(config);
    bc::threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"],
        config["client-certificate"], config["server-public-key"]);
    for (size_t i = 0; i < 60; ++i)
    {
        bc::payment_address payaddr = cycler.address(i, false);
        control.add_address(payaddr);
        control.add_key(payaddr,
            detwallet.generate_secret(i, false));
        fullnode.address.subscribe(payaddr, new_update,
            std::bind(subscribed, _1, _2,
                std::ref(fullnode), std::ref(control), std::ref(display),
                payaddr));
        payaddr = cycler.address(i, true);
        control.add_address(payaddr);
        control.add_key(payaddr,
            detwallet.generate_secret(i, true));
        fullnode.address.subscribe(payaddr, new_update,
            std::bind(subscribed, _1, _2,
                std::ref(fullnode), std::ref(control), std::ref(display),
                payaddr));
    }
    std::thread thr([&fullnode]()
        {
            while (!stopped)
            {
                fullnode.update();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    std::thread broadcaster(broadcast_subsystem);
    string_buffer& console_output = display.console_output;
    std::string& user_input = display.user_input;
    console_output.push_back("Type 'help' to get started.");
	while(!stopped)
    {
        display.draw();
        int c = getch();
        if (c == KEY_F(1))
            break;
        switch (c)
        {
            case KEY_LEFT:
                control.previous_address();
                break;
            case KEY_RIGHT:
                control.next_address();
                break;
            case KEY_DOWN:
                display.select_next();
                break;
            case KEY_UP:
                display.select_previous();
                break;
            case KEY_BACKSPACE:
                if (!user_input.empty())
                    user_input.pop_back();
                break;
            case KEY_ENTER:
            case '\n':
                // submit command
                run_command(user_input, console_output,
                    control, display, detwallet, fullnode);
                user_input.clear();
                break;
            default:
                user_input.push_back(c);
                break;
        }
    }
    stopped = true;
    broadcaster.join();
    thr.join();
    endwin();
    pool.stop();
    pool.join();
    return 0;
}
