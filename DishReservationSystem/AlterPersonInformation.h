#pragma once

#include <QWidget>
#include "ui_AlterPersonInformation.h"
#include "qmessagebox.h"

class AlterPersonInformation : public QWidget
{
	Q_OBJECT

public:
	AlterPersonInformation(QWidget *parent = Q_NULLPTR);
	~AlterPersonInformation();

private:
	Ui::AlterPersonInformation ui;
	bool CheckInput();
	bool CheckNameInput(QString qstrname, int n);
	bool CheckIdPhoneNUm(QString qstrPhoneNUm);
	bool CheckEmail(QString qstremail);

private slots:
	void on_clearButton_clicked();
	void on_alterbutton_clicked();
};
