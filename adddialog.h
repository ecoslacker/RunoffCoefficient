/*
 * Cálculo del coeficiente de escurrimiento de acuerdo a la norma oficial
 * mexicana NOM-011-CONAGUA-2015, Conservación del recurso agua.
 * Copyright (C) 2017 Eduardo Jiménez
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QStringList>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();

    QString getArea() const;
    void setArea(const QString &value);

    int getSoilType() const;
    void setSoilType(int value);

    int getLandUse() const;
    void setLandUse(int value);

    QString getSoilTypeStr() const;
    void setSoilTypeStr(const QString &value);

    QString getLandUseStr() const;
    void setLandUseStr(const QString &value);

    QStringList getSoilTypes() const;
    void setSoilTypes(const QStringList &value);

    QStringList getLandUses() const;
    void setLandUses(const QStringList &value);

private:
    Ui::AddDialog *ui;
    QStringList soilTypes;
    QStringList landUses;
    QString area;
    QString soilTypeStr;
    QString landUseStr;
    int soilType;
    int landUse;

private slots:
    void adjustSoilType(int index);
    void adjustLandUse(int index);
    void adjustArea(QString text);
};

#endif // ADDDIALOG_H
