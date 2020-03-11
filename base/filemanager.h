#ifndef LTP_BASE_FILEMANAGER_H_
#define LTP_BASE_FILEMANAGER_H_

#include <QWidget>
#include "ui_filemanager.h"

namespace ltp
{
	namespace base
	{
		class FileManager : public QWidget
		{
			Q_OBJECT

		public:
			FileManager(QWidget *parent = 0);
			~FileManager();

		public slots:
			virtual void openCurrentItem() = 0;

		protected slots:
			//刷新列表
			virtual void refreshList() = 0;
			//跳转上一级
			virtual void cdToParent() = 0;
			//进入文件夹或打开文件
			virtual void processItem(QTableWidgetItem*) = 0;

		protected:
			Ui::FileManager ui;
		};
	}
}

#endif // LTP_BASE_FILEMANAGER_H_
