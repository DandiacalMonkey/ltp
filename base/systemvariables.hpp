#ifndef LTP_BASE_SYSTEM_VARIABLES_H_
#define LTP_BASE_SYSTEM_VARIABLES_H_

#include <array>
#include "globals.h"
#include "singleton.hpp"
#include "common/rmi/globals.h"

namespace ltp
{
	namespace base
	{
		template <typename SyncVariables>
		class SystemVariables
		{
			friend SystemVariables<SyncVariables>& getInstance<SystemVariables<SyncVariables>>();
		public:
			~SystemVariables() {};
			//��ȡ�����
			double macroVariable(int address) const
			{
				return syncVariables_.macroVariable(address);
			}
			//д�����
			double setMacroVariable(int address, double value)
			{
				syncVariables_.setMacroVariable(int address, double value);
			}
			//��ȡPLC����
			unsigned long plcVariable(rmi::PlcReadOnlyVariableName name) const
			{
				return syncVariables_.plcVariable(name);
			}
			//дPLC����
			void setPlcVariable(rmi::PlcWriteOnlyVariableName name, unsigned long value)
			{
				syncVariables_.setPlcVariable(name, value);
			}
			//��ȡ��ǰ��е����
			std::array<double, AXIS_MAX> mechanicalCoordinates(int channel) const
			{
				//������
				std::array<double, AXIS_MAX> coordinates;
				//ͨ��ƫ��
				int channelInterval = (channel - 1) * CHANNEL_INTERVAL;
				//���ú�����ӿڻ�ȡ��е����
				for (int i = 0; i < AXIS_MAX; ++i)
				{
					coordinates[i] = macroVariable(MECHANICAL_COORDINATE + i * AXIS_INTERVAL + channelInterval);
				}
				return coordinates;
			}

			//��ȡ��ǰ��������
			std::array<double, AXIS_MAX> workpieceCoordinates(int channel) const
			{
				//������
				std::array<double, AXIS_MAX> coordinates;
				//ͨ��ƫ��
				int channelInterval = (channel - 1) * CHANNEL_INTERVAL;
				//���ú�����ӿڻ�ȡ��������
				for (int i = 0; i < AXIS_MAX; ++i)
				{
					coordinates[i] = macroVariable(WORKPIECE_COORDINATE + i * AXIS_INTERVAL + channelInterval);
				}
				return coordinates;
			}

			//��ȡ��ǰ�ӹ�����
			std::array<double, AXIS_MAX> machiningRemains(int channel) const
			{
				//������
				std::array<double, AXIS_MAX> remains;
				//ͨ��ƫ��
				int channelInterval = (channel - 1) * CHANNEL_INTERVAL;
				//���ú�����ӿڻ�ȡ�ӹ�����
				for (int i = 0; i < AXIS_MAX; ++i)
				{
					remains[i] = macroVariable(MACHINING_REMAIN + i * AXIS_INTERVAL + channelInterval);
				}
				return remains;
			}

			//��ȡ��ǰ��︺��
			std::array<double, AXIS_MAX> motorLoads(int channel) const
			{
				//������
				std::array<double, AXIS_MAX> loads;
				//ͨ��ƫ��
				int channelInterval = (channel - 1) * CHANNEL_INTERVAL;
				//���ú�����ӿڻ�ȡ��︺��
				for (int i = 0; i < AXIS_MAX; ++i)
				{
					loads[i] = macroVariable(MOTOR_LOAD + i * AXIS_INTERVAL + channelInterval);
				}
				return loads;
			}

		private:
			SystemVariables() {};
			SyncVariables syncVariables_;
		};
	}
}


#endif // !LTP_BASE_SYSTEM_VARIABLES_H_
