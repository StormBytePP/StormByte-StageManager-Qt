#include "Compress.h"

StageManager::system::Compress::Compress(const std::filesystem::path& source, const std::filesystem::path& file): CompressionAction(file, source) {
}

void StageManager::system::Compress::execute() {
    m_process->start(QString::fromStdString("tar"), get_tar_command_arguments());
}
