#include "network.h"
#include "common/rmi/RemoteComm.h"

using ltp::client::Network;

void ltp::client::Network::connect()
{
	handle_ = remote_new_connect(host_.c_str());
	//判定是否连接成功
	if (handle_ >= 0)
	{
		remote_set_send_timeout(handle_, 20);
		remote_set_receive_timeout(handle_, 20);
		connectState_ = CONNECTED;
		emit connected(host_);
	}
	else
	{
		emit unconnected();
	}
}

void ltp::client::Network::disconnect()
{
	//主动关闭连接
	remote_close(handle_);
	connectState_ = UNCONNECTED;
	emit unconnected();
}

void ltp::client::Network::reconnect()
{
	disconnect();
	connect();
}

double ltp::client::Network::macroVariable(int address) const
{
	double value = 0;
	//处于连接状态才执行，防止超时次数过多卡顿
	if (remote_connect_status(handle_) == 0)
	{
		remote_read_macro_p(handle_, address, &value);
	}
	return value;
}

void ltp::client::Network::setMacroVariable(int address, double value)
{
	//处于连接状态才执行，防止超时次数过多卡顿
	if (remote_connect_status(handle_) == 0)
	{
		remote_write_macro(handle_, address, value);
	}
}

unsigned long ltp::client::Network::plcVariable(rmi::PlcReadOnlyVariableName name) const
{
	unsigned long value = 0;
	//处于连接状态才执行，防止超时次数过多卡顿
	if (remote_connect_status(handle_) == 0)
	{
		remote_read_plc_variable_p(handle_, name, &value);
	}
	return value;
}

void ltp::client::Network::setPlcVariable(rmi::PlcWriteOnlyVariableName name, unsigned long value)
{
	//处于连接状态才执行，防止超时次数过多卡顿
	if (remote_connect_status(handle_) == 0)
	{
		remote_write_plc_variable(handle_, name, value);
	}
}

int ltp::client::Network::openFile(int channel, const std::string& fileName)
{
	if (remote_connect_status(handle_) == 0)
	{
		return remote_open_file(handle_, channel, fileName.c_str());
	}
	else
	{
		return -1;
	}
}

std::string ltp::client::Network::openedFileName() const
{
	char fileName[256] = { 0 };
	if (remote_connect_status(handle_) == 0)
	{
		remote_get_open_file_name(handle_, fileName);
	}
	return std::move(std::string(fileName));
}

std::string ltp::client::Network::openedFilePath() const
{
	char filePath[1024] = { 0 };
	if (remote_connect_status(handle_) == 0)
	{
		remote_get_open_file_path(handle_, filePath);
	}
	return std::move(std::string(filePath));
}

int ltp::client::Network::fileLastModifiedTime(const std::string& filePath) const
{
	int lastModifiedTime = 0;
	if (remote_connect_status(handle_) == 0)
	{
		if (remote_get_file_last_modified_time(handle_, filePath.c_str(), &lastModifiedTime) == 0)
		{
			return lastModifiedTime;
		}
	}
	return 0;
}

std::string ltp::client::Network::openedFileMD5(int channel) const
{
	char md5[256] = { 0 };
	if (remote_connect_status(handle_) == 0)
	{
		remote_get_exe_file_md5sum(handle_, channel, md5);
	}
	return std::string(md5);
}

Network::Network()
	:connectState_(UNCONNECTED)
{
	const int kCheckConnectionInterval = 200;
	checkConnectionTimer_.start(kCheckConnectionInterval);
	QObject::connect(&checkConnectionTimer_, SIGNAL(timeout()), SLOT(checkConnection()));
}

Network::~Network()
{
	disconnect();
}

void Network::checkConnection()
{
	switch (connectState_)
	{
	case ltp::client::Network::CONNECTED:
		if (remote_connect_status(handle_) != 0)
		{
			connectState_ = DISCONNECTED;
			emit disconnected();
		}
		break;
	case ltp::client::Network::UNCONNECTED:
		//网络未连接时不用检查
		break;
	case ltp::client::Network::DISCONNECTED:
		if (remote_connect_status(handle_) == 0)
		{
			connectState_ = CONNECTED;
			emit connected(host_);
		}
		break;
	default:
		break;
	}
}