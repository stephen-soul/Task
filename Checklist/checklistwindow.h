#ifndef CHECKLISTWINDOW_H
#define CHECKLISTWINDOW_H

#include <QMainWindow>

namespace Ui {
class checklistwindow;
}

class checklistwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit checklistwindow(QWidget *parent = 0);
    ~checklistwindow();

private:
    Ui::checklistwindow *ui;
};

#endif // CHECKLISTWINDOW_H
