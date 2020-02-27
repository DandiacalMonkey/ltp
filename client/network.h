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
			//返回服务器ip
			const std::string& host() const
			{
				return host_;
			}
			//设定服务器ip
			void setHost(const std::string& host)
			{
				host_ = host;
			}
			void connect();
			void disconnect();
			void reconnect();
			//读写宏变量
			double macroVariable(int address) const;
			void setMacroVariable(int address, double value);
			//读写PLC变量
			unsigned long plcVariable(rmi::PlcVariableName name) const;
			void setPlcVariable(rmi::PlcVariableName name, unsigned long value);
		private:
			Network();
			//服务器ip
			std::string host_;
			//连接到控制器的句柄
			int handle_;
		};
	}
}

#endif // LTP_CLIENT_NETWORK_H_