#include "programeditwidget.h"

using ltp::client::ProgramEditWidget;

ProgramEditWidget::ProgramEditWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 左侧按钮栏设置
	ui.editModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON1, QString(tr("程序编辑")));
	ui.editModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON2, QString(tr("示教编辑")));
	ui.editModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON3, QString(tr("编辑示教")));
	ui.editModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON5, QString(tr("执行")));
	ui.editModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON6, QString(tr("关闭")));
}

ProgramEditWidget::~ProgramEditWidget()
{
}
