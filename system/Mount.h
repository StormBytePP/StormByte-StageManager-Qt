#pragma once

#include "Action.h"
#include <filesystem>
#include <string>

namespace StageManager::system {
    enum FileSystem: unsigned short { TMPFS, PROC, SYS, DEV };

    class Mount: public Action {
        public:
            Mount(const std::filesystem::path &base, const FileSystem &fs);
            Mount(const std::filesystem::path &source, const std::filesystem::path &destination, const FileSystem &fs, const unsigned long &flags);
            ~Mount() override = default;
            void execute() override;

        private:
            std::filesystem::path m_source;
            std::filesystem::path m_destination;
            FileSystem m_fs;
            unsigned long m_flags;

            const std::string filesystem_mount_string() const;
    };
}
