#include "maincontainer.h"

using ltp::client::MainContainer;

MainContainer::MainContainer(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	// 提示信息
	connect(ui.fileManagerWidget_, SIGNAL(signalTips(QString)), this, SIGNAL(signalTips(QString)));
	connect(ui.programEditWidget_, SIGNAL(signalTips(QString)), this, SIGNAL(signalTips(QString)));
	// 主菜单切换
	connect(ui.processWidget_, SIGNAL(onModule(int)), this, SLOT(onModule(int)));
	// 其他界面切到主界面
	connect(ui.processWidget_, SIGNAL(onHome()), this, SLOT(onHome()));
	connect(ui.programEditWidget_, SIGNAL(onHome()), this, SLOT(onHome()));
	connect(ui.fileManagerWidget_, SIGNAL(onHome()), this, SLOT(onHome()));

	// 切到加工界面, 执行文件
	connect(ui.fileManagerWidget_, SIGNAL(onProcessFile(QString)), this, SLOT(onProcessModule(QString)));
	connect(ui.fileManagerWidget_, SIGNAL(onProcessFile(QString)), ui.processWidget_, SIGNAL(processFile(QString)));
	connect(ui.programEditWidget_, SIGNAL(processFile(QString)), this, SLOT(onProcessModule(QString)));
	connect(ui.programEditWidget_, SIGNAL(processFile(QString)), ui.processWidget_, SIGNAL(processFile(QString)));

	// 切到文件编辑界面，打开文件
	connect(ui.fileManagerWidget_, SIGNAL(onOpenFile(QString)), ui.programEditWidget_, SIGNAL(openFile(QString)));
	connect(ui.fileManagerWidget_, SIGNAL(onOpenFile(QString)), this, SLOT(onEditModule()));

	// 编辑界面保存，同时上载到ftp客户端
	connect(ui.programEditWidget_, SIGNAL(signalSaved(QString)), ui.fileManagerWidget_, SIGNAL(signalSaved(QString)));
}

MainContainer::~MainContainer()
{

}

void MainContainer::onModule(int moduleIndex)
{
	switch(moduleIndex)
	{
	case BUTTON1:					// 加工界面
		ui.mainContainerClassStackedWidget_->setCurrentWidget(ui.processWidget_);
		ui.processWidget_->changeModule(PROCESS_WIDGET);
		emit signalChangeModules(QString(tr("加工")));
		break;
	case BUTTON2:					// 文件管理界面
		ui.mainContainerClassStackedWidget_->setCurrentWidget(ui.fileManagerWidget_);
		ui.fileManagerWidget_->onStartPage();
		emit signalChangeModules(QString(tr("文件管理")));
		break;
	case BUTTON3:					// 编辑界面
		ui.mainContainerClassStackedWidget_->setCurrentWidget(ui.programEditWidget_);
		ui.programEditWidget_->onStartPage();
		emit signalChangeModules(QString(tr("编辑")));
		break;
	default:
		break;
	}
}

void MainContainer::onHome()
{
	// 切换到主界面
	ui.mainContainerClassStackedWidget_->setCurrentWidget(ui.processWidget_);
	ui.processWidget_->changeModule(MAIN_WIDGET);
	emit signalChangeModules(QString(tr("主页")));
}

void MainContainer::onEditModule()
{
	// 切换到程序编辑界面
	onModule(BUTTON3);
}

void MainContainer::onProcessModule(QString fileName)
{
	// 切换到加工模块
	onModule(BUTTON1);
	// 标题栏文件名修改
	emit signalChangeProcessFileName(fileName);
}