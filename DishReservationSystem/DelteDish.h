#pragma once

#include <QWidget>
#include "ui_DelteDish.h"

class DelteDish : public QWidget
{
	Q_OBJECT

public:
	DelteDish(QWidget *parent = Q_NULLPTR);
	~DelteDish();

private:
	Ui::DelteDish ui;
private slots:
	 void on_clearButton_clicked();
	 void on_deleteButton_clicked();
};
