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
/// ����û�����
/// </summary>
void DelteDish::on_clearButton_clicked()
{
	ui.lineEdit->clear();
}

