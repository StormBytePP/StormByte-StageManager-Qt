#ifndef STAGEMANAGER_MAIN_WINDOW_H
#define STAGEMANAGER_MAIN_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class StageManager; }
QT_END_NAMESPACE

namespace StageManager::ui {
    class SystemTray;
    class MainWindow: public QMainWindow {
        Q_OBJECT
        private:
            Ui::StageManager *ui;
            SystemTray *tray;

        private slots:
            void handleButton();

        public:
            MainWindow(QWidget *parent = nullptr);
            ~MainWindow();

    };
}
#endif // STAGEMANAGER_MAIN_WINDOW_H
