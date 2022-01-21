
#include "mainwindow.h"

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QListWidget>
#include <QScrollArea>
#include <QTextEdit>
#include <QuickTemplateObject.h>
#include <QtPrivateDeclar.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{

    QuickTemplateObject *manager = new QuickTemplateObject;

	QHBoxLayout *layout = new QHBoxLayout(this);
	
    QVBoxLayout *Leftlayout = new QVBoxLayout();
// left

// 1.1
    QGroupBox *leftBox = new QGroupBox("软件源");
    QVBoxLayout *leftBoxLayout = new QVBoxLayout(leftBox);
    Leftlayout->addWidget(leftBox);
    // leftBoxLayout->addStretch();

// 1.1.1
    QGroupBox *inputAptSourceBox = new QGroupBox("软件源列表");
    QVBoxLayout *inputAptSourceBoxLayout = new QVBoxLayout(inputAptSourceBox);
    leftBoxLayout->addWidget(inputAptSourceBox);

    QTextEdit *remoteUrl = new QTextEdit();
    remoteUrl->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
    remoteUrl->setPlaceholderText(QString("例如: \n"
        "https://community-packages.deepin.com/deepin/ apricot\n"
        "deb https://community-packages.deepin.com/deepin/ apricot\n"
        "..."));
    inputAptSourceBoxLayout->addWidget(remoteUrl);
    QLabel *sourceLabel = new QLabel("指定源:");
    QComboBox *sourceCombo = new QComboBox;

    QHBoxLayout *sourceHLayout = new QHBoxLayout;
    sourceHLayout->addWidget(sourceLabel);
    sourceHLayout->addWidget(sourceCombo, 1);

    inputAptSourceBoxLayout->addLayout(sourceHLayout);

    connect(remoteUrl, &QTextEdit::textChanged, this,[=](){
        sourceCombo->clear();
        for (auto str : remoteUrl->toPlainText().split("\n"))
        {
            if (str.startsWith("deb") || str.startsWith("http")) {
                bool isDeb = str.startsWith("deb");
                QStringList words = str.split(" ");
                if ((isDeb && words.length() >= 3) || (!isDeb && words.length() >= 2)) {
                    QString url = isDeb?words[1]:words[0];
                    QString _codename = isDeb?words[2]:words[1];
                    if (url.at(url.length()-1) == "/") {
                        url.remove(url.length()-1, 1);
                    }
                    QStringList _tmp = url.split("/");
                    QString _dist = _tmp.last();
                    _tmp.removeLast();
                    QString _url = _tmp.join("/");

                    QString _text = QString("%1 - %2").arg(_dist).arg(_codename);
                    QString _data = QString("%1/%2/dists/%3/Release").arg(_url).arg(_dist).arg(_codename);
                    sourceCombo->addItem(_text,_data);
                }
            }
        }
    });

// 1.2
    // leftBoxLayout.
    QLabel *urlLabel = new QLabel("源地址:");
    QLineEdit *url = new QLineEdit;
    QLabel *originLabel = new QLabel("源名称:");
    QLineEdit *origin = new QLineEdit;
    QLabel *labelLabel = new QLabel("源标识:");
    QLineEdit *label = new QLineEdit;
    QLabel *codenameLabel = new QLabel("源代号:");
    QLineEdit *codename = new QLineEdit;
    QLabel *suiteLabel = new QLabel("源套件:");
    QLineEdit *suite = new QLineEdit;
    QLabel *versionLabel = new QLabel("源版本:");
    QLineEdit *version = new QLineEdit;
    QLabel *dateLabel = new QLabel("源日期:");
    QLineEdit *date = new QLineEdit;
    QLabel *architecturesLabel = new QLabel("源架构:");
    QLineEdit *architectures = new QLineEdit;
    QLabel *componentsLabel = new QLabel("源组成:");
    QLineEdit *components = new QLineEdit;
    QLabel *descriptionLabel = new QLabel("源简介:");
    QLineEdit *description = new QLineEdit;

    origin->setText("Linux Deepin");
    label->setText("Deepin");
    codename->setText("apricot");
    suite->setText("4.0.2-desktop");
    version->setText("2019");
    date->setText("Tue, 18 Jan 2022 09:36:49 UTC");
    architectures->setText("i386 amd64 arm64 mips64el");
    components->setText("main contrib non-free");
    description->setText("Deepin debian packages");

    QGroupBox *remoteInfoBox = new QGroupBox("软件源信息");
    QGridLayout *remoteInfoBoxLayout = new QGridLayout(remoteInfoBox);
    // remoteInfoLayout->addWidget(QWidget *, int row, int column)
    remoteInfoBoxLayout->addWidget(urlLabel, 0, 0);
    remoteInfoBoxLayout->addWidget(url, 0, 1);
    remoteInfoBoxLayout->addWidget(originLabel, 1, 0);
    remoteInfoBoxLayout->addWidget(origin, 1, 1);
    remoteInfoBoxLayout->addWidget(labelLabel, 2, 0);
    remoteInfoBoxLayout->addWidget(label, 2, 1);
    remoteInfoBoxLayout->addWidget(codenameLabel, 3, 0);
    remoteInfoBoxLayout->addWidget(codename, 3, 1);
    remoteInfoBoxLayout->addWidget(suiteLabel, 4, 0);
    remoteInfoBoxLayout->addWidget(suite, 4, 1);
    remoteInfoBoxLayout->addWidget(versionLabel, 5, 0);
    remoteInfoBoxLayout->addWidget(version, 5, 1);
    remoteInfoBoxLayout->addWidget(dateLabel, 6, 0);
    remoteInfoBoxLayout->addWidget(date, 6, 1);
    remoteInfoBoxLayout->addWidget(architecturesLabel, 7, 0);
    remoteInfoBoxLayout->addWidget(architectures, 7, 1);
    remoteInfoBoxLayout->addWidget(componentsLabel, 8, 0);
    remoteInfoBoxLayout->addWidget(components, 8, 1);
    remoteInfoBoxLayout->addWidget(descriptionLabel, 9, 0);
    remoteInfoBoxLayout->addWidget(description, 9, 1);

    leftBoxLayout->addWidget(remoteInfoBox);
    leftBoxLayout->addStretch();

    QVBoxLayout *Rightlayout = new QVBoxLayout();
// right


// 2.1
    QGroupBox *rightBox = new QGroupBox("软件包");
    QVBoxLayout *rightBoxLayout = new QVBoxLayout(rightBox);
    Rightlayout->addWidget(rightBox);

// 2.1.1
    QGroupBox *remotePackageBox = new QGroupBox("软件源包信息");
    QGridLayout *remotePackageBoxLayout = new QGridLayout(remotePackageBox);

    QLabel *packageSwitchLabel = new QLabel("软件包分类:");
    QComboBox *packageArchCombo = new QComboBox();
    
    remotePackageBoxLayout->addWidget(packageSwitchLabel, 0, 0);
    remotePackageBoxLayout->addWidget(packageArchCombo, 0, 1, 1, 3);
    // remotePackageBoxLayout->addWidget(packageSwitchLabel, 0, 0);

// 2.1.2
    QLabel *packageSearchLabel = new QLabel("软件包名称:");
    QLineEdit *packageSearch = new QLineEdit();
    remotePackageBoxLayout->addWidget(packageSearchLabel, 1, 0);
    remotePackageBoxLayout->addWidget(packageSearch, 1, 1, 1, 3);

// 2.1.3
    QListWidget *packageResultList = new QListWidget();


// 2.2
    rightBoxLayout->addWidget(remotePackageBox);
    rightBoxLayout->addWidget(packageResultList);
    rightBoxLayout->addStretch();

// 2 end
    layout->addLayout(Leftlayout,1);
    layout->addLayout(Rightlayout,1);

    resize(1200, 800);



    connect(sourceCombo, &QComboBox::currentTextChanged, [=](const QString &text){
        url->setText(sourceCombo->currentData().toString());
        manager->requestRelease(url->text());
    });
    connect(manager, &QuickTemplateObject::loaded, [=](QtPrivateDeclar *declar){
        origin->setText(declar->getOrigin());
        label->setText(declar->getLabel());
        codename->setText(declar->getCodename());
        suite->setText(declar->getSuite());
        version->setText(declar->getVersion());
        date->setText(declar->getDate());
        architectures->setText(declar->getArchitectures());
        components->setText(declar->getComponents());
        description->setText(declar->getDescription());

    // remotePackage
        packageArchCombo->clear();
        packageArchCombo->addItem("未指定", -1);
        packageArchCombo->addItems(declar->getArchitectures().split(" "));
    });

}
MainWindow::~MainWindow()
{
	
}
