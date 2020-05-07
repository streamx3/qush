#include <QTextStream>
#include "QushCmdHelp.h"

QushCmdHelp::QushCmdHelp(QString name, QString help):
    Command(name, help){

}

QushCmdHelp::~QushCmdHelp(){

}

bool QushCmdHelp::exe(QList<QString> argv){
    QTextStream ts(stdout);
    ts << "Help:\n";
    ts.flush();
    auto cmds = mRoot->lexemes();
    auto it = (*cmds).begin();
    while(it != (*cmds).end()){
        ts << "  " << (*(*it)).name() << " -- " << (*(*it)).help() << "\n";
        ts.flush();
        ++it;
    }
    return true;
}
