#include "modulebuttonswidget.h"

#include <QButtonGroup>

using ltp::client::ModuleButtonsWidget;

ModuleButtonsWidget::ModuleButtonsWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 建立互斥性
	ui.moduleButton1_->setAutoExclusive(true);
	ui.moduleButton2_->setAutoExclusive(true);
	ui.moduleButton3_->setAutoExclusive(true);
	ui.moduleButton4_->setAutoExclusive(true);
	ui.moduleButton5_->setAutoExclusive(true);
	ui.moduleButton6_->setAutoExclusive(true);

	buttonGroup_ = new QButtonGroup(this);
	buttonGroup_->addButton(ui.moduleButton1_, BUTTON1);
	buttonGroup_->addButton(ui.moduleButton2_, BUTTON2);
	buttonGroup_->addButton(ui.moduleButton3_, BUTTON3);
	buttonGroup_->addButton(ui.moduleButton4_, BUTTON4);
	buttonGroup_->addButton(ui.moduleButton5_, BUTTON5);
	buttonGroup_->addButton(ui.moduleButton6_, BUTTON6);

	// buttonGroup_信号槽
	connect(buttonGroup_, SIGNAL(buttonClicked(int)), SIGNAL(buttonClicked(int)));
	connect(buttonGroup_, SIGNAL(buttonPressed(int)), SIGNAL(buttonPressed(int)));
	connect(buttonGroup_, SIGNAL(buttonReleased(int)), SIGNAL(buttonReleased(int)));
	// 返回按钮信号槽
	connect(ui.returnButton_, SIGNAL(buttonClicked(int)), SIGNAL(returnButtonClicked(int)));
}

ModuleButtonsWidget::~ModuleButtonsWidget()
{

}

void ModuleButtonsWidget::setButtonEnabled(bool enabled)
{

}

void ModuleButtonsWidget::setReturnButtonEnabled(bool enabled)
{
	ui.returnButton_->setEnabled(enabled);
}

void ModuleButtonsWidget::setCommandButtonName(int id, QString name)
{
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