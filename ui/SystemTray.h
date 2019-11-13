#ifndef STAGEMANAGERTRAY_H
#define STAGEMANAGERTRAY_H

#include <QSystemTrayIcon>


namespace StageManager::ui {
    class SystemTrayMenu;
    class SystemTray: public QSystemTrayIcon {
        Q_OBJECT
        public:
            SystemTray();
            ~SystemTray();

        private:
            SystemTrayMenu *m_menu;
    };
}

#endif // STAGEMANAGERTRAY_H
