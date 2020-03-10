#include "maincontainer.h"
#include "base/globals.h"

using ltp::client::MainContainer;

MainContainer::MainContainer(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initModuleButtonsWidget();
	// 主菜单切换new
	connect(ui.homeModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onModule(int)));
	// 其他界面切到主界面
	connect(ui.fileManagerModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	connect(ui.programEditModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	connect(ui.processModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));

	// 切到加工界面, 执行文件

	// 文件管理界面，左侧按钮切换
	connect(ui.fileManagerModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onFileWidgetModule(int)));
	// 文件管理界面，执行、打开按钮是否enable
	connect(ui.fileManagerWidget_, SIGNAL(downloadEnable(bool)), this, SLOT(enableFileButtons(bool)));
	// 编辑界面保存，同时上载到ftp客户端
	connect(ui.programEditWidget_, SIGNAL(signalSaved(QString)), ui.fileManagerWidget_, SLOT(uploadFile(QString)));
	// 编辑界面，左侧按钮切换new
	connect(ui.programEditModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onProgrameEditWidgetModule(int)));
	// 示教编辑界面，左侧按钮切换new
	connect(ui.teachEditModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), ui.programEditWidget_, SLOT(onTeachEditModule(int)));
	connect(ui.teachEditModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(backProgrameModule()));
}

MainContainer::~MainContainer()
{
	
}

void MainContainer::initModuleButtonsWidget()
{
	// 加工界面左侧按钮栏设置
	ui.processModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("加工状态")));
	ui.processModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("坐标系")));
	ui.processModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("起始行")));
	ui.processModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON2, false);
	ui.processModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON6, false);

	// 主界面左侧按钮栏设置
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("加工")));
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("文件管理")));
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON3, QString(tr("编辑")));
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON4, QString(tr("设置")));
	ui.homeModuleButtonsWidget_->setCheckableButton(false);
	ui.homeModuleButtonsWidget_->setReturnButtonEnabled(false);
	ui.homeModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON4, false);

	// 编辑界面左侧按钮栏设置
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("程序编辑")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("示教编辑")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON3, QString(tr("编辑示教")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON5, QString(tr("执行")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("关闭")));
	ui.programEditModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON3, false);

	// 文件管理界面左侧按钮栏设置
	ui.fileManagerModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("用户盘")));
	ui.fileManagerModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON5, QString(tr("执行")));
	ui.fileManagerModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("打开")));
	enableFileButtons(false);		// 执行、打开初始disable

	// 编辑界面左侧按钮栏设置
	ui.teachEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("G114")));
	ui.teachEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("G00")));
	ui.teachEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON3, QString(tr("G01")));
	ui.teachEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON4, QString(tr("G02")));
	ui.teachEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON5, QString(tr("G102")));
}

void MainContainer::backProgrameModule()
{
	// 返回程序编辑界面
	onProgrameEditWidgetModule(base::LEFTBUTTON1);
	ui.programEditModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
}

void MainContainer::onProgrameEditWidgetModule(int module)
{
	// 编辑界面切换
	switch (module)
	{
	case base::LEFTBUTTON1:					// 程序编辑
		ui.programEditWidget_->onEditBarModule(module);
		ui.moduleButtonsWidget_->setCurrentWidget(ui.programEditModuleButtonsWidget_);
		break;
	case base::LEFTBUTTON2:					// 示教编辑
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditModuleButtonsWidget_);
		ui.teachEditModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
		ui.programEditWidget_->onEditBarModule(module);
		break;
	case base::LEFTBUTTON3:					// 编辑示教
		ui.programEditWidget_->onEditBarModule(module);
		break;
	case base::LEFTBUTTON5:					// 执行
		// todo
		break;
	case base::LEFTBUTTON6:					// 关闭
		ui.programEditWidget_->closeFile();
		break;
	default:
		break;
	}
}

void MainContainer::onFileWidgetModule(int module)
{
	// 文件管理界面切换
	switch (module)
	{
	case base::LEFTBUTTON1:					// 用户盘
		break;
	case base::LEFTBUTTON5:					// 执行，切到加工界面
		{
			QString filename = ui.fileManagerWidget_->getCurrentFileName();
			if (ui.fileManagerWidget_->checkDownload(filename))
			{
				// 切换到加工模块 todo
				//onModule(base::LEFTBUTTON1);
				// 标题栏文件名修改
				//emit signalChangeProcessFileName(fileName);
				//ui.processWidget_->onProcessFile(filename);
			}
		}		
		break;
	case base::LEFTBUTTON6:					// 打开，切到编辑界面
		{
			QString filename = ui.fileManagerWidget_->getCurrentFileName();
			if (ui.fileManagerWidget_->checkDownload(filename))
			{
				// 切换到程序编辑界面 todo
				//onModule(base::LEFTBUTTON3);
				//ui.programEditWidget_->onOpenFile(filename);
			}
		}
		break;
	default:
		break;
	}
}

void MainContainer::enableFileButtons(bool enable)
{
	// 初始禁用文件管理界面执行和打开功能，在选择文件后启用
	if (enable)
	{
		ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, true);
		ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON6, true);
	} 
	else
	{
		ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, false);
		ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON6, false);
	}
}

void MainContainer::onModule(int moduleIndex)
{
	// 主界面切换
	switch (moduleIndex)
	{
	case base::LEFTBUTTON1:					// 加工界面
		ui.mainContainerWidget_->setCurrentWidget(ui.processWidget_);
		ui.moduleButtonsWidget_->setCurrentWidget(ui.processModuleButtonsWidget_);
		ui.processModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
		emit signalChangeModules(QString(tr("加工")));
		break;
	case base::LEFTBUTTON2:					// 文件管理界面
		ui.mainContainerWidget_->setCurrentWidget(ui.fileManagerWidget_);
		ui.moduleButtonsWidget_->setCurrentWidget(ui.fileManagerModuleButtonsWidget_);
		ui.fileManagerModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
		emit signalChangeModules(QString(tr("文件管理")));
		break;
	case base::LEFTBUTTON3:					// 编辑界面
		ui.mainContainerWidget_->setCurrentWidget(ui.programEditWidget_);
		ui.moduleButtonsWidget_->setCurrentWidget(ui.programEditModuleButtonsWidget_);
		ui.programEditModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
		emit signalChangeModules(QString(tr("编辑")));
		break;
	case base::LEFTBUTTON4:					// 设置界面
		break;
	default:
		break;
	}
}

void MainContainer::onHome()
{
	// 切换到主界面
	ui.mainContainerWidget_->setCurrentWidget(ui.processWidget_);
	ui.moduleButtonsWidget_->setCurrentWidget(ui.homeModuleButtonsWidget_);
	emit signalChangeModules(QString(tr("主页")));
}

