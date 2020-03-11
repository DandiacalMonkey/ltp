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
			//设定远程ip地址
			void setFtpHost(const std::string& ip)
			{
				ip_ = ip;
				ftpTransmissionManager_.setHost(ip);
			}

		public slots:
			//打开当前选中项
			virtual void openCurrentItem();
			//ftp连接
			void connectToFtp();

		signals:
			//连接成功
			void connectSuccess();
			//连接失败
			void connectFail();

		protected slots:
			//刷新列表
			virtual void refreshList();
			//跳转上一级
			virtual void cdToParent();
			//进入文件夹或打开文件
			virtual void processItem(QTableWidgetItem*);

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

		private slots:
			//ftp命令结束
			void ftpCommandFinished(int, bool error);
			//加载文件信息
			void addToList(const QUrlInfo& urlInfo);

		};
	}
}

#endif // FTPFILEMANAGER_H
