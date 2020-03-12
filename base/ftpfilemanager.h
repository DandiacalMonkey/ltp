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
			//�趨Զ��ip��ַ
			void setFtpHost(const std::string& ip)
			{
				ip_ = ip;
				ftpTransmissionManager_.setHost(ip);
			}

		public slots:
			//�򿪵�ǰѡ����
			virtual void openCurrentItem();
			//ִ�е�ǰѡ����
			virtual void executeCurrentItem();
			//ftp����
			void connectToFtp();
			//�ϴ��ļ�
			void uploadFile(const QString& filePath);

		signals:
			//���ļ��ź�
			void openFile(const QString& localFilePath, const QString& remoteFilePath);
			//ִ���ļ��ź�
			void executeFile(const QString& localFilePath, const QString& remoteFilePath);

		protected slots:
			//ˢ���б�
			virtual void refreshList();
			//��ת��һ��
			virtual void cdToParent();
			//�����ļ��л���ļ�
			virtual void openItem(QTableWidgetItem*);
			//ִ���ļ�
			virtual void executeItem(QTableWidgetItem*);
			//ѡ�е��ļ��仯
			virtual void selectedItemChanged();
			
		private:
			//�����ϴ����ص�ftp
			FtpTransmissionManager ftpTransmissionManager_;
			//��װqftpʵ���ļ��б��ȡ
			std::shared_ptr<QFtp> ftp_;
			//����ip��ַ
			std::string ip_;
			//��ǰ��ʾ���б��е���Ŀ�Ƿ����ļ���
			QHash<QString, bool> isDirectory_;
			//��ǰ·��
			QString currentPath_;
			//���ڴ���ļ���ʹ�õı�����ʱ�ļ�
			const QString editTemporaryFilePath_;
			//����򿪵��ļ���Զ���ļ���
			QString lastOpenedRemoteFilePath_;

		private slots:
			//ftp�������
			void ftpCommandFinished(int, bool error);
			//�����ļ���Ϣ
			void addToList(const QUrlInfo& urlInfo);

		};
	}
}

#endif // FTPFILEMANAGER_H
