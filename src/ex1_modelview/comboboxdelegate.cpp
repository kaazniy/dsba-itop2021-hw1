#include "comboboxdelegate.h"


ComboBoxDelegate::ComboBoxDelegate (QObject *parent, const std::set<QString> &options) : QStyledItemDelegate (parent), countries (options) {}



QWidget *ComboBoxDelegate::createEditor (QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *cb = new QComboBox (parent);
    for (auto i : countries) {cb->addItem(i);}
    return cb;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *> (editor);
    if (!cb)
        return;
    auto current_value = index.data (Qt::EditRole).toString ();
    int i = cb->findText (current_value);
    if (i >= 0)
        cb->setCurrentIndex (i);
}


void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *cb = qobject_cast<QComboBox *> (editor);
  model->setData (index, cb->currentText (), Qt::EditRole);
}
