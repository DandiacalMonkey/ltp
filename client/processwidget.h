#ifndef LTP_CLIENT_PROCESSWIDGET_H_
#define LTP_CLIENT_PROCESSWIDGET_H_

#include <QtGui/QWidget>
#include "ui_processwidget.h"

namespace ltp
{
	namespace client
	{
		enum ModuleWidgetEnum
		{
			MAIN_WIDGET,
			PROCESS_WIDGET,
			FILE_MANAGER_WIDGET,
			EDIT_WIDGET
		};

		class ProcessWidget : public QWidget
		{
			Q_OBJECT
		 
		public:
			ProcessWidget(QWidget *parent = 0);
			~ProcessWidget();  
			void changeModule(int widgetID);

		private:
			Ui::ProcessWidgetClass ui;

		private slots:
			void mainModuleWidgetChanged(int);			// 主界面模块切换

		signals:
			void onModule(int);
			void onHome();
			void processFile(QString);					// 加工文件
		};
	}
}
#endif // LTP_CLIENT_PROCESSWIDGET_H_