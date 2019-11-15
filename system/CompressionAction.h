#pragma once

#include "Action.h"
#include <filesystem>
#include <string>
#include <QProcess>
#include <QStringList>

namespace StageManager::system {
    enum CompressionType: unsigned short { NONE = 0, GZIP, BZIP2, XZ, ZSTD };

    class CompressionAction: public Action {
        public:
            CompressionAction(const std::filesystem::path& file, const std::filesystem::path& folder);
            virtual ~CompressionAction() override;

        protected:
            std::filesystem::path m_file, m_folder;
            QProcess* m_process;

            CompressionType get_compression_type() const;
            const QStringList get_tar_command_arguments() const;
            const QStringList get_untar_command_arguments() const;

        private:
            QStringList get_tar_compression_arguments() const;
    };
}


