#pragma once

#include <QWidget>
#include "ui_CheckCommentWindow.h"
#include "qstandarditemmodel.h"

class CheckCommentWindow : public QWidget
{
	Q_OBJECT

public:
	CheckCommentWindow(QWidget *parent = Q_NULLPTR);
	~CheckCommentWindow();
	void ShowCommentTable(char* dishname, char* restname);

private:
	Ui::CheckCommentWindow ui;
	QStandardItemModel* InitDishTable();

private slots:
	void on_backButton_clicked();
};
