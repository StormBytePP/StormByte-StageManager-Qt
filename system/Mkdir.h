#pragma once

#include "Action.h"
#include <filesystem>

namespace StageManager::system {
    class Mkdir: public Action {
        public:
            Mkdir(const std::filesystem::path& path);
            ~Mkdir() override = default;
            void execute() override;

        private:
            std::filesystem::path m_path;
    };
}
