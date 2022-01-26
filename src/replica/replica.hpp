//
// 2022-01-26 12:29:55 dpw
//

#ifndef REPLICA_HPP
#define REPLICA_HPP

namespace replica {
    namespace clk std::chrono::system_clock;
    namespace fs = std::filesystem;

    struct PollSpec {
        bool enabled;
        std::chrono::duration interval;
    };

    struct BackupSpec {
        std::string version;
        std::string name;
        vector<std::string> src_folders;
        vector<std::string> targets;
        bool compress;
        vector<std::string> compression_rules;
        bool encrypt;
        vector<std::string> encryption_rules;
        PollSpec poll_spec;
    };

    struct FileSpec {
        std::string filename;
        std::string sha;
        std::uintmax_t size;
        fs::file_time_type last_modified;
        clk::time_point last_replica;
        FileSpec last_file_spec;
    };
}

#endif

