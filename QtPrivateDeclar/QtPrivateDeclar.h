#ifndef __QtPrivateDeclar__H__
#define __QtPrivateDeclar__H__

#include <QObject>
#include <qglobal.h>

QT_BEGIN_NAMESPACE
class QtPrivateDeclarPrivate;
QT_END_NAMESPACE

class QtPrivateDeclar
{
    Q_DECLARE_PRIVATE(QtPrivateDeclar);
public:
    QtPrivateDeclar();
    
    void setContent(const QString &content);


    /*********** 此处定义所有私有类的数据成员操作函数 ***********/
    void setOrigin(QString origin);
    QString getOrigin();
    void setLabel(QString label);
    QString getLabel();
    void setVersion(QString version);
    QString getVersion();
    void setCodename(QString codename);
    QString getCodename();
    void setSuite(QString suite);
    QString getSuite();
    void setDate(QString date);
    QString getDate();
    void setArchitectures(QString architectures);
    QString getArchitectures();
    void setComponents(QString components);
    QString getComponents();
    void setDescription(QString description);
    QString getDescription();

private:
    QtPrivateDeclarPrivate *d_ptr;
};

// 这个是私有类，
class QtPrivateDeclarPrivate
{
    Q_DECLARE_PUBLIC(QtPrivateDeclar)
public:
    QtPrivateDeclarPrivate(QtPrivateDeclar *q)
    : q_ptr(q)
    /*********** 此处定义初始化所有数据成员 ***********/
    , origin("")
    , label("")
    , version("")
    , codename("")
    , suite("")
    , date("")
    , architectures("")
    , components("")
    , description("")
    {
    };
    QtPrivateDeclar *q_ptr;

    /*********** 此处定义数据成员 ***********/
    QString origin;
    QString label;
    QString version;
    QString codename;
    QString suite;
    QString date;
    QString architectures;
    QString components;
    QString description;

    

};

#endif  //!__QtPrivateDeclar__H__


// Qt中的Q_D宏和d指针
//   Q_D的设置意在方便地获取私有类指针，文件为qglobal.h。下面的##是宏定义的连字符。假设类名是A，那么A##Private翻译过来就是APrivate。
//   #define Q_D(Class) Class##Private * const d = d_func()

// d_func()函数如下实现：
// #define Q_DECLARE_PRIVATE(Class) \
//      inline Class##Private* d_func() { return reinterpret_cast<Class##Private *>(qGetPtrHelper(d_ptr)); } \
//      inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private *>(qGetPtrHelper(d_ptr)); } \
//      friend class Class##Private;
// 这里的d_func()虽然在宏里面，但是如果代入具体的类型，这里面就变成了以Class##Private的私有类指针为返回值，以func为函数名的函数。这里的qGetPtrHelper是

// 五、私有类函数调用
//  Qt中的公有类和私有类关系密切，私有类的函数是不能够直接使用的。要是想用，一定要通过其他类调用。
//  在Qt编译的时候，QFileSystemModel.h是一堆声明，会导出很多函数到QtWidget.dll里面去。
// 值得注意的是，这里导出的只是这个文件里所声明的类、函数和变量，而不会导出只在私有类头文件QFileSystemModel_p.h里面声明过的函数和变量。
//  当然，编译的时候，也会引用QFileSystemModelPrivate.h和QFileSystemModel.cpp里的声明以及定义。
// 一般情况下，我们只是Qt的使用者，在windows系统下，只要下载安装就好，不需要自己再编译了。
// 但是当我们想使用私有类做一些更深入的定制的时候，希望能够调直接调用私有类的成员。
// 这时候，如果只是include了.h文件，就会报undefined reference错误。也就是说，编译能过，链接过不了，找不到私有类成员。
//  解决的方法就是将对应的cpp文件也包含进工程目录里面，但这时候会有新的问题出现。
// 有些类的实现已经编译到库函数里面了，这时候又在cpp文件重新实现，会报警告：redeclared without dllimport attribute。
// 只需要把cpp文件中的实现函数删除掉就可以了。
//  虽然通过上面的方法，可以实现私有类的使用，但是值得注意的是，已经编译好的二进制文件dll里面的同名私有函数还在起着作用。
// 还是用QFileSystemModel为例，它已经被Qt编译好放到了QWidget.dll里面了。
// 在此dll文件里也会有QFileSystemModelPrivate的函数（只是不会有直接指向外部的声明，外部不能直接链接引用而已），否则私有类就完全没用了。
// 当新的工程要使用到QFileSystemModel，而QFileSystemModelPrivate被间接地引用，使用的版本就是之前编译好的成品。
// 当新的工程要直接调用私有类函数的时候，才是用的新的版本。