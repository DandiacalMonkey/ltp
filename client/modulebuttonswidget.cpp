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
	connect(buttonGroup_, SIGNAL(buttonClicked(int)), this, SLOT(buttonClicked(int)));
	connect(buttonGroup_, SIGNAL(buttonPressed(int)), this, SLOT(buttonPressed(int)));
	connect(buttonGroup_, SIGNAL(buttonReleased(int)), this, SLOT(buttonReleased(int)));
	// 返回按钮信号槽
	connect(ui.returnButton_, SIGNAL(buttonClicked(int)), this, SLOT(returnButtonClicked(int)));
}

ModuleButtonsWidget::~ModuleButtonsWidget()
{

}


void ModuleButtonsWidget::buttonClicked(int id)
{
	
}

void ModuleButtonsWidget::buttonPressed(int id)
{

}

void ModuleButtonsWidget::buttonReleased(int id)
{

}

void ModuleButtonsWidget::returnButtonClicked()
{

}

void ModuleButtonsWidget::setButtonEnabled(bool enabled)
{

}

void ModuleButtonsWidget::setReturnButtonEnabled(bool enabled)
{
	ui.returnButton_->setEnabled(enabled);
}