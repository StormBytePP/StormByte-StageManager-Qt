#ifndef LINUX_H
#define LINUX_H

#include <string>
#include <filesystem>
#include "File.h"

namespace StageManager::lib {
    class Linux {
        public:
            enum FileSystem: unsigned short { TMPFS, PROC, SYS, DEV };

            Linux(const std::string& base);
            Linux(const Linux&) = default;
            Linux(Linux&&) = default;
            Linux& operator=(const Linux&) = default;
            ~Linux() = default;

        private:
            std::filesystem::path m_base;

        public:
            bool mount(const FileSystem& system_type);
            bool umount(const FileSystem& system_type);
            bool mkdir(const std::string& path);
            void copy(const std::string& source, const std::string& destination);
            bool rm(const std::string& source);
            bool compress(const std::string& source, const File& destination);
            bool uncompress(const File& file, const std::string& destination);
            const std::string get_filesystem_string(const FileSystem& fs) const;
            bool mount(const std::filesystem::path &source, const std::filesystem::path &destination, const FileSystem &fs, const unsigned long &flags);
    };
}

#endif // LINUX_H
