#pragma once

#include "Action.h"
#include <filesystem>

namespace StageManager::system {
    class Umount: public Action {
        public:
            Umount(const std::filesystem::path& mount_point);
            ~Umount() override = default;
            void execute() override;

        private:
            std::filesystem::path m_mount_point;
    };
}
