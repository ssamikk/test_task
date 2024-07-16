#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

    void doWork(const QString &parameter);
signals:
    void resultReady(const QString &result);
public slots:
};

#endif // WORKER_H
