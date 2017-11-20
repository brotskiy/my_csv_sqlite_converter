#include "csvstream.h"

CsvStream::CsvStream(const QString& name, QObject* parent): file(name), QObject(parent)
{
}

QStringList CsvStream::readLine()
{
  QString strRecordLine = createStrRecordLine();
  QStringList lstRecordLine = createLstRecordLine(strRecordLine);

  return lstRecordLine;
}

QString CsvStream::createStrRecordLine() // возвращает string с одной записью из файла
{
  int quoteCount = 1;                    // количество " в строке. 1 - чтобы зайти в цикл
  QString strRecordLine;                 // строка таблицы

  while (quoteCount % 2 != 0)            // кавычек нечетное кол-во (случай: xxx,"x \n x",xxx)
  {
    QString temp(file.readLine());       // считывает до первого \n
    temp.remove("\r\n");                 // удаляем символ перехода на новую строку (в винде \r\n)

    if (temp.at(temp.size() - 1) == '\n') // если символ был не \r\n, а просто \n, то удаляем его
      temp.chop(1);

    quoteCount = temp.count('\"');       // сколько раз встретилась "

    if (strRecordLine.isEmpty())         // агрегируем слова в одну строку-запись
      strRecordLine = temp;
    else
      strRecordLine += '\n' + temp;
  }

  return strRecordLine;
}

QStringList CsvStream::createLstRecordLine(const QString& strRecordLine) // возвращает list c записью, разбитой по полям
{
  QStringList lstRecordLine = strRecordLine.split(',');

  QStringList::iterator cur = lstRecordLine.begin();

  while (cur != lstRecordLine.end())      // пока не пройдем весь список
  {
    QString temp = *cur;                  // получили текущее слово
    int quoteCount = temp.count('\"');        // сколько раз встретилась "

    if (quoteCount % 2 != 0)              // кавычки не закрыты
    {
      (*cur) = temp + ',' + (*(cur + 1)); // сливаем текущее слово со следующим
      lstRecordLine.erase(cur + 1);       // удаляем следующее, так как оно уже входит в состав текущего
    }
    else
    {
      (*cur) = deleteExtraQuotes(*cur);   // если кавычки закрыты, то обрабатываем текущее слово
      ++cur;                              // и переходим на следующее
    }
  }

  return lstRecordLine;
}

QString CsvStream::deleteExtraQuotes(const QString& word)
{
  QString temp;
  temp.reserve(word.size());

  QString::const_iterator first;
  QString::const_iterator last;

  if ((word.at(0) == '\"') && (word.at(word.size() - 1) == '\"'))
  {
    first = word.begin() + 1;
    last = first + word.size() - 2;
  }
  else
  {
    first = word.begin();
    last = word.end();
  }

  QString::const_iterator cur = first;
  while (cur != last)                         // идем по буквам слова
    if ((*cur == '\"') && (*(cur + 1) == '\"')) // т.к. символ " представляется в виде ""
    {
      temp.append(cur->toLatin1());
      cur += 2;
    }
    else
    {
      temp.append(cur->toLatin1());
      ++cur;
    }

  return temp;
}

QString CsvStream::prepareWordForCsv(const QString& word)
{
  QString temp;
  bool flagSymbols = false;

  if (word.contains(QRegExp("[\\\",\\\n]")))   // в строке есть особые символы
  {
    temp.append('\"');
    flagSymbols = true;
  }

  for (int i = 0; i < word.size(); ++i)
  {
    temp.append(word.at(i));

    if (word.at(i) == '\"')               // попали на кавычку
      temp.append(word.at(i));            // дублируем ее
  }

  if (flagSymbols)
    temp.append('\"');

  return temp;
}

void CsvStream::writeLine(const QStringList& lstLine)
{
  for (int i = 0; i < lstLine.size(); ++i)
  {
    file.write(prepareWordForCsv(lstLine.at(i)).toLatin1());

    if (i != lstLine.size() - 1)
      file.putChar(',');
  }

  file.putChar('\n');
}
