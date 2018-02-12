#include "checklistwindow.h"
#include "ui_checklistwindow.h"

checklistwindow::checklistwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::checklistwindow)
{
    ui->setupUi(this);
}

checklistwindow::~checklistwindow()
{
    delete ui;
}
