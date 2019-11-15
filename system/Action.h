#pragma once

#include <QObject>

namespace StageManager::system {
    class Action: public QObject {
        protected:
            Q_OBJECT

        signals:
            void done(bool);
            void progress(int);

        protected slots:
            void handleOK();
            void handleError();

        public:
            Action();
            virtual ~Action();
            virtual void execute() = 0;
    };
}
