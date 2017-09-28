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

#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    connect(ui->area, SIGNAL(textChanged(QString)), SLOT(adjustArea(QString)));
    connect(ui->soiltype, SIGNAL(currentIndexChanged(int)), SLOT(adjustSoilType(int)));
    connect(ui->landuse, SIGNAL(currentIndexChanged(int)), SLOT(adjustLandUse(int)));

    landUses << "Barbecho, áreas incultas y desnudas"
            << "Cultivos en hilera"
            << "Legumbres o rotación de pradera"
            << "Granos pequeños"
            << "Pastizal (75%)"
            << "Pastizal (50-75%)"
            << "Pastizal (50%)"
            << "Bosque (75%)"
            << "Bosque (50-75%)"
            << "Bosque (25-50%)"
            << "Bosque (25%)"
            << "Zona urbana"
            << "Camino"
            << "Pradera permanente";

    soilTypes << "Suelo permeable"
             << "Suelo de permeabilidad media"
             << "Suelo casi impermeable";

    ui->landuse->addItems(landUses);
    ui->soiltype->addItems(soilTypes);
}

AddDialog::~AddDialog()
{
    delete ui;
}

QString AddDialog::getArea() const
{
    return area;
}

void AddDialog::setArea(const QString &value)
{
    area = value;
}

int AddDialog::getSoilType() const
{
    return soilType;
}

void AddDialog::setSoilType(int value)
{
    soilType = value;
}

int AddDialog::getLandUse() const
{
    return landUse;
}

void AddDialog::setLandUse(int value)
{
    landUse = value;
}

QString AddDialog::getSoilTypeStr() const
{
    return soilTypeStr;
}

void AddDialog::setSoilTypeStr(const QString &value)
{
    soilTypeStr = value;
}

QString AddDialog::getLandUseStr() const
{
    return landUseStr;
}

void AddDialog::setLandUseStr(const QString &value)
{
    landUseStr = value;
}

QStringList AddDialog::getSoilTypes() const
{
    return soilTypes;
}

void AddDialog::setSoilTypes(const QStringList &value)
{
    soilTypes = value;
}

QStringList AddDialog::getLandUses() const
{
    return landUses;
}

void AddDialog::setLandUses(const QStringList &value)
{
    landUses = value;
}

void AddDialog::adjustSoilType(int index)
{
    soilType = index;
    soilTypeStr = ui->soiltype->currentText();
    qDebug() << "Soil type is (" << soilType << "): " << soilTypeStr;
}

void AddDialog::adjustLandUse(int index)
{
    landUse = index;
    landUseStr = ui->landuse->currentText();
    qDebug() << "Land use is (" << landUse << "): " << landUseStr;
}

void AddDialog::adjustArea(QString text)
{
    area = text;
}
