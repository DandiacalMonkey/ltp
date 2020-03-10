#ifndef LTP_CLIENT_MAINCONTAINER_H_
#define LTP_CLIENT_MAINCONTAINER_H_

#include <QtGui/QWidget>
#include "ui_maincontainer.h"

namespace ltp
{
	namespace client
	{
		class MainContainer : public QWidget
		{
			Q_OBJECT

		public:
			MainContainer(QWidget* parent = 0);
			~MainContainer();

		private:
			Ui::MainContainerClass ui;
			void initModuleButtonsWidget();					// 初始化左侧按钮模块信息

		signals:
			void signalChangeProcessFileName(QString);		// 当前加工文件名改变
			void signalChangeModules(QString);				// 切换模块，菜单栏信息修改

		private slots:
			void onModule(int);								// 切换主菜单模块
			void onHome();									// 返回主页
			void enableFileButtons(bool);					// 使能文件管理打开、执行按钮
			void onFileWidgetModule(int);					// 切换文件管理模块
			void onProgrameEditWidgetModule(int);			// 切换编辑模块
			void backProgrameModule();						// 切回编辑模块
		};
	}
}


#endif // LTP_CLIENT_MAINCONTAINER_H_