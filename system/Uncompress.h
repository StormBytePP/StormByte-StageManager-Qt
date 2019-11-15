#pragma once

#include "CompressionAction.h"
#include <filesystem>

namespace StageManager::system {
    class Uncompress: public CompressionAction {
        public:
            Uncompress(const std::filesystem::path& file, const std::filesystem::path& destination);
            virtual ~Uncompress() override = default;
            void execute() override;
    };
}
