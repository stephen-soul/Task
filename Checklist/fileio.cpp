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
    // If the file does not exist then output it to the console
    if(!file.exists()) {
        qDebug() << file.fileName() << " does not exist.";
    }
    if(file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream textStream(&file);
        for (int i = 0; i < items.count(); i++) {
            textStream << items.at(i);
        }
    } else {
        qDebug() << "Could not open the file";
        return;
    }
}
