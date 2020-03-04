#ifndef LTP_CLIENT_NETWORK_H_
#define LTP_CLIENT_NETWORK_H_

#include <string>
#include <QObject>
#include <QTimer>
#include "base/singleton.hpp"
#include "common/rmi/globals.h"

namespace ltp
{
	namespace client
	{
		class Network : public QObject
		{
			Q_OBJECT
			friend Network& ltp::base::getInstance<Network>();

		public:
			enum ConnectState
			{
				//ͨ������
				CONNECTED,
				//����δ����
				UNCONNECTED,
				//���������ӣ��ֱ��Ͽ�
				DISCONNECTED
			};
			~Network();
			//���ط�����ip
			const std::string& host() const
			{
				return host_;
			}
			//�趨������ip
			void setHost(const std::string& host)
			{
				host_ = host;
			}
			void connect();
			void disconnect();
			void reconnect();
			//��д�����
			double macroVariable(int address) const;
			void setMacroVariable(int address, double value);
			//��дPLC����
			unsigned long plcVariable(rmi::PlcReadOnlyVariableName name) const;
			void setPlcVariable(rmi::PlcWriteOnlyVariableName name, unsigned long value);
			//Զ�̴��ļ�
			int openFile(int channel, const std::string& fileName);
			//Զ�̴��ļ���������·����
			std::string openedFileName() const;
			//Զ�̴��ļ�������·����
			std::string openedFilePath() const;
			//Զ���ļ�MD5
			std::string openedFileMD5(int channel) const;
			
		signals:
			//��δ���ӻ����ӶϿ�״̬�ɹ�����
			void connected();
			//�����Ͽ�����
			void unconnected();
			//���粻ͨ������˳����µ����ӶϿ�
			void disconnected();

		private:
			Network();
			//������ip
			std::string host_;
			//���ӵ��������ľ��
			int handle_;
			//����״̬
			ConnectState connectState_;
			//�������״̬��ʱ��
			QTimer checkConnectionTimer_;

		private slots:
			void checkConnection();
		};
	}
}

#endif // LTP_CLIENT_NETWORK_H_