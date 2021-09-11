#include "AdminWindow.h"

AdminWindow::AdminWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

AdminWindow::~AdminWindow()
{
}


/// <summary>
/// 设置tableview的modle的初始设置
/// </summary>
/// <returns></returns>
QStandardItemModel* AdminWindow::InitDishTable()
{
	QStandardItemModel* modle = new QStandardItemModel();
	ui.table->setModel(modle);

	modle->setHorizontalHeaderItem(0, new QStandardItem(QString(u8"菜名")));
	modle->setHorizontalHeaderItem(1, new QStandardItem(QString(u8"原料")));
	modle->setHorizontalHeaderItem(2, new QStandardItem(QString(u8"口味")));
	modle->setHorizontalHeaderItem(3, new QStandardItem(QString(u8"价格")));
	modle->setHorizontalHeaderItem(4, new QStandardItem(QString(u8"已售")));
	modle->setHorizontalHeaderItem(5, new QStandardItem(QString(u8"剩余")));
	modle->setHorizontalHeaderItem(6, new QStandardItem(QString(u8"评分")));
	modle->setHorizontalHeaderItem(7, new QStandardItem(QString(u8"创建时间")));
	printf("\n表头设置完成\n");

	ui.table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

	ui.table->horizontalHeader()->setMinimumSectionSize(150);
	ui.table->verticalHeader()->setMinimumSectionSize(150);
	//ui.table->horizontalHeader()->setStretchLastSection(false);
	ui.table->verticalHeader()->hide();
	//ui.table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui.table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.table->horizontalHeader()->setStyleSheet("QHeaderView::section {"
		"background-color: rgba(255, 255, 255, 0);padding-left: 4px;border: 1px solid #6c6c6c;}");

	
	//ui.table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	return modle;
}

/// <summary>
/// 设置tableview的modle的初始设置
/// </summary>
/// <returns></returns>
QStandardItemModel* AdminWindow::InitOrderTable()
{
	QStandardItemModel* modle = new QStandardItemModel();
	ui.table->setModel(modle);

	modle->setHorizontalHeaderItem(0, new QStandardItem(QString(u8"订单编号")));
	modle->setHorizontalHeaderItem(1, new QStandardItem(QString(u8"用户id")));
	modle->setHorizontalHeaderItem(2, new QStandardItem(QString(u8"购买菜品")));
	modle->setHorizontalHeaderItem(3, new QStandardItem(QString(u8"评分")));
	modle->setHorizontalHeaderItem(4, new QStandardItem(QString(u8"评论")));
	modle->setHorizontalHeaderItem(5, new QStandardItem(QString(u8"购买时间")));
	printf("\n表头设置完成\n");

	ui.table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

	ui.table->horizontalHeader()->setMinimumSectionSize(150);
	ui.table->verticalHeader()->setMinimumSectionSize(150);
	//ui.table->horizontalHeader()->setStretchLastSection(false);
	ui.table->verticalHeader()->hide();
	//ui.table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui.table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.table->horizontalHeader()->setStyleSheet("QHeaderView::section {"
		"background-color: rgba(255, 255, 255, 0);padding-left: 4px;border: 1px solid #6c6c6c;}");


	//ui.table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	return modle;
}

/// <summary>
/// 获取用户选择的搜索方式
/// </summary>
/// <returns></returns>
char* AdminWindow::GetOrderWay()
{
	int orderway = ui.comboBox->currentIndex();
	switch (orderway)
	{
	case 0:
		return "";
		break;
	case 1:
		return "ORDER By soldout";
		break;
	case 2:
		return "ORDER By soldout DESC";
		break;
	case 3:
		return "ORDER By create_time";
		break;
	case 4:
		return "ORDER By create_time DESC";
		break;
	case 5:
		return "ORDER By price";
		break;
	case 6:
		return "ORDER By price DESC";
		break;
	case 7:
		return "ORDER By score";
		break;
	case 8:
		return "ORDER By score DESC";
		break;
	}

	return "";
}

/// <summary>
/// 设置修改按钮点击触发的事件
/// </summary>
void AdminWindow::on_alterButton_clicked()
{
	alterDish.show();
}

/// <summary>
/// 设置删除按钮点击触发的事件
/// </summary>
void AdminWindow::on_deleteButton_clicked()
{
	
	deleteDishWindow.show();
}

/// <summary>
/// 设置增加按钮点击触发的事件
/// </summary>
void AdminWindow::on_addButton_clicked()
{
	addDishWindow.show();
}


