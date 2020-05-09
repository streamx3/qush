#include <QTimer>
#include <QSharedPointer>
#include <QCoreApplication>

#include <Qush.h>
#include <QushVarStrTest.h>

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    auto sp_in = QSharedPointer<QTextStream>(new QTextStream(stdin));
    auto sp_out = QSharedPointer<QTextStream>(new QTextStream(stdout));

    Qush shell(sp_in, sp_out);
//    QushVarStrTest testStr;
    auto p_test_str = QSharedPointer<QushVarStrTest>(new QushVarStrTest());

    shell.regLexeme(p_test_str);

    shell.exe(QList<QString>({"help"}));

    QTimer::singleShot(0, &a, &QCoreApplication::quit);

    return a.exec();
}
