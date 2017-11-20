#include <QFile>
#include <QStringList>

#include "mainengine.h"
#include "csvstream.h"

MainEngine::MainEngine(QObject* parent): QObject(parent)
{
}

void MainEngine::fillSqlModel(const QString& name)
{
  if (!(name == "")) // чтобы не было реакции при очистке через makeDisabled()
  {
    QSqlQuery query(db);
    query.exec("SELECT * FROM " + name + ";");
    model.setQuery(query);
  }
}

void MainEngine::clear()
{
  model.clear();      // чистим модель и, следовательно, представление
  csvModel.clear();

  if (db.isOpen())    // если в прошлый Open открывалась база
    db.close();

  isOpen = false;     // сбрасываем состояние
}

void MainEngine::openSql(const QString& name)
{
  isOpen = true;
  currentFile = QFileInfo(name);

  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(name);
  db.open();

  emit sendListOfTables(db.tables());
}

void MainEngine::openCsv(const QString& name)
{
  isOpen = true;
  currentFile = QFileInfo(name);

  CsvStream csv(name, this);
  csv.open(QIODevice::ReadOnly);

  QStringList line = csv.readLine(); // в первом случае - заголовки столбцов, во втором - поля записи
  csvModel.insertColumns(0, line.size());

  for (int j = 0; j < line.size(); ++j)
    csvModel.setHeaderData(j, Qt::Horizontal, line.at(j));

  int rows = 0;
  while (!csv.atEnd()) // если в файле была только строка шапки, то сюда даже не зайдем
  {
    line = csv.readLine();
    csvModel.insertRows(rows, 1);

    for (int j = 0; j < line.size(); ++j)
      csvModel.setData(csvModel.index(rows, j), line.at(j));

    ++rows;
  }

  csv.close();
}

void MainEngine::convertToCsv(const QString& name)
{
  CsvStream csv(name, this);
  csv.open(QIODevice::WriteOnly | QIODevice::Truncate); // транкейт

  QStringList lstLine;

  for (int j = 0; j < model.columnCount(); ++j)
    lstLine.append(model.headerData(j, Qt::Horizontal).toString());

  csv.writeLine(lstLine);

  for (int i = 0; i < model.rowCount(); ++i)
  {
    lstLine.clear();

    for (int j = 0; j < model.columnCount(); ++j)
      lstLine.append(model.data(model.index(i, j)).toString());

    csv.writeLine(lstLine);
  }

  csv.close();
}






