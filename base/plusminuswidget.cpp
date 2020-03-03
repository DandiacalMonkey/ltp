#include "plusminuswidget.h"

#include <QButtonGroup>

using ltp::base::PlusMinusWidget;

PlusMinusWidget::PlusMinusWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setValue(100);
	connect(ui.minus_, SIGNAL(clicked()), this, SLOT(minusClicked()));
	connect(ui.plus_, SIGNAL(clicked()), this, SLOT(plusClicked()));
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

void PlusMinusWidget::plusClicked()
{
	// 每次点击“+”按钮，以当前值+1发送信号
	QString str = ui.valueLabel_->text();
	int value = str.toInt() + 1;
	emit valueChanged(value);
}

void PlusMinusWidget::minusClicked()
{
	// 每次点击“-”按钮，以当前值-1发送信号
	QString str = ui.valueLabel_->text();
	int value = str.toInt() - 1;
	emit valueChanged(value);
}