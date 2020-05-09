#ifndef QUSH_H
#define QUSH_H

#include <QHash>
#include <QList>
#include <QMutex>
#include <QVariant>
#include <QTextStream>
#include <QSharedPointer>
#include <QEnableSharedFromThis>

class Qush{
public:
    class Lexeme: public QEnableSharedFromThis<Lexeme>{
    public:
        enum class Type{
            UNKNOWN = 0,
            SHELL,
            COMMAND,
            VARIABLE
        };

        Lexeme(Type t, QString name, QString help);
        virtual ~Lexeme();
        Type getType();
        QString qstrType();
        QString name();
        QString help();
        bool setRoot(Qush* newRootQush);
        bool setRootShell(QSharedPointer<Lexeme> newRootShell);
        void setIO(QSharedPointer<QTextStream> newIn, QSharedPointer<QTextStream> newOut);
        QSharedPointer<Lexeme> getQSharedLexeme();
//        void print(QString str);

//        inline const static QString T_COMMAND =  "COMMAND"; // works for c++17 only
        static const QString STR_UNKNOWN;
        static const QString STR_SHELL;
        static const QString STR_COMMAND;
        static const QString STR_VARIABLE;
    protected:
        Type mType;
        QString mName;
        QString mHelp;
        Qush* rootQush;
        QSharedPointer<Lexeme> rootShell;
        QSharedPointer<QTextStream> in;
        QSharedPointer<QTextStream> out;
    };
    class Command: public Lexeme{
    public:
        Command(QString name, QString help);
        virtual ~Command();
        virtual bool exe(QList<QString> args);
//    protected:
    };

    class Variable: public Lexeme{
    public:
        Variable(QString name, QString help);
        virtual ~Variable();
        virtual bool get(QSharedPointer<QVariant> data);
        virtual bool set(QSharedPointer<QVariant> data);
        virtual QVariant::Type getQVType();
        virtual QString qstr();

    signals:
        void valueChanged(QVariant value);
    protected:
        QVariant mVariant;
    };

    class Shell: public Lexeme{
    public:
        Shell(QString name, QString help);
        virtual ~Shell();
        bool regLexeme(QSharedPointer<Lexeme> ptr);
        bool exe(QList<QString> args);
        QSharedPointer<QHash<QString, QSharedPointer<Lexeme>>> getLexemes();
    protected:
        QSharedPointer<QHash<QString, QSharedPointer<Lexeme>>> lexemes;
    };

    Qush(QSharedPointer<QTextStream> input, QSharedPointer<QTextStream> output);
    ~Qush();
    bool exe(QList<QString> name);
    bool regLexeme(QSharedPointer<Lexeme> ptr);
    QSharedPointer<QHash<QString, QSharedPointer<Lexeme>>> lexemes();
protected:
//    QMutex mtxIO; // TODO reconsider
    QSharedPointer<QTextStream> in;
    QSharedPointer<QTextStream> out;
    QSharedPointer<Qush::Shell> rootShell;
//    QSharedPointer<QHash<QString, QSharedPointer<Lexeme>>> mspLexemes;
};

typedef std::shared_ptr<Qush> ShprtQush;

#endif // QUSH_H
