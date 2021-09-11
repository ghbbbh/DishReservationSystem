#include "RestRegisterWindow.h"

RestRegisterWindow::RestRegisterWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

RestRegisterWindow::~RestRegisterWindow()
{
}

/// <summary>
/// 清楚用户输入
/// </summary>
void RestRegisterWindow::on_clearButton_clicked()
{
	ui.endHour->clear();
	ui.endMin->clear();
	ui.startHour->clear();
	ui.startMin->clear();
	ui.restname->clear();
	ui.startprice->clear();
	ui.sendprice->clear();
	ui.localBlock->setCurrentIndex(0);

}

/// <summary>
/// 检查用户输入
/// </summary>
/// <returns></returns>
bool RestRegisterWindow::CheckInput()
{
	if (!CheckName(ui.restname->text(), 16, "餐馆名"))
	{
		return false;
	}
	if (!CheckInputIsInt(ui.startprice->text(), QString(u8"起送价格")) ||
		!CheckInputIsInt(ui.sendprice->text(), QString(u8"配送费")) ||
		!CheckInputIsInt(ui.startHour->text(), QString(u8"开店时间的小时")) ||
		!CheckInputIsInt(ui.endHour->text(), QString(u8"闭店时间的小时")) ||
		!CheckInputIsInt(ui.startMin->text(), QString(u8"开店时间的分钟")) ||
		!CheckInputIsInt(ui.endMin->text(), QString(u8"闭店时间的分钟")))
	{
		return false;
	}

	if (ui.sendprice->text().toInt() > 6)
	{
		QMessageBox::warning(NULL, QString(u8"警告"),
			QString(u8"配送费不能超过六元"), QMessageBox::Ok);
		return false;
	}

	if (ui.sendprice->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"警告"),
			QString(u8"配送费不能小于0元"), QMessageBox::Ok);
		return false;
	}

	if (ui.startprice->text().toInt() > 30)
	{
		QMessageBox::warning(NULL, QString(u8"警告"),
			QString(u8"起送费不能超过三十元"), QMessageBox::Ok);
		return false;
	}

	if (ui.startprice->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"警告"),
			QString(u8"起送费低于0元"), QMessageBox::Ok);
		return false;
	}

	if (ui.startHour->text().toInt() > 24 || ui.startHour->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"警告"),
			QString(u8"开店时间小时必须在0-24时内\n请检查输入"), QMessageBox::Ok);
		return false;
	}
	if (ui.endHour->text().toInt() > 24 || ui.endHour->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"警告"),
			QString(u8"关店时间小时必须在0-24时内\n请检查输入"), QMessageBox::Ok);
		return false;
	}
	if (ui.startMin->text().toInt() > 60 || ui.startHour->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"警告"),
			QString(u8"开店时间分种必须在0-60分内\n请检查输入"), QMessageBox::Ok);
		return false;
	}
	if (ui.endMin->text().toInt() > 60 || ui.endMin->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"警告"),
			QString(u8"关店时间分种必须在0-60分内\n请检查输入"), QMessageBox::Ok);
		return false;
	}

	return true;
}