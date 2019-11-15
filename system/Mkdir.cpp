#include "Mkdir.h"

StageManager::system::Mkdir::Mkdir(const std::filesystem::path& path) {
    m_path = path;
}

void StageManager::system::Mkdir::execute() {
    emit done(std::filesystem::create_directory(m_path));
}
