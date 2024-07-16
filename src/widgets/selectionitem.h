#ifndef SELECTIONITEM_H
#define SELECTIONITEM_H

#include <QWidget>

namespace Ui
{
    class SelectionItem;
}

class SelectionItem : public QWidget
{
    Q_OBJECT

public:
    explicit SelectionItem(QWidget *parent = nullptr);
    ~SelectionItem();

    void setIcon(const QString &icon);
    void setText(const QString &text);
    QString text();

private:
    Ui::SelectionItem *ui;
};

#endif // SELECTIONITEM_H
