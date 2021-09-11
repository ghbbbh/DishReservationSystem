#pragma once

#include <QWidget>
#include "ui_UserWindow.h"
#include "qtoolbutton.h"
#include "CheckCommentWindow.h"
#include "qcheckbox.h"
#include "AddComment.h"
#include "AlterPersonInformation.h"
#include "AlterCommentWindow.h"
#include "qmovie.h"

class UserWindow : public QWidget
{
	Q_OBJECT

public:
	UserWindow(QWidget *parent = Q_NULLPTR);
	~UserWindow();
	QWidget* scrollW;
	CheckCommentWindow ccw;
	AddComment addComment;
	AlterCommentWindow alterCommentWindow;
	AlterPersonInformation alterPersonInfoWindow;
	QVector<QString> SelectorderId;
	QVector<QString> SelectRestName;
	QVector<QString> SelectDishName;
	QVector<QCheckBox*> SelectCheckBoxsAll;
	void ShowDishRecommend();
	char* GetOrderWay();
	char* GetSearchWay();
	void SetDishInfo(char* dishname,char* restname);
	void ShowShopChart();
	void ShowHistoryOrder();
	void ShowPersonInfo();
private:
	Ui::UserWindow ui;

private slots:
	void on_searchbutton_clicked();
	void on_lookCommentButton_clicked();
	void on_purChaseButton_clicked();
	void on_addshoppingChartButton_clicked();
	void on_shoppingCartWindow_clicked();
	void on_refreshButton_clicked();
	void on_orderMealWindow_clicked();
	void on_buyChartButton_clicked();
	void on_deleteSelect_clicked();
	void on_selectAll_clicked();
	void on_orderHistoryWindow_clicked();
	void on_personInformation_clicked();
	void on_alterpersonInfo_clicked();
};
