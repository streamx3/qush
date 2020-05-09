#include <QDebug>

#include "Qush.h"
#include "QushCmdHelp.h"

/// Qush static ------------------------------------------------------------------------------------

const QString Qush::Lexeme::STR_UNKNOWN = QString("UNKNOWN");
const QString Qush::Lexeme::STR_SHELL = QString("SHELL");
const QString Qush::Lexeme::STR_COMMAND = QString("COMMAND");
const QString Qush::Lexeme::STR_VARIABLE = QString("VARIABLE");

/// Qush -------------------------------------------------------------------------------------------

Qush::Qush(QSharedPointer<QTextStream> input, QSharedPointer<QTextStream> output):
    in(input), out(output){
    QString warn_prefix = "Qush::Qush() reveived NULL ";
    if(input.isNull())
        qDebug() << warn_prefix + "istream";
    if(output.isNull())
        qDebug() << warn_prefix + "ostream";
    auto hash = new QHash<QString, QSharedPointer<Qush::Lexeme>>();
    rootShell = QSharedPointer<Qush::Shell>(new Qush::Shell("", "main shell"));
    rootShell->setIO(in, out);
    rootShell->setRootShell(nullptr);
//    mspLexemes = QSharedPointer<QHash<QString, QSharedPointer<Qush::Lexeme>>>(hash);

    QushCmdHelp* cmd_help = new QushCmdHelp("help", "display this help.");

    auto sp_cmd_help = QSharedPointer<Command>(cmd_help);
//    qDebug() << cmd_help->qstrType();
    regLexeme(sp_cmd_help);
//    qDebug() << "registered: " << mspLexemes->size();

}

// -------------------------------------------------------------------------------------------------

Qush::~Qush(){

}

// -------------------------------------------------------------------------------------------------

bool Qush::regLexeme(QSharedPointer<Lexeme> ptr){
//    bool rv = false;
//    auto it = (*mspLexemes).find((*ptr).name());
//    if(it == (*mspLexemes).end()){
//        (*ptr).setRoot(this);
//        (*mspLexemes).insert((*ptr).name(), ptr);
//        rv = true;
//    }else{
//        qDebug() << "Value exists! Skipping.";
//    }
////    qDebug() << "reg done:" << (*ptr).name();
//    ptr->setIO(msp_in, msp_out);

//    return rv;
    if(rootShell.isNull() || ptr.isNull())
        return false;
    return rootShell->regLexeme(ptr);
}

// -------------------------------------------------------------------------------------------------

bool Qush::exe(QList<QString> name){
    bool rv = false;

    if(rootShell.isNull()){
        return rv;
    }
    rootShell->exe(name);

    return rv;
}

// -------------------------------------------------------------------------------------------------

QSharedPointer<QHash<QString, QSharedPointer<Qush::Lexeme>>> Qush::Shell::getLexemes(){
    if(lexemes.isNull()){
        qDebug() << "Qush::Lexemes is NULL!";
    }
    return lexemes;
}

/// Qush::Lexeme -----------------------------------------------------------------------------------

Qush::Lexeme::Lexeme(Type new_type, QString new_name, QString new_help):
    mType(new_type), mName(new_name), mHelp(new_help), rootQush(nullptr), rootShell(nullptr){
//    qDebug() << "Lexeme default";
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

// -------------------------------------------------------------------------------------------------

bool Qush::Lexeme::setRoot(Qush* newRootQush){
    bool rv = true;
    rootQush = newRootQush;
    if(nullptr == newRootQush){
        qDebug() << "trying to set nullptr as command's root";
        rv = false;
    }
    return rv;
}

// -------------------------------------------------------------------------------------------------

bool Qush::Lexeme::setRootShell(QSharedPointer<Lexeme> newRootShell){
    bool rv = false;
    if(newRootShell.isNull()){
//        qDebug() << "Trying to set NULL root shell";
        return rv;
    }

    rootShell = newRootShell;

    return rv;
}

// -------------------------------------------------------------------------------------------------

void Qush::Lexeme::setIO(QSharedPointer<QTextStream> newIn, QSharedPointer<QTextStream> newOut){
    if(newIn.isNull()){
        qDebug() << "Passed NULL as istream";
        return;
    }
    if(newOut.isNull()){
        qDebug() << "Passed NULL as ostream";
        return;
    }
    in = newIn;
    out = newOut;
}

// -------------------------------------------------------------------------------------------------

QString Qush::Lexeme::name(){
    return mName;
}

// -------------------------------------------------------------------------------------------------

QString Qush::Lexeme::help(){
    return mHelp;
}

// -------------------------------------------------------------------------------------------------

QSharedPointer<Qush::Lexeme> Qush::Lexeme::getQSharedLexeme(){
    return sharedFromThis();
}

/// Qush::Command ----------------------------------------------------------------------------------

Qush::Command::Command(QString name, QString help):Lexeme(Lexeme::Type::COMMAND, name, help){
//    qDebug() << "CMD";
}

// -------------------------------------------------------------------------------------------------

Qush::Command::~Command(){

}

// -------------------------------------------------------------------------------------------------

bool Qush::Command::exe(QList<QString> args){
    return false;
}

/// Qush::Variable ---------------------------------------------------------------------------------

Qush::Variable::Variable(QString name, QString help):Lexeme(Lexeme::Type::COMMAND, name, help){

}

// -------------------------------------------------------------------------------------------------

Qush::Variable::~Variable(){

}

// -------------------------------------------------------------------------------------------------

bool Qush::Variable::get(QSharedPointer<QVariant> data){
    bool rv = false;
    if(data.isNull())
        return rv;

    return rv;
}

// -------------------------------------------------------------------------------------------------

bool Qush::Variable::set(QSharedPointer<QVariant> data){
    bool rv = false;
    if(data.isNull())
        return rv;


    return rv;
}

// -------------------------------------------------------------------------------------------------

QVariant::Type Qush::Variable::getQVType(){
    return mVariant.type();
}

// -------------------------------------------------------------------------------------------------

QString Qush::Variable::qstr(){
    QString rv;

    if(mVariant.canConvert(QMetaType::QString)){
        rv = mVariant.toString();
    }else{
        rv = "N/A";
    }

    return rv;
}

/// Qush::Shel -------------------------------------------------------------------------------------

Qush::Shell::Shell(QString name, QString help):Lexeme(Qush::Lexeme::Type::SHELL,name,help){
    lexemes = QSharedPointer<QHash<QString, QSharedPointer<Lexeme>>>(
                new QHash<QString, QSharedPointer<Lexeme>>());
}

// -------------------------------------------------------------------------------------------------

Qush::Shell::~Shell(){

}

// -------------------------------------------------------------------------------------------------

bool Qush::Shell::regLexeme(QSharedPointer<Lexeme> ptr){
    bool rv = false;
    if(ptr.isNull()){
        qDebug() << "prt is NULL";
        return rv;
    }
//    if(rootShell.isNull()){
//        qDebug() << "root is NULL";
//        return rv;
//    }

    auto it = (*lexemes).find((*ptr).name());
    if(it == (*lexemes).end()){
        auto plex = this->getQSharedLexeme();
//        qDebug() << "sh::lex::regL pl = " << (plex.isNull() ? "NULL" : "NOT NULL");
        (*ptr).setRootShell(plex);
        (*lexemes).insert((*ptr).name(), ptr);
        rv = true;
    }else{
        qDebug() << "Value exists! Skipping.";
    }
//    qDebug() << "reg done:" << (*ptr).name();
    ptr->setIO(in, out);

    return rv;
}

// -------------------------------------------------------------------------------------------------

bool Qush::Shell::exe(QList<QString> args){
    bool rv = false;
    auto it = (*lexemes).find(args[0]);
    if(it != (*lexemes).end()){
        auto type = (*it)->getType();
        switch (type) {
            case Qush::Lexeme::Type::COMMAND:{
                auto sp = qSharedPointerDynamicCast<Qush::Command>(*it);
                rv = sp->exe(args);
                break;
            }
            case Qush::Lexeme::Type::SHELL:{
                break;
            }
            case Qush::Lexeme::Type::VARIABLE:{
                auto sp = qSharedPointerCast<Qush::Variable>(*it);
                // TODO implement me!
                break;
            }
            case Qush::Lexeme::Type::UNKNOWN:{
                break;
            }
        }
    }
    return rv;
}

/// ------------------------------------------------------------------------------------------------
