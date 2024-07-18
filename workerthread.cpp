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
        if (verifier.VerifyBuffer<Figure>(nullptr)) {
            auto figure = flatbuffers::GetRoot<Figure>(datagram.data());
            flatbuffers::Verifier verifierFigure = flatbuffers::Verifier((unsigned char *)figure->payload()->data(), figure->payload()->Length());
            switch (figure->type()) {
            case FigureType::FigureType_Ellipse:{
                if (verifierFigure.VerifyBuffer<EllipseData>(nullptr)){
                    auto rect = flatbuffers::GetRoot<EllipseData>(figure->payload()->data());
                    emit resultReady(new EllipseObject(rect));
                }
                break;
            }
            case FigureType::FigureType_Rect:{
                if (verifierFigure.VerifyBuffer<RectData>(nullptr)){
                    auto rect = flatbuffers::GetRoot<RectData>(figure->payload()->data());
                    emit resultReady(new RectObject(rect));
                }
                break;
            }
            case FigureType::FigureType_Triangle:{
                if (verifierFigure.VerifyBuffer<TriangleData>(nullptr)){
                    auto rect = flatbuffers::GetRoot<TriangleData>(figure->payload()->data());
                    emit resultReady(new TriangleObject(rect));
                }
                break;
            }
            case FigureType::FigureType_Line:{
                if (verifierFigure.VerifyBuffer<LineData>(nullptr)){
                    auto rect = flatbuffers::GetRoot<LineData>(figure->payload()->data());
                    emit resultReady(new LineObject(rect));
                }
                break;
            }
            default:
                break;
            }
        }
    }
}
