#include "Action.h"

StageManager::system::Action::Action() {
}

StageManager::system::Action::~Action() {
}

void StageManager::system::Action::handleOK() {
    emit done(true);
}

void StageManager::system::Action::handleError() {
    emit done(false);
}
