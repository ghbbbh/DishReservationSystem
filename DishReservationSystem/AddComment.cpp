#include "AddComment.h"

AddComment::AddComment(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
}

AddComment::~AddComment()
{
}
/// <summary>
/// ����û�����
/// </summary>
void AddComment::on_pushButton_2_clicked()
{

	ui.scorecombo->setCurrentIndex(0);
	ui.commentEdit->clear();
}

/// <summary>
/// ����û�����
/// </summary>
/// <returns></returns>
bool AddComment::CheckInput()
{
	if (CheckCommentInput(ui.commentEdit->toPlainText(), 40, QString(u8"����")))
	{
		return true;
	}
	return false;
}
