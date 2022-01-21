
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QMainWindow>

void moveCenter(MainWindow &wm) {
    QDesktopWidget *desktop = QApplication::desktop();
    wm.move((desktop->width() - wm.width()) /2,(desktop->height() - wm.height()) /2);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("apt软件源分析器");
    MainWindow wm;
    wm.show();
   
    moveCenter(wm);

    return a.exec();
}
