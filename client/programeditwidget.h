#ifndef LTP_CLIENT_PROGRAMEDITWIDGET_H_
#define LTP_CLIENT_PROGRAMEDITWIDGET_H_

#include <QtGui/QWidget>
#include "ui_programeditwidget.h"

namespace ltp
{
	namespace client
	{

		class ProgramEditWidget : public QWidget
		{
			Q_OBJECT
		 
		public:
			ProgramEditWidget(QWidget *parent = 0);
			~ProgramEditWidget();
			void onStartPage();

		private:
			Ui::ProgramEditWidgetClass ui;
					
		signals:
			void onHome();						// 回到主页
			void openFile(QString filename);	// 打开文件
			void signalTips(QString);			// 提示栏信息显示
			void processFile(QString);			// 加工文件
			void signalSaved(QString);			// 文件已保存

		private slots:
			void onEditModule(int);
			void returnProgrameEdit();			// 返回程序编辑界面
			
		};
	}
}
#endif // LTP_CLIENT_PROGRAMEDITWIDGET_H_