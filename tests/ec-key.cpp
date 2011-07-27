#include <iostream>
#include <iomanip>
#include <bitcoin/util/serializer.hpp>
#include <bitcoin/util/elliptic_curve_key.hpp>
#include <bitcoin/util/sha256.hpp>
#include <bitcoin/util/assert.hpp>
#include <bitcoin/util/logger.hpp>
#include <bitcoin/types.hpp>
using libbitcoin::elliptic_curve_key;
using libbitcoin::serializer;
using libbitcoin::hash_digest;
using libbitcoin::data_chunk;
using libbitcoin::log_info;
using libbitcoin::log_fatal;

int main()
{
    serializer ss;
    // blk number 170, tx 1, input 0
    // version = 1
    ss.write_4_bytes(1);
    // 1 inputs
    ss.write_var_uint(1);

    // input 0
    // prevout hash
    ss.write_hash(hash_digest{0x04, 0x37, 0xcd, 0x7f, 0x85, 0x25, 0xce, 0xed, 0x23, 0x24, 0x35, 0x9c, 0x2d, 0x0b, 0xa2, 0x60, 0x06, 0xd9, 0x2d, 0x85, 0x6a, 0x9c, 0x20, 0xfa, 0x02, 0x41, 0x10, 0x6e, 0xe5, 0xa5, 0x97, 0xc9});
    // prevout index 
    ss.write_4_bytes(0);

    // input script after running OP_CHECKSIG for this tx is a single
    // OP_CHECKSIG opcode
    data_chunk raw_data;
    raw_data = {0x04, 0x11, 0xdb, 0x93, 0xe1, 0xdc, 0xdb, 0x8a, 0x01, 0x6b, 0x49, 0x84, 0x0f, 0x8c, 0x53, 0xbc, 0x1e, 0xb6, 0x8a, 0x38, 0x2e, 0x97, 0xb1, 0x48, 0x2e, 0xca, 0xd7, 0xb1, 0x48, 0xa6, 0x90, 0x9a, 0x5c, 0xb2, 0xe0, 0xea, 0xdd, 0xfb, 0x84, 0xcc, 0xf9, 0x74, 0x44, 0x64, 0xf8, 0x2e, 0x16, 0x0b, 0xfa, 0x9b, 0x8b, 0x64, 0xf9, 0xd4, 0xc0, 0x3f, 0x99, 0x9b, 0x86, 0x43, 0xf6, 0x56, 0xb4, 0x12, 0xa3};
    data_chunk raw_script;
    raw_script = data_chunk();
    raw_script.push_back(raw_data.size());
    libbitcoin::extend_data(raw_script, raw_data);
    raw_script.push_back(172);
    ss.write_var_uint(raw_script.size());
    ss.write_data(raw_script);
    // sequence
    ss.write_4_bytes(0xffffffff);

    // 2 outputs for this tx
    ss.write_var_uint(2);

    // output 0
    ss.write_8_bytes(1000000000);
    // script for output 0
    raw_data = {0x04, 0xae, 0x1a, 0x62, 0xfe, 0x09, 0xc5, 0xf5, 0x1b, 0x13, 0x90, 0x5f, 0x07, 0xf0, 0x6b, 0x99, 0xa2, 0xf7, 0x15, 0x9b, 0x22, 0x25, 0xf3, 0x74, 0xcd, 0x37, 0x8d, 0x71, 0x30, 0x2f, 0xa2, 0x84, 0x14, 0xe7, 0xaa, 0xb3, 0x73, 0x97, 0xf5, 0x54, 0xa7, 0xdf, 0x5f, 0x14, 0x2c, 0x21, 0xc1, 0xb7, 0x30, 0x3b, 0x8a, 0x06, 0x26, 0xf1, 0xba, 0xde, 0xd5, 0xc7, 0x2a, 0x70, 0x4f, 0x7e, 0x6c, 0xd8, 0x4c};
    // when data < 75, we can just write it's length as a single byte ('special'
    // opcodes)
    raw_script = data_chunk();
    raw_script.push_back(raw_data.size());
    libbitcoin::extend_data(raw_script, raw_data);
    // OP_CHECKSIG
    raw_script.push_back(172);
    // now actually write the script
    ss.write_var_uint(raw_script.size());
    ss.write_data(raw_script);

    // output 0
    ss.write_8_bytes(4000000000);
    // script for output 0
    raw_data = {0x04, 0x11, 0xdb, 0x93, 0xe1, 0xdc, 0xdb, 0x8a, 0x01, 0x6b, 0x49, 0x84, 0x0f, 0x8c, 0x53, 0xbc, 0x1e, 0xb6, 0x8a, 0x38, 0x2e, 0x97, 0xb1, 0x48, 0x2e, 0xca, 0xd7, 0xb1, 0x48, 0xa6, 0x90, 0x9a, 0x5c, 0xb2, 0xe0, 0xea, 0xdd, 0xfb, 0x84, 0xcc, 0xf9, 0x74, 0x44, 0x64, 0xf8, 0x2e, 0x16, 0x0b, 0xfa, 0x9b, 0x8b, 0x64, 0xf9, 0xd4, 0xc0, 0x3f, 0x99, 0x9b, 0x86, 0x43, 0xf6, 0x56, 0xb4, 0x12, 0xa3};
    // when data < 75, we can just write it's length as a single byte ('special'
    // opcodes)
    raw_script = data_chunk();
    raw_script.push_back(raw_data.size());
    libbitcoin::extend_data(raw_script, raw_data);
    // OP_CHECKSIG
    raw_script.push_back(172);
    // now actually write the script
    ss.write_var_uint(raw_script.size());
    ss.write_data(raw_script);

    // End of 2 outputs

    // locktime
    ss.write_4_bytes(0);

    // write hash_type_code
    ss.write_4_bytes(1);

    // Dump hex to screen
    log_info() << "hashing:";
    {
        auto log_obj = log_info();
        log_obj << std::hex;
        for (int val: ss.get_data())
            log_obj << std::setfill('0') << std::setw(2) << val << ' ';
    }
    log_info();

    data_chunk raw_tx = {0x01, 0x00, 0x00, 0x00, 0x01, 0xc9, 0x97, 0xa5, 0xe5, 0x6e, 0x10, 0x41, 0x02, 0xfa, 0x20, 0x9c, 0x6a, 0x85, 0x2d, 0xd9, 0x06, 0x60, 0xa2, 0x0b, 0x2d, 0x9c, 0x35, 0x24, 0x23, 0xed, 0xce, 0x25, 0x85, 0x7f, 0xcd, 0x37, 0x04, 0x00, 0x00, 0x00, 0x00, 0x43, 0x41, 0x04, 0x11, 0xdb, 0x93, 0xe1, 0xdc, 0xdb, 0x8a, 0x01, 0x6b, 0x49, 0x84, 0x0f, 0x8c, 0x53, 0xbc, 0x1e, 0xb6, 0x8a, 0x38, 0x2e, 0x97, 0xb1, 0x48, 0x2e, 0xca, 0xd7, 0xb1, 0x48, 0xa6, 0x90, 0x9a, 0x5c, 0xb2, 0xe0, 0xea, 0xdd, 0xfb, 0x84, 0xcc, 0xf9, 0x74, 0x44, 0x64, 0xf8, 0x2e, 0x16, 0x0b, 0xfa, 0x9b, 0x8b, 0x64, 0xf9, 0xd4, 0xc0, 0x3f, 0x99, 0x9b, 0x86, 0x43, 0xf6, 0x56, 0xb4, 0x12, 0xa3, 0xac, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0xca, 0x9a, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x43, 0x41, 0x04, 0xae, 0x1a, 0x62, 0xfe, 0x09, 0xc5, 0xf5, 0x1b, 0x13, 0x90, 0x5f, 0x07, 0xf0, 0x6b, 0x99, 0xa2, 0xf7, 0x15, 0x9b, 0x22, 0x25, 0xf3, 0x74, 0xcd, 0x37, 0x8d, 0x71, 0x30, 0x2f, 0xa2, 0x84, 0x14, 0xe7, 0xaa, 0xb3, 0x73, 0x97, 0xf5, 0x54, 0xa7, 0xdf, 0x5f, 0x14, 0x2c, 0x21, 0xc1, 0xb7, 0x30, 0x3b, 0x8a, 0x06, 0x26, 0xf1, 0xba, 0xde, 0xd5, 0xc7, 0x2a, 0x70, 0x4f, 0x7e, 0x6c, 0xd8, 0x4c, 0xac, 0x00, 0x28, 0x6b, 0xee, 0x00, 0x00, 0x00, 0x00, 0x43, 0x41, 0x04, 0x11, 0xdb, 0x93, 0xe1, 0xdc, 0xdb, 0x8a, 0x01, 0x6b, 0x49, 0x84, 0x0f, 0x8c, 0x53, 0xbc, 0x1e, 0xb6, 0x8a, 0x38, 0x2e, 0x97, 0xb1, 0x48, 0x2e, 0xca, 0xd7, 0xb1, 0x48, 0xa6, 0x90, 0x9a, 0x5c, 0xb2, 0xe0, 0xea, 0xdd, 0xfb, 0x84, 0xcc, 0xf9, 0x74, 0x44, 0x64, 0xf8, 0x2e, 0x16, 0x0b, 0xfa, 0x9b, 0x8b, 0x64, 0xf9, 0xd4, 0xc0, 0x3f, 0x99, 0x9b, 0x86, 0x43, 0xf6, 0x56, 0xb4, 0x12, 0xa3, 0xac, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    BITCOIN_ASSERT(raw_tx == ss.get_data());

    hash_digest tx_hash = libbitcoin::generate_sha256_hash(ss.get_data());

    data_chunk pubkey{0x04, 0x11, 0xdb, 0x93, 0xe1, 0xdc, 0xdb, 0x8a, 0x01, 0x6b, 0x49, 0x84, 0x0f, 0x8c, 0x53, 0xbc, 0x1e, 0xb6, 0x8a, 0x38, 0x2e, 0x97, 0xb1, 0x48, 0x2e, 0xca, 0xd7, 0xb1, 0x48, 0xa6, 0x90, 0x9a, 0x5c, 0xb2, 0xe0, 0xea, 0xdd, 0xfb, 0x84, 0xcc, 0xf9, 0x74, 0x44, 0x64, 0xf8, 0x2e, 0x16, 0x0b, 0xfa, 0x9b, 0x8b, 0x64, 0xf9, 0xd4, 0xc0, 0x3f, 0x99, 0x9b, 0x86, 0x43, 0xf6, 0x56, 0xb4, 0x12, 0xa3};
    // Leave out last byte since that's the hash_type_code (SIGHASH_ALL in this
    // case)
    data_chunk signature{0x30, 0x44, 0x02, 0x20, 0x4e, 0x45, 0xe1, 0x69, 0x32, 0xb8, 0xaf, 0x51, 0x49, 0x61, 0xa1, 0xd3, 0xa1, 0xa2, 0x5f, 0xdf, 0x3f, 0x4f, 0x77, 0x32, 0xe9, 0xd6, 0x24, 0xc6, 0xc6, 0x15, 0x48, 0xab, 0x5f, 0xb8, 0xcd, 0x41, 0x02, 0x20, 0x18, 0x15, 0x22, 0xec, 0x8e, 0xca, 0x07, 0xde, 0x48, 0x60, 0xa4, 0xac, 0xdd, 0x12, 0x90, 0x9d, 0x83, 0x1c, 0xc5, 0x6c, 0xbb, 0xac, 0x46, 0x22, 0x08, 0x22, 0x21, 0xa8, 0x76, 0x8d, 0x1d, 0x09};
    BITCOIN_ASSERT(signature.size() == 70);

    elliptic_curve_key key;
    if (!key.set_public_key(pubkey))
    {
        log_fatal() << "unable to set EC public key";
        return -1;
    }

    log_info() << "checksig returns: " << (key.verify(tx_hash, signature) ? "true" : "false");
    return 0;
}

