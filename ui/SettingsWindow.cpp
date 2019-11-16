#include "SettingsWindow.h"
#include "./ui_SettingsWindow.h"
#include "system/Settings.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>

StageManager::ui::SettingsWindow::SettingsWindow(QWidget *parent): QDialog(parent), m_ui(new Ui::SettingsWindow) {
    m_ui->setupUi(this);
    setFixedSize(width(), height());
    m_settings = new StageManager::system::Settings();
    m_settings_new = nullptr;

    connect(m_ui->saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));
    connect(m_ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(m_ui->stageFolderButton, SIGNAL(clicked()), this, SLOT(stageButtonClicked()));
    connect(m_ui->stageFolder, SIGNAL(textChanged(const QString&)), SLOT(stageDestinationChanged(const QString&)));
    connect(m_ui->stageCompression, SIGNAL(valueChanged(const int&)), this, SLOT(stageCompressionChanged(const int&)));
    connect(m_ui->mountType, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(mountTypeChanged(const QString&)));
    connect(m_ui->zramCompression, SIGNAL(valueChanged(const int&)), this, SLOT(zramCompressionChanged(const int&)));
    connect(m_ui->tmpfsSize, SIGNAL(valueChanged(const int&)), this, SLOT(tmpfsSizeChanged(const int&)));
    connect(m_ui->folderDestination, SIGNAL(textChanged(const QString&)), this, SLOT(folderDestinationChanged(const QString&)));
    connect(m_ui->folderButton, SIGNAL(clicked()), this, SLOT(folderButtonclicked()));
}

StageManager::ui::SettingsWindow::~SettingsWindow() {
    delete m_ui;
    delete m_settings;
}

const StageManager::system::Settings *StageManager::ui::SettingsWindow::getSettings() const {
    return m_settings;
}

void StageManager::ui::SettingsWindow::closeEvent(QCloseEvent *event) {
    if (m_settings->valid()) {
        delete m_settings_new;
        event->accept();
    }
    else {
        showConfigStatusMessage(false);
        event->ignore();
    }
}

void StageManager::ui::SettingsWindow::reject() {
    if (m_settings->valid()) {
        delete m_settings_new;
        m_settings_new = nullptr;
        QDialog::reject();
    }
}

void StageManager::ui::SettingsWindow::accept() {
    bool operation = m_settings_new->save();
    showConfigStatusMessage(operation);
    if (operation) {
        delete m_settings;
        m_settings = m_settings_new;
        m_settings_new = nullptr;
        QDialog::accept();
    }
}

void StageManager::ui::SettingsWindow::show() {
    copySettings();
    updateUI();
    QDialog::show();
}

void StageManager::ui::SettingsWindow::stageDestinationChanged(const QString& destination) {
    m_settings_new->setStageDestination(destination);
}

void StageManager::ui::SettingsWindow::stageCompressionChanged(const int& compression) {
    m_settings_new->setStageCompression(compression);
}

void StageManager::ui::SettingsWindow::mountTypeChanged(const QString& mountType) {
    m_ui->zramGroup->setEnabled(false);
    m_ui->tmpfsGroup->setEnabled(false);
    m_ui->tmpfsGroup->setEnabled(false);
    if (mountType == "zram") m_ui->zramGroup->setEnabled(true);
    else if (mountType == "tmpfs") m_ui->tmpfsGroup->setEnabled(true);
    else if (mountType == "folder") m_ui->folderGroup->setEnabled(true);

    m_settings_new->setSystemType(mountType);
}

void StageManager::ui::SettingsWindow::zramCompressionChanged(const int& compression) {
    m_settings_new->setZramCompression(compression);
}

void StageManager::ui::SettingsWindow::tmpfsSizeChanged(const int& size) {
    m_settings_new->setTmpfsSize(size);
}

void StageManager::ui::SettingsWindow::folderDestinationChanged(const QString& destination) {
    m_settings_new->setFolderDestination(destination);
}

void StageManager::ui::SettingsWindow::saveButtonClicked() {
    accept();
}

void StageManager::ui::SettingsWindow::cancelButtonClicked() {
    reject();
}

void StageManager::ui::SettingsWindow::stageButtonClicked() {
    QString new_folder = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/", QFileDialog::ShowDirsOnly);
    m_settings_new->setStageDestination(new_folder);
    m_ui->stageFolder->setText(new_folder);
}

void StageManager::ui::SettingsWindow::folderButtonclicked() {
    QString new_folder = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/", QFileDialog::ShowDirsOnly);
    m_settings_new->setFolderDestination(new_folder);
    m_ui->folderDestination->setText(new_folder);
}

void StageManager::ui::SettingsWindow::showConfigStatusMessage(bool status) {
    if (status)
        QMessageBox::information(this, tr("Sucess"), tr("Configuration saved sucessfully"));
    else
        QMessageBox::critical(this, tr("Error"), tr("There are invalid values in configuration"));
}

void StageManager::ui::SettingsWindow::copySettings() {
    m_settings_new = new StageManager::system::Settings();
    m_settings_new->setStageCompression(m_settings->getStageCompression());
    m_settings_new->setStageDestination(m_settings->getStageDestination());
    m_settings_new->setSystemType(m_settings->getSystemType());
    m_settings_new->setTmpfsSize(m_settings->getTmpfsSize());
    m_settings_new->setZramCompression(m_settings->getZramCompression());
    m_settings_new->setFolderDestination(m_settings->getFolderDestination());
}

void StageManager::ui::SettingsWindow::updateUI() {
    m_ui->stageFolder->setText(m_settings->getStageDestination());
    m_ui->mountType->setCurrentText(m_settings->getSystemType());
    m_ui->zramCompression->setValue(m_settings->getZramCompression());
    m_ui->tmpfsSize->setValue(m_settings->getTmpfsSize());
    m_ui->folderDestination->setText(m_settings->getFolderDestination());

    if (m_ui->mountType->currentText() == "zram") m_ui->zramGroup->setEnabled(true);
    else if (m_ui->mountType->currentText() == "tmpfs") m_ui->tmpfsGroup->setEnabled(true);
    else if (m_ui->mountType->currentText() == "folder") m_ui->folderGroup->setEnabled(true);
}
