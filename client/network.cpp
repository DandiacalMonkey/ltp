#include "network.h"
#include "common/rmi/RemoteComm.h"

using ltp::client::Network;

void ltp::client::Network::connect()
{
	handle_ = remote_new_connect(host_.c_str());
}

void ltp::client::Network::disconnect()
{
	remote_close(handle_);
}

void ltp::client::Network::reconnect()
{
}

double ltp::client::Network::macroVariable(int address) const
{
	double value = 0;
	remote_read_macro_p(handle_, address, &value);
	return value;
}

void ltp::client::Network::setMacroVariable(int address, double value)
{
	remote_write_macro(handle_, address, value);
}

unsigned long ltp::client::Network::plcVariable(rmi::PlcVariableName name) const
{
	unsigned long value = 0;
	remote_read_plc_variable_p(handle_, name, &value);
	return value;
}

void ltp::client::Network::setPlcVariable(rmi::PlcVariableName name, unsigned long value)
{
	remote_write_plc_variable(handle_, name, value);
}

Network::Network()
{
}

Network::~Network()
{
}