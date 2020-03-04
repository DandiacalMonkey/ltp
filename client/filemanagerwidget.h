#ifndef LTP_CLIENT_FILEMANAGERWIDGET_H_
#define LTP_CLIENT_FILEMANAGERWIDGET_H_

#include <QtGui/QWidget>
#include "ui_filemanagerwidget.h"

namespace ltp
{
	namespace client
	{

		class FileManagerWidget : public QWidget
		{
			Q_OBJECT
		 
		public:
			FileManagerWidget(QWidget *parent = 0);
			~FileManagerWidget();
			void onStartPage();

		private:
			Ui::FileManagerWidgetClass ui;

		private slots:
			void onFileManagerModule(int);
			void enableButton(bool);

		signals:
			void onHome();								// 返回主页
			void onProcessFile(QString filename);
			void onOpenFile(QString);
			void signalSaved(QString);					// 文件已保存, 需要同步上载ftp
		};
	}
}
#endif // LTP_CLIENT_FILEMANAGERWIDGET_H_