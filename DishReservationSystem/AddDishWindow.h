#pragma once

#include <QWidget>
#include "ui_AddDishWindow.h"
#include <qmessagebox.h>

class AddDishWindow : public QWidget
{
	Q_OBJECT

public:
	AddDishWindow(QWidget *parent = Q_NULLPTR);
	~AddDishWindow();
	bool CheckInput();
	bool CheckName(QString qstrname, int n, QString qstrinfo);
	bool CheckRestIsInt(QString rest);
	bool CheckPriceNum(QString price);
private:
	Ui::AddDishWindow ui;
private slots:
	void on_clearButton_clicked();
	void on_addButton_clicked();
};
