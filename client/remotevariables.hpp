#ifndef LTP_CLIENT_REMOTE_VARIABLES_H_
#define LTP_CLIENT_REMOTE_VARIABLES_H_

#include "network.h"

namespace ltp
{
	namespace client
	{
		class RemoteVariables
		{
		public:
			RemoteVariables() {};
			~RemoteVariables() {};
			//��ȡ�����
			double macroVariable(int address) const
			{
				return base::getInstance<Network>().macroVariable(address);
			}
			//д�����
			void setMacroVariable(int address, double value)
			{
				base::getInstance<Network>().setMacroVariable(address, value);
			}
			//��ȡPLC����
			unsigned long plcVariable(rmi::PlcReadOnlyVariableName name) const
			{
				return base::getInstance<Network>().plcVariable(name);
			}
			//дPLC����
			void setPlcVariable(rmi::PlcWriteOnlyVariableName name, unsigned long value)
			{
				base::getInstance<Network>().setPlcVariable(name, value);
			}
		};
	}
}

#endif // !LTP_CLIENT_REMOTE_VARIABLES_H_
