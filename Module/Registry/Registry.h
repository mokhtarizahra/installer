#ifndef REGISTRY_H
#define REGISTRY_H

#include "ui_Registry.h"
#include "Designer.h"
#include <QWidget>


class MainWindow;
class showMessages;

class Registry : public  Designer
{
    Q_OBJECT
public:

    explicit Registry( QWidget *parent = nullptr);



//~Registry();

};

#endif // REGISTRY_H
