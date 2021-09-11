#pragma once

#include <QWidget>
#include "ui_AlterDish.h"
#include "qmessagebox.h"

class AlterDish : public QWidget
{
	Q_OBJECT

public:
	AlterDish(QWidget *parent = Q_NULLPTR);
	~AlterDish();
	
private:
	Ui::AlterDish ui;
	bool CheckInput();
	bool CheckName(QString qstrname, int n, QString qstrinfo);
	bool CheckRestIsInt(QString rest);
	bool CheckPriceNum(QString price);

private slots:
	void on_clearbutton_clicked();
	void on_alterButton_clicked();
};
