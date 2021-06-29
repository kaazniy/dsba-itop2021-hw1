#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QDate>
#include <QDateTime>
#include <QTableWidget>
#include <QSet>
#include <set>
#include <string>
#include <QComboBox>


class ExampleModel : public QAbstractTableModel
{
    Q_OBJECT
    
public:
    explicit ExampleModel(QObject *parent = nullptr);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void appendRow(QList<QVariant> newRow);

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());


    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    std::set<QString> get_info_col(int col);

    
private:
    QList<QList<QVariant> > exampleData;
};

#endif // EXAMPLEMODEL_H
