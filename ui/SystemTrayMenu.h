#pragma once

#include <QMenu>

namespace StageManager::ui {
    class SystemTrayMenu: public QMenu {
        Q_OBJECT
        public:
            SystemTrayMenu();
            virtual ~SystemTrayMenu();
    };
}
