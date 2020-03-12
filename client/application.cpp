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
	//过滤带Ctrl的键盘事件
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);
		if (keyEvent->modifiers() == Qt::ControlModifier)
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);			// 转换为键盘事件
			// 检测输入键值是否为外设键值
			if (base::getInstance<PhysicalButtonsProcessor>().isPhysicalButtonsProcessor(keyEvent))
			{
				// 执行外设键值对应的函数，发出外设按键信号
				base::getInstance<PhysicalButtonsProcessor>().getMapFunction(keyEvent);
				return true;
			}
		}
	}
	return QApplication::notify(receiver, event);
}
