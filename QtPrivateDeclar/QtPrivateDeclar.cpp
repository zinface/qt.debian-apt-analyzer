#include "QtPrivateDeclar.h"
#include <QTextStream>

QtPrivateDeclar::QtPrivateDeclar(): d_ptr(new QtPrivateDeclarPrivate(this))
{
    
}

void QtPrivateDeclar::setContent(const QString &content) {
    // QTextStream out(stdout);
    // out << content;
    QStringList lines = content.split("\n");
    for (auto line : lines)
    {
        if (line.startsWith("Origin")) {
            line.remove("Origin: ");
            setOrigin(line);
            continue;
        }
        if (line.startsWith("Label")) {
            line.remove("Label: ");
            setLabel(line);
            continue;
        }
        if (line.startsWith("Version")) {
            line.remove("Version: ");
            setVersion(line);
            continue;
        }
        if (line.startsWith("Codename")) {
            line.remove("Codename: ");
            setCodename(line);
            continue;
        }
        if (line.startsWith("Suite")) {
            line.remove("Suite: ");
            setSuite(line);
            continue;
        }
        if (line.startsWith("Date")) {
            line.remove("Date: ");
            setDate(line);
            continue;
        }
        if (line.startsWith("Architectures")) {
            line.remove("Architectures: ");
            setArchitectures(line);
            continue;
        }
        if (line.startsWith("Components")) {
            line.remove("Components: ");
            setComponents(line);
            continue;
        }
        if (line.startsWith("Description")) {
            line.remove("Description: ");
            setDescription(line);
            continue;
        }

    }
}


void QtPrivateDeclar::setOrigin(QString origin) {
    Q_D(QtPrivateDeclar);
    d->origin = origin;
}
QString QtPrivateDeclar::getOrigin() {
    Q_D(const QtPrivateDeclar);
    return d->origin;
}

void QtPrivateDeclar::setLabel(QString label) {
    Q_D(QtPrivateDeclar);
    d->label = label;
}
QString QtPrivateDeclar::getLabel() {
    Q_D(const QtPrivateDeclar);
    return d->label;
}

void QtPrivateDeclar::setVersion(QString version) {
    Q_D(QtPrivateDeclar);
    d->version = version;
}
QString QtPrivateDeclar::getVersion() {
    Q_D(const QtPrivateDeclar);
    return d->version;
}

void QtPrivateDeclar::setCodename(QString codename) {
    Q_D(QtPrivateDeclar);
    d->codename = codename;
}
QString QtPrivateDeclar::getCodename() {
    Q_D(const QtPrivateDeclar);
    return d->codename;
}

void QtPrivateDeclar::setSuite(QString suite) {
    Q_D(QtPrivateDeclar);
    d->suite = suite;
}
QString QtPrivateDeclar::getSuite() {
    Q_D(const QtPrivateDeclar);
    return d->suite;
}

void QtPrivateDeclar::setDate(QString date) {
    Q_D(QtPrivateDeclar);
    d->date = date;
}
QString QtPrivateDeclar::getDate() {
    Q_D(const QtPrivateDeclar);
    return d->date;
}

void QtPrivateDeclar::setArchitectures(QString architectures) {
    Q_D(QtPrivateDeclar);
    d->architectures = architectures;
}
QString QtPrivateDeclar::getArchitectures() {
    Q_D(const QtPrivateDeclar);
    return d->architectures;
}

void QtPrivateDeclar::setComponents(QString components) {
    Q_D(QtPrivateDeclar);
    d->components = components;
}
QString QtPrivateDeclar::getComponents() {
    Q_D(const QtPrivateDeclar);
    return d->components;
}

void QtPrivateDeclar::setDescription(QString description) {
    Q_D(QtPrivateDeclar);
    d->description = description;
}

QString QtPrivateDeclar::getDescription() {
    Q_D(QtPrivateDeclar);
    return d->description;
}