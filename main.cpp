#include "testtask.h"
#include <QApplication>
#include "api_generated.h"
#include "flatbuffers/verifier.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestTask w;
    w.show();
    return a.exec();
}
