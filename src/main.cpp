// clang-format off

#include <QApplication>
#include <QIcon>
#include <screenutil.h>

#include <QStyle>
#include <QStyleFactory>
#include <version.h>

#include <widgets/aptanalyzerwindow.h>

int main(int argc, char *argv[])
{
//    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QApplication a(argc, argv);
//    // 创建并应用暗色调色板
//    QPalette darkPalette;
//    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
//    darkPalette.setColor(QPalette::WindowText, Qt::white);
//    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
//    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
//    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
//    darkPalette.setColor(QPalette::ToolTipText, QColor(162, 162, 162));
//    darkPalette.setColor(QPalette::Text, Qt::white);
//    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
//    darkPalette.setColor(QPalette::ButtonText, Qt::white);
//    darkPalette.setColor(QPalette::BrightText, Qt::red);
//    darkPalette.setColor(QPalette::Link, QColor(255, 183, 47));
//    darkPalette.setColor(QPalette::Highlight, QColor(255, 183, 47));
//    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
//    // 设置禁用状态下的窗口文本颜色
//    darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, Qt::gray);
//    // 设置禁用状态下的按钮文本颜色
//    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::gray);
//    a.setPalette(darkPalette);

//    // 创建并应用亮色调色板
//    QPalette lightPalette;
//    lightPalette.setColor(QPalette::Window, QColor(240, 240, 240));
//    lightPalette.setColor(QPalette::WindowText, Qt::black);
//    lightPalette.setColor(QPalette::Base, QColor(255, 255, 255));
//    lightPalette.setColor(QPalette::AlternateBase, QColor(230, 230, 230));
//    lightPalette.setColor(QPalette::ToolTipBase, Qt::white);
//    lightPalette.setColor(QPalette::ToolTipText, Qt::gray);
//    lightPalette.setColor(QPalette::Text, Qt::black);
//    lightPalette.setColor(QPalette::Button,  Qt::gray);
//    lightPalette.setColor(QPalette::ButtonText, Qt::white);
//    lightPalette.setColor(QPalette::BrightText, Qt::red);
//    lightPalette.setColor(QPalette::Link, QColor(244, 122, 204));
//    lightPalette.setColor(QPalette::Highlight, QColor(76, 153, 209));
//    lightPalette.setColor(QPalette::HighlightedText, Qt::white);
//    // 设置禁用状态下的窗口文本颜色
//    lightPalette.setColor(QPalette::Disabled, QPalette::WindowText, Qt::gray);
////    lightPalette.setColor(QPalette::Disabled, QPalette::Button, Qt::gray);
//    // 设置禁用状态下的按钮文本颜色
//    lightPalette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::gray);
//    lightPalette.setColor(QPalette::All, QPalette::Base, Qt::white);
//    a.setPalette(lightPalette);


//    QStyle *s = a.style();
//    s->unpolish(&a);
//    a.setStyleSheet("");
//    s->polish(&a);
    a.setStyle(QStyleFactory::create("Light"));
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
