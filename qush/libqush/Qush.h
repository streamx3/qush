#ifndef QUSH_H
#define QUSH_H

#include <QHash>
#include <QList>
#include <QSharedPointer>

class Qush{
public:
    class Lexeme{
    public:
        enum class Type{
            UNKNOWN,
            SHELL,
            COMMAND,
            VARIABLE
        };

        Lexeme(Type t);
        virtual ~Lexeme();
        Type getType();
        QString qstrType();

//        inline const static QString T_COMMAND =  "COMMAND"; // works for c++17 only
        static const QString STR_UNKNOWN;
        static const QString STR_SHELL;
        static const QString STR_COMMAND;
        static const QString STR_VARIABLE;
    protected:
        Type mType;
    };
    class Command: public Lexeme{
    public:
        Command();
        Command(QString name, QString help);
        virtual ~Command();
        virtual bool exe(QList<QString> argv);
        QString name();
        QString help();
        bool setRoot(Qush* root);
    protected:
        QString mName;
        QString mHelp;
        Qush* mRoot;
    };


    Qush();
    ~Qush();
    bool exe(QList<QString> name);
    bool regCommand(QSharedPointer<Command> ptr);
    QSharedPointer<QHash<QString, QSharedPointer<Command>>> lexemes();
protected:
    QSharedPointer<QHash<QString, QSharedPointer<Command>>> mspLexemes;
};

typedef std::shared_ptr<Qush> ShprtQush;

#endif // QUSH_H
