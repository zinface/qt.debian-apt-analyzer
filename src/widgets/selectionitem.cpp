#include "selectionitem.h"
#include "ui_selectionitem.h"

#include <QColor>

SelectionItem::SelectionItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectionItem)
{
    ui->setupUi(this);
}

SelectionItem::~SelectionItem()
{
    delete ui;
}

void SelectionItem::setIcon(const QString &icon)
{
    QPixmap pixmap = QPixmap(icon).scaledToHeight(ui->icon->height(), Qt::SmoothTransformation);
    ui->icon->resize(pixmap.size());
    ui->icon->setPixmap(pixmap);
}

void SelectionItem::setText(const QString &text)
{
    ui->text->setText(text);
}

QString SelectionItem::text()
{
    return ui->text->text();
}
