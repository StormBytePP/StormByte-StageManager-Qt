#include "Linux.h"
#include "System.h"
#include <iostream>

StageManager::lib::Linux::Linux(const std::string& base): m_base(base) {
}

bool StageManager::lib::Linux::mount(const FileSystem& fs) {
    bool result = false;

    switch(fs) {
        case TMPFS:
            result = mount("", m_base, fs, 0);
            break;

        case PROC:
            result = mount("", m_base / "proc", fs, 0);
            break;

        case SYS:
            result = mount("/sys", m_base / "sys", fs, StageManager::lib::System::MS_BIND | StageManager::lib::System::MS_REC | StageManager::lib::System::MS_SLAVE);
            break;

        case DEV:
            result = mount("/dev", m_base / "dev", fs, StageManager::lib::System::MS_BIND | StageManager::lib::System::MS_REC | StageManager::lib::System::MS_SLAVE);
    }

    return result;
}

bool StageManager::lib::Linux::umount(const FileSystem& fs) {
    switch(fs) {
        case TMPFS:
            return StageManager::lib::System::umount(m_base.c_str()) == 0;

        case PROC:
            return StageManager::lib::System::umount((m_base / "proc").c_str()) == 0;

        case SYS:
            return StageManager::lib::System::umount((m_base / "sys").c_str()) == 0;

        case DEV:
            return StageManager::lib::System::umount((m_base / "dev").c_str()) == 0;
    }

    return false;
}

bool StageManager::lib::Linux::mkdir(const std::string &path) {
    return StageManager::lib::System::mkdir((m_base / path).c_str(), 0755) == 0;
}

void StageManager::lib::Linux::copy(const std::string &source, const std::string &destination) {
    std::filesystem::copy(source, destination, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
}

bool StageManager::lib::Linux::rm(const std::string &source) {
    return std::filesystem::remove_all((m_base / source).c_str()) > 0;
}

const std::string StageManager::lib::Linux::get_filesystem_string(const FileSystem& fs) const {
    switch (fs) {
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

bool StageManager::lib::Linux::mount(const std::filesystem::path &source, const std::filesystem::path &destination, const FileSystem &fs, const unsigned long &flags) {
    return StageManager::lib::System::mount(source.c_str(), destination.c_str(), get_filesystem_string(fs).c_str(), flags, nullptr) == 0;
}
