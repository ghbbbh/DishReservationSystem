#include "AlterPersonInformation.h"

AlterPersonInformation::AlterPersonInformation(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

AlterPersonInformation::~AlterPersonInformation()
{
}

/// <summary>
/// 检查用户输入
/// </summary>
/// <returns></returns>
bool AlterPersonInformation::CheckInput()
{
	if (ui.phone->text().isEmpty() || ui.name->text().isEmpty() || ui.email->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString(u8"警告"), QString(u8"请完成输入"), QMessageBox::Ok);
		return false;
	}

	if (!CheckIdPhoneNUm(ui.phone->text())|| !CheckEmail(ui.email->text()) 
		|| !CheckNameInput(ui.name->text(),10))
	{
		return false;
	}

	return true;
}


/// <summary>
/// 清空用户输入
/// </summary>
void AlterPersonInformation::on_clearButton_clicked()
{
	ui.adressBlock->clear();
	ui.name->clear();
	ui.email->clear();
	ui.sexCombo->setCurrentIndex(0);
	ui.blockCombo->setCurrentIndex(0);
	ui.adressBlock->setCurrentIndex(0);
}

