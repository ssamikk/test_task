#include "testtask.h"
#include "ui_testtask.h"
#include "workerthread.h"
#include "infomodel.h"

#include <QActionGroup>
#include <QToolButton>


TestTask::TestTask(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestTask)
{
    ui->setupUi(this);
    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);
    actionGroup->addAction(ui->actionDrow);
    actionGroup->addAction(ui->actionInfo);
    showDrow(true);
    connect(ui->actionDrow, &QAction::toggled, this, &TestTask::showDrow);
    connect(ui->actionInfo, &QAction::toggled, this, &TestTask::showInfo);
    startWorkInAThread();
    scen = new QGraphicsScene(this);
    ui->graphicsView->setScene(scen);
    model = new InfoModel(this);
    ui->tableView->setModel(model);
}

TestTask::~TestTask()
{
    workerThread->exit();
    delete ui;
}

void TestTask::showDrow(bool flag)
{
    if (flag) {
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void TestTask::showInfo(bool flag)
{
    if (flag) {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void TestTask::handleResults(DataObject *obj)
{
    scen->addItem(obj->item());
    model->addObj(obj);
    QToolButton *removeButton = new QToolButton(ui->tableView);
    removeButton->setIcon(QIcon(":/img/remove.png"));
    connect(removeButton, &QToolButton::clicked, this, &TestTask::removeRow);
    ui->tableView->setIndexWidget(model->index(model->rowCount()-1, InfoModel::CRemove), removeButton);
    QToolButton *button = new QToolButton(ui->tableView);
    button->setIcon(QIcon(":/img/visible.png"));
    connect(button, &QToolButton::clicked, this, &TestTask::makeVisible);
    ui->tableView->setIndexWidget(model->index(model->rowCount()-1, InfoModel::CVisible), button);
}

void TestTask::removeRow()
{
    QToolButton *removeButton = (QToolButton*)sender();
    if (removeButton != nullptr){
        model->removeRow(ui->tableView->rowAt(removeButton->y()));
    }
}

void TestTask::makeVisible()
{
    QToolButton *button = (QToolButton*)sender();
    if (button != nullptr){
        QModelIndex index = model->index(ui->tableView->rowAt(button->y()), InfoModel::CVisible);
        model->setData(index, !index.data().toBool(), Qt::EditRole);
        button->setIcon(QIcon(index.data().toBool() ? ":/img/visible.png" : ":/img/unvisible.png"));
    }
}

void TestTask::startWorkInAThread()
{
    workerThread = new WorkerThread(this);
    connect(workerThread, &WorkerThread::resultReady, this, &TestTask::handleResults);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}
