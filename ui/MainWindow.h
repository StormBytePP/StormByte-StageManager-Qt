#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class StageManager; }
QT_END_NAMESPACE

namespace StageManager::ui {
    class SystemTray;
    class SettingsWindow;
    class MainWindow: public QMainWindow {
        Q_OBJECT
        public:
            MainWindow(QWidget *parent = nullptr);
            ~MainWindow() override;
            void show();
            void closeEvent(QCloseEvent *event) override;

        private slots:
            void configurationButtonClicked();
            void addStageTabButtonClicked();

        private:
            Ui::StageManager *m_ui;
            SystemTray *m_tray;
            SettingsWindow *m_settings;
    };
}
