#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"
#include "comboboxdelegate.h"

#include <QAbstractProxyModel>
#include <QWidget>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QFileDialog>
#include <algorithm>
#include <QString>
#include <QSet>

#include <iostream>

void fillModelWithData(ExampleModel* titanicModel, QString path)
{
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    ///QString firstline = inputStream.readLine();

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
            out << (m->data(idx)).toString();
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


void MainWindow::load_combobox()
{
    ui->tableView->setModel(titanicModel);
    auto countries = titanicModel->get_info_col(2);
    ComboBoxDelegate *cb_delegate = new ComboBoxDelegate (titanicModel, countries);
    ui->tableView->setItemDelegateForColumn(2, cb_delegate);

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
    MainWindow::load_combobox();
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
    ui->tableView->setModel(titanicModel);
    QList<QModelIndex> position = ui->tableView->selectionModel()->selectedRows();
    if (position.size() == 0)
    {
        titanicModel->insertRows(0, 1);
    }else
    {
        titanicModel->insertRows(position[0].row(), position.size());
    }
    MainWindow::load_combobox();
}


void MainWindow::on_deletePushButton_clicked()
{
    ui->tableView->setModel(titanicModel);
    QList<QModelIndex> position = ui->tableView->selectionModel()->selectedRows();
    std::vector<int> new_position;
    for (int i = 0; i < position.size();i++)
    {
        new_position.push_back((int) position[i].row());
    }
    std::sort(new_position.begin(), new_position.end());
    std::reverse(new_position.begin(), new_position.end());



    if (position.size() == 0)
    {
        titanicModel->removeRows(0,1);
    }else
    {
        for (int ind = 0; ind < new_position.size();ind++)
        {
            titanicModel->removeRows(new_position.at(ind),1);
        }
        //titanicModel->removeRows(position[0].row() , position.size());
    }
    MainWindow::load_combobox();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dialog;
    dialog.exec();
}



