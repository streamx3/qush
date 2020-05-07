#ifndef QUSHCMDHELP_H
#define QUSHCMDHELP_H

#include <Qush.h>

class QushCmdHelp : public Qush::Command{
public:
    QushCmdHelp(QString name, QString help);
    virtual ~QushCmdHelp();
    virtual bool exe(QList<QString> argv);
};

#endif // QUSHCMDHELP_H
