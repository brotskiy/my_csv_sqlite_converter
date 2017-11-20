#include <QtTest>
#include <QString>
#include <QStringList>

#define private public // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "../csvstream.h"

class Test_CsvStream : public QObject
{
    Q_OBJECT

  public:
    Test_CsvStream();

  private slots:
    void createLstRecordLine();
    void deleteExtraQuotes();

    void prepareWordForCsv();
};

Test_CsvStream::Test_CsvStream()
{
}

void Test_CsvStream::createLstRecordLine()
{
  CsvStream csv("abc.csv");

  QString row("\"\",\",ab,,\"\",c\"\", ,,\",");
  QStringList row_r;
  row_r << "" << ",ab,,\",c\", ,," << "";

  QCOMPARE(csv.createLstRecordLine(row), row_r);
}

void Test_CsvStream::deleteExtraQuotes()
{
  CsvStream csv("abc.csv");

  QString word1("\"one, two, three,\"\"\"\",\"\"\"\"\"");
  QString word1_r("one, two, three,\"\",\"\"");

  QString word2("\"\"");
  QString word2_r("");

  QCOMPARE(csv.deleteExtraQuotes(word1), word1_r);
  QCOMPARE(csv.deleteExtraQuotes(word2), word2_r);
  QCOMPARE(csv.deleteExtraQuotes(word2_r), word2_r);
}

void Test_CsvStream::prepareWordForCsv()
{
  CsvStream csv("abc.csv");

  QString word1("");

  QString word2("\",ab ,,\"\",\",");
  QString word2_r("\"\"\",ab ,,\"\"\"\",\"\",\"");

  QCOMPARE(csv.prepareWordForCsv(word1), word1);
  QCOMPARE(csv.prepareWordForCsv(word2), word2_r);
}

QTEST_APPLESS_MAIN(Test_CsvStream)

#include "tst_test_csvstream.moc"
