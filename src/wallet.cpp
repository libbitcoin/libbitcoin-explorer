#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <ncurses.h>
#include "config.hpp"
#include "util.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class wallet_control;

typedef boost::circular_buffer<std::string> string_buffer;

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
        ++selected_entry_;
        BITCOIN_ASSERT(selected_entry_ <= history_.size());
        if (selected_entry_ == 21)
            selected_entry_ = 0;
    }
    void select_previous()
    {
        if (selected_entry_ == 0)
            selected_entry_ = 21;
        --selected_entry_;
    }

    void set_cursor(size_t y, size_t x)
    {
        cursor_y_ = y;
        cursor_x_ = x;
    }
private:
    typedef std::vector<wallet_history_entry> wallet_history;

    uint64_t balance_ = 0;
    std::string receive_address_;
    size_t selected_entry_ = 0;
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
    bc::deterministic_wallet detwallet;
};

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

private:
    wallet_display& display_;
    address_cycler& addr_cycler_;
};

#include <unistd.h>

void wallet_display::draw()
{
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
    const bc::blockchain::history_list& history, wallet_display& display,
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
    obelisk::fullnode_interface& fullnode, wallet_display& display,
    const bc::payment_address& payaddr)
{
    //std::cout << "Worker: " << worker << std::endl;
    fullnode.address.fetch_history(payaddr,
        std::bind(history_fetched, _1, _2,
            std::ref(display), payaddr.encoded()),
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

void run_command(std::string user_input, string_buffer& console_output,
    wallet_control& control, bc::deterministic_wallet& detwallet)
{
    boost::trim(user_input);
    std::vector<std::string> strs;
    boost::split(strs, user_input, boost::is_any_of(" \t"));
    if (strs.empty())
        return;
    const std::string& cmd = strs[0];
    console_output.push_back(std::string("> ") + user_input);
    if (cmd == "help")
    {
        console_output.push_back("Commands:");
        console_output.push_back("send ADDRESS AMOUNT [FEE]");
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

int main()
{
    bc::deterministic_wallet detwallet;
    // investigate why master_public_keys are different.
    // TODO: bug here?
    detwallet.set_master_public_key(bc::decode_hex(
        "3315ae236373067ea27d92f10f9475b1ff727eebe45f4ce4dd21cf548a237755397"
        "548d57fdb94610aef20993b4ff4695cae581d3be98743593336b21090c7d2"));
    //std::string user_data = read_data();
    //if (!detwallet.set_seed(user_data))
    //{
    //    data_chunk mpk = decode_hex(user_data);
    //    if (!detwallet.set_master_public_key(mpk))
    //    {
    //        std::cerr << "wallet: No valid master public key, or "
    //            << "private secret key was passed in." << std::endl;
    //        return -1;
    //    }
    //}
    // TODO: read froma argv... this is testing only.
    detwallet.new_seed();
    initscr();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    wallet_display display;
    address_cycler cycler;
    //cycler.detwallet = detwallet;
    // TODO: this is a bug. detwallet should be copyable.
    cycler.detwallet.set_master_public_key(bc::decode_hex(
        "3315ae236373067ea27d92f10f9475b1ff727eebe45f4ce4dd21cf548a237755397"
        "548d57fdb94610aef20993b4ff4695cae581d3be98743593336b21090c7d2"));
    //BITCOIN_ASSERT(
    //    cycler.detwallet.master_public_key() == detwallet.master_public_key());
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
    obelisk::fullnode_interface fullnode(pool, config["service"]);
    for (size_t i = 0; i < 60; ++i)
    {
        bc::payment_address payaddr = cycler.address(i, false);
        fullnode.address.subscribe(payaddr, new_update,
            std::bind(subscribed, _1, _2,
                std::ref(fullnode), std::ref(display), payaddr));
        payaddr = cycler.address(i, true);
        fullnode.address.subscribe(payaddr, new_update,
            std::bind(subscribed, _1, _2,
                std::ref(fullnode), std::ref(display), payaddr));
    }
    std::thread thr([&fullnode]()
        {
            while (!stopped)
            {
                fullnode.update();
                sleep(0.1);
            }
        });
    std::string user_input;
    string_buffer console_output(20);
    console_output.push_back("Type 'help' to get started.");
	while(!stopped)
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

        display.set_cursor(50, user_input.size() + 2);
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
                run_command(user_input, console_output, control, detwallet);
                user_input.clear();
                break;
            default:
                user_input.push_back(c);
                break;
        }
    }
    stopped = true;
    thr.join();
    endwin();
    pool.stop();
    pool.join();
    return 0;
}

