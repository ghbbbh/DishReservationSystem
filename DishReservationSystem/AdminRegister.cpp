#include "AdminRegister.h"

AdminRegister::AdminRegister(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
}

AdminRegister::~AdminRegister()
{
}

/// <summary>
/// ����û�����
/// </summary>
/// <returns></returns>
bool AdminRegister::CheckInput()
{
	
	if ( ui.id->text().isEmpty() || ui.password->text().isEmpty() || ui.name->text().isEmpty()
		|| ui.restname->text().isEmpty() || ui.email->text().isEmpty())
	{
		
		QMessageBox::warning(NULL, QString(u8"����"), QString(u8"���������"), QMessageBox::Ok);
		return false;
	}

	if (!CheckAdminIdInput(ui.id->text()) || !CheckEmail(ui.email->text()) 
		|| !CheckName(ui.name->text(), 10, QString(u8"����")) 
		|| !CheckName(ui.restname->text(), 15, QString(u8"������")))
	{
		return false;
	}

	return true;
}

/// <summary>
/// ����û�����
/// </summary>
void AdminRegister::on_clearButton_clicked()
{
	ui.id->clear();
	ui.password->clear();
	ui.email->clear();
	ui.name->clear();
	ui.restname->clear();
}
