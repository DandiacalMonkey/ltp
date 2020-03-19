#include "setwidget.h"

using ltp::client::SetWidget;

SetWidget::SetWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connectState(false);			// 初始连接状态
	connect(ui.connectButton_, SIGNAL(clicked(bool)), this, SLOT(connectClicked(bool)));
}

SetWidget::~SetWidget()
{
	
}

void SetWidget::connectState(bool connected)
{
	if (connected)			// 连接状态改变按钮文字，输入框禁用
	{
		ui.connectButton_->setText(tr("断开"));
		ui.controllerIPLineEdit_->setEnabled(false);
		ui.teachIPLineEdit_->setEnabled(false);
	} 
	else					// 断开状态改变按钮文字，输入框启用
	{
		ui.connectButton_->setText(tr("连接"));
		ui.controllerIPLineEdit_->setEnabled(true);
		ui.teachIPLineEdit_->setEnabled(true);
	}
}

void SetWidget::connectClicked(bool)
{
	if (ui.connectButton_->text() == tr("断开"))
	{
		emit connectIP(ui.controllerIPLineEdit_->getIP(), ui.teachIPLineEdit_->getIP(), false);
	}
	else if (ui.connectButton_->text() == tr("连接"))
	{
		emit connectIP(ui.controllerIPLineEdit_->getIP(), ui.teachIPLineEdit_->getIP(), true);
	}
}