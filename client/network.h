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
				//通信正常
				CONNECTED,
				//网络未连接
				UNCONNECTED,
				//网络已连接，又被断开
				DISCONNECTED
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
			unsigned long plcVariable(rmi::PlcReadOnlyVariableName name) const;
			void setPlcVariable(rmi::PlcWriteOnlyVariableName name, unsigned long value);
			//远程打开文件
			int openFile(int channel, const std::string& fileName);
			//远程打开文件名（不带路径）
			std::string openedFileName() const;
			//远程打开文件名（带路径）
			std::string openedFilePath() const;
			//远程文件MD5
			std::string openedFileMD5(int channel) const;
			
		signals:
			//由未连接或连接断开状态成功连接
			void connected();
			//主动断开连接
			void unconnected();
			//网络不通、服务端出错导致的连接断开
			void disconnected();

		private:
			Network();
			//服务器ip
			std::string host_;
			//连接到控制器的句柄
			int handle_;
			//连接状态
			ConnectState connectState_;
			//检查连接状态定时器
			QTimer checkConnectionTimer_;

		private slots:
			void checkConnection();
		};
	}
}

#endif // LTP_CLIENT_NETWORK_H_