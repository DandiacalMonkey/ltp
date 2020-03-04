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

		signals:
			void signalChangeProcessFileName(QString);		// 当前加工文件名改变
			void signalChangeModules(QString);				// 切换模块，菜单栏信息修改

		private slots:
			void onModule(int);								// 切换模块
			void onHome();									// 返回主页
			void onEditModule();							// 切到程序编辑模块
			void onProcessModule(QString);					// 切到加工模块
		};
	}
}


#endif // LTP_CLIENT_MAINCONTAINER_H_