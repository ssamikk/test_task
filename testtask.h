#ifndef TESTTASK_H
#define TESTTASK_H

#include "dataobject.h"

#include <QGraphicsScene>
#include <QMainWindow>

class WorkerThread;
class InfoModel;

namespace Ui {
class TestTask;
}

class TestTask : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestTask(QWidget *parent = 0);
    ~TestTask();
private slots:
    void showDrow(bool flag);
    void showInfo(bool flag);
    void handleResults(DataObject *obj);
    void removeRow();
    void makeVisible();
private:
    Ui::TestTask *ui;
    QGraphicsScene *scen;
    void startWorkInAThread();
    WorkerThread *workerThread;
    InfoModel *model;
};

#endif // TESTTASK_H
