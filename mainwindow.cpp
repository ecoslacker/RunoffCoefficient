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

#include "mainwindow.h"
#include "ui_mainwindow.h"

//const int MIN_COLS = 3;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QIcon winIcon(":/icons/icons/16x16/river.png");
    setWindowIcon(winIcon);

    // Connect actions
    connect(ui->actionAbout,     SIGNAL(triggered(bool)), SLOT(about()));
    connect(ui->actionAdd,       SIGNAL(triggered(bool)), SLOT(addRow()));
    connect(ui->actionRemove,    SIGNAL(triggered(bool)), SLOT(removeRow()));
    connect(ui->actionSave,      SIGNAL(triggered(bool)), SLOT(saveFile()));
    connect(ui->actionOpen,      SIGNAL(triggered(bool)), SLOT(openFile()));
    connect(ui->calculateButton, SIGNAL(pressed()),       SLOT(calculate()));

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

    // Initialize model stuff
    model = new QStandardItemModel;
    headers << "Fila" << "Área (hectáreas)" << "Uso de suelo" << "Tipo de suelo";
    model->setHorizontalHeaderLabels(headers);
    setupModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about()
{
    aboutDialog *aboutDlg = new aboutDialog();
    aboutDlg->exec();
}

void MainWindow::addRow()
{
    QString label;
    QString area;
    QString soilType;
    QString landUse;

    int maxRows = model->rowCount();
    label = QString::number(maxRows + 1);

    // Open dialog for adding properties
    AddDialog *addDlg = new AddDialog;
    if (addDlg->exec() == QDialog::Accepted) {
        qDebug() << "Accepted";
        area = addDlg->getArea();
        soilType = addDlg->getSoilTypeStr();
        landUse = addDlg->getLandUseStr();
        qDebug() << area << " " << landUse << " " << soilType;

        QList<QStandardItem*> row;

        QStandardItem *itemCol1 = new QStandardItem(label);     // Column 1
        QStandardItem *itemCol2 = new QStandardItem(area);      // Column 2
        QStandardItem *itemCol3 = new QStandardItem(landUse);   // Column 3
        QStandardItem *itemCol4 = new QStandardItem(soilType);  // Column 4

        row.append(itemCol1);
        row.append(itemCol2);
        row.append(itemCol3);
        row.append(itemCol4);

        model->appendRow(row);

        // Adjust the colum size to their content
        ui->treeView->resizeColumnToContents(0);
        ui->treeView->resizeColumnToContents(1);
        ui->treeView->resizeColumnToContents(2);
        ui->treeView->resizeColumnToContents(3);

        // Configure the row labels
        enumRows();
    } else {
        qDebug() << "Rejected";
    }
}

void MainWindow::removeRow()
{
    // Get the number of rows of the model
    int maxRows = model->rowCount();
    if (maxRows > 0) {
        bool ok;
        // Input the row to remove
        int row = QInputDialog::getInt(this, tr("Seleccione"),
                                       tr("Fila a elminar"), 1, 1, maxRows, 1, &ok);
        if (ok)
            qDebug() << "Everything ok!";
        qDebug() << "Eliminar fila " << row;
        model->removeRow(row-1);
        enumRows();
    } else {
        qDebug() << "No es posible elimiar filas";
    }
}

void MainWindow::setupModel()
{
    ui->treeView->setModel(model);
    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->setStyleSheet("QTreeView { alternate-background-color: #eee }"
                                "QTreeView { show-decoration-selected: 1; }"
                                "QTreeView::item { border: 1px solid #d9d9d9; border-top-color: transparent; border-bottom-color: transparent;}"
                                "QTreeView::item:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1); border: 1px solid #bfcde4; }"
                                "QTreeView::item:selected { border: 1px solid #567dbc; }"
                                "QTreeView::item:selected:active{ background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc); }"
                                "QTreeView::item:selected:!active { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6b9be8, stop: 1 #577fbf);}");
}

void MainWindow::calculate()
{

    int rows = model->rowCount();
    // If there are no rows in the model,
    // no further calculations are needed
    if (rows == 0)
        return;

    RunoffCoefficient *rc = new RunoffCoefficient;
    QVector<float> areasVector;
    QVector<int> landUseVector;
    QVector<int> soilTypeVector;
    float precipitation;
    float runoffCoefficientValue;

    // Get precipitation, strings will convert to 0
    precipitation = ui->precipitation->text().toFloat();
    qDebug() << "Precipitation:" << precipitation;
    if (precipitation <= 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("La precipitación debe ser un valor numérico mayor a cero.");
        msgBox.exec();
        return;
    }

    for (int row = 0; row < rows; row++) {
        QStandardItem *itemArea = new QStandardItem();
        QStandardItem *itemLandUse = new QStandardItem();
        QStandardItem *itemSoilType = new QStandardItem();

        // Get the area from item at first column, land use from second column
        // and soil type from third column
        itemArea = model->item(row, 1);
        itemLandUse = model->item(row, 2);
        itemSoilType = model->item(row, 3);

        // Try to convert text to area, strings will convert to 0
        float area = itemArea->text().toFloat();
        qDebug() << "Area:" << area;
        if (area <= 0) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("El área debe ser un valor numérico mayor a cero.");
            msgBox.exec();
            return;
        } else {
            areasVector.append(area);
        }

        // Get the land use as integer, if invalid show an error message dialog
        int nlanduse = getLandUse(itemLandUse->text());
        if (nlanduse == -1) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("No se reconoce el valor (" + QString::number(nlanduse) + "): " +  itemLandUse->text());
            msgBox.exec();
            return;
        } else {
            landUseVector.append(nlanduse);
        }

        // Get the soil type as integer, if invalid show an error message dialog
        int nsoiltype = getSoilType(itemSoilType->text());
        if (nsoiltype == -1) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("No se reconoce el valor (" + QString::number(nsoiltype) + "): " +  itemLandUse->text());
            msgBox.exec();
            return;
        } else {
            soilTypeVector.append(nsoiltype);
        }
    }

    // Finally, if all went well then compute the runoff coefficient
    rc->setAreas(areasVector.toStdVector());
    rc->setLanduses(landUseVector.toStdVector());
    rc->setSoiltypes(soilTypeVector.toStdVector());
    rc->setPrecipitation(precipitation);
    rc->calculate();
    runoffCoefficientValue = rc->getRunoffCoefficient();
    qDebug() << "Runoff Coefficient:" << runoffCoefficientValue;

    // Set the runoff coefficient to the value
    ui->runoffCoefficient->setText(QString::number(runoffCoefficientValue, 'f', 4));
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar archivo"),
                                                    QDir::homePath(),
                                                    tr("Texto (*.txt);;Delimitado por comas (*.csv)"));
    qDebug() << "Saving file: " << fileName;

    // Create a text file
    QFile textFile(fileName);
    if (textFile.open(QIODevice::ReadWrite)) {
        QTextStream writer(&textFile);

        // Write precipitation value in a single line
        writer << ui->precipitation->text() << endl;

        // Write "area, land use index, soil type index" in each line
        for (int i=0; i < model->rowCount(); i++) {

            QString land_use = model->item(i, 2)->text();  // Land use text
            QString soil_type = model->item(i, 3)->text(); // Soil type text

            // Write area and indexes
            writer << model->item(i, 1)->text() << ","
                   << landUses.indexOf(land_use) << ","
                   << soilTypes.indexOf(soil_type) << endl;
        }
    }

}

void MainWindow::openFile()
{
    QList<QStringList> fileData;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir archivo"),
                                            QDir::homePath(),
                                            tr("Delimitado por comas (*.csv);;Texto (*.txt);;Todos los archivos (*.*)"));
    qDebug() << "Openning file: " << fileName;

    // Check that the file actually exists
    QFileInfo testFile(fileName);
    if (!testFile.exists()) {
        qDebug() << "ERROR: File: " << fileName << " does not found.";
        return;
    }

    // Read data
    fileData = CSV::parseFromFile(fileName, "UTF-8");

    // Check that data is not empty
    if (fileData.isEmpty()) {
        qDebug() << "ERROR: The data is empty.";
        return;
    }

    // Check that there are at least MIN_COLS data columns
//    foreach (QStringList line, fileData) {
//        if (line.length() != MIN_COLS) {
//            qDebug() << "ERROR: There should be at least " << MIN_COLS << " data columns.";
//            return;
//        }
//    }

    qDebug() << "Data:" << fileData;

    // Check that there are at least MIN_COLS data columns
    model->clear();
    model->setHorizontalHeaderLabels(headers);
    int rowNumber = 1;
    foreach (QStringList line, fileData) {
        if (rowNumber == 1) {
            QString rain = fileData.at(0).at(0);
            ui->precipitation->setText(rain);
            rowNumber++;
            continue;
        }
        QList<QStandardItem*> row;

        int landUseIndex = line.at(1).toInt();
        int soilTypeIndex = line.at(2).toInt();

        // Check for valid indexes
        if (landUseIndex < 0 || landUseIndex > 13) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error datos inválidos");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("El uso de suelo " +  QString::number(landUseIndex) + " no es válido." +
                           "\nLos valores deben estar entre 0  y 13");
            msgBox.exec();
            return;
        }

        if (soilTypeIndex < 0 || soilTypeIndex > 2) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error datos inválidos");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("El tipo de suelo " +  QString::number(soilTypeIndex) + " no es válido." +
                           "\nLos valores deben estar entre 0  y 2");
            msgBox.exec();
            return;
        }

        QStandardItem *itemCol1 = new QStandardItem(QString::number(rowNumber));       // Column 1
        QStandardItem *itemCol2 = new QStandardItem(line.at(0));                       // Column 2
        QStandardItem *itemCol3 = new QStandardItem(landUses.at(landUseIndex));        // Column 3
        QStandardItem *itemCol4 = new QStandardItem(soilTypes.at(soilTypeIndex));      // Column 4

        row.append(itemCol1);
        row.append(itemCol2);
        row.append(itemCol3);
        row.append(itemCol4);

        model->appendRow(row);

        // Adjust the colum size to their content
        ui->treeView->resizeColumnToContents(0);
        ui->treeView->resizeColumnToContents(1);
        ui->treeView->resizeColumnToContents(2);
        ui->treeView->resizeColumnToContents(3);

        rowNumber++;
    }

    // Configure the row labels
    enumRows();

}

int MainWindow::getLandUse(QString landuse)
{
    int nlanduse = -1;
    for (int i = 0; i < int(landUses.size()); i++) {
        if (landuse == landUses.at(i)) {
            nlanduse = i;
            break;
        }
    }
    return nlanduse;
}

int MainWindow::getSoilType(QString soiltype)
{
    int nsoiltype = -1;
    for(int i = 0; i < int(soilTypes.size()); i++) {
        if (soiltype == soilTypes.at(i)) {
            nsoiltype = i;
            break;
        }
    }
    return nsoiltype;
}

void MainWindow::enumRows()
{
    for (int i = 0; i < model->rowCount(); i++) {
        QStandardItem *itemCell = new QStandardItem(QString::number(i+1));
        model->setItem(i, 0, itemCell);
    }
}
