#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QRect"
#include "QDesktopWidget"
#include "QMessageBox"
#include "QInputDialog"
#include "QDir"

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
    // Set the score to 0 if nothing was loaded
    score = 0;
    // Set the total score to 0 if nothing was loaded
    totalScore = 0;
    fileName = "";
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_newPushButton_clicked() {
    ui->scoreGoesHere->setText(QString::number(score));
    ui->totalScoreGoesHere->setText(QString::number(totalScore));
    // When the user selects new, ask for a project  in a QInputDialog
    bool ok;
    QString text = QInputDialog::getText(this, tr("Project Name"),
                                         tr("Project Name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    // If the user actually enters something, then proceed. Else do nothing
    if(ok && !text.isEmpty()) {
        fileName = text;
        ui->projectNameGoesHere->setText(text);
        // Then ask if they want a tutorial
        QMessageBox::StandardButton tutorialChoice;
        tutorialChoice = QMessageBox::question(this, "Tutorial", "Would you like a tutorial?"),
                                                            QMessageBox::Yes|QMessageBox::No;
        if(tutorialChoice == QMessageBox::Yes) {
            startTutorial = true;
            // If a new project is selected, do this
            // Set the list widget item 0 (the example) to be center aligned
            ui->listWidget->addItem("I'm an example! Try me!");
            totalScore++;
            ui->listWidget->addItem("I'm another example! Cross me out!");
            totalScore++;
            ui->totalScoreGoesHere->setText(QString::number(totalScore));
            for(int i = 0; i < 2; i++) {
                ui->listWidget->item(i)->setTextAlignment(Qt::AlignHCenter);
            }
        } else {
            startTutorial = false;
        }
        // Then set the current index to 1 and the save button to true
        ui->stackedWidget->setCurrentIndex(1);
        ui->actionSave->setEnabled(true);
        startingFresh = false;
    }
}

void MainWindow::on_actionExitMenu_triggered() {
    // If the user selects quit then end the program
    QApplication::quit();
}

void MainWindow::on_actionNewMenu_triggered() {
    ui->scoreGoesHere->setText(QString::number(score));
    ui->totalScoreGoesHere->setText(QString::number(totalScore));
    // When the user selects new, ask for a project  in a QInputDialog
    bool ok;
    QString text = QInputDialog::getText(this, tr("Project Name"),
                                         tr("Project Name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    // If the user actually enters something, then proceed. Else do nothing
    if(ok && !text.isEmpty()) {
        ui->projectNameGoesHere->setText(text);
        // Then ask if they want a tutorial
        QMessageBox::StandardButton tutorialChoice;
        tutorialChoice = QMessageBox::question(this, "Tutorial", "Would you like a tutorial?"),
                                                            QMessageBox::Yes|QMessageBox::No;
        if(tutorialChoice == QMessageBox::Yes) {
            startTutorial = true;
            // If a new project is selected, do this
            // Set the list widget item 0 (the example) to be center aligned
            ui->listWidget->addItem("I'm an example! Try me!");
            totalScore++;
            ui->listWidget->addItem("I'm another example! Cross me out!");
            totalScore++;
            ui->totalScoreGoesHere->setText(QString::number(totalScore));
            for(int i = 0; i < 2; i++) {
                ui->listWidget->item(i)->setTextAlignment(Qt::AlignHCenter);
            }
        } else {
            startTutorial = false;
        }
        // Then set the current index to 1 and the save button to true
        ui->stackedWidget->setCurrentIndex(1);
        ui->actionSave->setEnabled(true);
        startingFresh = false;
    }
}

void MainWindow::on_deleteButton_clicked()
{
    // When the delete button is clicked, check if it's the only item available
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
        totalScore--;
        ui->totalScoreGoesHere->setText(QString::number(totalScore));
        score--;
        ui->scoreGoesHere->setText(QString::number(score));
    }
    //qDeleteAll(ui->listWidget->selectedItems());
}

void MainWindow::on_newTaskButton_clicked()
{
    // When the new task button is clicked, add a task
    bool ok;
    QString newTask = QInputDialog::getText(this, tr("New Task Name"),
                                         tr("Task Name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    // If the user enters a new task, add it and center it and then increment the total score
    if(ok && !newTask.isEmpty()) {
        ui->listWidget->addItem(newTask);
        ui->listWidget->item(ui->listWidget->count()-1)->setTextAlignment(Qt::AlignHCenter);
        totalScore++;
        ui->totalScoreGoesHere->setText(QString::number(totalScore));
    }
}

void MainWindow::on_listWidget_itemPressed(QListWidgetItem *item)
{
    // Check if an item is already striked. If not, set it and add to the score
    if(!item->font().strikeOut()) {
        QFont font;
        font.setStrikeOut(true);
        item->setFont(font);
        score++;
        ui->scoreGoesHere->setText(QString::number(score));
    }
}

void MainWindow::on_actionSave_triggered()
{

    // When the user hits save we need to save the information
    for(int i = 0; i < ui->listWidget->count(); i++) {
        listOfItems.append(ui->listWidget->item(i)->text());
    }
    file->saveFile(fileName, listOfItems);
}
