#include "maincontainer.h"

using ltp::client::MainContainer;

MainContainer::MainContainer(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	// ��ʾ��Ϣ
	connect(ui.fileManagerWidget_, SIGNAL(signalTips(QString)), this, SIGNAL(signalTips(QString)));
	connect(ui.programEditWidget_, SIGNAL(signalTips(QString)), this, SIGNAL(signalTips(QString)));
	// ���˵��л�
	connect(ui.processWidget_, SIGNAL(onModule(int)), this, SLOT(onModule(int)));
	// ���������е�������
	connect(ui.processWidget_, SIGNAL(onHome()), this, SLOT(onHome()));
	connect(ui.programEditWidget_, SIGNAL(onHome()), this, SLOT(onHome()));
	connect(ui.fileManagerWidget_, SIGNAL(onHome()), this, SLOT(onHome()));

	// �е��ӹ�����, ִ���ļ�
	connect(ui.fileManagerWidget_, SIGNAL(onProcessFile(QString)), this, SLOT(onProcessModule(QString)));
	connect(ui.fileManagerWidget_, SIGNAL(onProcessFile(QString)), ui.processWidget_, SIGNAL(processFile(QString)));
	connect(ui.programEditWidget_, SIGNAL(processFile(QString)), this, SLOT(onProcessModule(QString)));
	connect(ui.programEditWidget_, SIGNAL(processFile(QString)), ui.processWidget_, SIGNAL(processFile(QString)));

	// �е��ļ��༭���棬���ļ�
	connect(ui.fileManagerWidget_, SIGNAL(onOpenFile(QString)), ui.programEditWidget_, SIGNAL(openFile(QString)));
	connect(ui.fileManagerWidget_, SIGNAL(onOpenFile(QString)), this, SLOT(onEditModule()));

	// �༭���汣�棬ͬʱ���ص�ftp�ͻ���
	connect(ui.programEditWidget_, SIGNAL(signalSaved(QString)), ui.fileManagerWidget_, SIGNAL(signalSaved(QString)));
}

MainContainer::~MainContainer()
{

}

void MainContainer::onModule(int moduleIndex)
{
	switch(moduleIndex)
	{
	case BUTTON1:					// �ӹ�����
		ui.mainContainerClassStackedWidget_->setCurrentWidget(ui.processWidget_);
		ui.processWidget_->changeModule(PROCESS_WIDGET);
		emit signalChangeModules(QString(tr("�ӹ�")));
		break;
	case BUTTON2:					// �ļ��������
		ui.mainContainerClassStackedWidget_->setCurrentWidget(ui.fileManagerWidget_);
		ui.fileManagerWidget_->onStartPage();
		emit signalChangeModules(QString(tr("�ļ�����")));
		break;
	case BUTTON3:					// �༭����
		ui.mainContainerClassStackedWidget_->setCurrentWidget(ui.programEditWidget_);
		ui.programEditWidget_->onStartPage();
		emit signalChangeModules(QString(tr("�༭")));
		break;
	default:
		break;
	}
}

void MainContainer::onHome()
{
	// �л���������
	ui.mainContainerClassStackedWidget_->setCurrentWidget(ui.processWidget_);
	ui.processWidget_->changeModule(MAIN_WIDGET);
	emit signalChangeModules(QString(tr("��ҳ")));
}

void MainContainer::onEditModule()
{
	// �л�������༭����
	onModule(BUTTON3);
}

void MainContainer::onProcessModule(QString fileName)
{
	// �л����ӹ�ģ��
	onModule(BUTTON1);
	// �������ļ����޸�
	emit signalChangeProcessFileName(fileName);
}