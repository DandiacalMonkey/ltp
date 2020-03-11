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
			//ftp����
			void connectToFtp();

		signals:
			//���ӳɹ�
			void connectSuccess();
			//����ʧ��
			void connectFail();

		protected slots:
			//ˢ���б�
			virtual void refreshList();
			//��ת��һ��
			virtual void cdToParent();
			//�����ļ��л���ļ�
			virtual void processItem(QTableWidgetItem*);

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

		private slots:
			//ftp�������
			void ftpCommandFinished(int, bool error);
			//�����ļ���Ϣ
			void addToList(const QUrlInfo& urlInfo);

		};
	}
}

#endif // FTPFILEMANAGER_H
