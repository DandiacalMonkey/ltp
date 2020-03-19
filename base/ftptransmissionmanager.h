#ifndef LTP_BASE_FTPTRANSMISSIONMANAGER_H_
#define LTP_BASE_FTPTRANSMISSIONMANAGER_H_

#include <memory>
#include <QObject>
#include <QFtp>
#include <QFile>
#include "base/progressdialog.h"


namespace ltp
{
	namespace base
	{
		class FtpTransmissionManager : public QObject
		{
			Q_OBJECT

		public:
			FtpTransmissionManager();
			~FtpTransmissionManager();

		public slots:
			//连接服务器
			void connect(const std::string& ip);
			//下载文件
			bool downloadFile(const QString& remoteFilePath, const QString& localFilePath);
			//上传文件
			bool uploadFile(const QString& localFilePath, const QString& remoteFilePath);

		signals:
			//连接成功
			void connectSuccess();
			//连接失败
			void connectFail();

		private:
			//包装qftp实现下载上传功能
			std::shared_ptr<QFtp> ftp_;
			//储存ip地址
			std::string ip_;
			//上传和下载时使用的文件
			std::shared_ptr<QFile> file_;
			//进度框
			ProgressDialog* progressDialog_;

		private slots:
			//命令结束
			void ftpCommandFinished(int, bool error);
			// 更新进度条
			void updateDataTransferProgress(qint64, qint64);
			// 取消下载
			void cancelDownload();
		};
	}
}

#endif // !LTP_BASE_FTPTRANSMISSIONMANAGER_H_
