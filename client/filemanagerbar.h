#ifndef LTP_CLIENT_FILEMANAGERBAR_H_
#define LTP_CLIENT_FILEMANAGERBAR_H_

#include <QtGui/QWidget>
#include <QProgressDialog>
#include <QHash>
#include <QNetworkConfigurationManager>
#include "ui_filemanagerbar.h"
#include "base/globals.h"

class QFile;
class QFtp;
class QUrlInfo;
class QNetworkSession;

namespace ltp
{
	namespace client
	{
		class FileManagerBar : public QWidget
		{
			Q_OBJECT
		 
		public:
			FileManagerBar(QWidget *parent = 0);
			~FileManagerBar();  
			QString getCurrentFileName();			// 获取当前文件名
			bool checkDownload(QString);			// 检查文件是否下载

		private:
			Ui::FileManagerBarClass ui;
			QHash<QString, bool> isDirectory;
			QString currentPath;
			QFtp *ftp;
			QFile *file;

			QNetworkSession *networkSession;
			QNetworkConfigurationManager manager;
			QDialog *progressDialog;

		private slots:
			void enableDownloadButton();				// 使能下载按钮
			void enableConnectButton();					// 使能连接按钮
			void processItem(QTableWidgetItem*);		// 进入文件夹
			void connectOrDisconnect();					// 是否连接
			void connectToFtp();						// ftp连接
			void ftpCommandFinished(int, bool error);	// 命令结束
			void addToList(const QUrlInfo &urlInfo);	// 加载文件信息
			void updateDataTransferProgress(qint64 readBytes, qint64 totalBytes);
			void cdToParent();							// 返回上一级菜单
			bool downloadFile(QString);					// 下载文件
			void downloadCurrentFile();					// 下载当前选中文件
			void cancelDownload();						// 取消下载
			void uploadCurrentFile();					// 上载当前选中文件
			bool uploadFile(QString);					// 上载文件

		signals:
			void downloadEnable(bool);
		};
	}
}
#endif // LTP_CLIENT_FILEMANAGERBAR_H_