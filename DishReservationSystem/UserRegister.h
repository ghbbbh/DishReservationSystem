#pragma once

#include <QWidget>
#include "ui_UserRegister.h"
#include "qmessagebox.h"


class UserRegister : public QWidget
{
	Q_OBJECT

public:
	UserRegister(QWidget *parent = Q_NULLPTR);
	~UserRegister();

private:
	Ui::UserRegister ui;
	bool CheckInput();
	bool CheckUserIdInput(QString qstrid);
	bool CheckIdPhoneNUm(QString qstrPhoneNUm);
	bool CheckEmail(QString qstremail);
private slots:
	void on_registerButton_clicked();
	void on_clearButton_clicked();
};
