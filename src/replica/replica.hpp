//
// 2022-01-26 12:29:55 dpw
//

#ifndef REPLICA_HPP
#define REPLICA_HPP

#include <filesystem>
#include <chrono>
#include <vector>
#include <string>

namespace replica {
    namespace chrono = std::chrono;
    namespace fs = std::filesystem;

    struct PollSpec {
        bool enabled;
        // std::chrono::duration interval;
        long interval;
    };

    struct BackupSpec {
        std::string version;
        std::string name;
        std::vector<std::string> src_folders;
        std::vector<std::string> targets;
        bool compress;
        std::vector<std::string> compression_rules;
        bool encrypt;
        std::vector<std::string> encryption_rules;
        replica::PollSpec poll_spec;
    };

    struct FileSpec {
        std::string filename;
        std::string sha;
        std::uintmax_t size;
        fs::file_time_type last_modified;
        chrono::system_clock::time_point last_replica;
        // replica::FileSpec last_file_spec;
    };
}

#endif

