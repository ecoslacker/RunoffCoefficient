/*
 * This code was taken from: https://github.com/hnaohiro/qt-csv
 * No license was found about its usage.
 *
 */

#ifndef CSV_H
#define CSV_H

#include <QStringList>

namespace CSV
{
    QList<QStringList> parseFromString(const QString &string);
    QList<QStringList> parseFromFile(const QString &filename, const QString &codec = QString());
    bool write(const QList<QStringList> data, const QString &filename, const QString &codec = QString());
}

#endif // CSV_H
