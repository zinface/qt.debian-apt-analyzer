// clang-format off

#include <QApplication>
#include <QIcon>
#include <screenutil.h>

#include <version.h>

#include <widgets/aptanalyzerwindow.h>

int main(int argc, char *argv[])
{
//    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QApplication a(argc, argv);
//    QFont font("", 8);
//    a.setFont(font);
    a.setApplicationName("Debian 软件仓库分析工具 - v" PROJECT_VERSION);
    a.setApplicationVersion(PROJECT_VERSION);
    a.setOrganizationName("spark-union");
    a.setOrganizationDomain("https://www.spark-app.store/");
    a.setWindowIcon(QIcon("://icon.png"));

    AptAnalyzerWindow w;
    w.show();

    ScreenUtil::moveCenter(w);

    return a.exec();
}
