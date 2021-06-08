#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QFileDialog>
#include <QString>

#include <iostream>

void fillModelWithData(ExampleModel* titanicModel, QString path)
{
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    QString firstline = inputStream.readLine();

    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        
        QList<QVariant> dataRow;
        for (QString& item : line.split(";")) {
            dataRow.append(item);
        }
        titanicModel->appendRow(dataRow);
    }
    inputFile.close();
}

void saveModelAsFile(ExampleModel* m, QString path)
{
    QFile outFile(path);
    outFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&outFile);
    
    for (int i = 0; i < m->rowCount(); ++i)
    {
        for (int j = 0; j < m->columnCount(); ++j)
        {
            QModelIndex idx = m->index(i, j);
            out << m->data(idx).toString();
            if (j != m->columnCount() - 1)
            {
                out << ",";
            }
        }
        out << "\n";
    }
    outFile.close();
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    titanicModel = new ExampleModel(this);
    ui->tableView->setModel(titanicModel);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete titanicModel;
}

void MainWindow::onLoadButtonPushed()
{
    QString path = QFileDialog::getOpenFileName(this);
    fillModelWithData(titanicModel, path);
    ui->tableView->setSortingEnabled(true);
}

//void MainWindow::setListViewColumn(int value)
//{
//    ui->listView->setModelColumn(value);
//}



void MainWindow::on_savePushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this);
    saveModelAsFile(titanicModel, path);
}


void MainWindow::on_AddMovieButton_clicked()
{
    QList<QModelIndex> position = ui->tableView->selectionModel()->selectedRows();
    if (position.size() == 0)
    {
        titanicModel->insertRows(0, 1);
    }else
    {
        titanicModel->insertRows(position[0].row(), position.size());
    }
}


void MainWindow::on_deletePushButton_clicked()
{
    QList<QModelIndex> position = ui->tableView->selectionModel()->selectedRows();

    if (position.size() == 0)
    {
        titanicModel->removeRows(0,1);
    }else
    {
        titanicModel->removeRows(position[0].row() , position.size());
    }
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dialog;
    dialog.exec();
}


