#include "maincontainer.h"
#include "base/globals.h"
#include "physicalbuttonsprocessor.h"

using ltp::client::MainContainer;

MainContainer::MainContainer(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initModuleButtonsWidget();
	// ���˵��л�
	connect(ui.homeModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onModule(int)));
	// ���������е�������
	connect(ui.fileManagerModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	connect(ui.programEditModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	connect(ui.processModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	connect(ui.setModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(onHome()));
	// �ļ�������棬��ఴť�л�
	connect(ui.fileManagerModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onFileWidgetModule(int)));
	// �ļ�������棬ִ�С��򿪰�ť�Ƿ�enable
	connect(ui.fileManagerWidget_, SIGNAL(downloadEnable(bool)), this, SLOT(enableFileButtons(bool)));
	// �༭���汣�棬ͬʱ���ص�ftp�ͻ���
	connect(ui.programEditWidget_, SIGNAL(signalSaved(QString)), ui.fileManagerWidget_, SLOT(uploadFile(QString)));
	// �ӹ����棬��ఴť�л�
	connect(ui.processModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onProcessWidgetModule(int)));
	// �༭���棬��ఴť�л�
	connect(ui.programEditModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onProgrameEditWidgetModule(int)));
	// ʾ�̱༭���棬��ఴť�л�
	connect(ui.teachEditModuleButtonsWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onProgramTeachEditModule(int)));
	connect(ui.teachEditModuleButtonsWidget_, SIGNAL(signalReturnButtonClicked()), this, SLOT(backProgrameModule()));
	// ���谴ť��Ӧ
	connect(&base::getInstance<PhysicalButtonsProcessor>(), SIGNAL(returnButtonClicked()), this, SLOT(returnButtonClicked()));
	connect(&base::getInstance<PhysicalButtonsProcessor>(), SIGNAL(leftButtonClicked(int)), this, SLOT(leftButtonClicked(int)));
}

MainContainer::~MainContainer()
{
	
}

void MainContainer::leftButtonClicked(int key)
{
	// ���谴���л���ǰ����
	auto tempWidget = ui.moduleButtonsWidget_->currentWidget();
	if (ui.moduleButtonsWidget_->currentIndex() == HOME_BUTTONS_WIDGET)				// ������
	{
		onModule(key);
	}
	else if (ui.moduleButtonsWidget_->currentIndex() == PROCESS_BUTTONS_WIDGET)		// �ӹ�����
	{
		onProcessWidgetModule(key);
	}
	else if (ui.moduleButtonsWidget_->currentIndex() == FILEMANAGER_BUTTONS_WIDGET)	// �ļ��������
	{
		onFileWidgetModule(key);
	}
	else if (ui.moduleButtonsWidget_->currentIndex() == PROGRAMEDIT_BUTTONS_WIDGET)	// �༭����
	{
		onProgrameEditWidgetModule(key);
	}
	else if (ui.moduleButtonsWidget_->currentIndex() == TEACHEDIT_BUTTONS_WIDGET)	// ʾ�̱༭����
	{
		onProgramTeachEditModule(key);
	}
}

void MainContainer::returnButtonClicked()
{
	auto tempWidget = ui.moduleButtonsWidget_->currentWidget();
	// �����桢�ӹ����桢�ļ�������桢�༭���桢���ý���
	if (ui.moduleButtonsWidget_->currentIndex() == HOME_BUTTONS_WIDGET ||
		ui.moduleButtonsWidget_->currentIndex() == PROCESS_BUTTONS_WIDGET ||
		ui.moduleButtonsWidget_->currentIndex() == FILEMANAGER_BUTTONS_WIDGET ||
		ui.moduleButtonsWidget_->currentIndex() == PROGRAMEDIT_BUTTONS_WIDGET ||
		ui.moduleButtonsWidget_->currentIndex() == SET_BUTTONS_WIDGET)				
	{
		onHome();					// ������ҳ��
	}
	else if (ui.moduleButtonsWidget_->currentIndex() == TEACHEDIT_BUTTONS_WIDGET)	// ʾ�̱༭����
	{
		backProgrameModule();		// ���س����̽���
	}
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

	// ���ý�����ఴť������
	ui.setModuleButtonsWidget_->setCommandButtonName(base::LEFTBUTTON1, QString(tr("��������")));
}

void MainContainer::backProgrameModule()
{
	// ���س���༭����
	onProgrameEditWidgetModule(base::LEFTBUTTON1);
	ui.programEditModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
}

void MainContainer::onProcessWidgetModule(int module)
{
	// �ӹ������л�
	switch (module)
	{
	case base::LEFTBUTTON1:					// �ӹ�״̬
		break;
	case base::LEFTBUTTON2:					// ����ϵ
		break;
	case base::LEFTBUTTON6:					// ��ʼ��
		break;
	default:
		break;
	}
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

void MainContainer::onProgramTeachEditModule(int module)
{
	// �л��༭ģ��
	ui.programEditWidget_->onTeachEditModule(module);
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
		ui.mainContainerWidget_->setCurrentWidget(ui.setWidget_);
		ui.moduleButtonsWidget_->setCurrentWidget(ui.setModuleButtonsWidget_);	
		ui.setModuleButtonsWidget_->setCheckedButton(base::LEFTBUTTON1, true);
		emit signalChangeModules(QString(tr("����")));
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

