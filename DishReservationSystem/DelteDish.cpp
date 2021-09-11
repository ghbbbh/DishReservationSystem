#include "DelteDish.h"

DelteDish::DelteDish(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

DelteDish::~DelteDish()
{
}

/// <summary>
/// 清楚用户输入
/// </summary>
void DelteDish::on_clearButton_clicked()
{
	ui.lineEdit->clear();
}

