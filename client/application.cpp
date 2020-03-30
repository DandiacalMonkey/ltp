#include "application.h"
#include <QMouseEvent>
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include "physicalbuttonsprocessor.h"
#include "base/keyboarddialog.h"

using ltp::client::Application;

Application::Application(int& argc, char** argv)
	:QApplication(argc, argv)
{
	
}

bool Application::notify(QObject* receiver, QEvent* event)
{
	//过滤带Ctrl的键盘事件
	if (event->type() == QEvent::KeyPress)					// 键盘按下
	{
		QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);		// 转换为键盘事件
		if (keyEvent->modifiers() == Qt::ControlModifier)
		{	
			// 检测输入键值是否为外设键值, 且屏蔽Qt长按的重复按下事件
			if (base::getInstance<PhysicalButtonsProcessor>().isPhysicalButtonsPressProcessor(keyEvent) &&
				!keyEvent->isAutoRepeat())
			{
				// 执行外设键值对应的函数，发出外设按键信号
				base::getInstance<PhysicalButtonsProcessor>().getMapPressFunction(keyEvent);
				return true;
			}
		}
	}
	else if (event->type() == QEvent::KeyRelease)			// 键盘松开
	{
		QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);		// 转换为键盘事件
		if (keyEvent->modifiers() == Qt::ControlModifier)
		{	
			// 检测输入键值是否为外设键值, 且屏蔽Qt长按的重复松开事件
			if (base::getInstance<PhysicalButtonsProcessor>().isPhysicalButtonsRealeaseProcessor(keyEvent) &&
				!keyEvent->isAutoRepeat())
			{
				// 执行外设键值对应的函数，发出外设按键信号
				base::getInstance<PhysicalButtonsProcessor>().getMapRealeaseFunction(keyEvent);
				return true;
			}
		}
	}

	// 鼠标事件的接收者为输入控件，需要显示虚拟键盘
	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);		// 转换为鼠标事件
		QWidget* nowWidget = dynamic_cast<QWidget*>(receiver);				// 当前选中位置

		// 鼠标左键点击，且点击的不是键盘上的控件
		if (mouseEvent->button() == Qt::LeftButton && !base::getInstance<base::KeyBoardDialog>().isAncestorOf(nowWidget))
		{			
			if (nowWidget->inherits("QLineEdit"))				// 当前焦点为QLineEdit，显示虚拟键盘
			{
				base::getInstance<base::KeyBoardDialog>().show();
				base::getInstance<base::KeyBoardDialog>().raise();
			}
			/*else if (nowWidget->parent() != nullptr)
			{
				if (nowWidget->parent()->inherits("QTextEdit"))	// 当前焦点为QTextEdit，显示虚拟键盘	
				{
					currentEditType_ = "QTextEdit";
					currentWidget_ = nowWidget;
					base::getInstance<base::KeyBoardDialog>().show();
					base::getInstance<base::KeyBoardDialog>().raise();
				}
				else
				{
					currentWidget_ = nullptr;
					currentEditType_ = "";
					base::getInstance<base::KeyBoardDialog>().hide();
				}
			}*/
			else												// 非输入框焦点，隐藏虚拟键盘
			{
				base::getInstance<base::KeyBoardDialog>().hide();
			}
		}
	}
	return QApplication::notify(receiver, event);
}
