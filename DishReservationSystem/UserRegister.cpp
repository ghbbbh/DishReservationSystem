#include "UserRegister.h"

UserRegister::UserRegister(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

UserRegister::~UserRegister()
{
}


/// <summary>
/// 检查用户输入
/// </summary>
/// <returns></returns>
bool UserRegister::CheckInput()
{
	
	if (ui.id->text().isEmpty() || ui.password->text().isEmpty() || ui.name->text().isEmpty()
		|| ui.phonenum->text().isEmpty() || ui.email->text().isEmpty() )
	{
		QMessageBox::warning(NULL, QString(u8"警告"), QString(u8"请完成输入"), QMessageBox::Ok);
		return false;
	}

	if (!CheckUserIdInput((ui.id->text())) || !CheckIdPhoneNUm(ui.phonenum->text())
		|| !CheckEmail(ui.email->text()))
	{
		return false;
	}

	return true;
}

/// <summary>
/// 清除用户输入
/// </summary>
void UserRegister::on_clearButton_clicked()
{
	ui.id->clear();
	ui.password->clear();
	ui.email->clear();
	ui.name->clear();
	ui.phonenum->clear();
	printf("用户输入已被清除\n");
}

