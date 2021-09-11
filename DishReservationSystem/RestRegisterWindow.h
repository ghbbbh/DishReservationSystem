#pragma once

#include <QWidget>
#include "ui_RestRegisterWindow.h"
#include "qmessagebox.h"

class RestRegisterWindow : public QWidget
{
	Q_OBJECT

public:
	RestRegisterWindow(QWidget *parent = Q_NULLPTR);
	~RestRegisterWindow();
	bool CheckName(QString qstrname, int n, QString qstrinfo);
	bool CheckInputIsInt(QString input, QString tipinfo);

private:
	Ui::RestRegisterWindow ui;
	bool CheckInput();
private slots:
	void on_regiButton_clicked();
	void on_clearButton_clicked();

};
