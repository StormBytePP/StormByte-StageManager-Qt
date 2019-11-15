#include "Umount.h"
extern "C" {
    #include <sys/mount.h>
}

StageManager::system::Umount::Umount(const std::filesystem::path& mount_point) {
    m_mount_point = mount_point;
}

void StageManager::system::Umount::execute() {
    emit(umount(m_mount_point.c_str()) == 0);
}
