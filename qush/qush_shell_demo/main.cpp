#include <QCoreApplication>
#include <QTimer>

#include <Qush.h>

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    Qush shell;
    shell.exe(QList<QString>({"help"}));

    QTimer::singleShot(0, &a, &QCoreApplication::quit);

    return a.exec();
}
