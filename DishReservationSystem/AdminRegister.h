#pragma once

#include <QWidget>
#include "ui_AdminRegister.h"
#include "qmessagebox.h"
#include "RestRegisterWindow.h"

class AdminRegister : public QWidget
{
	Q_OBJECT

public:
	AdminRegister(QWidget *parent = Q_NULLPTR);
	~AdminRegister();
	RestRegisterWindow resRegisterWindow;
	bool CheckInput();
	
private:
	Ui::AdminRegister ui;
	bool CheckAdminIdInput(QString qstrid);
	bool CheckEmail(QString qstremail);
	bool CheckName(QString qstrname, int n, QString qstrinfo);

private slots:
	void on_registerButton_clicked();
	void on_clearButton_clicked();
};

