#include "plusminuswidget.h"

#include <QButtonGroup>

using ltp::base::PlusMinusWidget;

PlusMinusWidget::PlusMinusWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setValue(100);
}

PlusMinusWidget::~PlusMinusWidget()
{

}

void PlusMinusWidget::setValue(int value)
{
	// 修改数值
	QString text = QString::number(value) + QString("%");
	ui.valueLabel_->setText(text);
}
