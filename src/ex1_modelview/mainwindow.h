#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTransposeProxyModel>
#include <QSortFilterProxyModel>

#include "examplemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadButtonPushed();
    //void setListViewColumn(int value);

    //void on_tableView_activated(const QModelIndex &index);

    void on_savePushButton_clicked();

    void on_AddMovieButton_clicked();

    void on_deletePushButton_clicked();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    ExampleModel *titanicModel;

    QTransposeProxyModel *tmodel;
    QSortFilterProxyModel *sortModel;
};

#endif // MAINWINDOW_H
