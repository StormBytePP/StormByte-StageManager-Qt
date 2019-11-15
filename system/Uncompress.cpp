#include "Uncompress.h"

StageManager::system::Uncompress::Uncompress(const std::filesystem::path& file, const std::filesystem::path& destination): CompressionAction(file, destination) {
}

void StageManager::system::Uncompress::execute() {
    m_process->start(QString::fromStdString("tar"), get_untar_command_arguments());
}
