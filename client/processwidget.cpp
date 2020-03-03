#include "processwidget.h"

using ltp::client::ProcessWidget;

ProcessWidget::ProcessWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 加工界面左侧按钮栏设置
	ui.processModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON1, QString(tr("加工状态")));
	ui.processModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON2, QString(tr("坐标系")));
	ui.processModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON6, QString(tr("起始行")));
	ui.processModuleButtonWidget_->hide();
	ui.mainModuleButtonWidget_->setReturnButtonEnabled(false);

	// 主界面左侧按钮栏设置
	ui.mainModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON1, QString(tr("加工")));
	ui.mainModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON2, QString(tr("文件管理")));
	ui.mainModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON3, QString(tr("编辑")));
	ui.mainModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON4, QString(tr("设置")));
	ui.mainModuleButtonWidget_->setCheckableButton(false);

	// disable现未做的设置,起始行和坐标系
	ui.processModuleButtonWidget_->setButtonEnabled(ltp::client::BUTTON2, false);
	ui.processModuleButtonWidget_->setButtonEnabled(ltp::client::BUTTON6, false);
	ui.mainModuleButtonWidget_->setButtonEnabled(ltp::client::BUTTON4, false);

	// 主界面切换
	connect(ui.mainModuleButtonWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(mainModuleWidgetChanged(int)));
	// 返回主界面
	connect(ui.processModuleButtonWidget_, SIGNAL(signalReturnButtonClicked()), this, SIGNAL(onHome()));
	// 打开加工文件
	connect(this, SIGNAL(processFile(QString)), ui.processWidgetBar_, SLOT(onProcessFile(QString)));
}

ProcessWidget::~ProcessWidget()
{

}

void ProcessWidget::mainModuleWidgetChanged(int index)
{
	emit onModule(index);
}

void ProcessWidget::changeModule(int widgetID)
{
	ui.processModuleButtonWidget_->hide();
	ui.mainModuleButtonWidget_->hide();
	if (widgetID == MAIN_WIDGET)			// 主界面需要显示的左侧按钮栏
	{
		ui.mainModuleButtonWidget_->show();
		ui.mainModuleButtonWidget_->setReturnButtonEnabled(false);
	} 
	else if (widgetID == PROCESS_WIDGET)	// 加工界面需要显示的左侧按钮栏
	{
		ui.processModuleButtonWidget_->show();
		ui.processModuleButtonWidget_->setCheckedButton(ltp::client::BUTTON1, true);
	}
}