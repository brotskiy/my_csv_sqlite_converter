#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>        //qtableview
#include <QString>

#include "mainengine.h"
#include "dialog.h"

class Dialog;

/**
 * @brief The main window of the application. Contains a table view for viewing csv and SQLite files,
 * menu with open/close/convert options and combobox for choosing database tables.
 */
class MainWindow: public QMainWindow
{
    Q_OBJECT

  private:
    MainEngine guts;

    QMenuBar* menuBar;
    QToolBar* toolBar;
    QTableView* view;
    QComboBox* tablesBox;
    Dialog* dialog;

    void createMenuBar(MainWindow* parent); // OK
    void createToolBar(MainWindow* parent); // OK
    void makeEnabled(const QString& fileType); // OK     fileType: csv либо sql
    void makeDisabled(); // OK
    void createConnections();

  public:

    /**
     * @brief Creates a main window.
     * @param parent: is always 0.
     */
    explicit MainWindow(QWidget* parent = 0); // explicit

    /**
     * @brief Returns the information about currently opened file.
     */
    const QFileInfo& whatCurrentFile()
    {
      return guts.getCurrentFile();
    }

    /**
     * @brief Returns constant link to the model, storing csv-file representation in the
     * application.
     */
    const MyTableModel& getConstCsvModel()
    {
      return guts.getConstLinkCsvModel();
    }

  private slots:
    void slotOpen();                               // открыть проводник
    void slotFillBox(const QStringList& tables);

    void convertToSql();
    void convertToCsv();
};


#endif // MAINWINDOW_H
