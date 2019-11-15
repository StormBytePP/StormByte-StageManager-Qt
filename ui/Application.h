#pragma once

#include <QApplication>

namespace StageManager::ui {
    class MainWindow;
    class Application: public QApplication {
        Q_OBJECT
        public:
            Application(int &argc, char *argv[]);
            virtual ~Application();

        private:
            MainWindow *m_main_window;

    };
}
