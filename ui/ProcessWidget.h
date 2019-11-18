#pragma once

#include <QWidget>
#include <QProcess>

namespace Ui { class ProcessWidget; }

namespace StageManager::ui {
    class ProcessWidget : public QWidget
    {
        Q_OBJECT
        public:
            ProcessWidget(QWidget *parent, const QString& program, const QStringList& parameters = QStringList());
            ~ProcessWidget() override;
            void setTabIndex(const int& tab_order);
            int getTabIndex() const;
            void setAvoidFinishConfirmation(bool force_finish);

        signals:
            void finished(int);

        private slots:
            void handleProcessStderr();
            void handleProcessStdout();
            void handleReadyRead();
            void handleFinished(const int &exitCode, const QProcess::ExitStatus &exitStatus);
            void handleFinishButton();

        private:
            Ui::ProcessWidget *m_ui;
            QProcess *m_process;
            int m_tab;
            bool m_avoid_confirmation;

            bool eventFilter(QObject *object, QEvent *event) override;
            void finishAction(bool cancelable = true);
    };
}

