#ifndef LTP_BASE_FTPTRANSMISSIONMANAGER_H_
#define LTP_BASE_FTPTRANSMISSIONMANAGER_H_

#include <memory>
#include <QObject>
#include <QFtp>
#include <QFile>
#include <QDialog>


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
			//设定远程ip地址
			void setHost(const std::string& ip)
			{
				ip_ = ip;
			}

		public slots:
			//连接服务器
			void connect();
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
			QDialog* progressDialog_;

		private slots:
			//命令结束
			void ftpCommandFinished(int, bool error);

		};
	}
}

#endif // !LTP_BASE_FTPTRANSMISSIONMANAGER_H_
