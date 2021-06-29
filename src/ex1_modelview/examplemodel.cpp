#include "examplemodel.h"
//#include "combobox.cpp"

ExampleModel::ExampleModel(QObject *parent) : QAbstractTableModel(parent) {}


std::set<QString> ExampleModel::get_info_col(int col)
{
    std::set<QString> unique_vals;
    for (auto row:exampleData)
    {
        unique_vals.insert(row.at(col).toString());
    }
    return unique_vals;
}

int ExampleModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    
    return exampleData.size();
}

int ExampleModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    
    if (exampleData.empty())
    {
        return 0;
    }
    return exampleData[1].size();
}


QVariant ExampleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int row = index.row();
        int column = index.column();
        if (column == 2)
        {
//            QComboBox *mainLayout = new QGridLayout(this);
//            QWidget *mainWidget = new QWidget(this);
//            setCellWidget(row, column, QWidget* widget);
        }else { }
        return exampleData.at(row).at(column);
    }
    return QVariant();
}



bool ExampleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {
        switch (index.column())
        {
            case 0:
            {
                bool success = false;
                QVariant try_add_item = value.toInt(&success);
                if (success)
                {
                    exampleData[index.row()][index.column()] = try_add_item;
                }else
                {
                    return false;
                }
                break;
            }
            case 1:
            {
                QVariant try_add_item = value.toString();
                exampleData[index.row()][index.column()] = try_add_item;
                break;
            }
            case 2:
            {
                QVariant try_add_item = value.toString();
                exampleData[index.row()][index.column()] = try_add_item;
                break;
            }
            case 3:
            {
                QVariant try_add_item = value.toString();
                exampleData[index.row()][index.column()] = try_add_item;
                break;
            }
            case 4:
            {
                QVariant try_add_item = value.toString();
                exampleData[index.row()][index.column()] = try_add_item;
                break;
            }
            case 5:
            {
                bool success = false;
                QVariant try_add_item = value.toInt(&success);
                if (success)
                {
                    exampleData[index.row()][index.column()] = try_add_item;
                }else
                {
                    return false;
                }
                break;
            }
            case 6:
            {
                QVariant try_add_item = value.toString();
                exampleData[index.row()][index.column()] = try_add_item;
                break;
            }
            case 7:
            {
                QVariant try_add_item = value.toString();
                exampleData[index.row()][index.column()] = try_add_item;
                break;
            }
            case 8:
            {
                bool y_success = false;
                int y = 0;
                bool m_success = false;
                int m = 0;
                bool d_success = false;
                int d = 0;
                QString cell_data = value.toString();
                if (cell_data.count('.') != 2){return false;}
                d = ((value.toString().split("."))[0]).toInt(&d_success);
                m = ((value.toString().split("."))[1]).toInt(&m_success);
                y = ((value.toString().split("."))[2]).toInt(&y_success);
                if (d_success && m_success && y_success)
                {
                    exampleData[index.row()][index.column()] = QDate(y,m,d);
                }else
                {
                    return false;
                }
                break;
            }
            case 9:
            {
                bool success = false;
                QVariant try_add_item = value.toInt(&success);
                if (success)
                {
                    exampleData[index.row()][index.column()] = try_add_item;
                }else
                {
                    return false;
                }
                break;
            }
            case 10:
            {
                bool success = false;
                QVariant try_add_item = value.toInt(&success);
                if (success)
                {
                    exampleData[index.row()][index.column()] = try_add_item;
                }else
                {
                    return false;
                }
                break;
            }
            case 11:
            {
                bool success = false;
                QVariant try_add_item = value.toInt(&success);
                if (success)
                {
                    exampleData[index.row()][index.column()] = try_add_item;
                }else
                {
                    return false;
                }
                break;
            }
            case 12:
            {
                QVariant try_add_item = value.toString();
                exampleData[index.row()][index.column()] = try_add_item;
                break;
            }
            case 13:
            {
                bool success = false;
                QVariant try_add_item = value.toInt(&success);
                if (success)
                {
                    exampleData[index.row()][index.column()] = try_add_item;
                }else
                {
                    return false;
                }
                break;
            }
            case 14:
            {
                QVariant try_add_item = value.toString();
                exampleData[index.row()][index.column()] = try_add_item;
                break;
            }
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ExampleModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}


void ExampleModel::appendRow(QList<QVariant> newRow)
{
    bool columnFlag = false;
    if (exampleData.isEmpty())
    {
        columnFlag = true;
        beginInsertColumns(QModelIndex(), 0, newRow.size());
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    //exampleData.append(newRow);
    exampleData.push_front(newRow);
    endInsertRows();
    
    if (columnFlag)
    {
        endInsertColumns();
    }
    
}

bool ExampleModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    if (exampleData.size() == 0)
    {
        return false;
    }
    beginInsertRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row)
    {
        QList<QVariant> emptyRow;
        for (int j = 0; j < exampleData[0].size(); j++)
        {
            emptyRow.append("");
            //exampleData.insert(position, "");
        }
        exampleData.insert(position, emptyRow);
    }

    endInsertRows();
    return true;
}

bool ExampleModel::removeRows(int position, int rows, const QModelIndex &index)
{
    if (exampleData.size() == 0) { return false; }
    //beginRemoveRows(QModelIndex(), position, rows);
    if ( rows == 1) { exampleData.removeAt(position); }
    else
    {
        for (int row = 0; row < rows; ++row)
        {
            exampleData.removeAt(position);
        }
    }
    //endRemoveRows();
    return true;
}
