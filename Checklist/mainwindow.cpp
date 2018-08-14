#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QRect"
#include "QDesktopWidget"
#include "QMessageBox"
#include "QInputDialog"
#include "QDir"
#include <QCloseEvent>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
    MainWindow::setWindowTitle("Task");
    ui->stackedWidget->setCurrentIndex(0);
    // Set fixed size of the main menu to 600x500
    this->setFixedSize(QSize(370, 430));
    //this->setMinimumSize(600, 500);
    // Set the project name font
    QFontDatabase::addApplicationFont(":/fonts/Lobster-Regular.ttf");
    QFont projectFont = QFont("Lobster", 25, 1);
    ui->projectNameGoesHere->setFont(projectFont);
    // Set the ui font
    QFontDatabase::addApplicationFont(":/fonts/Jua-Regular.ttf");
    QFont uiFont = QFont("Jua", 15, 1);
    ui->scoreLabel->setFont(uiFont);
    ui->scoreGoesHere->setFont(uiFont);
    ui->label_2->setFont(uiFont);
    ui->label_3->setFont(uiFont);
    ui->totalScoreGoesHere->setFont(uiFont);
    // Set the task font
    QFontDatabase::addApplicationFont(":/fonts/Rubik-Regular.ttf");
    QFont taskFont = QFont("Rubik", 12, 1);
    ui->listWidget->setFont(taskFont);
    // Start with the save button disabled because you can't save on the main menu
    ui->actionSave->setEnabled(false);
    ui->actionMinified->setEnabled(false);
    ui->actionFull_View->setEnabled(false);
    score = 0;
    totalScore = 0;
    taskNumber = 0;
    fileName = "";
    checkedForSave = false;
    canDelete = false;
    hasSaved = false;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_newPushButton_clicked() {
    newStart();
}

void MainWindow::on_actionExitMenu_triggered() {
    // If the user selects quit then end the program
    checkUnsaved();
}

void MainWindow::on_actionNewMenu_triggered() {
    newStart();
}

void MainWindow::on_deleteButton_clicked()
{
    if(canDelete) {
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
        canDelete = false;
        taskNumber--;
    }
    //qDeleteAll(ui->listWidget->selectedItems());
}

void MainWindow::on_newTaskButton_clicked()
{
    // When the new task button is clicked, add a task
    taskNumber++;
    bool ok;
    QString newTask = QInputDialog::getText(this, tr("New Task Name"),
                                         tr("Task Name:"), QLineEdit::Normal,
                                         "My Awesome Task #" + QString::number(taskNumber), &ok);
    // If the user enters a new task, add it and center it and then increment the total score
    if(ok && !newTask.isEmpty()) {
        ui->listWidget->addItem(newTask);
        ui->listWidget->item(ui->listWidget->count()-1)->setTextAlignment(Qt::AlignHCenter);
        totalScore++;
        ui->totalScoreGoesHere->setText(QString::number(totalScore));
        listOfItems.append(newTask);
    } else
        taskNumber--;
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
        canDelete = true;
    }
}

void MainWindow::on_actionSave_triggered()
{
    for(int i = 0; i < ui->listWidget->count(); i++) {
        if(ui->listWidget->item(i)->font().strikeOut()) {
            listOfItems.append(ui->listWidget->item(i)->text() + " - DONE");
        } else {
            listOfItems.append(ui->listWidget->item(i)->text());
        }
    }
    file->saveFile(fileName, listOfItems);
    listOfItems.clear();
    checkedForSave = true;
}

void MainWindow::on_actionMinified_triggered() {
    resizeScreen(370, 430);
}

void MainWindow::on_actionFull_View_triggered() {
    resizeScreen(600, 430);
}

void MainWindow::on_actionLoad_triggered() {
    load();
    checkedForSave = false;
}

void MainWindow::on_loadPushButton_clicked()
{
    load();
    checkedForSave = false;
}

void MainWindow::newStart() {
    ui->scoreGoesHere->setText(QString::number(score));
    ui->totalScoreGoesHere->setText(QString::number(totalScore));
    // When the user selects new, ask for a project name in a QInputDialog
    bool ok;
    QString text = QInputDialog::getText(this, tr("Project Name"),
                                         tr("Project Name:"), QLineEdit::Normal,
                                         "My Awesome Project", &ok);
    // If the user actually enters something, then proceed. Else do nothing
    if(ok && !text.isEmpty()) {
        fileName = text;
        score = 0;
        // Then ask if they want a tutorial
        QMessageBox::StandardButton tutorialChoice;
        tutorialChoice = QMessageBox::question(this, "Tutorial", "Would you like a tutorial?"),
                                                            QMessageBox::Yes|QMessageBox::No;
        // If so, add some examples
        if(tutorialChoice == QMessageBox::Yes) {
            // If a new project is selected, do this
            // Set the list widget item 0 (the example) to be center aligned
            ui->listWidget->addItem("I'm an example! Try me!");
            totalScore++;
            ui->listWidget->addItem("I'm another example! Cross me out!");
            totalScore++;
            for(int i = 0; i < 2; i++) {
                ui->listWidget->item(i)->setTextAlignment(Qt::AlignHCenter);
            }
        } else {
            totalScore = 0;
            ui->listWidget->clear();
        }
        ui->totalScoreGoesHere->setText(QString::number(totalScore));
        ui->projectNameGoesHere->setText(text);
        ui->scoreGoesHere->setText(QString::number(score));
        // Then set the current index to 1 and the save button to enabled
        ui->stackedWidget->setCurrentIndex(1);
        ui->actionSave->setEnabled(true);
        ui->actionMinified->setEnabled(false);
        ui->actionFull_View->setEnabled(true);
        //startingFresh = false;
    }
}

void MainWindow::load() {
    // On load, reset scores and names and load items looking for finished tasks
    score = 0;
    totalScore = 0;
    ui->listWidget->clear();
    listOfItems.clear();
    listOfItems = file->loadFile();
    if (listOfItems.at(0) != "") {
        QString passedProjectName = listOfItems.at(0);
        passedProjectName.replace(QString(".txt"), QString(""));
        ui->projectNameGoesHere->setText(passedProjectName);
        listOfItems.erase(listOfItems.begin());
        for(int i = 0; i < listOfItems.size(); i++) {
            if(listOfItems.at(i).contains(" - DONE")) {
                QString fixed = listOfItems.at(i);
                fixed.replace(QString(" - DONE"), QString(""));
                ui->listWidget->addItem(fixed);
                QFont font;
                font.setStrikeOut(true);
                ui->listWidget->item(i)->setFont(font);
                ui->listWidget->item(i)->setTextAlignment(Qt::AlignHCenter);
                score++;
                totalScore++;
            } else {
                ui->listWidget->addItem(listOfItems.at(i));
                ui->listWidget->item(i)->setTextAlignment(Qt::AlignHCenter);
                totalScore++;
            }
        }
        // Set scores
        ui->scoreGoesHere->setText(QString::number(score));
        ui->totalScoreGoesHere->setText(QString::number(totalScore));
        // Then set the current index to 1 and the save button to enabled
        ui->stackedWidget->setCurrentIndex(1);
        ui->actionSave->setEnabled(true);
        ui->actionMinified->setEnabled(false);
        ui->actionFull_View->setEnabled(true);
    }
}

void MainWindow::resizeScreen(int height, int width) {
    //Resize screen for different views
    this->setFixedSize(QSize(height, width));
    if(ui->actionMinified->isEnabled()) {
        ui->actionMinified->setEnabled(false);
        ui->actionFull_View->setEnabled(true);
    } else {
        ui->actionMinified->setEnabled(true);
        ui->actionFull_View->setEnabled(false);
    }
}

void MainWindow::checkUnsaved() {
    // On exit make sure there's no unsaved data
    QVector<QString> listContent;
    for (int i = 0; i < ui->listWidget->count(); i++) {
        if(ui->listWidget->item(i)->font().strikeOut()) {
            listContent.append(ui->listWidget->item(i)->text() + " - DONE");
        } else {
            listContent.append(ui->listWidget->item(i)->text());
        }
    }
    if(listOfItems != listContent) {
        QMessageBox::StandardButton unsavedProject;
        unsavedProject = QMessageBox::question(this, "Unsaved Progress!", "You have unsaved progress. Save?"),
                                                            QMessageBox::Yes|QMessageBox::No;
        // If the project isn't saved, ask the user if they want to
        if(unsavedProject == QMessageBox::Yes) {
            for(int i = 0; i < ui->listWidget->count(); i++) {
                if(ui->listWidget->item(i)->font().strikeOut()) {
                    listOfItems.append(ui->listWidget->item(i)->text() + " - DONE");
                } else {
                    listOfItems.append(ui->listWidget->item(i)->text());
                }
            }
            file->saveFile(fileName, listOfItems);
        }
        checkedForSave = true;
    }
    // Otherwise just exit the program
    QApplication::quit();
}
