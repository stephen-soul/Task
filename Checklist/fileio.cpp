#include "fileio.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QObject>

FileIO::FileIO() {

}

FileIO::~FileIO() {

}

void FileIO::saveFile(QString fileName, QVector<QString> items) {
    // Open the file dialog to let the user pick a name and save location
    QString filter = "Text File (*.txt)";
    QString name = QFileDialog::getSaveFileName(0,
                                                "Save file...",
                                                fileName+".txt",
                                                filter);
    QFile file(name);
    // Then open the file in the specified location and save it
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

QVector<QString> FileIO::loadFile() {
    // Add a filter and let the user open the file
    QString filter = "Text File (*.txt)";
    QString filename = QFileDialog::getOpenFileName(0,
                                                    "Open File...",
                                                    "",
                                                    filter);
    QVector<QString> fileContents;
    QFile file(filename);
    QFileInfo fileInfo(file.fileName());
    QString returnedName(fileInfo.fileName());
    fileContents.append(returnedName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream textstream(&file);
        while(!textstream.atEnd()) {
            fileContents.append(textstream.readLine());
        }
        file.close();
    }
    return fileContents;
}
