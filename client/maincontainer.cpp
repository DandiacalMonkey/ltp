#include "maincontainer.h"
#include "base/globals.h"
#include "physicalbuttonsprocessor.h"
#include "network.h"
#include "machiningstates.h"
#include "teachcommandline.h"
#include "teachcommandg114.h"
#include "teachcommandplanararc.h"
#include "teachcommandspatialarc.h"
#include "teachcommandpoint.h"
#include "teachcommandspatialcircle.h"
#include "hintwidgetproxy.h"
#include "hintbar.h"

using ltp::client::MainContainer;

MainContainer::MainContainer(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initModuleButtonsWidget();
	// 网络联通后，尝试连接ftp
	connect(&base::getInstance<Network>(), SIGNAL(connected(const std::string&)), ui.fileManagerWidget_, SLOT(connectToFtp(const std::string&)));
	// 主菜单切换
	connect(ui.homeModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onModule(int)));
	// 其他界面切到主界面
	connect(ui.fileManagerModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	connect(ui.programEditModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	connect(ui.processModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	connect(ui.setModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	// 文件管理界面，左侧按钮切换
	connect(ui.fileManagerModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onFileWidgetModule(int)));
	// 文件管理界面，执行、打开按钮是否enable
	connect(ui.fileManagerWidget_, SIGNAL(selectedFile()), SLOT(selectedFile()));
	connect(ui.fileManagerWidget_, SIGNAL(selectedFolder()), SLOT(selectedFolder()));
	connect(ui.fileManagerWidget_, SIGNAL(selectedNone()), SLOT(selectedNone()));
	// 文件打开
	connect(ui.fileManagerWidget_, SIGNAL(openFtpFile(const QString&, const QString&)), SLOT(openEditFile(const QString&, const QString&)));
	connect(ui.fileManagerWidget_, SIGNAL(executeFtpFile(const QString&)), SLOT(openProcessFile(const QString&)));
	// 编辑界面保存，同时上载到ftp客户端
	connect(ui.programEditWidget_, SIGNAL(signalSaved(QString)), ui.fileManagerWidget_, SLOT(uploadFile(QString)));
	// 加工界面，左侧按钮切换
	connect(ui.processModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onProcessWidgetModule(int)));
	// 编辑界面，左侧按钮切换
	connect(ui.programEditModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onProgrameEditWidgetModule(int)));
	// 编辑界面，文件是否可执行，可编辑
	connect(ui.programEditWidget_, SIGNAL(signalFileOpened()), SLOT(editModuleFileEnable()));
	connect(ui.programEditWidget_, SIGNAL(signalFileClosed()), SLOT(editModuleFileDisable()));
	// 示教编辑界面，左侧按钮切换
	connect(ui.teachEditModuleButtonsWidget1_, SIGNAL(signalButtonClicked(int)), this, SLOT(onProgramTeachEditModule1(int)));
	connect(ui.teachEditModuleButtonsWidget1_, SIGNAL(signalReturnButtonClicked()), this, SLOT(backProgrameModule()));
	connect(ui.teachEditModuleButtonsWidget2_, SIGNAL(signalButtonClicked(int)), this, SLOT(onProgramTeachEditModule2(int)));
	connect(ui.teachEditModuleButtonsWidget2_, SIGNAL(signalReturnButtonClicked()), this, SLOT(backProgrameModule()));
	// 示教编程操作界面
	connect(ui.teachEditOperationButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(teachEditOperation(int)));
	connect(ui.teachEditOperationButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(backTeachModule()));
	connect(ui.programEditWidget_, SIGNAL(signalTeachIsLastPoint(bool)), this, SLOT(teachIsLastPoint(bool)));
	connect(ui.programEditWidget_, SIGNAL(signalTeachPreviousEnabled(bool)), this, SLOT(teachPreviousEnabled(bool)));
	// 外设按钮响应
	connect(&base::getInstance<PhysicalButtonsProcessor>(), SIGNAL(returnButtonClicked()), this, SLOT(returnButtonClicked()));
	connect(&base::getInstance<PhysicalButtonsProcessor>(), SIGNAL(leftButtonClicked(int)), this, SLOT(leftButtonClicked(int)));
}

MainContainer::~MainContainer()
{
	
}

void MainContainer::openProcessFile(const QString& remoteFtpFilePath)
{
	//当前模式，不为自动时报错
	if (base::getInstance<MachiningStates>().mode() != base::MEMORY)
	{
		base::getInstance<HintWidgetProxy<HintBar>>().setHint(tr("请切换到自动模式下执行"));
	}
	//正在加工中，不能执行文件
	else if (base::getInstance<MachiningStates>().machiningState() == base::BUSY)
	{
		base::getInstance<HintWidgetProxy<HintBar>>().setHint(tr("请先停止加工并复位后再执行"));
	}
	else
	{
		//切换到加工界面
		onModule(base::LEFTBUTTON1);
		//远程加载
		base::getInstance<MachiningStates>().remoteOpenFtpFile(remoteFtpFilePath);
	}
}

void MainContainer::leftButtonClicked(int key)
{
	// 外设按键切换当前界面
	auto tempWidget = ui.moduleButtonsWidget_->currentWidget();
	ModuleButtonsWidget *currentModuleWidget = static_cast<ModuleButtonsWidget*>(tempWidget);
	currentModuleWidget->setButtonClicked(key);
}

void MainContainer::returnButtonClicked()
{
	// 外设切换返回按钮
	auto tempWidget = ui.moduleButtonsWidget_->currentWidget();
	ModuleButtonsWidget *currentModuleWidget = static_cast<ModuleButtonsWidget*>(tempWidget);
	currentModuleWidget->setReturnButtonClicked();
}

void ltp::client::MainContainer::teachIsLastPoint(bool isLast)
{
	ui.teachEditOperationButtonsWidget_->setCommandButtonName(base::LEFTBUTTON6, isLast ? "确定" : "记录点");
}

void ltp::client::MainContainer::teachPreviousEnabled(bool enabled)
{
	ui.teachEditOperationButtonsWidget_->setButtonEnabled(base::LEFTBUTTON4, enabled);
}

void ltp::client::MainContainer::editModuleFileEnable()
{
	ui.programEditModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON2, true);
	ui.programEditModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, true);
}

void ltp::client::MainContainer::editModuleFileDisable()
{
	ui.programEditModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON2, false);
	ui.programEditModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, false);
}

void MainContainer::openEditFile(const QString& localFilePath, const QString& remoteFtpFilePath)
{
	//切换到编辑界面
	onModule(base::LEFTBUTTON3);
	//打开文件
	ui.programEditWidget_->onOpenFile(localFilePath);
	//将文件名修改为远程文件名
	ui.programEditWidget_->setRemoteFilePath(remoteFtpFilePath);
}

void MainContainer::initModuleButtonsWidget()
{
	// 加工界面左侧按钮栏设置
	ui.processModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("加工状态")));
	ui.processModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("坐标系")));
	ui.processModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("起始行")));
	ui.processModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON2, false);
	ui.processModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON3, false);
	ui.processModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON4, false);
	ui.processModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, false);
	ui.processModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON6, false);

	// 主界面左侧按钮栏设置
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("加工")));
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("文件管理")));
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON3, QString(tr("编辑")));
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON4, QString(tr("设置")));
	ui.homeModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, false);
	ui.homeModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON6, false);
	ui.homeModuleButtonsWidget_->setCheckableButton(false);
	ui.homeModuleButtonsWidget_->setReturnButtonEnabled(false);

	// 编辑界面左侧按钮栏设置
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("程序编辑")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("示教编辑")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON3, QString(tr("编辑示教")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON5, QString(tr("执行")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("关闭")));
	ui.programEditModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON2, false);
	ui.programEditModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON3, false);
	ui.programEditModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON4, false);
	ui.programEditModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, false);

	// 文件管理界面左侧按钮栏设置
	ui.fileManagerModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("用户盘")));
	ui.fileManagerModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON5, QString(tr("执行")));
	ui.fileManagerModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("打开")));
	ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON2, false);
	ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON3, false);
	ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON4, false);
	ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, false);
	ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON6, false);

	// 编辑界面左侧按钮栏设置
	ui.teachEditModuleButtonsWidget1_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("G114")));
	ui.teachEditModuleButtonsWidget1_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("快速定位")));
	ui.teachEditModuleButtonsWidget1_->setCommandButtonName(base::LEFTBUTTON3, QString(tr("直线")));
	ui.teachEditModuleButtonsWidget1_->setCommandButtonName(base::LEFTBUTTON4, QString(tr("平面圆弧")));
	ui.teachEditModuleButtonsWidget1_->setCommandButtonName(base::LEFTBUTTON5, QString(tr("空间圆弧")));
	ui.teachEditModuleButtonsWidget1_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("下一页")));
	ui.teachEditModuleButtonsWidget1_->setCheckableButton(false);

	// 编辑界面左侧按钮栏设置
	ui.teachEditModuleButtonsWidget2_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("点坐标")));
	ui.teachEditModuleButtonsWidget2_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("空间整圆")));
	ui.teachEditModuleButtonsWidget2_->setButtonEnabled(base::LEFTBUTTON3, false);
	ui.teachEditModuleButtonsWidget2_->setButtonEnabled(base::LEFTBUTTON4, false);
	ui.teachEditModuleButtonsWidget2_->setButtonEnabled(base::LEFTBUTTON5, false);
	ui.teachEditModuleButtonsWidget2_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("上一页")));
	ui.teachEditModuleButtonsWidget2_->setCheckableButton(false);

	// 设置界面左侧按钮栏设置
	ui.setModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("连接设置")));
	ui.setModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON2, false);
	ui.setModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON3, false);
	ui.setModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON4, false);
	ui.setModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, false);
	ui.setModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON6, false);

	// 示教编程操作按钮栏设置
	ui.teachEditOperationButtonsWidget_->setButtonEnabled(base::LEFTBUTTON1, false);
	ui.teachEditOperationButtonsWidget_->setButtonEnabled(base::LEFTBUTTON2, false);
	ui.teachEditOperationButtonsWidget_->setCommandButtonName(base::LEFTBUTTON3, QString(tr("模式切换")));
	ui.teachEditOperationButtonsWidget_->setCommandButtonName(base::LEFTBUTTON4, QString(tr("上一点")));
	ui.teachEditOperationButtonsWidget_->setCommandButtonName(base::LEFTBUTTON5, QString(tr("取消")));
	ui.teachEditOperationButtonsWidget_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("确定")));
	ui.teachEditOperationButtonsWidget_->setCheckableButton(false);
}

void MainContainer::backProgrameModule()
{
	// 返回程序编辑界面
	onProgrameEditWidgetModule(base::LEFTBUTTON1);
	ui.programEditModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
}

void ltp::client::MainContainer::teachEditOperation(int module)
{
	switch (module)
	{
	case base::LEFTBUTTON3:
		ui.programEditWidget_->modeChange();
		break;
	case base::LEFTBUTTON4:
		ui.programEditWidget_->previousPoint();
		break;
	case base::LEFTBUTTON5:
		ui.programEditWidget_->cancelTeach();
		break;
	case base::LEFTBUTTON6:
		ui.programEditWidget_->checkPoint();
		break;
	default:
		break;
	}
}

void MainContainer::backTeachModule()
{
	// 返回示教模块选择
	onProgrameEditWidgetModule(base::LEFTBUTTON2);
	// 切换储存的菜单
	ui.moduleButtonsWidget_->setCurrentWidget(lastModuleButtonsWidget_);
}

void MainContainer::onProcessWidgetModule(int module)
{
	// 加工界面切换
	switch (module)
	{
	case base::LEFTBUTTON1:					// 加工状态
		break;
	case base::LEFTBUTTON2:					// 坐标系
		break;
	case base::LEFTBUTTON6:					// 起始行
		break;
	default:
		break;
	}
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
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditModuleButtonsWidget1_);
		ui.programEditWidget_->onEditBarModule(module);
		break;
	case base::LEFTBUTTON3:					// 编辑示教
		ui.programEditWidget_->onEditBarModule(module);
		break;
	case base::LEFTBUTTON5:					// 执行
		ui.programEditWidget_->saveFile();
		ui.fileManagerWidget_->executeLastOpenedFile();
		break;
	case base::LEFTBUTTON6:					// 关闭
		ui.programEditWidget_->closeFile();
		break;
	default:
		break;
	}
}

void MainContainer::onProgramTeachEditModule1(int module)
{
	//储存指针，用于记录返回时应返回的页面
	lastModuleButtonsWidget_ = ui.teachEditModuleButtonsWidget1_;
	switch (module)
	{
	case base::LEFTBUTTON1:						// G114
		ui.programEditWidget_->onTeachEditModule(
			std::shared_ptr<TeachCommand>(new TeachCommandG114()));
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditOperationButtonsWidget_);
		break;
	case base::LEFTBUTTON2:						// G00
		ui.programEditWidget_->onTeachEditModule(
			std::shared_ptr<TeachCommand>(new TeachCommandLine("G00", ":/LtpClient/image/teach_command_g00.png")));
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditOperationButtonsWidget_);
		break;
	case base::LEFTBUTTON3:						// G01
		ui.programEditWidget_->onTeachEditModule(
			std::shared_ptr<TeachCommand>(new TeachCommandLine("G01", ":/LtpClient/image/teach_command_g01.png")));
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditOperationButtonsWidget_);
		break;
	case base::LEFTBUTTON4:						// G02,G03
		ui.programEditWidget_->onTeachEditModule(
			std::shared_ptr<TeachCommand>(new TeachCommandPlanarArc()));
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditOperationButtonsWidget_);
		break;
	case base::LEFTBUTTON5:						// G02.4圆弧
		ui.programEditWidget_->onTeachEditModule(
			std::shared_ptr<TeachCommand>(new TeachCommandSpatialArc()));
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditOperationButtonsWidget_);
		break;
	case base::LEFTBUTTON6:						// 下一页
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditModuleButtonsWidget2_);
		break;
	default:
		break;
	}
}

void MainContainer::onProgramTeachEditModule2(int module)
{
	//储存指针，用于记录返回时应返回的页面
	lastModuleButtonsWidget_ = ui.teachEditModuleButtonsWidget2_;
	switch (module)
	{
	case base::LEFTBUTTON1:						// 点坐标
		ui.programEditWidget_->onTeachEditModule(
			std::shared_ptr<TeachCommand>(new TeachCommandPoint()));
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditOperationButtonsWidget_);
		break;
	case base::LEFTBUTTON2:						// 空间整圆
		ui.programEditWidget_->onTeachEditModule(
			std::shared_ptr<TeachCommand>(new TeachCommandSpatialCircle()));
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditOperationButtonsWidget_);
		break;
	case base::LEFTBUTTON6:						// 上一页
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditModuleButtonsWidget1_);
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
			ui.fileManagerWidget_->executeCurrentItem();
		}		
		break;
	case base::LEFTBUTTON6:					// 打开，切到编辑界面
		{
			ui.fileManagerWidget_->openCurrentItem();
		}
		break;
	default:
		break;
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
		ui.mainContainerWidget_->setCurrentWidget(ui.setWidget_);
		ui.moduleButtonsWidget_->setCurrentWidget(ui.setModuleButtonsWidget_);	
		ui.setModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
		emit signalChangeModules(QString(tr("设置")));
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

void ltp::client::MainContainer::selectedFile()
{
	ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, true);
	ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON6, true);
}

void ltp::client::MainContainer::selectedFolder()
{
	ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, false);
	ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON6, true);
}

void ltp::client::MainContainer::selectedNone()
{
	ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON5, false);
	ui.fileManagerModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON6, false);
}
