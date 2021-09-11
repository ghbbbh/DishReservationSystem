#include "AlterDish.h"

AlterDish::AlterDish(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

AlterDish::~AlterDish()
{
}

/// <summary>
///	����û�����
/// </summary>
void AlterDish::on_clearbutton_clicked()
{
	
	ui.dishname->text().clear();
	ui.togethers->text().clear();
	ui.price->text().clear();
	ui.taste->text().clear();
	ui.restnum->text().clear();
}

/// <summary>
/// ����û�����
/// </summary>
/// <returns></returns>
bool AlterDish::CheckInput()
{
	

	if (ui.dishname->text().isEmpty() || ui.togethers->text().isEmpty() || ui.taste->text().isEmpty()
		|| ui.price->text().isEmpty() || ui.restnum->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString(u8"����"), QString(u8"���������"), QMessageBox::Ok);
		return false;
	}

	if (!CheckName(ui.dishname->text(), 16, QString(u8"��Ʒ��"))
		|| !CheckName(ui.togethers->text(), 30, QString(u8"ԭ��"))
		|| !CheckName(ui.taste->text(), 16, QString(u8"��ζ")))
	{
		return false;
	}

	if (!CheckRestIsInt(ui.restnum->text()))
	{
		return false;
	}

	if (!CheckPriceNum(ui.price->text()))
	{
		return false;
	}

	return true;
}


