#pragma once

#include <QWidget>
#include "ui_AlterCommentWindow.h"

class AlterCommentWindow : public QWidget
{
	Q_OBJECT

public:
	AlterCommentWindow(QWidget *parent = Q_NULLPTR);
	~AlterCommentWindow();
	bool CheckInput();
	bool CheckCommentInput(QString comment, int n, QString str);

private:
	Ui::AlterCommentWindow ui;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
};
