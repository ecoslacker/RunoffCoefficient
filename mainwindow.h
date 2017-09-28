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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QTextStream>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>
#include "aboutdialog.h"
#include "adddialog.h"
#include "runoffcoefficient.h"
#include "csv/csv.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringList headers;
    QStandardItemModel *model;
    QStringList soilTypes;
    QStringList landUses;

private slots:
    void about();
    void addRow();
    void removeRow();
    void setupModel();
    void calculate();
    void saveFile();
    void openFile();
    int getLandUse(QString landuse);
    int getSoilType(QString soiltype);
    void enumRows();
};

#endif // MAINWINDOW_H
