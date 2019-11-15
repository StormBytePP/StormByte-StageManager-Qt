#pragma once

#include "Action.h"
#include <filesystem>

namespace StageManager::system {
    class Cp: public Action {
        public:
            Cp(const std::filesystem::path& origin, const std::filesystem::path& destination);
            ~Cp() override = default;
            void execute() override;

        private:
            std::filesystem::path m_origin, m_destination;
    };
}
