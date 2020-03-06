#ifndef LTP_BASE_SYSTEM_VARIABLES_H_
#define LTP_BASE_SYSTEM_VARIABLES_H_

#include <array>
#include <unordered_set>
#include <unordered_map>
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
			void setMacroVariable(int address, double value)
			{
				syncVariables_.setMacroVariable(address, value);
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
					coordinates[i] = macroVariable(MECHANICAL_COORDINATE + i * AXIS_CONTROL_INTERVAL + channelInterval);
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
					coordinates[i] = macroVariable(WORKPIECE_COORDINATE + i * AXIS_CONTROL_INTERVAL + channelInterval);
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
					remains[i] = macroVariable(MACHINING_REMAIN + i * AXIS_CONTROL_INTERVAL + channelInterval);
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
					loads[i] = macroVariable(MOTOR_LOAD + i * AXIS_CONTROL_INTERVAL + channelInterval);
				}
				return loads;
			}

			std::vector<char> validFeedAxes()
			{
				/*��Ч���б�*/
				std::unordered_set<char> validFeedAxes;
				/*���п��ܵ����ַ�˳��*/
				char axesChar[] = { 'X', 'Y', 'Z', 'A', 'B', 'C', 'U', 'V', 'W' };
				std::vector<char> feedAxes(axesChar, axesChar + sizeof(axesChar));
				/*��ʱ����*/
				double tempData;
				for (int i = 0; i < AXIS_MAX; ++i)
				{
					/*����Ч���*/
					tempData = macroVariable(FEED_AXIS_VALID + i * AXIS_SETTING_INTERVAL);
					/*����Ч*/
					if (tempData > 1e-3)
					{
						/*���ַ�*/
						tempData = macroVariable(FEED_AXIS_CHARACTER + i * AXIS_SETTING_INTERVAL);
						/*ת��Ϊ�ַ�������*/
						validFeedAxes.insert(static_cast<char>(tempData));
					}
				}
				/*��˳������������*/
				for (auto pr = feedAxes.begin(); pr != feedAxes.end();)
				{
					/*�Ƴ�δ�ҵ�����*/
					if (validFeedAxes.find(*pr) == validFeedAxes.end())
					{
						pr = feedAxes.erase(pr);
					}
					else
					{
						pr++;
					}
				}
				return std::move(feedAxes);
			}

			std::unordered_map<char, int> axesAddress()
			{
				std::unordered_map<char, int> result;
				/*��ʱ����*/
				double tempData;
				for (int i = 0; i < AXIS_MAX; ++i)
				{
					/*����Ч���*/
					tempData = macroVariable(FEED_AXIS_VALID + i * AXIS_SETTING_INTERVAL);
					/*����Ч*/
					if (tempData > 1e-3)
					{
						/*���ַ�*/
						tempData = macroVariable(FEED_AXIS_CHARACTER + i * AXIS_SETTING_INTERVAL);
						/*�������ַ������ַӳ��*/
						result[static_cast<char>(tempData)] = 
							static_cast<int>(macroVariable(base::AXIS_ADDRESS + i * AXIS_SETTING_INTERVAL));
					}
				}
				return std::move(result);
			}

		private:
			SystemVariables() {};
			SyncVariables syncVariables_;
		};
	}
}


#endif // !LTP_BASE_SYSTEM_VARIABLES_H_
