#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QRect"
#include "QDesktopWidget"
#include "QMessageBox"

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
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_newPushButton_clicked() {
    // When the user selects new, ask if they want a tutorial
    QMessageBox::StandardButton tutorialChoice;
    tutorialChoice = QMessageBox::question(this, "Tutorial", "Would you like a tutorial?"),
                                                        QMessageBox::Yes|QMessageBox::No;
    if(tutorialChoice == QMessageBox::Yes) {
        startTutorial = true;
        // If a new project is selected, do this
        // Set the list widget item 0 (the example) to be center aligned
        ui->listWidget->addItem("I'm an example! Try me!");
        ui->listWidget->addItem("I'm another example! Cross me out!");
        for(int i = 0; i < 2; i++) {
            ui->listWidget->item(i)->setTextAlignment(Qt::AlignHCenter);
        }
    } else {
        startTutorial = false;
    }
    // Then set the current index to 1 and the save button to true
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
        QMessageBox::StandardButton tutorialChoice;
        tutorialChoice = QMessageBox::question(this, "Tutorial", "Would you like a tutorial?"),
                                                            QMessageBox::Yes|QMessageBox::No;
        if(tutorialChoice == QMessageBox::Yes) {
            startTutorial = true;
            // If a new project is selected, do this
            // Set the list widget item 0 (the example) to be center aligned
            ui->listWidget->addItem("I'm an example! Try me!");
            ui->listWidget->addItem("I'm another example! Cross me out!");
            for(int i = 0; i < 2; i++) {
                ui->listWidget->item(i)->setTextAlignment(Qt::AlignHCenter);
            }
        } else {
            startTutorial = false;
        }
        ui->stackedWidget->setCurrentIndex(1);
        ui->actionSave->setEnabled(true);
    }
    // What I intend to add here is an option to 'delete' the current progress (or save) and restart
}

void MainWindow::on_deleteButton_clicked()
{
    // When the delete button is clicked, check if it's the only item available
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
    //qDeleteAll(ui->listWidget->selectedItems());
}

void MainWindow::on_listWidget_itemPressed(QListWidgetItem *item)
{
    QFont font;
    font.setStrikeOut(true);
    item->setFont(font);
}
