#include "network.h"
#include "common/RemoteComm.h"

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
	double value;
	remote_read_macro_p(handle_, address, &value);
	return value;
}

void ltp::client::Network::setMacroVariable(int address, double value)
{
	remote_write_macro(handle_, address, value);
}

Network::Network()
{
}

Network::~Network()
{
}