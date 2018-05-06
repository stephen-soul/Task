#include "fileio.h"
#include <QFile>
#include <QDir>
#include <QDebug>

FileIO::FileIO() {

}

FileIO::~FileIO() {

}

void FileIO::saveFile(QString fileName, QVector<QString> items) {
    QFile file(fileName + ".txt");
    file.remove();
    // Open the file, write the contents of the array to the file and then close
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QTextStream textStream(&file);
        for (int i = 0; i < items.count(); i++) {
            textStream << items.at(i) << "\n";
        }
        file.close();
    } else {
        qDebug() << "Could not open the file";
        return;
    }
}
