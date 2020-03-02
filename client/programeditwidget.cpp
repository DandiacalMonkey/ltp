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

	// 示教编程按钮栏设置
	ui.teachEditModuleButtonWidget_->hide();
	ui.teachEditModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON1, QString(tr("G114")));
	ui.teachEditModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON2, QString(tr("G00")));
	ui.teachEditModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON3, QString(tr("G01")));
	ui.teachEditModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON4, QString(tr("G02")));
	ui.teachEditModuleButtonWidget_->setCommandButtonName(ltp::client::BUTTON5, QString(tr("G102")));

	// 返回主界面
	connect(ui.editModuleButtonWidget_, SIGNAL(signalReturnButtonClicked()), this, SIGNAL(onHome()));
	// 编辑界面切换
	connect(ui.editModuleButtonWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onEditModule(int)));
	// 示教编辑
	connect(ui.teachEditModuleButtonWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(returnProgrameEdit()));
	// 打开文件
	connect(this, SIGNAL(openFile(QString)), ui.programEditBar_, SLOT(onOpenFile(QString)));
	// 提示信息
	connect(ui.programEditBar_, SIGNAL(signalTips(QString)), this, SIGNAL(signalTips(QString)));
	// 示教编辑模块切换
	connect(ui.teachEditModuleButtonWidget_, SIGNAL(signalButtonClicked(int)), ui.programEditBar_, SLOT(onTeachEditModule(int)));
}

ProgramEditWidget::~ProgramEditWidget()
{

}

void ProgramEditWidget::onEditModule(int index)
{
	switch(index)
	{
	case BUTTON1:			// 程序编辑
		ui.teachEditModuleButtonWidget_->hide();
		ui.editModuleButtonWidget_->show();
		ui.programEditBar_->onEditBarModule(BUTTON1);
		break;
	case BUTTON2:			// 示教编程
		ui.editModuleButtonWidget_->hide();
		ui.teachEditModuleButtonWidget_->show();
		ui.programEditBar_->onEditBarModule(BUTTON2);
		break;
	case BUTTON3:			// 编辑示教
		ui.programEditBar_->onEditBarModule(BUTTON3);
		break;
	case BUTTON5:			// 执行
		{
			// 检查文件是否修改
			ui.programEditBar_->checkCurrentFileModified();
			QString filename = ui.programEditBar_->getCurrentFileName();
			// 转到加工界面
			emit processFile(filename);
			break;
		}		
	case BUTTON6:			// 关闭
		ui.programEditBar_->closeFile();
		break;
	default:
		break;
	}
}

void ProgramEditWidget::returnProgrameEdit()
{
	onStartPage();
}

void ProgramEditWidget::onStartPage()
{
	// 切到程序编辑界面
	onEditModule(BUTTON1);
	ui.editModuleButtonWidget_->setCheckedButton(BUTTON1, true);
}
