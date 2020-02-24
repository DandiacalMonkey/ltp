#ifndef LTP_CLIENT_NETWORK_H_
#define LTP_CLIENT_NETWORK_H_

#include <string>
#include "base/singleton.hpp"

namespace ltp
{
	namespace client
	{
		class Network
		{
			friend Network& ltp::base::getInstance<Network>();
		public:
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
			double macroVariable(int address) const;
			void setMacroVariable(int address, double value);
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