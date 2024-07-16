#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include "dataobject.h"

#include <QThread>
#include <QUdpSocket>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(QObject *parent = nullptr);
private:
    QUdpSocket *udpSocket;
    void run() override;
private slots:
    void readPendingDatagrams();
signals:
    void resultReady(DataObject *result);
};


#endif // WORKERTHREAD_H
