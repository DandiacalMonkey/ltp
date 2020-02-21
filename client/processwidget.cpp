#include "processwidget.h"

using ltp::client::ProcessWidget;

ProcessWidget::ProcessWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 左侧按钮栏设置
	ui.processModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON1, QString(tr("加工状态")));
	ui.processModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON2, QString(tr("坐标系")));
	ui.processModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON6, QString(tr("起始行")));
}

ProcessWidget::~ProcessWidget()
{
}
