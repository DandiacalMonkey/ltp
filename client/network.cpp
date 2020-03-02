#include "network.h"
#include "common/rmi/RemoteComm.h"

using ltp::client::Network;

void ltp::client::Network::connect()
{
	handle_ = remote_new_connect(host_.c_str());
	//�ж��Ƿ����ӳɹ�
	if (handle_ >= 0)
	{
		remote_set_send_timeout(handle_, 20);
		remote_set_receive_timeout(handle_, 20);
		connectState_ = CONNECTED;
		emit connected();
	}
}

void ltp::client::Network::disconnect()
{
	//�����ر�����
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
	//��������״̬��ִ�У���ֹ��ʱ�������࿨��
	if (remote_connect_status(handle_) == 0)
	{
		remote_read_macro_p(handle_, address, &value);
	}
	return value;
}

void ltp::client::Network::setMacroVariable(int address, double value)
{
	//��������״̬��ִ�У���ֹ��ʱ�������࿨��
	if (remote_connect_status(handle_) == 0)
	{
		remote_write_macro(handle_, address, value);
	}
}

unsigned long ltp::client::Network::plcVariable(rmi::PlcReadOnlyVariableName name) const
{
	unsigned long value = 0;
	//��������״̬��ִ�У���ֹ��ʱ�������࿨��
	if (remote_connect_status(handle_) == 0)
	{
		remote_read_plc_variable_p(handle_, name, &value);
	}
	return value;
}

void ltp::client::Network::setPlcVariable(rmi::PlcWriteOnlyVariableName name, unsigned long value)
{
	//��������״̬��ִ�У���ֹ��ʱ�������࿨��
	if (remote_connect_status(handle_) == 0)
	{
		remote_write_plc_variable(handle_, name, value);
	}
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
		//����δ����ʱ���ü��
		break;
	case ltp::client::Network::DISCONNECTED:
		if (remote_connect_status(handle_) == 0)
		{
			connectState_ = CONNECTED;
			emit connected();
		}
		break;
	default:
		break;
	}
}