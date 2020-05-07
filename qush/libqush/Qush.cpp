#include <QDebug>

#include "Qush.h"
#include "QushCmdHelp.h"

/// Qush static ------------------------------------------------------------------------------------

const QString Qush::Lexeme::STR_UNKNOWN = QString("UNKNOWN");
const QString Qush::Lexeme::STR_SHELL = QString("SHELL");
const QString Qush::Lexeme::STR_COMMAND = QString("COMMAND");
const QString Qush::Lexeme::STR_VARIABLE = QString("VARIABLE");

// -------------------------------------------------------------------------------------------------

Qush::Qush(){
    auto hash = new QHash<QString, QSharedPointer<Qush::Command>>();
    mspLexemes = QSharedPointer<QHash<QString, QSharedPointer<Qush::Command>>>(hash);

    QushCmdHelp* cmd_help = new QushCmdHelp("help", "display this help.");

    auto sp_cmd_help = QSharedPointer<Command>(cmd_help);
//    qDebug() << cmd_help->qstrType();
    regCommand(sp_cmd_help);
}

// -------------------------------------------------------------------------------------------------

Qush::~Qush(){

}

bool Qush::regCommand(QSharedPointer<Command> ptr){
    bool rv = false;
    auto it = (*mspLexemes).find((*ptr).name());
    (*ptr).setRoot(this);
    if(it == (*mspLexemes).end()){
        (*mspLexemes).insert((*ptr).name(), ptr);
        rv = true;
    }else{
        qDebug() << "Value exists! Skipping.";
    }
//    qDebug() << "reg done:" << (*ptr).name();
    return rv;
}

// -------------------------------------------------------------------------------------------------

QSharedPointer<QHash<QString, QSharedPointer<Qush::Command>>> Qush::lexemes(){
    auto copy = mspLexemes;
    return copy;
}

// -------------------------------------------------------------------------------------------------

bool Qush::exe(QList<QString> name){
    bool rv = false;
    auto it = (*mspLexemes).find(name[0]);
    if(it != (*mspLexemes).end()){
        rv = (*it)->exe(name);
    }
    return rv;
}

/// Qush::Lexeme -----------------------------------------------------------------------------------

Qush::Lexeme::Lexeme(Type t){
//    qDebug() << "Lexeme default";
    this->mType = t;
}

// -------------------------------------------------------------------------------------------------

Qush::Lexeme::~Lexeme(){

}

// -------------------------------------------------------------------------------------------------

Qush::Lexeme::Type Qush::Lexeme::getType(){
    return this->mType;
}

// -------------------------------------------------------------------------------------------------

QString Qush::Lexeme::qstrType(){
    QString rv;
    switch (mType){
    case Qush::Lexeme::Type::COMMAND:
        rv = Qush::Lexeme::STR_COMMAND;
        break;
    case Qush::Lexeme::Type::SHELL:
        rv = Qush::Lexeme::STR_SHELL;
        break;
    case Qush::Lexeme::Type::VARIABLE:
        rv = Qush::Lexeme::STR_VARIABLE;
        break;
    default:
        rv = Qush::Lexeme::STR_UNKNOWN;
    }
    return rv;
}

/// Qush::Command ----------------------------------------------------------------------------------

Qush::Command::Command():Lexeme(Lexeme::Type::COMMAND){
//    qDebug() << "CMD default";
}

// -------------------------------------------------------------------------------------------------

Qush::Command::Command(QString name, QString help):Command(){
//    qDebug() << "CMD sp.";
    mName = name;
    mHelp = help;
}

// -------------------------------------------------------------------------------------------------

Qush::Command::~Command(){

}

// -------------------------------------------------------------------------------------------------

bool Qush::Command::exe(QList<QString> argv){
    return false;
}

// -------------------------------------------------------------------------------------------------

bool Qush::Command::setRoot(Qush* root){
    bool rv = true;
    mRoot = root;
    if(nullptr == root){
        qDebug() << "trying to set nullptr as command's root";
        rv = false;
    }
    return rv;
}

// -------------------------------------------------------------------------------------------------

QString Qush::Command::name(){
    return mName;
}

// -------------------------------------------------------------------------------------------------

QString Qush::Command::help(){
    return mHelp;
}

/// ------------------------------------------------------------------------------------------------
