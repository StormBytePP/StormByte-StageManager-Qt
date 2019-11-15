#include "ui/Application.h"

int main(int argc, char *argv[])
{
    StageManager::ui::Application a(argc, argv);
    return a.exec();
}
