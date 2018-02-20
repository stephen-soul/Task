#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

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

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_itemSelectionChanged();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;
    bool tutorialComplete;
};

#endif // MAINWINDOW_H
