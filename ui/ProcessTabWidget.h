#pragma once

#include <QTabWidget>
#include <QMap>

namespace StageManager::ui {
    class ProcessWidget;
    class ProcessTabWidget: public QTabWidget
    {
        Q_OBJECT
        public:
            ProcessTabWidget(QWidget* &widget);
            ~ProcessTabWidget() override;
            void addStageTab(const QString& stage = "");
            void removeStageTab(const int& index, bool force = true);
            void removeAllStageTabs(bool force);

        private slots:
            void handleProcessTerminate(const int& tab_order);

        private:
            QMap<int, ProcessWidget*> m_tab_contents;

            void removeTabFromMap(const int& tab_index, bool force);
    };
}
