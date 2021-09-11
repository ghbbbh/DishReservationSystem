#pragma once
#include <QWidget>
#include "ui_Log.h"
#include <qmessagebox.h>
#include "AdminRegister.h"
#include "UserRegister.h"
#include "AdminWindow.h"
#include "UserWindow.h"

class Log : public QWidget
{
	Q_OBJECT

public:
	Log(QWidget *parent = Q_NULLPTR);
	~Log();
	AdminRegister adminRegister;
	UserRegister userRegister;
	AdminWindow	adminWindow;
	UserWindow userwindow;

private:
	Ui::Log ui;
	bool CheckInput();
	


private slots:
	void on_logButton_clicked();
	void on_regButton_clicked();
};
