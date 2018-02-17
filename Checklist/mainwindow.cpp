#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    // Set fixed size of the main menu to 750x500
    this->setFixedSize(QSize(750, 500));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionExitMenu_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNew_triggered()
{
    if(ui->stackedWidget->currentIndex() != 1)
        ui->stackedWidget->setCurrentIndex(1);
}
