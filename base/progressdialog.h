#ifndef LTP_BASE_PROGRESSDIALOG_H_
#define LTP_BASE_PROGRESSDIALOG_H_

#include <QtGui/QDialog>
#include "ui_progressdialog.h"

namespace ltp
{
	namespace base
	{
		class ProgressDialog : public QDialog
		{
			Q_OBJECT
				
		public:
			ProgressDialog(QWidget* parent = 0);
			~ProgressDialog();
			void setContentName(const QString &);
			void setTitleName(const QString&);
			void setProgressLoad(int currentNum, int totalNum);		// 设置当前进度条值

		private:
			Ui::ProgressDialogClass ui;

		signals:
			void siganlCancel();

		private slots:
			void closeWindow();										// 关闭窗口
			void moveDialog(QPoint);								// 移动窗口
		};
	}
}


#endif // LTP_BASE_PROGRESSDIALOG_H_