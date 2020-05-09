#include "QushCmdHelp.h"
#include <QDebug>

QushCmdHelp::QushCmdHelp(QString name, QString help):
    Command(name, help){

}

QushCmdHelp::~QushCmdHelp(){

}

bool QushCmdHelp::exe(QList<QString> argv){
    bool rv = false;
    if(out.isNull()){
        return rv;
    }
    (*out) << "Help:\n";
    out->flush();
//    qDebug() << "F1 rs = " << (rootShell.isNull() ? "NULL" : "NOT NULL");
    auto r = qSharedPointerDynamicCast<Qush::Shell>(rootShell);
    auto cmds = r->getLexemes();
    if(cmds.isNull()){
        return rv;
    }
    rv = true;
    auto it = (*cmds).begin();
    while(it != (*cmds).end()){
        (*out) << "  " << (*(*it)).name() << " -- " << (*(*it)).help() << "\n";
        out->flush();
        ++it;
    }
    return rv;
}
