#ifndef LTP_CLIENT_PROGRAMEDITWIDGET_H_
#define LTP_CLIENT_PROGRAMEDITWIDGET_H_

#include <QtGui/QWidget>
#include <QTimer>
#include "base/globals.h"
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
			void onEditBarModule(int);			// 切换编辑内部模块
			void closeFile();					// 关闭文件
			QString getCurrentFileName(){return ui.textEdit_->getCurrentFileName();}	// 获取当前文件名
			void checkCurrentFileModified(){ui.textEdit_->checkModified();}				// 检查文件是否修改
			void setRemoteFilePath(const QString& filePath);									// 设定显示的文件名

			void onOpenFile(QString fileName);		// 打开文件
			void saveFile();						// 保存文件
			void onTeachEditModule(int);			// 切换示教编辑模块

		private:
			Ui::ProgramEditWidgetClass ui;
			QTimer timer_;

		private:
			void onProgrameEdit();			// 程序编辑
			void onTeachEdit();				// 示教编辑
			void onEditTeach();				// 编辑示教

		private slots:
			void setValidAxes(const std::vector<base::Axis> &validAxes);
			void onHint(QString);
			void onTimer();
			void fileClosed();

		signals:
			void signalSaved(QString);
		};
	}
}
#endif // LTP_CLIENT_PROGRAMEDITBAR_H_