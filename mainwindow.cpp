#include <QFileDialog>
#include "mainwindow.h"

void MainWindow::createMenuBar(MainWindow* parent) // OK
{
  menuBar = new QMenuBar(parent);
  QMenu* menuFile = new QMenu("File", menuBar);
  QMenu* menuConvert = new QMenu("Convert to...", menuFile);

  menuBar->addAction(menuFile->menuAction());

  menuFile->addAction("Open");                      // 0
  menuFile->addAction(menuConvert->menuAction());   // 1
  menuFile->addSeparator();                         // 2
  menuFile->addAction("Exit");                      // 3

  menuConvert->addAction("CSV");                    // 1.0
  menuConvert->addAction("SQLite");                 // 1.1

  menuBar->actions().at(0)->menu()->actions().at(1)->setEnabled(false);
  menuBar->actions().at(0)->menu()->actions().at(1)->menu()->actions().at(0)->setEnabled(false);
  menuBar->actions().at(0)->menu()->actions().at(1)->menu()->actions().at(1)->setEnabled(false);
}

void MainWindow::createToolBar(MainWindow* parent) // OK
{
  toolBar = new QToolBar(parent);
  tablesBox = new QComboBox(toolBar);

  toolBar->setMovable(false);
  toolBar->addWidget(tablesBox);
  tablesBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
  tablesBox->setEnabled(false);
}

void MainWindow::createConnections()
{
  QAction* button = menuBar->actions().at(0)->menu()->actions().at(0);   // open
  connect(button, SIGNAL(triggered(bool)), this, SLOT(slotOpen()));

  button = menuBar->actions().at(0)->menu()->actions().at(1)->menu()->actions().at(0); // to CSV
  connect(button, SIGNAL(triggered(bool)), this, SLOT(convertToCsv()));

  button = menuBar->actions().at(0)->menu()->actions().at(1)->menu()->actions().at(1); // to SQLite
  connect(button, SIGNAL(triggered(bool)), this, SLOT(convertToSql()));

  button = menuBar->actions().at(0)->menu()->actions().at(3);           // exit application
  connect(button, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

  // заполнение модели соотвествующей таблицей    OK
  connect(tablesBox, SIGNAL(currentIndexChanged(const QString&)), &guts, SLOT(fillSqlModel(const QString&)));

  // заполнение tablexBox списком таблиц базы   ОК
  connect(&guts, SIGNAL(sendListOfTables(const QStringList&)), this, SLOT(slotFillBox(const QStringList&)));
}

void MainWindow::makeEnabled(const QString& fileType) // OK
{
  menuBar->actions().at(0)->menu()->actions().at(1)->setEnabled(true);  // convert to...

  if (fileType == "sql")
  {
    menuBar->actions().at(0)->menu()->actions().at(1)->menu()->actions().at(0)->setEnabled(true); // to csv
    tablesBox->setEnabled(true);
  }
  else
    menuBar->actions().at(0)->menu()->actions().at(1)->menu()->actions().at(1)->setEnabled(true); // to sql
}

void MainWindow::makeDisabled() // OK
{
  menuBar->actions().at(0)->menu()->actions().at(1)->setEnabled(false);  // convert to...
  menuBar->actions().at(0)->menu()->actions().at(1)->menu()->actions().at(0)->setEnabled(false); // to csv
  menuBar->actions().at(0)->menu()->actions().at(1)->menu()->actions().at(1)->setEnabled(false); // to sql
  tablesBox->clear();
  tablesBox->setEnabled(false);
}

void MainWindow::slotOpen() // OK??
{
  QString name = QFileDialog::getOpenFileName(this, "Explorer", "", "SQLite files(*.sqlite *.db);;CSV files(*.csv)");

  if (name != "")         // если реально выбрали файл, а не нажали Cancel
  {
    if (guts.isOpenNow())           // если нажали Open 2 раза подряд
    {
      makeDisabled();     // приводим видимость виджетов в исходное "пустое" состояние
      guts.clear();
    }

    if (name.endsWith(".sqlite") || name.endsWith(".db"))
    {
      makeEnabled("sql");
      view->setModel(guts.getSqlModel());
      guts.openSql(name);
    }
    else if (name.endsWith(".csv"))
    {
      makeEnabled("csv");
      view->setModel(guts.getCsvModel());
      guts.openCsv(name);
    }
  }
}

void MainWindow::slotFillBox(const QStringList& tables) // OK??
{
  tablesBox->addItems(tables);
}

void MainWindow::convertToSql() // OK
{
  dialog = new Dialog(this);
  dialog->exec();
}

void MainWindow::convertToCsv()
{
  QString dirFile = whatCurrentFile().absolutePath() + QDir::separator() + tablesBox->currentText();
  QString name = QFileDialog::getSaveFileName(this, "Explorer", dirFile, "CSV files(*.csv)");

  if (name != "")
    guts.convertToCsv(name);
}

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) // OK
{
  resize(1024, 768);

  createMenuBar(this);
  setMenuBar(menuBar);

  createToolBar(this);
  addToolBar(Qt::TopToolBarArea, toolBar);

  createConnections();

  view = new QTableView(this);
  setCentralWidget(view);
}


