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
/// ����tableview��modle�ĳ�ʼ����
/// </summary>
/// <returns></returns>
QStandardItemModel* AdminWindow::InitDishTable()
{
	QStandardItemModel* modle = new QStandardItemModel();
	ui.table->setModel(modle);

	modle->setHorizontalHeaderItem(0, new QStandardItem(QString(u8"����")));
	modle->setHorizontalHeaderItem(1, new QStandardItem(QString(u8"ԭ��")));
	modle->setHorizontalHeaderItem(2, new QStandardItem(QString(u8"��ζ")));
	modle->setHorizontalHeaderItem(3, new QStandardItem(QString(u8"�۸�")));
	modle->setHorizontalHeaderItem(4, new QStandardItem(QString(u8"����")));
	modle->setHorizontalHeaderItem(5, new QStandardItem(QString(u8"ʣ��")));
	modle->setHorizontalHeaderItem(6, new QStandardItem(QString(u8"����")));
	modle->setHorizontalHeaderItem(7, new QStandardItem(QString(u8"����ʱ��")));
	printf("\n��ͷ�������\n");

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
/// ����tableview��modle�ĳ�ʼ����
/// </summary>
/// <returns></returns>
QStandardItemModel* AdminWindow::InitOrderTable()
{
	QStandardItemModel* modle = new QStandardItemModel();
	ui.table->setModel(modle);

	modle->setHorizontalHeaderItem(0, new QStandardItem(QString(u8"�������")));
	modle->setHorizontalHeaderItem(1, new QStandardItem(QString(u8"�û�id")));
	modle->setHorizontalHeaderItem(2, new QStandardItem(QString(u8"�����Ʒ")));
	modle->setHorizontalHeaderItem(3, new QStandardItem(QString(u8"����")));
	modle->setHorizontalHeaderItem(4, new QStandardItem(QString(u8"����")));
	modle->setHorizontalHeaderItem(5, new QStandardItem(QString(u8"����ʱ��")));
	printf("\n��ͷ�������\n");

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
/// ��ȡ�û�ѡ���������ʽ
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
/// �����޸İ�ť����������¼�
/// </summary>
void AdminWindow::on_alterButton_clicked()
{
	alterDish.show();
}

/// <summary>
/// ����ɾ����ť����������¼�
/// </summary>
void AdminWindow::on_deleteButton_clicked()
{
	
	deleteDishWindow.show();
}

/// <summary>
/// �������Ӱ�ť����������¼�
/// </summary>
void AdminWindow::on_addButton_clicked()
{
	addDishWindow.show();
}


