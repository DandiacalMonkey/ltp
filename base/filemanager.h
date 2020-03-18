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
			//打开当前选中项
			virtual void openCurrentItem() = 0;
			//执行当前选中项
			virtual void executeCurrentItem() = 0;
			//执行最后打开的文件
			virtual void executeLastOpenedFile() = 0;

		signals:
			//连接成功
			void connectSuccess();
			//连接失败
			void connectFail();
			//打开文件信号
			void openFile(const QString& filePath);
			//执行文件信号
			void executeFile(const QString& filePath);
			//选中文件
			void selectedFile();
			//选中文件夹
			void selectedFolder();
			//没有选中内容
			void selectedNone();

		protected slots:
			//刷新列表
			virtual void refreshList() = 0;
			//跳转上一级
			virtual void cdToParent() = 0;
			//进入文件夹或打开文件
			virtual void openItem(QTableWidgetItem*) = 0;
			//执行文件
			virtual void executeItem(QTableWidgetItem*) = 0;
			//选中的文件变化
			virtual void selectedItemChanged() = 0;

		protected:
			Ui::FileManager ui;
		};
	}
}

#endif // LTP_BASE_FILEMANAGER_H_
