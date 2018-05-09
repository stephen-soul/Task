#ifndef FILEIO_H
#define FILEIO_H
#include <QVector>
#include <QString>
#include <QStringList>

class FileIO {
public:
    FileIO();
    ~FileIO();
    void saveFile(QString fileName, QVector<QString> items);
    QVector<QString> loadFile();
};

#endif // FILEIO_H
