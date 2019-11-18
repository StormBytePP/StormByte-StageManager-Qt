#include "ProcessTabWidget.h"
#include "ProcessWidget.h"
#include <iostream>

StageManager::ui::ProcessTabWidget::ProcessTabWidget(QWidget* &widget):QTabWidget(widget) {
}

StageManager::ui::ProcessTabWidget::~ProcessTabWidget() {
    removeAllStageTabs(true);
}

void StageManager::ui::ProcessTabWidget::handleProcessTerminate(const int& tab_order) {
    std::cout << "Received terminate " << tab_order << std::endl;
    removeStageTab(tab_order);
}

void StageManager::ui::ProcessTabWidget::addStageTab(const QString&) {
    ProcessWidget *widget = new ProcessWidget(this, "script", QStringList() << "-qfc" << "/bin/bash -il");
    int tab = addTab(widget, "test");
    m_tab_contents[tab]=widget;
    m_tab_contents[tab]->setTabIndex(tab);
    connect(m_tab_contents[tab], SIGNAL(finished(int)), this, SLOT(handleProcessTerminate(const int&)));
    this->setTabText(tab, this->tabText(tab) + " " + QString::number(tab));
}

void StageManager::ui::ProcessTabWidget::removeStageTab(const int &index, bool force) {
    /* Important to call QTabWidget::removeTab before removing item from map */
    removeTab(index);
    removeTabFromMap(index, force);
}

void StageManager::ui::ProcessTabWidget::removeAllStageTabs(bool force) {
    /* Here we can't use iterator because remove from map updates indexes that make it not possible */
    auto allKeys = m_tab_contents.keys();
    for(auto it = allKeys.begin(); it != allKeys.end(); it++) {
        m_tab_contents[*it]->setAvoidFinishConfirmation(force);
        delete m_tab_contents[*it];
    }
    m_tab_contents.clear();
}

void StageManager::ui::ProcessTabWidget::removeTabFromMap(const int &tab_index, bool force) {
    QMap<int, ProcessWidget*> new_tab_contents;
    auto allKeys = m_tab_contents.keys();
    for (auto it = allKeys.begin(); it != allKeys.end(); it++) {
        if (*it == tab_index) {
            m_tab_contents[tab_index]->setAvoidFinishConfirmation(force);
            delete m_tab_contents[tab_index];
        }
        else if (*it < tab_index) new_tab_contents[*it]=m_tab_contents[*it];
        else {
            int newPos = (*it) - 1;
            ProcessWidget *widget = m_tab_contents[*it];
            widget->setTabIndex(newPos);
            new_tab_contents[newPos] = widget;
        }
    }
    m_tab_contents = new_tab_contents;
}
