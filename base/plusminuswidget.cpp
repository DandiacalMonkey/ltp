#include "plusminuswidget.h"

#include <QButtonGroup>

using ltp::base::PlusMinusWidget;

PlusMinusWidget::PlusMinusWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	currentLevel_ = 0;
	connect(ui.minus_, SIGNAL(clicked()), this, SLOT(minusClicked()));
	connect(ui.plus_, SIGNAL(clicked()), this, SLOT(plusClicked()));
}

PlusMinusWidget::~PlusMinusWidget()
{

}

void PlusMinusWidget::setValue(int value)
{
	// 修改数值
	ui.valueLabel_->setText(QString::number(value));
}

void PlusMinusWidget::plusClicked()
{
	// 每次点击“+”按钮，以当前值+intervalValue_发送信号
	int value = currentLevel_ + intervalValue_;
	if (value >= lowestLevel_ && value <= highestLevel_)
	{
		emit valueChanged(value);
	}
}

void PlusMinusWidget::minusClicked()
{
	// 每次点击“-”按钮，以当前值-intervalValue_发送信号
	int value = currentLevel_ - intervalValue_;
	if (value >= lowestLevel_ && value <= highestLevel_)
	{
		emit valueChanged(value);
	}
} 