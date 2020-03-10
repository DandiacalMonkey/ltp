#include "maincontainer.h"
#include "base/globals.h"

using ltp::client::MainContainer;

MainContainer::MainContainer(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initModuleButtonsWidget();
	// ���˵��л�new
	connect(ui.homeModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onModule(int)));
	// ���������е�������
	connect(ui.fileManagerModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	connect(ui.programEditModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	connect(ui.processModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));

	// �е��ӹ�����, ִ���ļ�

	// �ļ�������棬��ఴť�л�
	connect(ui.fileManagerModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onFileWidgetModule(int)));
	// �ļ�������棬ִ�С��򿪰�ť�Ƿ�enable
	connect(ui.fileManagerWidget_, SIGNAL(downloadEnable(bool)), this, SLOT(enableFileButtons(bool)));
	// �༭���汣�棬ͬʱ���ص�ftp�ͻ���
	connect(ui.programEditWidget_, SIGNAL(signalSaved(QString)), ui.fileManagerWidget_, SLOT(uploadFile(QString)));
	// �༭���棬��ఴť�л�new
	connect(ui.programEditModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onProgrameEditWidgetModule(int)));
	// ʾ�̱༭���棬��ఴť�л�new
	connect(ui.teachEditModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), ui.programEditWidget_, SLOT(onTeachEditModule(int)));
	connect(ui.teachEditModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(backProgrameModule()));
}

MainContainer::~MainContainer()
{
	
}

void MainContainer::initModuleButtonsWidget()
{
	// �ӹ�������ఴť������
	ui.processModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("�ӹ�״̬")));
	ui.processModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("����ϵ")));
	ui.processModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("��ʼ��")));
	ui.processModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON2, false);
	ui.processModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON6, false);

	// ��������ఴť������
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("�ӹ�")));
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("�ļ�����")));
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON3, QString(tr("�༭")));
	ui.homeModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON4, QString(tr("����")));
	ui.homeModuleButtonsWidget_->setCheckableButton(false);
	ui.homeModuleButtonsWidget_->setReturnButtonEnabled(false);
	ui.homeModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON4, false);

	// �༭������ఴť������
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("����༭")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("ʾ�̱༭")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON3, QString(tr("�༭ʾ��")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON5, QString(tr("ִ��")));
	ui.programEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("�ر�")));
	ui.programEditModuleButtonsWidget_->setButtonEnabled(base::LEFTBUTTON3, false);

	// �ļ����������ఴť������
	ui.fileManagerModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("�û���")));
	ui.fileManagerModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON5, QString(tr("ִ��")));
	ui.fileManagerModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON6, QString(tr("��")));
	enableFileButtons(false);		// ִ�С��򿪳�ʼdisable

	// �༭������ఴť������
	ui.teachEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("G114")));
	ui.teachEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON2, QString(tr("G00")));
	ui.teachEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON3, QString(tr("G01")));
	ui.teachEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON4, QString(tr("G02")));
	ui.teachEditModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON5, QString(tr("G102")));
}

void MainContainer::backProgrameModule()
{
	// ���س���༭����
	onProgrameEditWidgetModule(base::LEFTBUTTON1);
	ui.programEditModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
}

void MainContainer::onProgrameEditWidgetModule(int module)
{
	// �༭�����л�
	switch (module)
	{
	case base::LEFTBUTTON1:					// ����༭
		ui.programEditWidget_->onEditBarModule(module);
		ui.moduleButtonsWidget_->setCurrentWidget(ui.programEditModuleButtonsWidget_);
		break;
	case base::LEFTBUTTON2:					// ʾ�̱༭
		ui.moduleButtonsWidget_->setCurrentWidget(ui.teachEditModuleButtonsWidget_);
		ui.teachEditModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
		ui.programEditWidget_->onEditBarModule(module);
		break;
	case base::LEFTBUTTON3:					// �༭ʾ��
		ui.programEditWidget_->onEditBarModule(module);
		break;
	case base::LEFTBUTTON5:					// ִ��
		// todo
		break;
	case base::LEFTBUTTON6:					// �ر�
		ui.programEditWidget_->closeFile();
		break;
	default:
		break;
	}
}

void MainContainer::onFileWidgetModule(int module)
{
	// �ļ���������л�
	switch (module)
	{
	case base::LEFTBUTTON1:					// �û���
		break;
	case base::LEFTBUTTON5:					// ִ�У��е��ӹ�����
		{
			QString filename = ui.fileManagerWidget_->getCurrentFileName();
			if (ui.fileManagerWidget_->checkDownload(filename))
			{
				// �л����ӹ�ģ�� todo
				//onModule(base::LEFTBUTTON1);
				// �������ļ����޸�
				//emit signalChangeProcessFileName(fileName);
				//ui.processWidget_->onProcessFile(filename);
			}
		}		
		break;
	case base::LEFTBUTTON6:					// �򿪣��е��༭����
		{
			QString filename = ui.fileManagerWidget_->getCurrentFileName();
			if (ui.fileManagerWidget_->checkDownload(filename))
			{
				// �л�������༭���� todo
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
	// ��ʼ�����ļ��������ִ�кʹ򿪹��ܣ���ѡ���ļ�������
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
	// �������л�
	switch (moduleIndex)
	{
	case base::LEFTBUTTON1:					// �ӹ�����
		ui.mainContainerWidget_->setCurrentWidget(ui.processWidget_);
		ui.moduleButtonsWidget_->setCurrentWidget(ui.processModuleButtonsWidget_);
		ui.processModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
		emit signalChangeModules(QString(tr("�ӹ�")));
		break;
	case base::LEFTBUTTON2:					// �ļ��������
		ui.mainContainerWidget_->setCurrentWidget(ui.fileManagerWidget_);
		ui.moduleButtonsWidget_->setCurrentWidget(ui.fileManagerModuleButtonsWidget_);
		ui.fileManagerModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
		emit signalChangeModules(QString(tr("�ļ�����")));
		break;
	case base::LEFTBUTTON3:					// �༭����
		ui.mainContainerWidget_->setCurrentWidget(ui.programEditWidget_);
		ui.moduleButtonsWidget_->setCurrentWidget(ui.programEditModuleButtonsWidget_);
		ui.programEditModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
		emit signalChangeModules(QString(tr("�༭")));
		break;
	case base::LEFTBUTTON4:					// ���ý���
		break;
	default:
		break;
	}
}

void MainContainer::onHome()
{
	// �л���������
	ui.mainContainerWidget_->setCurrentWidget(ui.processWidget_);
	ui.moduleButtonsWidget_->setCurrentWidget(ui.homeModuleButtonsWidget_);
	emit signalChangeModules(QString(tr("��ҳ")));
}

