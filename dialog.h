#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets>
#include <QtSql>
#include <QList>
#include <QString>

#include "mytablemodel.h"

/**
 * @brief It is a convenient dialog window, where you can choose a SQLite database and
 * specife a table in it, which you want your csv-file to be converted to.
 *
 * - If there is no such database, then it will be created.
 * - If database contains such table, then it will be overwrited.
 * - If there are no tables in the database, then current csv-file name will be suggested.
 */
class Dialog : public QDialog
{
    Q_OBJECT

  private:
    QSqlDatabase db;
    QStringList lst;
    QStringList columnTypes;

    QGroupBox* gbx1;
    QGroupBox* gbx2;
    QToolButton* cmd;
    QLineEdit* edit;
    QComboBox* combo;
    QDialogButtonBox* btns;

    QString whatTypeOfAttribute(const QString& str) const;
    void fillFromHeader(const MyTableModel& model);
    void fillFromData(const MyTableModel& model);

  public:

    /**
     * @brief Creates a dialog window with given parent.
     * @param parent: parent of this window.
     */
    explicit Dialog(QWidget* parent = 0); // explicit

  private slots:

    /**
     * @brief Creates a native explorer window, where you can choose the database,
     * which your csv-file will be saved into.
     */
    void aqcuireDbName();
    void actWithDb(const QString& name);
    void convertToSQL();
};

#endif // DIALOG_H
