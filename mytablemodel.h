#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QtWidgets>

/**
 * @brief This class is used for storing data from csv-file. Actually, it is a ordinary model, which
 * stores QStrings.
 */
class MyTableModel: public QAbstractTableModel
{
  private:
    int rows = 0;
    int columns = 0;

    QHash<QModelIndex, QString> storedData;
    QHash<int, QString> headers;

  public:

    /**
     * @brief Creates a model with a given parent.
     * @param parent: parent object.
     */
    explicit MyTableModel(QObject* parent = 0);

    /**
     * @brief Returns the amount of rows in the model.
     */
    int rowCount(const QModelIndex& = QModelIndex()) const
    {
      return rows;
    }

    /**
     * @brief Returns the amount of columns in the model.
     */
    int columnCount(const QModelIndex& = QModelIndex()) const
    {
      return columns;
    }

    /**
     * @brief Returns the data from the cell with a given index.
     * @param index: QModelIndex, specifying the cell of the table.
     * @param role: always DisplayRole.
     * @return QVariant, which, actually, is a QString.
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;   // геттер данных

    /**
     * @brief Writes data into the cell with a given index.
     * @param index: QModelIndex, specifying the cell of the table.
     * @param value: value to be written in the form of QVariant.
     * @param role: always EditRole.
     * @return Whether the operation was successful.
     */
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole); //сеттер одной ячейки

    /**
     * @brief Returns the caption of some row or column.
     * @param section: serial number of the row/column.
     * @param orientation: Horizontal/Vertical.
     * @param role: always DisplayRole.
     * @return QVariant, which, actually, is a QString.
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    /**
     * @brief Gives a caption to the row or column with a given role.
     * @param section: serial number of the row/column.
     * @param orientation: Horizontal/Vertical.
     * @param value: value to be written in the form of QVariant.
     * @param role: always EditRole.
     * @return Whether the operation was successful.
     */
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole);

    /**
     * @brief Frees all occupied resources.
     */
    void clear();

    /**
     * @brief Returns roles of the cell, specified by its index.
     * @param index: QModelIndex of the required cell.
     * @return Standart ItemFlags.
     */
    Qt::ItemFlags flags(const QModelIndex& index) const;

    /**
     * @brief Inserts into model count rows after the given one.
     * @param row: serial number of the row, which new rows will be added after.
     * @param count: amount of rows to be added.
     * @param parent: always emty model index.
     * @return Whether the operation was successful.
     */
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
};

#endif // MYTABLEMODEL_H
