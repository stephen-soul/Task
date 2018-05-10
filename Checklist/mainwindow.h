#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QStringList>
#include "fileio.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
private slots:
    void on_newPushButton_clicked();

    void on_actionExitMenu_triggered();

    void on_actionNewMenu_triggered();

    void on_deleteButton_clicked();

    void on_listWidget_itemPressed(QListWidgetItem *item);

    void on_newTaskButton_clicked();

    void on_actionSave_triggered();

    void on_actionMinified_triggered();

    void on_actionFull_View_triggered();

    void on_actionLoad_triggered();

    void on_loadPushButton_clicked();

private:
    Ui::MainWindow *ui;

    FileIO *file;

    int score;

    int totalScore;

    QString fileName;

    QVector<QString> listOfItems;

    void newStart();

    void load();

    void resizeScreen(int height, int width);

    bool checkedForSave;

public:
    void checkUnsaved();
};

#endif // MAINWINDOW_H
