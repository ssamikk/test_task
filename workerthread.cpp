#include "dataobject.h"
#include "ellipseobject.h"
#include "workerthread.h"

#include <QNetworkDatagram>
#include "api_generated.h"
#include "flatbuffers/flatbuffers.h"
#include "rectobject.h"
#include "triangleobject.h"
#include "lineobject.h"

WorkerThread::WorkerThread(QObject *parent): QThread(parent)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 10002);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void WorkerThread::run() {
    exec();
}

void WorkerThread::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        flatbuffers::Verifier verifier = flatbuffers::Verifier((unsigned char *)datagram.data().data(), datagram.data().length());
        if (verifier.VerifyBuffer<EllipseData>(nullptr)) {
            auto rect = flatbuffers::GetRoot<EllipseData>(datagram.data());
            emit resultReady(new EllipseObject(rect));
        } else if (verifier.VerifyBuffer<RectData>(nullptr)){
            auto rect = flatbuffers::GetRoot<RectData>(datagram.data());
            emit resultReady(new RectObject(rect));
        } else if (verifier.VerifyBuffer<LineData>(nullptr)) {
            auto rect = flatbuffers::GetRoot<LineData>(datagram.data());
            emit resultReady(new LineObject(rect));
        } else if (verifier.VerifyBuffer<TriangleData>(nullptr)) {
            auto rect = flatbuffers::GetRoot<TriangleData>(datagram.data());
            emit resultReady(new TriangleObject(rect));
        }
    }
}
