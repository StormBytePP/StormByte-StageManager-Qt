#include "MainWindow.h"
#include "SystemTray.h"
#include "./ui_MainWindow.h"

StageManager::ui::MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::StageManager) {
    ui->setupUi(this);
    tray = new SystemTray();
}

StageManager::ui::MainWindow::~MainWindow() {
    delete ui;
    delete tray;
}

