#include "AlterCommentWindow.h"

AlterCommentWindow::AlterCommentWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
}

AlterCommentWindow::~AlterCommentWindow()
{
}

/// <summary>
/// ����û�����
/// </summary>
void AlterCommentWindow::on_pushButton_2_clicked()
{

	ui.scorecombo->setCurrentIndex(0);
	ui.commentEdit->clear();
}

/// <summary>
/// ����û�����
/// </summary>
/// <returns></returns>
bool AlterCommentWindow::CheckInput()
{
	if (CheckCommentInput(ui.commentEdit->toPlainText(), 40, QString(u8"����")))
	{
		return true;
	}
	return false;
}
