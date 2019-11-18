#include "ProcessWidget.h"
#include "ui_ProcessWidget.h"

#include <QKeyEvent>
#include <QMessageBox>

StageManager::ui::ProcessWidget::ProcessWidget(QWidget *parent, const QString& program, const QStringList& parameters): QWidget(parent), m_ui(new Ui::ProcessWidget), m_avoid_confirmation(false) {
    m_ui->setupUi(this);
    m_process = new QProcess;
    m_ui->commandLine->installEventFilter(this);
    connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(handleProcessStderr()));
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(handleProcessStdout()));
    connect(m_process, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(handleFinished(int, QProcess::ExitStatus)));
    connect(m_ui->finishButton, SIGNAL(clicked()), this, SLOT(handleFinishButton()));
    m_process->start(program, parameters, QIODevice::ReadWrite);
    m_process->setReadChannelMode(QProcess::SeparateChannels);
    m_process->waitForStarted();
}
#include <iostream>
StageManager::ui::ProcessWidget::~ProcessWidget() {
    m_process->close();
    m_process->kill();
    m_process->waitForFinished();
    delete m_process;
    delete m_ui;
    std::cout << "Deleted process " << m_tab << std::endl;
}

void StageManager::ui::ProcessWidget::setTabIndex(const int &tab_order) {
    m_tab = tab_order;
}

int StageManager::ui::ProcessWidget::getTabIndex() const {
    return m_tab;
}

void StageManager::ui::ProcessWidget::handleProcessStderr() {
    m_ui->processOutput->append(m_process->readAllStandardError());
}

void StageManager::ui::ProcessWidget::handleProcessStdout() {
    m_ui->processOutput->append(m_process->readAllStandardOutput());
}

void StageManager::ui::ProcessWidget::handleReadyRead() {
    m_process->setReadChannel(QProcess::StandardOutput);
}

bool StageManager::ui::ProcessWidget::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QTextEdit *text_edit = static_cast<QTextEdit*>(object);
        QKeyEvent *key_event = static_cast<QKeyEvent*>(event);

        QString current_text = text_edit->toPlainText();
        switch(key_event->key()) {
            case Qt::Key_Tab:
                text_edit->setFocus();
                return true;
            case Qt::Key_Enter:
            case Qt::Key_Return:
                m_process->write(QString(current_text + "\n").toUtf8());
                text_edit->setText("");
                return true;
            default:
                return false;
        }
    }
    return false;
}

void StageManager::ui::ProcessWidget::handleFinished(const int&, const QProcess::ExitStatus&) {
    if (!m_avoid_confirmation) finishAction(false);
}

void StageManager::ui::ProcessWidget::handleFinishButton() {
    finishAction(true);
}

void StageManager::ui::ProcessWidget::finishAction(bool cancelable) {
    m_ui->finishButton->setEnabled(false);
    QMessageBox::StandardButtons buttons;
    if (cancelable) {
        buttons = QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    }
    else {
        buttons = QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No);
    }
    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Finish?"), tr("Do you want to save changes?"), buttons);
    switch(reply) {
        case QMessageBox::Yes:
        case QMessageBox::No:
            disconnect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(handleFinished(int, QProcess::ExitStatus)));
            emit finished(m_tab);
            break;
        default:
            m_ui->finishButton->setEnabled(true);
            break;
    }
}

void StageManager::ui::ProcessWidget::setAvoidFinishConfirmation(bool force) {
    m_avoid_confirmation = force;
}
