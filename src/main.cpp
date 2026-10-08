#include <QApplication>
#include "mainwindow.h"
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

extern "C" int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                                 LPSTR lpCmdLine, int nShowCmd)
{
    return main(__argc, __argv);
}