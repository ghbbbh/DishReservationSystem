#include "CheckCommentWindow.h"

CheckCommentWindow::CheckCommentWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
}

CheckCommentWindow::~CheckCommentWindow()
{
}

/// <summary>
///�������۱��Ѿ����úõ�modle 
/// </summary>
/// <returns></returns>
QStandardItemModel* CheckCommentWindow::InitDishTable()
{
	QStandardItemModel* modle = new QStandardItemModel();
	ui.commenttable->setModel(modle);

	modle->setHorizontalHeaderItem(0, new QStandardItem(QString(u8"����")));
	modle->setHorizontalHeaderItem(1, new QStandardItem(QString(u8"����ʱ��")));
	printf("\n��ͷ�������\n");

	//ui.commenttable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.commenttable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.commenttable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

	ui.commenttable->horizontalHeader()->setMinimumSectionSize(175);
	ui.commenttable->verticalHeader()->setMinimumSectionSize(175);
	//ui.table->horizontalHeader()->setStretchLastSection(false);
	ui.commenttable->verticalHeader()->hide();
	//ui.table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui.table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.commenttable->horizontalHeader()->setStyleSheet("QHeaderView::section {"
		"background-color: rgba(255, 255, 255, 0);padding-left: 4px;border: 1px solid #6c6c6c;}");

	return modle;
}

/// <summary>
/// ����û�����
/// </summary>
void CheckCommentWindow::on_backButton_clicked()
{
	this->close();
}

