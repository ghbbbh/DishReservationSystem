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
/// 检查用户输入
/// </summary>
/// <returns></returns>
bool Log::CheckInput()
{
	
	//判断是否有空输入
	if (ui.idline->text().isEmpty() || ui.passwordline->text().isEmpty())
	{
		QMessageBox::warning(NULL, QString(u8"警告"), QString(u8"请输入账户或者密码"), QMessageBox::Ok);
		return false;
	}
	
	return true;
}
