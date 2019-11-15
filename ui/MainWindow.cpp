#include "MainWindow.h"
#include "SystemTray.h"
#include "./ui_MainWindow.h"
#include <iostream>
#include "system/Compress.h"

StageManager::ui::MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::StageManager) {
    ui->setupUi(this);
    tray = new SystemTray();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(handleButton()));
    /*
    connect(m_uncompress, SIGNAL(done(bool)), this, SLOT(eventDone(bool)));
    connect(m_uncompress, SIGNAL(progress(int)), this, SLOT(eventProgress(int)));
    */
}

StageManager::ui::MainWindow::~MainWindow() {
    delete ui;
    delete tray;
}

void StageManager::ui::MainWindow::handleButton() {
    ui->pushButton->setText("Please wait...");
    ui->pushButton->setEnabled(false);
}

void StageManager::ui::MainWindow::eventDone(bool result) {
    if (result)
        ui->pushButton->setText("DONE OK");
    else
        ui->pushButton->setText("ERROR UNCOMPRESSING");

    ui->pushButton->setEnabled(true);
}
