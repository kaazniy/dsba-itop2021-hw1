#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H
#include <QStyledItemDelegate>
#include <QComboBox>
#include <set>
#include <QSet>


/// подправить название
class ComboBoxDelegate  : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ComboBoxDelegate (QObject *parent, const std::set<QString> &options);
    QWidget *createEditor (QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    std::set<QString> countries;

};

#endif // COMBOBOXDELEGATE_H
