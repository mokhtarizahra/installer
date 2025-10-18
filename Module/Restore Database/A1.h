#ifndef A1_H
#define A1_H

#include <QObject>

class A1 : public QObject
{
    Q_OBJECT
public:
    explicit A1(QObject *parent = nullptr);
    void runA1();  // یک متد برای انجام کار مربوط به A1
};

#endif // A1_H
