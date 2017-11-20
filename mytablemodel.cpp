#include "mytablemodel.h"

MyTableModel::MyTableModel(QObject* parent): QAbstractTableModel(parent)
{
}

QVariant MyTableModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();
  else
    return (role == Qt::DisplayRole || role == Qt::EditRole) ? storedData.value(index) : QVariant();
}

bool MyTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  if (role == Qt::EditRole)
  {
    storedData[index] = value.toString();
    emit dataChanged(index, index);

    return true;
  }
  else
    return false;
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();
  else
    return (orientation == Qt::Horizontal) ? headers[section] : QString::number(section + 1);
}

bool MyTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role)
{
  if (role == Qt::EditRole)
  {
    headers[section] = value.toString();
    columns = section + 1;
    emit headerDataChanged(orientation, section, section);

    return true;
  }
  else
    return false;
}

Qt::ItemFlags MyTableModel::flags(const QModelIndex& index) const
{
  Qt::ItemFlags flag = QAbstractTableModel::flags(index);

  return index.isValid() ? (flag | Qt::ItemIsSelectable) : flag;
}

void MyTableModel::clear()
{
  rows = 0;
  columns = 0;
  storedData.clear();
  headers.clear();
}

bool MyTableModel::insertRows(int row, int count, const QModelIndex& parent)
{
  beginInsertRows(parent, row, row + count - 1);
  rows += 1;
  endInsertRows();

  return true;
}
