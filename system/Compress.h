#pragma once

#include "CompressionAction.h"
#include <filesystem>

namespace StageManager::system {
    class Compress: public CompressionAction {
        public:
            Compress(const std::filesystem::path& source, const std::filesystem::path& file);
            virtual ~Compress() override = default;
            void execute() override;
    };
}
