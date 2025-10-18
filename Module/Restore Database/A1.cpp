#include "A1.h"
#include <QDebug>

A1::A1(QObject *parent) : QObject(parent)
{
    // سازنده‌ی کلاس
}

void A1::runA1()
{
    // کدی که مربوط به کار خاص A1 هست رو اینجا بنویسید
    qDebug() << "Running A1";
}
