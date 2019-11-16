#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class SettingsWindow; }
QT_END_NAMESPACE

namespace StageManager::system { class Settings; }

namespace StageManager::ui {
    class SettingsWindow: public QDialog {
        Q_OBJECT

        public:
            explicit SettingsWindow(QWidget *parent = nullptr);
            ~SettingsWindow() override;
            const StageManager::system::Settings *getSettings() const;
            void closeEvent(QCloseEvent *event) override;
            void reject() override;
            void accept() override;
            void show();

        private slots:
            void stageDestinationChanged(const QString& destination);
            void stageCompressionChanged(const int& compression);
            void mountTypeChanged(const QString& mountType);
            void zramCompressionChanged(const int& compression);
            void tmpfsSizeChanged(const int& size);
            void folderDestinationChanged(const QString& destination);
            void saveButtonClicked();
            void cancelButtonClicked();
            void stageButtonClicked();
            void folderButtonclicked();

        private:
            Ui::SettingsWindow *m_ui;
            StageManager::system::Settings *m_settings, *m_settings_new;

            void showConfigStatusMessage(bool status);
            void copySettings();
            void updateUI();
    };
}
