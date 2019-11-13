#include "SystemTray.h"
#include "SystemTrayMenu.h"

StageManager::ui::SystemTray::SystemTray(): QSystemTrayIcon(QIcon::fromTheme("edit-undo")) {
    m_menu = new StageManager::ui::SystemTrayMenu();
    setVisible(true);
    setContextMenu(m_menu);
}

StageManager::ui::SystemTray::~SystemTray() {
    delete m_menu;
}
