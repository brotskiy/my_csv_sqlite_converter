#ifndef CSVSTREAM_H
#define CSVSTREAM_H

#include <QDebug>

#include <QString>
#include <QStringList>
#include <QFile>

/**
* @brief This class handles the interaction with csv-files. It gives the opportunity to connect
* to the file and read/write rows.
*/
class CsvStream: public QObject
{
    Q_OBJECT

  private:
    QFile file; // ? какой-то варнинг, хотя по книге все нормально

    QString createStrRecordLine(); // !!!!!!!!!!!!!!!!!!!!!!!!!!!
    QStringList createLstRecordLine(const QString& strRecordLine); // OK
    QString deleteExtraQuotes(const QString& word); // OK

    QString prepareWordForCsv(const QString& word); // OK

  public:

    /**
     * @brief Creates a csv-file object with given path and parent.
     * @param name: absolute path to the file.
     * @param parent: parent of this object.
     */
    CsvStream(const QString& name, QObject* parent = 0);

    /**
     * @brief Opens a file with given flags.
     * @param flags: standart OpenMode flags.
     */
    void open(QFile::OpenMode flags)
    {
      file.open(flags);
    }

    /**
     * @brief Closes the file, freeing occupied resources.
     */
    void close()
    {
      file.close();
    }

    /**
     * @brief Checks, if current position is the end of file.
     */
    bool atEnd()
    {
      return file.atEnd();
    }

    /**
     * @brief Reads one line from file and returns the fields of record as list.
     * @return QStringList with fields of a record.
     */
    QStringList readLine();

    /**
     * @brief Write one line, represented by list of fields, into csv-file.
     * @param lstline: list, containig fields of a record.
     */
    void writeLine(const QStringList& lstLine);
};

#endif // CSVSTREAM_H
