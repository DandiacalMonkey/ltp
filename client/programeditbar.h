#ifndef LTP_CLIENT_PROGRAMEDITBAR_H_
#define LTP_CLIENT_PROGRAMEDITBAR_H_

#include <QtGui/QWidget>
#include "ui_programeditbar.h"
#include "base/globals.h"

namespace ltp
{
	namespace client
	{
		
		class ProgramEditBar : public QWidget
		{
			Q_OBJECT
		 
		public:
			ProgramEditBar(QWidget *parent = 0);
			~ProgramEditBar();  
			void onEditBarModule(int);			// 切换编辑内部模块
			void closeFile();					// 关闭文件
			QString getCurrentFileName(){return ui.textEdit_->getCurrentFileName();}	// 获取当前文件名
			void checkCurrentFileModified(){ui.textEdit_->checkModified();}				// 检查文件是否修改

		private:
			Ui::ProgramEditBarClass ui;

		private:
			void onProgrameEdit();			// 程序编辑
			void onTeachEdit();				// 示教编辑
			void onEditTeach();				// 编辑示教
			void updateFileName();			// 更新打开文件名

		private slots:
			void setValidAxes(const std::vector<ltp::base::Axis> &validAxes);
			void onTeachEditModule(int);			// 切换示教编辑模块
			void onOpenFile(QString fileName);		// 打开文件

		signals:
			void signalTips(QString);
			void signalSaved(QString);
		};
	}
}
#endif // LTP_CLIENT_PROGRAMEDITBAR_H_