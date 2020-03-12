#include "application.h"
#include <QKeyEvent>
#include "physicalbuttonsprocessor.h"

using ltp::client::Application;

Application::Application(int& argc, char** argv)
	:QApplication(argc, argv)
{
}

bool Application::notify(QObject* receiver, QEvent* event)
{
	//���˴�Ctrl�ļ����¼�
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);
		if (keyEvent->modifiers() == Qt::ControlModifier)
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);			// ת��Ϊ�����¼�
			// ��������ֵ�Ƿ�Ϊ�����ֵ
			if (base::getInstance<PhysicalButtonsProcessor>().isPhysicalButtonsProcessor(keyEvent))
			{
				// ִ�������ֵ��Ӧ�ĺ������������谴���ź�
				base::getInstance<PhysicalButtonsProcessor>().getMapFunction(keyEvent);
				return true;
			}
		}
	}
	return QApplication::notify(receiver, event);
}
