#include "application.h"
#include <QKeyEvent>

using ltp::client::Application;

Application::Application(int& argc, char** argv)
	:QApplication(argc, argv)
{
}

bool Application::notify(QObject* receiver, QEvent* event)
{
	//过滤带Ctrl的键盘事件
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);
		if (keyEvent->modifiers() == Qt::ControlModifier)
		{
			return true;
		}
	}
	return QApplication::notify(receiver, event);
}
