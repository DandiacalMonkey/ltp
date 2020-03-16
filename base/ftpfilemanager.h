#ifndef FTPFILEMANAGER_H
#define FTPFILEMANAGER_H

#include <QUrlInfo>
#include <QFtp>
#include "filemanager.h"
#include "ftptransmissionmanager.h"

namespace ltp
{
	namespace base
	{
		class FtpFileManager : public FileManager
		{
			Q_OBJECT

		public:
			FtpFileManager(QWidget *parent = nullptr);
			~FtpFileManager();

		public slots:
			//打开当前选中项
			virtual void openCurrentItem();
			//执行当前选中项
			virtual void executeCurrentItem();
			//ftp连接
			void connectToFtp();
			void connectToFtp(const std::string& ip);
			//上传文件
			void uploadFile(const QString& filePath);

		signals:
			//打开文件信号
			void openFile(const QString& localFilePath, const QString& remoteFilePath);
			//执行文件信号
			void executeFile(const QString& localFilePath, const QString& remoteFilePath);

		protected slots:
			//刷新列表
			virtual void refreshList();
			//跳转上一级
			virtual void cdToParent();
			//进入文件夹或打开文件
			virtual void openItem(QTableWidgetItem*);
			//执行文件
			virtual void executeItem(QTableWidgetItem*);
			//选中的文件变化
			virtual void selectedItemChanged();
			
		private:
			//用于上传下载的ftp
			FtpTransmissionManager ftpTransmissionManager_;
			//包装qftp实现文件列表获取
			std::shared_ptr<QFtp> ftp_;
			//储存ip地址
			std::string ip_;
			//当前显示的列表中的项目是否是文件夹
			QHash<QString, bool> isDirectory_;
			//当前路径
			QString currentPath_;
			//用于存放文件打开使用的本地临时文件
			const QString editTemporaryFilePath_;
			//最近打开的文件的远程文件名
			QString lastOpenedRemoteFilePath_;

		private slots:
			//ftp命令结束
			void ftpCommandFinished(int, bool error);
			//加载文件信息
			void addToList(const QUrlInfo& urlInfo);

		};
	}
}

#endif // FTPFILEMANAGER_H
