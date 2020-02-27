#ifndef LTP_CLIENT_NETWORK_H_
#define LTP_CLIENT_NETWORK_H_

#include <string>
#include "base/singleton.hpp"
#include "common/rmi/globals.h"

namespace ltp
{
	namespace client
	{
		class Network
		{
			friend Network& ltp::base::getInstance<Network>();
		public:
			enum ConnectState
			{
				CONNECTED,
				DISCONNECTED,
				CONNECTING,
				CONTROLER_EXCEPTION
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
			unsigned long plcVariable(rmi::PlcVariableName name) const;
			void setPlcVariable(rmi::PlcVariableName name, unsigned long value);
		private:
			Network();
			//������ip
			std::string host_;
			//���ӵ��������ľ��
			int handle_;
		};
	}
}

#endif // LTP_CLIENT_NETWORK_H_