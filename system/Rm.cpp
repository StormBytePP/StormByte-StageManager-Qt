#include "Rm.h"

StageManager::system::Rm::Rm(const std::filesystem::path& path) {
    m_path = path;
}

void StageManager::system::Rm::execute() {
    emit done(std::filesystem::remove_all(m_path) > 0);
}
