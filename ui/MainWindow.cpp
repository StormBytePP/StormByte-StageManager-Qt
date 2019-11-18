#include "MainWindow.h"
#include "SystemTray.h"
#include "SettingsWindow.h"
#include "./ui_MainWindow.h"
#include "system/Settings.h"
#include <QCloseEvent>
#include <QMessageBox>

StageManager::ui::MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), m_ui(new Ui::StageManager) {
    m_ui->setupUi(this);
    m_tray = new SystemTray();
    m_settings = new SettingsWindow();

    connect(m_ui->configurationButton, SIGNAL(clicked()), this, SLOT(configurationButtonClicked()));
    connect(m_ui->addStageTabButton, SIGNAL(clicked()), this, SLOT(addStageTabButtonClicked()));

    /*
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(handleButton()));
    connect(m_uncompress, SIGNAL(done(bool)), this, SLOT(eventDone(bool)));
    connect(m_uncompress, SIGNAL(progress(int)), this, SLOT(eventProgress(int)));
    */
}

StageManager::ui::MainWindow::~MainWindow() {
    delete m_ui;
    delete m_tray;
    delete m_settings;
}

void StageManager::ui::MainWindow::show() {
    if (!m_settings->getSettings()->valid()) m_settings->show();
    QMainWindow::show();
}

void StageManager::ui::MainWindow::configurationButtonClicked() {
    m_settings->show();
}

void StageManager::ui::MainWindow::addStageTabButtonClicked() {
    m_ui->stageTabWidget->addStageTab();
}

void StageManager::ui::MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton q = QMessageBox::question(this, tr("Really quit?"), tr("Do you want to finish the program?"));
    if (q == QMessageBox::Yes) event->accept(); else event->ignore();
}
