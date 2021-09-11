#include "AddDishWindow.h"

AddDishWindow::AddDishWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

AddDishWindow::~AddDishWindow()
{
}

/// <summary>
/// ����û�����
/// </summary>
void AddDishWindow::on_clearButton_clicked()
{
	ui.dishname->clear();
	ui.togethers->clear();
	ui.price->clear();
	ui.taste->clear();
	ui.restnum->clear();

}

/// <summary>
/// ����û�����
/// </summary>
/// <returns></returns>
bool AddDishWindow::CheckInput()
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

