
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

};

#endif // MAINWINDOW_H

