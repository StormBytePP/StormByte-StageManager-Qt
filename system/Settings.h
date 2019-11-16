#pragma once

#include <QSettings>
#include <QVariant>

namespace StageManager::system {
    class Settings: public QSettings {
        public:
            Settings();
            ~Settings() = default;

            int getStageCompression() const;
            void setStageCompression(const int& compression);
            QString getStageDestination() const;
            void setStageDestination(const QString& destination);
            QString getSystemType() const;
            void setSystemType(const QString& type);
            int getTmpfsSize() const;
            void setTmpfsSize(const int& size);
            int getZramCompression() const;
            void setZramCompression(const int& compression);
            QString getFolderDestination() const;
            void setFolderDestination(const QString& destination);

            bool valid() const;
            bool save();
            void reset();

        private:
            QVariant m_storage_compression, m_storage_destination, m_system_type, m_system_tmpfs_size, m_system_zram_compression, m_system_folder_destination;

            static const QVariant default_stage_compression;
            static const QVariant default_stage_destination;
            static const QVariant default_system_type;
            static const QVariant default_system_tmpfs_size;
            static const QVariant default_system_zram_compression;
            static const QVariant default_system_folder_destination;
    };
}

/*
 *
    beginGroup("storage");
        setValue("compression", value("storage/compression", 9));
        setValue("destination", value("storage/destination", ""));
    endGroup();
    beginGroup("system");
        setValue("type", value("storage/type", "zram"));
        beginGroup("tmpfs");
            setValue("size", value("storage/system/tmpfs/size", "20G"));
        endGroup();
        beginGroup("zram");
            setValue("compression", value("storage/system/zram/compression", 9));
        endGroup();
        beginGroup("folder");
            setValue("destination", value("storage/system/folder/destination", ""));
        endGroup();
    endGroup();
 */
