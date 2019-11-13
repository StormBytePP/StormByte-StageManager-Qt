#ifndef STAGEMANAGERTRAYMENU_H
#define STAGEMANAGERTRAYMENU_H

#include <QMenu>

namespace StageManager::ui {
    class SystemTrayMenu: public QMenu {
        Q_OBJECT
        public:
            SystemTrayMenu();
            virtual ~SystemTrayMenu();
    };
}

#endif // STAGEMANAGERTRAYMENU_H
