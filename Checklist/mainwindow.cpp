#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QRect"
#include "QDesktopWidget"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QRect position = frameGeometry();
      position.moveCenter(QDesktopWidget().availableGeometry().center());
      move(position.topLeft());
    ui->stackedWidget->setCurrentIndex(0);
    // Set fixed size of the main menu to 750x500
    this->setFixedSize(QSize(750, 500));
    // Start with the save button disabled because you can't save on the main menu
    ui->actionSave->setEnabled(false);
    ui->listWidget->clearFocus();
    ui->listWidget->item(1)->setTextAlignment(Qt::AlignHCenter);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_newPushButton_clicked() {
    // When the user selects new, set the current index to 1 and the save button to true
    ui->stackedWidget->setCurrentIndex(1);
    ui->actionSave->setEnabled(true);
}

void MainWindow::on_actionExitMenu_triggered() {
    // If the user selects quit then end the program
    QApplication::quit();
}

void MainWindow::on_actionNewMenu_triggered() {
    // If the new button is pressed, check if the user is not on the 'checklist' page. If they are not change it and enable the save button
    if(ui->stackedWidget->currentIndex() != 1) {
        ui->stackedWidget->setCurrentIndex(1);
        ui->actionSave->setEnabled(true);
    }
    // What I intend to add here is an option to 'delete' the current progress (or save) and restart
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    // On the current row change, get the current row and set the font to strike out like you would an actual checklist
    QFont font;
    font.setStrikeOut(true);
    ui->listWidget->item(currentRow)->setFont(font);
}
