#include "aptanalyzerwindow.h"
#include "selectionitem.h"
#include "ui_aptanalyzerwindow.h"

#include <apt/release.h>

#include <defer.h>
#include <qrcutil.h>
#include <screenutil.h>
#include <zlib.h>

#include <QKeyEvent>
#include <QClipboard>
#include <qssdebugkeypresseater.h>

#define USER_D 990
#define USER_C 991

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

    new QssDebugKeyPressEater(this);

    QList<int> sizes;
    sizes << 1000 << 100;
    ui->splitter_2->setSizes(sizes);

    ui->aptDistroList->clear();
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
    foreach (auto var, QR("://distributions.txt").split('\n', QString::SkipEmptyParts))
#else
    foreach (auto var, QR("://distributions.txt").split('\n', Qt::SkipEmptyParts))
#endif
    {
        // 跳过 # 开头的部分
        if (var.startsWith("#")) continue;

        // 处理 “A/B   :C” 中间出现的任意空白字符部分
        var = var.replace(QRegExp("\\s+"), "");

        QListWidgetItem *item = new QListWidgetItem;
        // 检查是有包含需要替换项的部分
        if (var.contains(":"))
        {
            /**
            # 显示规则：<显示项>
                      debian/bookworm
                      用于 debian/dists/bookworm
                                ^     ^
            # 显示规则：<显示项>:<替换部分>
                      lingmo/polaris:https://packages-lingmo.simplelinux.cn.eu.org/polaris
                      用于 https://packages-lingmo.simplelinux.cn.eu.org/polaris/dists/polaris
                                                                               ^     ^
            # 发行版本路径为：debian 版本代码为 sid
            # debian 规则：https://mirrors.bfsu.edu.cn/debian/dists/sid
                                                            ^     ^

            # 发行版本路径为：deepin/beige 版本代码为 beige
            # deepin 规则：https://mirrors.bfsu.edu.cn/deepin/beige/dists/beige/
                                                                  ^     ^
            */
            auto splits = var.split(":");
            item->setText(splits.at(0));

            item->setData(USER_D, splits.at(1));
            auto vsplits = splits.at(0).split("/");
            if (vsplits.count() == 2)
            {
                item->setData(USER_C, vsplits.at(1));
            }
            else
            {
                if (vsplits.count() == 1)
                {
                    item->setData(USER_C, ""); // 不需要 codename
                }
                else
                {
                    item->setData(USER_C, vsplits.mid(1).join("/"));
                }
            }
            if (var.contains("http"))
            {
                item->setData(USER_D, splits.mid(1).join(":"));
            }
        }
        else
        {
            item->setText(var);
            auto splits = var.split("/");
            item->setData(USER_D, splits.at(0));
            item->setData(USER_C, splits.at(1));
        }

        ui->aptDistroList->addItem(item);
        if (item->text().startsWith("lingmo"))
        {
            SelectionItem *item_widget = new SelectionItem;
            item_widget->setIcon(":/lingmo.png");
            item_widget->setText(item->text());
            item->setText("");
            item->setSizeHint(item_widget->sizeHint());
            ui->aptDistroList->setItemWidget(item, item_widget);
        }
        else if (item->text().startsWith("debian"))
        {
            SelectionItem *item_widget = new SelectionItem;
            item_widget->setIcon(":/debian.png");
            item_widget->setText(item->text());
            item->setText("");
            item->setSizeHint(item_widget->sizeHint());
            ui->aptDistroList->setItemWidget(item, item_widget);
        }
        else if (item->text().startsWith("deepin"))
        {
            SelectionItem *item_widget = new SelectionItem;
            item_widget->setIcon(":/deepin.png");
            item_widget->setText(item->text());
            item->setText("");
            item->setSizeHint(item_widget->sizeHint());
            ui->aptDistroList->setItemWidget(item, item_widget);
        }
        else if (item->text().startsWith("ubuntu") && !item->text().startsWith("ubuntukylin"))
        {
            SelectionItem *item_widget = new SelectionItem;
            item_widget->setIcon(":/ubuntu.png");
            item_widget->setText(item->text());
            item->setText("");
            item->setSizeHint(item_widget->sizeHint());
            ui->aptDistroList->setItemWidget(item, item_widget);
        }
        else if (item->text().startsWith("ubuntukylin"))
        {
            SelectionItem *item_widget = new SelectionItem;
            item_widget->setIcon(":/ubuntukylin.png");
            item_widget->setText(item->text());
            item->setText("");
            item->setSizeHint(item_widget->sizeHint());
            ui->aptDistroList->setItemWidget(item, item_widget);
        }
        else if (item->text().startsWith("kylin"))
        {
            SelectionItem *item_widget = new SelectionItem;
            item_widget->setIcon(":/kylin.png");
            item_widget->setText(item->text());
            item->setText("");
            item->setSizeHint(item_widget->sizeHint());
            ui->aptDistroList->setItemWidget(item, item_widget);
        }
        else if (item->text().startsWith("loongnix"))
        {
            SelectionItem *item_widget = new SelectionItem;
            item_widget->setIcon(":/loongnix.png");
            item_widget->setText(item->text());
            item->setText("");
            item->setSizeHint(item_widget->sizeHint());
            ui->aptDistroList->setItemWidget(item, item_widget);
        }
        else if (item->text().startsWith("termux"))
        {
            SelectionItem *item_widget = new SelectionItem;
            item_widget->setIcon(":/termux.png");
            item_widget->setText(item->text());
            item->setText("");
            item->setSizeHint(item_widget->sizeHint());
            ui->aptDistroList->setItemWidget(item, item_widget);
        }
        else if (item->text().startsWith("Microsoft"))
        {
            SelectionItem *item_widget = new SelectionItem;
            if (item->text().contains("VSCode")) {
                item_widget->setIcon(":/vscode.png");
            } else if (item->text().contains("Edge")) {
                item_widget->setIcon(":/edge.png");
            }
            item_widget->setText(item->text());
            item->setText("");
            item->setSizeHint(item_widget->sizeHint());
            ui->aptDistroList->setItemWidget(item, item_widget);
        }
        else if (item->text().startsWith("ROS"))
        {
            SelectionItem *item_widget = new SelectionItem;
            item_widget->setIcon(":/ros.png");
            item_widget->setText(item->text());
            item->setText("");
            item->setSizeHint(item_widget->sizeHint());
            ui->aptDistroList->setItemWidget(item, item_widget);
        }
        else
        {
            SelectionItem *item_widget = new SelectionItem;
            item_widget->setIcon(":/linux.png");
            item_widget->setText(item->text());
            item->setText("");
            item->setSizeHint(item_widget->sizeHint());
            ui->aptDistroList->setItemWidget(item, item_widget);
        }
    }

    ui->apt_packages_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->groupBox->setTitle(QString("发行版与源 - (数量: %1)").arg(ui->aptDistroList->count()));
}

AptAnalyzerWindow::~AptAnalyzerWindow()
{
    delete ui;
}

void AptAnalyzerWindow::on_aptDistroList_itemClicked(QListWidgetItem *item)
{
    auto distribution = item->data(USER_D).toString();
    auto codename = item->data(USER_C).toString();

// 0. 清空源信息
    foreach (auto var, AptRelease::keys())
    {
        auto lab_var = ui->tabWidget->findChild<QLabel *>("r_" + var);
        if (lab_var)
        {
            lab_var->setText("");
        }
    }

// 1. 加载源信息
    // https://mirrors.bfsu.edu.cn/debian/dists/bookworm/Release
    auto url = QString("https://mirrors.bfsu.edu.cn/%1/dists/%2/Release").arg(distribution).arg(codename);
    if (distribution.startsWith("http"))
    {
        url = QString("%1/dists/%2/Release").arg(distribution).arg(codename);
        if (codename.isEmpty())
        {
            url = QString("%1/%2/Release").arg(distribution).arg(codename);
        }
    }
    AptRelease r = AptRelease::fromUrl(url);

    foreach (auto var, r.properties())
    {
        auto lab_var = ui->tabWidget->findChild<QLabel *>("r_" + var.key());
        if (lab_var)
        {
            lab_var->setText(var.value());
            lab_var->setTextInteractionFlags(Qt::TextSelectableByMouse);
        }
    }
    ui->apt_packages_browser->setText(r.content());

// 1.1 显示分类
    ui->lab_Components->setText(r.Components().value());
    ui->lab_Architectures->setText(r.Architectures().value());

    ui->comb_Components->disconnect();
    ui->comb_Components->clear();
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
    ui->comb_Components->addItems(r.Components().value().split(QRegExp("\\s+"), QString::SkipEmptyParts));
#else
    ui->comb_Components->addItems(r.Components().value().split(QRegExp("\\s+"), Qt::SkipEmptyParts));
#endif
    connect(ui->comb_Components, SIGNAL(currentIndexChanged(int)), this, SLOT(apt_repo_reload_packages()));

    ui->comb_Architectures->disconnect();
    ui->comb_Architectures->clear();
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
    ui->comb_Architectures->addItems(r.Architectures().value().split(QRegExp("\\s+"), QString::SkipEmptyParts));
#else
    ui->comb_Architectures->addItems(r.Architectures().value().split(QRegExp("\\s+"), Qt::SkipEmptyParts));
#endif
    connect(ui->comb_Architectures, SIGNAL(currentIndexChanged(int)), this, SLOT(apt_repo_reload_packages()));

// 2.加载架构与组件对应数据
// https://mirrors.bfsu.edu.cn/debian/dists/bookworm/main/binary-amd64/Release
    apt_repo_load_packages(distribution, codename);

    m_distribution = distribution ;
    m_codename = codename  ;
}

void AptAnalyzerWindow::on_e_search_returnPressed()
{
    ui->stacked_apt_packages->setCurrentWidget(ui->stack_loading);
    Defer defer([this]()
    {
        ui->stacked_apt_packages->setCurrentWidget(ui->stack_table);
    });

    QString input = ui->e_search->text();
    int rows = ui->apt_packages_table->rowCount();
    if (input.isEmpty())
    {
        for (int i = 0; i < rows; ++i)
        {
            ui->apt_packages_table->setRowHidden(i, false);
        }
    }
    else
    {
        for (int i = 0; i < rows; ++i)
        {
            ui->apt_packages_table->setRowHidden(i, true);
        }

        auto items = ui->apt_packages_table->findItems(input, Qt::MatchContains);

        if (items.isEmpty() == false)
        {
            for (int i = 0; i < items.count(); ++i)
            {
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

    if (distribution.startsWith("http"))
    {
        // 包含 http 项时
        url = QString("%1/dists/%2/%3/binary-%4/Release").arg(distribution).arg(codename)
              .arg(ui->comb_Components->currentText())
              .arg(ui->comb_Architectures->currentText());
        if (codename.isEmpty())
        {
            url = QString("%1/%2/%3/binary-%4/Release").arg(distribution).arg(codename)
                  .arg(ui->comb_Components->currentText())
                  .arg(ui->comb_Architectures->currentText());

            if (ui->comb_Components->currentText().isEmpty())
            {
                url = QString("%1/Release").arg(distribution);
            }
        }
    }
    Request req_release(url);
    Response resp_release = HttpClient::instance().get(req_release);

    if (resp_release.status() == 200)
    {
        ui->apt_packages_browser->setText(resp_release.content());
    }

    //    https://mirrors.bfsu.edu.cn/debian/dists/bookworm/main/binary-amd64/Packages.xz
    //    https://mirrors.bfsu.edu.cn/debian/dists/bullseye/main/binary-all/Packages.gz
    url = QString("https://mirrors.bfsu.edu.cn/%1/dists/%2/%3/binary-%4/Packages.gz").arg(distribution).arg(codename)
          .arg(ui->comb_Components->currentText())
          .arg(ui->comb_Architectures->currentText());

    if (distribution.startsWith("http"))
    {
        url = QString("%1/dists/%2/%3/binary-%4/Packages.gz").arg(distribution).arg(codename)
              .arg(ui->comb_Components->currentText())
              .arg(ui->comb_Architectures->currentText());

        if (codename.isEmpty())
        {
            url = QString("%1/%2/%3/binary-%4/Packages.gz").arg(distribution).arg(codename)
                  .arg(ui->comb_Components->currentText())
                  .arg(ui->comb_Architectures->currentText());

            if (ui->comb_Components->currentText().isEmpty())
            {
                url = QString("%1/Packages.gz").arg(distribution);
            }
        }
    }

    ui->apt_loading_progress->setValue(0);
    Response head_package_gz = HttpClient::instance().head(Request(url));

    if (head_package_gz.status() != 404)
    {
        // 1. 成功访问到 gz 文件，立即准备 get 获取
        ui->apt_loading_progress->setValue(10);

        Request req_package(url);
        req_package.setHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36 UOS Community");
        Response get_package = HttpClient::instance().get(req_package);
        auto full = get_package.content();

        ui->apt_loading_progress->setValue(50);

        // 2. 解析 gz 文件，获取标准可见数据
        QByteArray uncompress;
        z_stream zlib = {0};
        zlib.avail_in = head_package_gz.headContentLength();
        zlib.next_in = (Bytef *)full.data();

        int e = inflateInit2(&zlib, MAX_WBITS + 16);
        if (e == Z_OK)
        {
            while (true)
            {
                char buffer[4096] = {0};
                zlib.avail_out = 4096;
                zlib.next_out = (Bytef *)buffer;

                int code = inflate(&zlib, Z_FINISH);
                uncompress.append(buffer, 4096 - zlib.avail_out);

                if (code == Z_STREAM_END)
                {
                    break;
                }
            }
            inflateEnd(&zlib);
        }

        ui->apt_loading_progress->setValue(80);

        // 3. 将服务器的 Packages 数据进行分割为 splits 块
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
        auto splits = QString(uncompress).split("\n\n", QString::SkipEmptyParts);
#else
        auto splits = QString(uncompress).split("\n\n", Qt::SkipEmptyParts);
#endif
        QList<AptPackage> apt_packages;
        foreach (auto var, splits)
        {
            // 3.1 尝试对每一块数据进行 AptPackage 标准数据解析
            AptPackage apt_package(var);
            if (apt_package.properties().count() > 3)
            {
                // 当有效属性值超过 3 个时放入集合
                apt_packages << apt_package;
            }
        }
        // 4. 检查 apt_packages 集合是否包含数据集
        if (apt_packages.count() == 0)
        {
            QString message = QString("报告：已获取 Package.gz 文件，但文件内容为空\n"
                                      "地址：%1\n"
                                      "前缀：%2").arg(url).arg(distribution);
            ui->apt_packages_browser->setText(message);
            ui->apt_packages_table->clearContents();
            ui->apt_packages_table->setRowCount(0);
            ui->apt_packages_content->setText(message);
            return;
        }
        ui->apt_packages_content->setText(apt_packages[0].content());

        ui->apt_packages_table->clearContents();
        ui->apt_packages_table->setRowCount(apt_packages.count());
        ui->stacked_apt_packages->setCurrentWidget(ui->stack_loading);
        Defer defer([this]()
        {
            ui->stacked_apt_packages->setCurrentWidget(ui->stack_table);
        });

        int count = apt_packages.count();
        for (int i = 0; i < apt_packages.count(); ++i)
        {
            auto var = apt_packages[i];
            QTableWidgetItem *package = new QTableWidgetItem;
            package->setText(var.Package().value());
            package->setData(Qt::UserRole, var.content());
            QTableWidgetItem *version = new QTableWidgetItem;
            version->setText(var.Version().value());
            QTableWidgetItem *filename = new QTableWidgetItem;
            filename->setText(var.Filename().value());

            ui->apt_packages_table->setItem(i, 0, package);
            ui->apt_packages_table->setItem(i, 1, version);
            ui->apt_packages_table->setItem(i, 2, filename);
        }

        ui->apt_loading_progress->setValue(100);

        return;
    }

    url.replace("Packages.gz", "Packages");
    ui->apt_loading_progress->setValue(0);
    Response head_package = HttpClient::instance().head(Request(url));

    if (head_package.status() != 404)
    {
        // 1. 成功访问到 gz 文件，立即准备 get 获取
        ui->apt_loading_progress->setValue(10);

        Request req_package(url);
        req_package.setHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36 UOS Community");
        Response get_package = HttpClient::instance().get(req_package);
        auto full = get_package.content();

        ui->apt_loading_progress->setValue(50);

        // 2. 解析 gz 文件，获取标准可见数据
        QByteArray uncompress = full;

        ui->apt_loading_progress->setValue(80);

        // 3. 将服务器的 Packages 数据进行分割为 splits 块
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
        auto splits = QString(uncompress).split("\n\n", QString::SkipEmptyParts);
#else
        auto splits = QString(uncompress).split("\n\n", Qt::SkipEmptyParts);
#endif
        QList<AptPackage> apt_packages;
        foreach (auto var, splits)
        {
            // 3.1 尝试对每一块数据进行 AptPackage 标准数据解析
            AptPackage apt_package(var);
            if (apt_package.properties().count() > 3)
            {
                // 当有效属性值超过 3 个时放入集合
                apt_packages << apt_package;
            }
        }
        // 4. 检查 apt_packages 集合是否包含数据集
        if (apt_packages.count() == 0)
        {
            QString message = QString("报告：已获取 Package 文件，但文件内容为空\n"
                                      "地址：%1\n"
                                      "前缀：%2").arg(url).arg(distribution);
            ui->apt_packages_browser->setText(message);
            ui->apt_packages_table->clearContents();
            ui->apt_packages_table->setRowCount(0);
            ui->apt_packages_content->setText(message);
            return;
        }
        ui->apt_packages_content->setText(apt_packages[0].content());

        ui->apt_packages_table->clearContents();
        ui->apt_packages_table->setRowCount(apt_packages.count());
        ui->stacked_apt_packages->setCurrentWidget(ui->stack_loading);
        Defer defer([this]()
        {
            ui->stacked_apt_packages->setCurrentWidget(ui->stack_table);
        });

        int count = apt_packages.count();
        for (int i = 0; i < apt_packages.count(); ++i)
        {
            auto var = apt_packages[i];
            QTableWidgetItem *package = new QTableWidgetItem;
            package->setText(var.Package().value());
            package->setData(Qt::UserRole, var.content());
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

    if (head_package_gz.status() == 404 && head_package.status() == 404)
    {
        // 无法请求到架构任何数据时显示错误页
        ui->apt_loading_progress->setValue(100);
        ui->stacked_apt_packages->setCurrentWidget(ui->stack_fail);
    }
    else
    {
        // 否则显示回 table 页
        ui->stacked_apt_packages->setCurrentWidget(ui->stack_table);
    }
}

/**
 * @brief 重新加载软件信息列表
 * @note  由：架构选择、组件等下拉选项触发
 * @retval None
 */
void AptAnalyzerWindow::apt_repo_reload_packages()
{
    int rows = ui->apt_packages_table->rowCount();
    for (int i = 0; i < rows; ++i)
    {
        ui->apt_packages_table->setRowHidden(i, false);
    }
    apt_repo_load_packages(m_distribution, m_codename);
}

void AptAnalyzerWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key_C)
    {
        auto item = ui->apt_packages_table->currentItem();
        if (item && item->column() == 2)
        {
            QString fileurl = QString("https://mirrors.bfsu.edu.cn/%1/%2").arg(m_distribution).arg(item->text());
            if (m_distribution.startsWith("http"))
            {
                fileurl = QString("%1/%2").arg(m_distribution).arg(item->text());
            }
            qApp->clipboard()->setText(fileurl);
            return;
        }
    }

    FramelessWidget::keyPressEvent(event);
}

void AptAnalyzerWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == Qt::CheckState::Checked)
        this->setStyleSheet(QR("://light.css"));
    else
    {
        this->setStyleSheet("");
    }
}

/**
 * @brief 左侧列表项搜索过滤
 * @param arg1
 */
void AptAnalyzerWindow::on_e_filter_distribution_textChanged(const QString &arg1)
{
    QString input = arg1;
    int rows = ui->aptDistroList->count();
    if (input.isEmpty())
    {
        for (int i = 0; i < rows; ++i)
        {
            ui->aptDistroList->setRowHidden(i, false);
        }
    }
    else
    {
        QList<QListWidgetItem *> items;
        for (int i = 0; i < rows; ++i)
        {
            auto item = ui->aptDistroList->item(i);
            auto widget = ui->aptDistroList->itemWidget(item);
            ui->aptDistroList->setRowHidden(i, true);

            // 从 item 中取出的控件进行转换
            auto seletion = qobject_cast<SelectionItem *>(widget);
            if (seletion)
            {
                if (seletion->text().contains(input, Qt::CaseInsensitive))
                {
                    items.append(item);
                }
            }
        }

        if (items.isEmpty() == false)
        {
            for (int i = 0; i < items.count(); ++i)
            {
                int row = ui->aptDistroList->row(items.at(i));
                ui->aptDistroList->setRowHidden(row, false);
            }
        }
    }
}


void AptAnalyzerWindow::on_apt_packages_table_cellClicked(int row, int column)
{
    auto package = ui->apt_packages_table->item(row, 0);
    if (package)
    {
        ui->apt_packages_content->setText(package->data(Qt::UserRole).toString());
    }
}

