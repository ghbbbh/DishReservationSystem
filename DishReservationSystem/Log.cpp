#include "Log.h"

Log::Log(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this); 
}

Log::~Log()
{
}

/// <summary>
/// ����û�����
/// </summary>
/// <returns></returns>
bool Log::CheckInput()
{
	
	//�ж��Ƿ��п�����
	if (ui.idline->text().isEmpty() || ui.passwordline->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString(u8"����"), QString(u8"�������˻���������"), QMessageBox::Ok);
		return false;
	}
	
	return true;
}
