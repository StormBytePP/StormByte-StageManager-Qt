#include "Cp.h"

StageManager::system::Cp::Cp(const std::filesystem::path& origin, const std::filesystem::path& destination) {
    m_origin = origin;
    m_destination = destination;
}

void StageManager::system::Cp::execute() {
    std::filesystem::copy(m_origin, m_destination, std::filesystem::copy_options::recursive);
    emit done(true);
}
