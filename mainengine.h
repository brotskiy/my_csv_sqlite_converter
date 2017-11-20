#ifndef MAINENGINE_H
#define MAINENGINE_H

#include <QtSql>
#include <QFileInfo>
#include <QString>

#include "mytablemodel.h"
#include "csvstream.h"

/**
 * @brief This class contains all functionality, ensuring to interaction with databases and files
 * and their representation in the application.
 */
class MainEngine: public QObject
{
    Q_OBJECT

  private:
    bool isOpen = false;

    QFileInfo currentFile;
    QSqlDatabase db;          // соединение с бд
    QSqlQueryModel model;
    MyTableModel csvModel;

  public:
    /**
     * @brief Creates a object with given parent.
     * @param parent: parent object.
     */
    explicit MainEngine(QObject* parent = 0); // explicit

    /**
     * @brief Returns constant link to the model, storing csv-file representation in the
     * application.
     */
    const MyTableModel& getConstLinkCsvModel()
    {
      return csvModel;
    }

    /**
     * @brief Returns pointer to the model, storing csv-file representation in the
     * application.
     */
    MyTableModel* getCsvModel()
    {
      return &csvModel;
    }

    /**
     * @brief Returns pointer to the model, storing database representation in the
     * application.
     */
    QSqlQueryModel* getSqlModel()
    {
      return &model;
    }

    /**
     * @brief Returns information about currently opened file.
     */
    const QFileInfo& getCurrentFile() const
    {
      return currentFile;
    }

    /**
     * @brief Checks, whether application stores some data.
     */
    bool isOpenNow() const
    {
      return isOpen;
    }

    /**
     * @brief Frees any occupied resources.
     */
    void clear();

    /**
     * @brief Connects to the database and emits signal with the list of it tables.
     * @param name: absolute path to the database.
     */
    void openSql(const QString& name);

    /**
     * @brief Connects to the csv-file and gets all data from it.
     * @param name: absolute path to the csv-file.
     */
    void openCsv(const QString& name);

    /**
     * @brief Creates or rewrites a csv-file with the given absolute path.
     * @param name: absolute path to the file.
     */
    void convertToCsv(const QString& name);

  public slots:

    /**
     * @brief Gets all data from the given table of the currently opened database.
     * @param name: name of table.
     */
    void fillSqlModel(const QString& name);

  signals:

    /**
     * @brief Is emitted on the database connecting and contains list of tables.
     */
    void sendListOfTables(const QStringList&);
};

#endif // MAINENGINE_H
