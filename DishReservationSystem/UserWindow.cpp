#include "UserWindow.h"


UserWindow::UserWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QMovie* movie = new QMovie(u8":/image/longmao_matting.gif");
	ui.backgif1->setMovie(movie);                  // 在标签中添加动画
	movie->start();
}

UserWindow::~UserWindow()
{

}

/// <summary>
/// 获取用户选择排序方式
/// </summary>
/// <returns></returns>
char* UserWindow::GetOrderWay()
{
	
	int orderway = ui.orderway->currentIndex();
	switch (orderway)
	{
	case 0:
		return "";
		break;
	case 1:
		return "ORDER By price";
		break;
	case 2:
		return "ORDER By score";
		break;
	case 3:
		return "ORDER By sold";
		break;
	case 4:
		return "ORDER By rest";
		break;
	case 5:
		return "ORDER By create_time";
		break;
	}

	return "";
}

/// <summary>
/// 获取用户的搜索范围
/// </summary>
/// <returns></returns>
char* UserWindow::GetSearchWay()
{
	
	int searchWay = ui.searchway->currentIndex();
	switch (searchWay)
	{
	case 0:
		return "dishname";
		break;
	case 1:
		return "restname";
		break;
	case 2:
		return "local";
		break;
	}

	return "";
}

/// <summary>
/// 设置搜索按钮点击触发的事件
/// </summary>
void UserWindow::on_searchbutton_clicked()
{
	ShowDishRecommend();
}


/// <summary>
///设置点击购物车按钮触发的事件
/// </summary>
void UserWindow::on_shoppingCartWindow_clicked()
{
	printf("已点击购物车界面\n");
	ui.stackedWidget->setCurrentIndex(1);
	ShowShopChart();
}

/// <summary>
/// 设置刷新事件
/// </summary>
void UserWindow::on_refreshButton_clicked()
{
	ShowShopChart();
}

/// <summary>
/// 设置订餐按钮触发的事件
/// </summary>
void UserWindow::on_orderMealWindow_clicked()
{
	ui.stackedWidget->setCurrentIndex(0);
	ShowDishRecommend();
}

/// <summary>
/// 设置历史订单按钮触发的事件
/// </summary>
void UserWindow::on_orderHistoryWindow_clicked()
{
	ui.stackedWidget->setCurrentIndex(2);
	ShowHistoryOrder();
}

/// <summary>
/// 设置全选按钮触发的事件
/// </summary>
void UserWindow::on_selectAll_clicked()
{
	
	for (int i = 0; i < SelectCheckBoxsAll.size(); i++)
	{
		SelectCheckBoxsAll[i]->setCheckState(Qt::CheckState::Checked);
	}
}

/// <summary>
/// 设置个人信息按钮点击触发的事件
/// </summary>
void UserWindow::on_personInformation_clicked()
{

	ui.stackedWidget->setCurrentIndex(3);
	ShowPersonInfo();
}

/// <summary>
/// 设置修改个人信息按钮点击触发的事件
/// </summary>
void UserWindow::on_alterpersonInfo_clicked()
{
	alterPersonInfoWindow.show();
}

