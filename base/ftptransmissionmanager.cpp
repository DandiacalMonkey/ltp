#include "ftptransmissionmanager.h"
#include <QUrl>

using ltp::base::FtpTransmissionManager;

void ltp::base::FtpTransmissionManager::connect()
{
	ftp_.reset(new QFtp());
	QObject::connect(ftp_.get(), SIGNAL(commandFinished(int, bool)), this, SLOT(ftpCommandFinished(int, bool)));
	//connect(ftp_.get(), SIGNAL(dataTransferProgress(qint64, qint64)), this, SLOT(updateDataTransferProgress(qint64, qint64)));

	QUrl url(QString::fromStdString(ip_));
	ftp_->connectToHost(url.toString(), 21);
	ftp_->login();
}

bool FtpTransmissionManager::downloadFile(const QString& remoteFilePath, const QString& localFilePath)
{
	file_.reset(new QFile(localFilePath));
	//��ֻ��ɾ���ļ�
	if (!file_->open(QIODevice::WriteOnly))
	{
		return false;
	}
	//��������
	ftp_->get(remoteFilePath, file_.get());
	//����ģ̬���ȿ򣬵ȴ��������
	progressDialog_->exec();
	return true;
}

bool FtpTransmissionManager::uploadFile(const QString& localFilePath, const QString& remoteFilePath)
{
	file_.reset(new QFile(localFilePath));
	//�ϴ�ֻ��Ҫ���ļ�
	if (!file_->open(QIODevice::ReadOnly))
	{
		return false;
	}
	//��������
	ftp_->put(file_.get(), remoteFilePath);
	//����ģ̬���ȿ򣬵ȴ��������
	progressDialog_->exec();
	return true;
}

FtpTransmissionManager::FtpTransmissionManager()
{
	progressDialog_ = new QDialog();
	progressDialog_->setModal(true);
}

FtpTransmissionManager::~FtpTransmissionManager()
{
}

void FtpTransmissionManager::ftpCommandFinished(int, bool error)
{
	switch (ftp_->currentCommand())
	{
	//����
	case QFtp::ConnectToHost:
		{
			if (error)
			{
				//����ʧ��
				emit connectFail();
			}
			else
			{
				//���ӳɹ�
				emit connectSuccess();
			}
			return;
		}
		break;
	//����
	case QFtp::Get:
		{
			if (error)
			{
				//�رա�ɾ���ļ�
				file_->close();
				file_->remove();
				progressDialog_->reject();
			}
			else
			{
				//���سɹ������ر��ļ�
				file_->close();
				progressDialog_->accept();
			}
		}
		break;
	//�ϴ�
	case QFtp::Put:
	{
		if (error)
		{
			//�رա�ɾ���ļ�
			file_->close();
			progressDialog_->reject();
		}
		else
		{
			//���سɹ������ر��ļ�
			file_->close();
			progressDialog_->accept();
		}
	}
	break;
	default:
		break;
	}
}