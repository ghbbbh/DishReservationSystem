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
/// ����û�����
/// </summary>
/// <returns></returns>
bool UserRegister::CheckInput()
{
	
	if (ui.id->text().isEmpty() || ui.password->text().isEmpty() || ui.name->text().isEmpty()
		|| ui.phonenum->text().isEmpty() || ui.email->text().isEmpty() )
	{
		QMessageBox::warning(NULL, QString(u8"����"), QString(u8"���������"), QMessageBox::Ok);
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
/// ����û�����
/// </summary>
void UserRegister::on_clearButton_clicked()
{
	ui.id->clear();
	ui.password->clear();
	ui.email->clear();
	ui.name->clear();
	ui.phonenum->clear();
	printf("�û������ѱ����\n");
}

