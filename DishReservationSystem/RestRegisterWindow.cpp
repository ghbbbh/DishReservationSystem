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
/// ����û�����
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
/// ����û�����
/// </summary>
/// <returns></returns>
bool RestRegisterWindow::CheckInput()
{
	if (!CheckName(ui.restname->text(), 16, "�͹���"))
	{
		return false;
	}
	if (!CheckInputIsInt(ui.startprice->text(), QString(u8"���ͼ۸�")) ||
		!CheckInputIsInt(ui.sendprice->text(), QString(u8"���ͷ�")) ||
		!CheckInputIsInt(ui.startHour->text(), QString(u8"����ʱ���Сʱ")) ||
		!CheckInputIsInt(ui.endHour->text(), QString(u8"�յ�ʱ���Сʱ")) ||
		!CheckInputIsInt(ui.startMin->text(), QString(u8"����ʱ��ķ���")) ||
		!CheckInputIsInt(ui.endMin->text(), QString(u8"�յ�ʱ��ķ���")))
	{
		return false;
	}

	if (ui.sendprice->text().toInt() > 6)
	{
		QMessageBox::warning(NULL, QString(u8"����"),
			QString(u8"���ͷѲ��ܳ�����Ԫ"), QMessageBox::Ok);
		return false;
	}

	if (ui.sendprice->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"����"),
			QString(u8"���ͷѲ���С��0Ԫ"), QMessageBox::Ok);
		return false;
	}

	if (ui.startprice->text().toInt() > 30)
	{
		QMessageBox::warning(NULL, QString(u8"����"),
			QString(u8"���ͷѲ��ܳ�����ʮԪ"), QMessageBox::Ok);
		return false;
	}

	if (ui.startprice->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"����"),
			QString(u8"���ͷѵ���0Ԫ"), QMessageBox::Ok);
		return false;
	}

	if (ui.startHour->text().toInt() > 24 || ui.startHour->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"����"),
			QString(u8"����ʱ��Сʱ������0-24ʱ��\n��������"), QMessageBox::Ok);
		return false;
	}
	if (ui.endHour->text().toInt() > 24 || ui.endHour->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"����"),
			QString(u8"�ص�ʱ��Сʱ������0-24ʱ��\n��������"), QMessageBox::Ok);
		return false;
	}
	if (ui.startMin->text().toInt() > 60 || ui.startHour->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"����"),
			QString(u8"����ʱ����ֱ�����0-60����\n��������"), QMessageBox::Ok);
		return false;
	}
	if (ui.endMin->text().toInt() > 60 || ui.endMin->text().toInt() < 0)
	{
		QMessageBox::warning(NULL, QString(u8"����"),
			QString(u8"�ص�ʱ����ֱ�����0-60����\n��������"), QMessageBox::Ok);
		return false;
	}

	return true;
}