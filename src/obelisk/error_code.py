
class obelisk_exception(Exception):
    pass


class error_code(object):
    
    service_stopped = 1
    operation_failed = 2

    # blockchain errors
    not_found = 3
    duplicate = 4
    unspent_output = 5
    unsupported_payment_type = 6

    # network errors
    resolve_failed = 7
    network_unreachable = 8
    address_in_use = 9
    listen_failed = 10
    accept_failed = 11
    bad_stream = 12
    channel_timeout = 13

    # transaction pool
    blockchain_reorganized = 14
    pool_filled = 15

    # validate tx
    coinbase_transaction = 16
    is_not_standard = 17
    double_spend = 18
    input_not_found = 19

    # check_transaction()
    empty_transaction = 20
    output_value_overflow = 21
    invalid_coinbase_script_size = 22
    previous_output_null = 23

    # validate block
    previous_block_invalid = 24

    # check_block()
    size_limits = 25
    proof_of_work = 26
    futuristic_timestamp = 27
    first_not_coinbase = 28
    extra_coinbases = 29
    too_many_sigs = 30
    merkle_mismatch = 31

    # accept_block()
    incorrect_proof_of_work = 32
    timestamp_too_early = 33
    non_final_transaction = 34
    checkpoints_failed = 35
    old_version_block = 36
    coinbase_height_mismatch = 37

    # connect_block()
    duplicate_or_spent = 38
    validate_inputs_failed = 39
    fees_out_of_range = 40
    coinbase_too_large = 41

    @staticmethod
    def name_from_id(id):
        for key, value in error_code.__dict__.iteritems():
            if value == id:
                return key
        return None

