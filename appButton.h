#ifndef __APPBUTTON_H__
#define __APPBUTTON_H__

#include "application.h"

#include <QWidget>
#include <QPushButton>

class AppButton : public QPushButton
{
    public:
        AppButton(Application* application, QWidget *parent = 0);

    private:
        Application* application;
};

#endif
