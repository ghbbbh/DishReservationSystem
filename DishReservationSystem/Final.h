#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Final.h"

class Final : public QMainWindow
{
    Q_OBJECT

public:
    Final(QWidget *parent = Q_NULLPTR);

private:
    Ui::FinalClass ui;
};
