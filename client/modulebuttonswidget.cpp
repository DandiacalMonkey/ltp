#include "modulebuttonswidget.h"

#include <QButtonGroup>

using ltp::client::ModuleButtonsWidget;

ModuleButtonsWidget::ModuleButtonsWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 建立互斥性
	setExclusive(true);

	buttonGroup_ = new QButtonGroup(this);
	buttonGroup_->addButton(ui.moduleButton1_, BUTTON1);
	buttonGroup_->addButton(ui.moduleButton2_, BUTTON2);
	buttonGroup_->addButton(ui.moduleButton3_, BUTTON3);
	buttonGroup_->addButton(ui.moduleButton4_, BUTTON4);
	buttonGroup_->addButton(ui.moduleButton5_, BUTTON5);
	buttonGroup_->addButton(ui.moduleButton6_, BUTTON6);

	// buttonGroup_信号槽
	connect(buttonGroup_, SIGNAL(buttonClicked(int)), SIGNAL(signalButtonClicked(int)));
	connect(buttonGroup_, SIGNAL(buttonPressed(int)), SIGNAL(signalButtonPressed(int)));
	connect(buttonGroup_, SIGNAL(buttonReleased(int)), SIGNAL(signalButtonReleased(int)));
	// 返回按钮信号槽
	connect(ui.returnButton_, SIGNAL(clicked(bool)), SIGNAL(signalReturnButtonClicked()));
}

ModuleButtonsWidget::~ModuleButtonsWidget()
{

}

void ModuleButtonsWidget::setButtonEnabled(int id, bool enabled)
{
	switch(id)
	{
	case BUTTON1:
		ui.moduleButton1_->setEnabled(enabled);
		break;
	case BUTTON2:
		ui.moduleButton2_->setEnabled(enabled);
		break;
	case BUTTON3:
		ui.moduleButton3_->setEnabled(enabled);
		break;
	case BUTTON4:
		ui.moduleButton4_->setEnabled(enabled);
		break;
	case BUTTON5:
		ui.moduleButton5_->setEnabled(enabled);
		break;
	case BUTTON6:
		ui.moduleButton6_->setEnabled(enabled);
		break;
	default:
		break;
	}
}

void ModuleButtonsWidget::setReturnButtonEnabled(bool enabled)
{
	ui.returnButton_->setEnabled(enabled);
}

void ModuleButtonsWidget::setCommandButtonName(int id, QString name)
{
	// 设置按钮名
	if (id == BUTTON1)
	{
		ui.moduleButton1_->setText(name);
	} 
	else if (id == BUTTON2)
	{
		ui.moduleButton2_->setText(name);
	}
	else if (id == BUTTON3)
	{
		ui.moduleButton3_->setText(name);
	}
	else if (id == BUTTON4)
	{
		ui.moduleButton4_->setText(name);
	}
	else if (id == BUTTON5)
	{
		ui.moduleButton5_->setText(name);
	}
	else if (id == BUTTON6)
	{
		ui.moduleButton6_->setText(name);
	}
}

void ModuleButtonsWidget::setCheckedButton(int id, bool checked)
{
	if (id == BUTTON1)
	{
		ui.moduleButton1_->setChecked(checked);
	} 
	else if (id == BUTTON2)
	{
		ui.moduleButton2_->setChecked(checked);
	}
	else if (id == BUTTON3)
	{
		ui.moduleButton3_->setChecked(checked);
	}
	else if (id == BUTTON4)
	{
		ui.moduleButton4_->setChecked(checked);
	}
	else if (id == BUTTON5)
	{
		ui.moduleButton5_->setChecked(checked);
	}
	else if (id == BUTTON6)
	{
		ui.moduleButton6_->setChecked(checked);
	}
}

void ModuleButtonsWidget::setExclusive(bool exclusive)
{
	// 建立互斥性
	ui.moduleButton1_->setAutoExclusive(exclusive);
	ui.moduleButton2_->setAutoExclusive(exclusive);
	ui.moduleButton3_->setAutoExclusive(exclusive);
	ui.moduleButton4_->setAutoExclusive(exclusive);
	ui.moduleButton5_->setAutoExclusive(exclusive);
	ui.moduleButton6_->setAutoExclusive(exclusive);
}

void ModuleButtonsWidget::setCheckableButton(bool checked)
{
	// Checkable设置
	ui.moduleButton1_->setCheckable(checked);
	ui.moduleButton2_->setCheckable(checked);
	ui.moduleButton3_->setCheckable(checked);
	ui.moduleButton4_->setCheckable(checked);
	ui.moduleButton5_->setCheckable(checked);
	ui.moduleButton6_->setCheckable(checked);
	ui.returnButton_->setCheckable(checked);
}