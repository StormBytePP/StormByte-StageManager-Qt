#include "MainWindow.h"
#include "SystemTray.h"
#include "SettingsWindow.h"
#include "./ui_MainWindow.h"
#include "system/Settings.h"

StageManager::ui::MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), m_ui(new Ui::StageManager) {
    m_ui->setupUi(this);
    m_tray = new SystemTray();
    m_settings = new SettingsWindow();

    connect(m_ui->configurationButton, SIGNAL(clicked()), this, SLOT(configurationButtonClicked()));
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
