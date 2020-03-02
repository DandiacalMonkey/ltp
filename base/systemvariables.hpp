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
			//获取宏变量
			double macroVariable(int address) const
			{
				return syncVariables_.macroVariable(address);
			}
			//写宏变量
			double setMacroVariable(int address, double value)
			{
				syncVariables_.setMacroVariable(int address, double value);
			}
			//获取PLC变量
			unsigned long plcVariable(rmi::PlcReadOnlyVariableName name) const
			{
				return syncVariables_.plcVariable(name);
			}
			//写PLC变量
			void setPlcVariable(rmi::PlcWriteOnlyVariableName name, unsigned long value)
			{
				syncVariables_.setPlcVariable(name, value);
			}
			//获取当前机械坐标
			std::array<double, AXIS_MAX> mechanicalCoordinates(int channel) const
			{
				//储存结果
				std::array<double, AXIS_MAX> coordinates;
				//通道偏移
				int channelInterval = (channel - 1) * CHANNEL_INTERVAL;
				//调用宏变量接口获取机械坐标
				for (int i = 0; i < AXIS_MAX; ++i)
				{
					coordinates[i] = macroVariable(MECHANICAL_COORDINATE + i * AXIS_INTERVAL + channelInterval);
				}
				return coordinates;
			}

			//获取当前工件坐标
			std::array<double, AXIS_MAX> workpieceCoordinates(int channel) const
			{
				//储存结果
				std::array<double, AXIS_MAX> coordinates;
				//通道偏移
				int channelInterval = (channel - 1) * CHANNEL_INTERVAL;
				//调用宏变量接口获取工件坐标
				for (int i = 0; i < AXIS_MAX; ++i)
				{
					coordinates[i] = macroVariable(WORKPIECE_COORDINATE + i * AXIS_INTERVAL + channelInterval);
				}
				return coordinates;
			}

			//获取当前加工余量
			std::array<double, AXIS_MAX> machiningRemains(int channel) const
			{
				//储存结果
				std::array<double, AXIS_MAX> remains;
				//通道偏移
				int channelInterval = (channel - 1) * CHANNEL_INTERVAL;
				//调用宏变量接口获取加工余量
				for (int i = 0; i < AXIS_MAX; ++i)
				{
					remains[i] = macroVariable(MACHINING_REMAIN + i * AXIS_INTERVAL + channelInterval);
				}
				return remains;
			}

			//获取当前马达负载
			std::array<double, AXIS_MAX> motorLoads(int channel) const
			{
				//储存结果
				std::array<double, AXIS_MAX> loads;
				//通道偏移
				int channelInterval = (channel - 1) * CHANNEL_INTERVAL;
				//调用宏变量接口获取马达负载
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
