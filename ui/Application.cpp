#include <QStyle>
#include <QDesktopWidget>
#include <QSettings>

#include "Application.h"
#include "MainWindow.h"

StageManager::ui::Application::Application(int &argc, char *argv[]): QApplication(argc, argv) {
    m_main_window = new MainWindow();
    m_main_window->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            m_main_window->size(),
            this->desktop()->availableGeometry()
        )
    );
    m_main_window->show();

}

StageManager::ui::Application::~Application() {
    m_main_window->hide();
    delete m_main_window;
}
