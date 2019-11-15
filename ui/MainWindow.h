#pragma once

#include <QMainWindow>
#include "system/Compress.h"

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
            void eventDone(bool result);

        public:
            MainWindow(QWidget *parent = nullptr);
            ~MainWindow();

    };
}
