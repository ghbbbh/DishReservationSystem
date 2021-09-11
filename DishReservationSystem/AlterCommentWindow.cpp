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
/// 清除用户输入
/// </summary>
void AlterCommentWindow::on_pushButton_2_clicked()
{

	ui.scorecombo->setCurrentIndex(0);
	ui.commentEdit->clear();
}

/// <summary>
/// 检查用户输入
/// </summary>
/// <returns></returns>
bool AlterCommentWindow::CheckInput()
{
	if (CheckCommentInput(ui.commentEdit->toPlainText(), 40, QString(u8"评价")))
	{
		return true;
	}
	return false;
}
