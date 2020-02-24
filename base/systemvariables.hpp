#ifndef LTP_BASE_SYSTEM_VARIABLES_H_
#define LTP_BASE_SYSTEM_VARIABLES_H_

#include <array>
#include "globals.h"
#include "singleton.hpp"

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

		private:
			SystemVariables() {};
			SyncVariables syncVariables_;
		};
	}
}


#endif // !LTP_BASE_SYSTEM_VARIABLES_H_
