#pragma once

#include <QWidget>
#include "ui_AdminWindow.h"
#include "qstandarditemmodel.h"
#include "AlterDish.h"
#include "DelteDish.h"
#include "AddDishWindow.h"
#include "qtableview.h"

class AdminWindow : public QWidget
{
	Q_OBJECT

public:
	AdminWindow(QWidget *parent = Q_NULLPTR);
	~AdminWindow();
	QStandardItemModel* InitDishTable();
	QStandardItemModel* InitOrderTable();
	AlterDish alterDish;
	DelteDish deleteDishWindow;
	AddDishWindow addDishWindow;
	char* GetOrderWay();
	void ShowDishTable(char* dishTableName);
	void ShowOrderList(char* orderlistname);
private:
	Ui::AdminWindow ui;

private slots:
	void on_searchButton_clicked();
	void on_alterButton_clicked();
	void on_addButton_clicked();
	void on_deleteButton_clicked();
	void on_pushButton_clicked();
};
