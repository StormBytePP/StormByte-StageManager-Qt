#include "Mount.h"
extern "C" {
    #include <sys/mount.h>
}

StageManager::system::Mount::Mount(const std::filesystem::path& base, const FileSystem& fs) {
    switch(fs) {
        case TMPFS:
            Mount("", base, fs, 0);
            break;

        case PROC:
            Mount("", base / "proc", fs, 0);
            break;

        case SYS:
            Mount("/sys", base / "sys", fs, MS_BIND | MS_REC | MS_SLAVE);
            break;

        case DEV:
            Mount("/dev", base / "dev", fs, MS_BIND | MS_REC | MS_SLAVE);
    }
}

StageManager::system::Mount::Mount(const std::filesystem::path &source, const std::filesystem::path &destination, const FileSystem &fs, const unsigned long &flags) {
    m_source = source;
    m_destination = destination;
    m_fs = fs;
    m_flags = flags;
}

const std::string StageManager::system::Mount::filesystem_mount_string() const {
    switch (m_fs) {
        case TMPFS:
            return "tmpfs";

        case PROC:
            return "proc";

        case SYS:
            return "sysfs";

        case DEV:
            return "devtmpfs";
    }
    return "";
}

void StageManager::system::Mount::execute() {
        emit done(mount(m_source.c_str(), m_destination.c_str(), filesystem_mount_string().c_str(), m_flags, nullptr) == 0);
}
