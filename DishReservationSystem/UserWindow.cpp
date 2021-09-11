#include "UserWindow.h"


UserWindow::UserWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QMovie* movie = new QMovie(u8":/image/longmao_matting.gif");
	ui.backgif1->setMovie(movie);                  // �ڱ�ǩ����Ӷ���
	movie->start();
}

UserWindow::~UserWindow()
{

}

/// <summary>
/// ��ȡ�û�ѡ������ʽ
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
/// ��ȡ�û���������Χ
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
/// ����������ť����������¼�
/// </summary>
void UserWindow::on_searchbutton_clicked()
{
	ShowDishRecommend();
}


/// <summary>
///���õ�����ﳵ��ť�������¼�
/// </summary>
void UserWindow::on_shoppingCartWindow_clicked()
{
	printf("�ѵ�����ﳵ����\n");
	ui.stackedWidget->setCurrentIndex(1);
	ShowShopChart();
}

/// <summary>
/// ����ˢ���¼�
/// </summary>
void UserWindow::on_refreshButton_clicked()
{
	ShowShopChart();
}

/// <summary>
/// ���ö��Ͱ�ť�������¼�
/// </summary>
void UserWindow::on_orderMealWindow_clicked()
{
	ui.stackedWidget->setCurrentIndex(0);
	ShowDishRecommend();
}

/// <summary>
/// ������ʷ������ť�������¼�
/// </summary>
void UserWindow::on_orderHistoryWindow_clicked()
{
	ui.stackedWidget->setCurrentIndex(2);
	ShowHistoryOrder();
}

/// <summary>
/// ����ȫѡ��ť�������¼�
/// </summary>
void UserWindow::on_selectAll_clicked()
{
	
	for (int i = 0; i < SelectCheckBoxsAll.size(); i++)
	{
		SelectCheckBoxsAll[i]->setCheckState(Qt::CheckState::Checked);
	}
}

/// <summary>
/// ���ø�����Ϣ��ť����������¼�
/// </summary>
void UserWindow::on_personInformation_clicked()
{

	ui.stackedWidget->setCurrentIndex(3);
	ShowPersonInfo();
}

/// <summary>
/// �����޸ĸ�����Ϣ��ť����������¼�
/// </summary>
void UserWindow::on_alterpersonInfo_clicked()
{
	alterPersonInfoWindow.show();
}

