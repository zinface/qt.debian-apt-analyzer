#ifndef APTANALYZERWINDOW_H
#define APTANALYZERWINDOW_H

#include <QWidget>
#include <framelesswidget.h>


class QListWidgetItem;
namespace Ui
{
    class AptAnalyzerWindow;
}

class AptAnalyzerWindow : public FramelessWidget
{
    Q_OBJECT

public:
    explicit AptAnalyzerWindow(QWidget *parent = nullptr);
    ~AptAnalyzerWindow();

private slots:
    void on_aptDistroList_itemClicked(QListWidgetItem *item);

    void on_e_search_returnPressed();
    void on_btn_search_clicked();


    void apt_repo_load_packages(QString distribution, QString codename);
    void apt_repo_reload_packages();

private:
    Ui::AptAnalyzerWindow *ui;

    QString m_distribution;
    QString m_codename;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // APTANALYZERWINDOW_H
