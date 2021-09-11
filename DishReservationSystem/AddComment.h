#pragma once

#include <QWidget>
#include "ui_AddComment.h"

class AddComment : public QWidget
{
	Q_OBJECT

public:
	AddComment(QWidget *parent = Q_NULLPTR);
	~AddComment();
	bool CheckInput();
	bool CheckCommentInput(QString comment, int n, QString str);
private:
	Ui::AddComment ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
};
