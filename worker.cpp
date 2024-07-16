#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::doWork(const QString &parameter) {
    QString result;
    /* ... here is the expensive or blocking operation ... */
    emit resultReady(result);
}
