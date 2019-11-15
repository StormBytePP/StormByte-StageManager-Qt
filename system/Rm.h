#pragma once

#include "Action.h"
#include <filesystem>

namespace StageManager::system {
    class Rm: public Action {
        public:
            Rm(const std::filesystem::path& path);
            ~Rm() override = default;
            void execute() override;

        private:
            std::filesystem::path m_path;
    };
}
