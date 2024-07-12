#include "aptanalyzerwindow.h"
#include "screenutil.h"
#include "ui_aptanalyzerwindow.h"

#include <apt/release.h>

#include <qrcutil.h>

#include <defer.h>
#include <zlib.h>

AptAnalyzerWindow::AptAnalyzerWindow(QWidget *parent) :
    FramelessWidget(parent),
    ui(new Ui::AptAnalyzerWindow)
{
    ui->setupUi(this);

    setupUi(ui->frame);
    setTitleLayout(ui->title_layout);

    QPixmap pixmap("://diversity-2019.png");
    pixmap.setDevicePixelRatio(ScreenUtil::ratio(this));
    setWindowIcon(pixmap);
    setTitleIcon(pixmap.scaled(QSize(40, 40)*ScreenUtil::ratio(this), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->aptDistroList->clear();
    ui->aptDistroList->addItems(QR("://distributions.txt").split('\n', Qt::SkipEmptyParts));


    ui->apt_packages_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

AptAnalyzerWindow::~AptAnalyzerWindow()
{
    delete ui;
}

void AptAnalyzerWindow::on_aptDistroList_itemClicked(QListWidgetItem *item)
{
    auto dc_splits = item->text().split("/");
    auto distribution = dc_splits.at(0);
    auto codename = dc_splits.at(1);

// 1. 加载源信息
    // https://mirrors.bfsu.edu.cn/debian/dists/bookworm/Release
    auto url = QString("https://mirrors.bfsu.edu.cn/%1/dists/%2/Release").arg(distribution).arg(codename);
    AptRelease r = AptRelease::fromUrl(url);

    foreach (auto var, r.properties()) {
        auto lab_var = ui->tabWidget->findChild<QLabel*>("r_" + var.key());
        if (lab_var) {
            lab_var->setText(var.value());
            lab_var->setTextInteractionFlags(Qt::TextSelectableByMouse);
        }
    }

// 1.1 显示分类
    ui->lab_Components->setText(r.Components().value());
    ui->lab_Architectures->setText(r.Architectures().value());

    ui->comb_Components->disconnect();
    ui->comb_Components->clear();
    ui->comb_Components->addItems(r.Components().value().split(QRegExp("\\s+"), Qt::SkipEmptyParts));
    connect(ui->comb_Components, SIGNAL(currentIndexChanged(int)), this, SLOT(apt_repo_reload_packages()));

    ui->comb_Architectures->disconnect();
    ui->comb_Architectures->clear();
    ui->comb_Architectures->addItems(r.Architectures().value().split(QRegExp("\\s+"), Qt::SkipEmptyParts));
    connect(ui->comb_Architectures, SIGNAL(currentIndexChanged(int)), this, SLOT(apt_repo_reload_packages()));

// 2.加载架构与组件对应数据
// https://mirrors.bfsu.edu.cn/debian/dists/bookworm/main/binary-amd64/Release
    apt_repo_load_packages(distribution, codename);
}

void AptAnalyzerWindow::on_e_search_returnPressed()
{
    ui->stacked_apt_packages->setCurrentWidget(ui->stack_loading);
    Defer defer([this](){
        ui->stacked_apt_packages->setCurrentWidget(ui->stack_table);
    });

    QString input = ui->e_search->text();
    int rows = ui->apt_packages_table->rowCount();
    if (input.isEmpty()) {
        for (int i = 0; i < rows; ++i) {
            ui->apt_packages_table->setRowHidden(i, false);
        }
    } else {
        auto items = ui->apt_packages_table->findItems(input, Qt::MatchContains);

        for (int i = 0; i < rows; ++i) {
            ui->apt_packages_table->setRowHidden(i, true);
        }

        if (items.isEmpty() == false) {
            for (int i = 0; i < items.count(); ++i) {
                ui->apt_packages_table->setRowHidden(items.at(i)->row(), false);
            }
        }
    }
}

void AptAnalyzerWindow::on_btn_search_clicked()
{
    on_e_search_returnPressed();
}

void AptAnalyzerWindow::apt_repo_load_packages(QString distribution, QString codename)
{
    QString url = QString("https://mirrors.bfsu.edu.cn/%1/dists/%2/%3/binary-%4/Release").arg(distribution).arg(codename)
              .arg(ui->comb_Components->currentText())
              .arg(ui->comb_Architectures->currentText());
    Request req_release(url);
    Response resp_release = HttpClient::instance().get(req_release);

    ui->apt_packages_browser->setText(resp_release.content());

    //    https://mirrors.bfsu.edu.cn/debian/dists/bookworm/main/binary-amd64/Packages.xz
    //    https://mirrors.bfsu.edu.cn/debian/dists/bullseye/main/binary-all/Packages.gz
    url = QString("https://mirrors.bfsu.edu.cn/%1/dists/%2/%3/binary-%4/Packages.gz").arg(distribution).arg(codename)
              .arg(ui->comb_Components->currentText())
              .arg(ui->comb_Architectures->currentText());

    ui->apt_loading_progress->setValue(0);
    Response head_package_gz = HttpClient::instance().head(Request(url));
    if (head_package_gz .status() == 200) {
        ui->apt_loading_progress->setValue(10);
        Request req_package(url);
        req_package.setHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36 UOS Community");
        Response get_package = HttpClient::instance().get(req_package);
        auto src = get_package.content();

        ui->apt_loading_progress->setValue(50);

        QByteArray uncompress;
        z_stream zlib = {0};
        zlib.avail_in = head_package_gz.headContentLength();
        zlib.next_in = (Bytef*)src.data();

        int e = inflateInit2(&zlib, MAX_WBITS + 16);
        if (e == Z_OK) {
            while (true) {
                char buffer[4096] = {0};
                zlib.avail_out = 4096;
                zlib.next_out = (Bytef*)buffer;

                int code = inflate(&zlib, Z_FINISH);
                uncompress.append(buffer, 4096 - zlib.avail_out);

                if (code == Z_STREAM_END) {
                    break;
                }
            }
            inflateEnd(&zlib);
        }

        ui->apt_loading_progress->setValue(80);

        QStringList packages;
        auto splits = QString(uncompress).split("\n\n", Qt::SkipEmptyParts);
        QList<AptPackage> apt_packages;
        foreach (auto var, splits) {
            AptPackage apt_package(var);
            if (apt_package.properties().count() > 3) {
                apt_packages << apt_package;
            }
        }
        ui->apt_packages_browser->setText(packages.join("\n"));
        ui->apt_packages_browser->setText(splits.at(0));

        ui->apt_packages_table->clearContents();
        ui->apt_packages_table->setRowCount(apt_packages.count());
        ui->stacked_apt_packages->setCurrentWidget(ui->stack_loading);
        Defer defer([this](){
            ui->stacked_apt_packages->setCurrentWidget(ui->stack_table);
        });

        int count = apt_packages.count();
        for (int i = 0; i < apt_packages.count(); ++i) {
            auto var = apt_packages[i];
            QTableWidgetItem *package = new QTableWidgetItem;
            package->setText(var.Package().value());
            QTableWidgetItem *version = new QTableWidgetItem;
            version->setText(var.Version().value());
            QTableWidgetItem *filename = new QTableWidgetItem;
            filename->setText(var.Filename().value());

            ui->apt_packages_table->setItem(i, 0, package);
            ui->apt_packages_table->setItem(i, 1, version);
            ui->apt_packages_table->setItem(i, 2, filename);
        }

        ui->apt_loading_progress->setValue(100);
    }
}

void AptAnalyzerWindow::apt_repo_reload_packages()
{
    auto dc_splits = ui->aptDistroList->currentItem()->text().split("/");
    auto distribution = dc_splits.at(0);
    auto codename = dc_splits.at(1);
    apt_repo_load_packages(distribution, codename);
}

