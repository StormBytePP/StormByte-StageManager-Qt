#include "Settings.h"
#include <filesystem>

const QVariant StageManager::system::Settings::default_stage_compression          = 9;
const QVariant StageManager::system::Settings::default_stage_destination          = "";
const QVariant StageManager::system::Settings::default_system_type                  = "zram";
const QVariant StageManager::system::Settings::default_system_tmpfs_size            = 20;
const QVariant StageManager::system::Settings::default_system_zram_compression      = 9;
const QVariant StageManager::system::Settings::default_system_folder_destination    = "";

StageManager::system::Settings::Settings():QSettings("StormByte.org", "StageManager") {
    reset();
}

int StageManager::system::Settings::getStageCompression() const {
    return m_storage_compression.toInt();
}

void StageManager::system::Settings::setStageCompression(const int& compression) {
    m_storage_compression = compression;
}

QString StageManager::system::Settings::getStageDestination() const {
    return m_storage_destination.toString();
}

void StageManager::system::Settings::setStageDestination(const QString& destination) {
    m_storage_destination = destination;
}

QString StageManager::system::Settings::getSystemType() const {
    return m_system_type.toString();
}

void StageManager::system::Settings::setSystemType(const QString& type) {
    m_system_type = type;
}

int StageManager::system::Settings::getTmpfsSize() const {
    return m_system_tmpfs_size.toInt();
}

void StageManager::system::Settings::setTmpfsSize(const int& size) {
    m_system_tmpfs_size = size;
}

int StageManager::system::Settings::getZramCompression() const {
    return m_system_zram_compression.toInt();
}

void StageManager::system::Settings::setZramCompression(const int& compression) {
    m_system_zram_compression = compression;
}

QString StageManager::system::Settings::getFolderDestination() const {
    return m_system_folder_destination.toString();
}

void StageManager::system::Settings::setFolderDestination(const QString& destination) {
    m_system_folder_destination = destination;
}

void StageManager::system::Settings::reset() {
    m_storage_compression = value("stage/compression", default_stage_compression);
    m_storage_destination = value("stage/destination", default_stage_destination);
    m_system_type = value("system/type", default_system_type);
    m_system_tmpfs_size = value("system/tmpfs/size", default_system_tmpfs_size);
    m_system_zram_compression = value("system/zram/compression", default_system_zram_compression);
    m_system_folder_destination = value("system/folder/destination", default_system_folder_destination);
}

bool StageManager::system::Settings::valid() const {
    bool ok = false;
    int compression = m_storage_compression.toInt(&ok);
    std::string destination = m_storage_destination.toString().toStdString();

    ok = ok && compression >=0 && compression <=9 && destination != "" && std::filesystem::exists(destination.c_str());

    if (ok) {
        if (m_system_type.toString() == "zram") {
            compression = m_system_zram_compression.toInt(&ok);
            ok = ok && compression >=0 && compression <=9;
        }
        else if (m_system_type.toString() == "tmpfs") {
            int size = m_system_tmpfs_size.toInt(&ok);
            ok = ok && size >=15;
        }
        else if (m_system_type.toString() == "folder") {
            destination = m_system_folder_destination.toString().toStdString();
            ok = destination != "" && std::filesystem::exists(destination.c_str());
        }
        else ok = false;
    }

    return ok;
}

bool StageManager::system::Settings::save() {
    if (valid()) {
        beginGroup("stage");
            setValue("compression", m_storage_compression);
            setValue("destination", m_storage_destination);
        endGroup();
        beginGroup("system");
            setValue("type", m_system_type);
            beginGroup("tmpfs");
                setValue("size", m_system_tmpfs_size);
            endGroup();
            beginGroup("zram");
                setValue("compression", m_system_zram_compression);
            endGroup();
            beginGroup("folder");
                setValue("destination", m_system_folder_destination);
            endGroup();
        endGroup();

        return true;
    }
    else return false;
}
