#ifndef LTP_CLIENT_MACHININGSTATES_H_
#define LTP_CLIENT_MACHININGSTATES_H_

#include <vector>
#include <unordered_map>
#include <QString>
#include <QObject>
#include <QTimer>
#include "base/globals.h"
#include "base/singleton.hpp"

namespace ltp
{
	namespace client
	{
		class MachiningStates : public QObject
		{
			Q_OBJECT
			friend MachiningStates& base::getInstance<MachiningStates>();

		public:
			//获取远程模式
			base::Mode mode() const;
			//获取远程加工状态
			base::MachiningState machiningState() const;
			//获取远程加载的文件名(包含路径)
			QString machiningFilePath() const;
			//获取远程加载的文件名(不包含路径)
			QString machiningFileName() const;
			//获取报警等级
			base::ErrorLevel errorLevel() const;
			//获取有效轴
			const std::vector<base::Axis>& validAxes() const;
			//将轴枚举转换为轴字符
			char axisEnumToAxisCharacter(base::Axis axisEnum) const;
			std::vector<char> axesEnumToAxesCharacter(const std::vector<base::Axis>& axesEnum) const;
			//将轴字符转换为轴枚举
			base::Axis axisCharacterToAxisEnum(char axisCharacter) const;
			std::vector<base::Axis> axesCharacterToAxesEnum(const std::vector<char>& axesCharacter) const;
			//根据轴枚举获取轴地址
			int axisEnumToAxisAddress(base::Axis axisEnum) const;

		signals:
			//检测到模式切换时发出信号
			void modeChanged(base::Mode mode);
			//检测到加工状态切换发出信号
			void machiningStateChanged(base::MachiningState machiningState);
			//报错等级变化信号
			void errorLevelChanged(base::ErrorLevel errorLevel);
			//检测到正在加工的文件名(含路径)变化
			void machiningFilePathChanged(QString filePath);
			//检测到正在加工的文件名(不含路径)变化，仅路径变化时不发送
			void machiningFileNameChanged(QString filePath);
			//有效轴变化信号
			void validAxesChanged(const std::vector<base::Axis>& validAxes);

		private:
			base::Mode mode_;
			base::MachiningState machiningState_;
			base::ErrorLevel errorLevel_;
			QString filePath_;
			QString fileName_;
			//有效轴
			std::vector<base::Axis> validAxes_;
			//更新状态使用的定时器
			QTimer timer_;
			//轴枚举到轴字符的映射
			std::unordered_map<base::Axis, char> axisEnumAxisCharacterMap_;
			//轴字符到轴枚举的映射
			std::unordered_map<char, base::Axis> axisCharacterAxisEnumMap_;
			//轴枚举到轴地址的映射
			std::unordered_map<base::Axis, int> axesAddress_;
			//作为单例使用
			MachiningStates(QObject* parent = nullptr);
			~MachiningStates();

		private slots:
			//更新状态，确定是否变化，发送相应信号
			void updateState();
			//网络连接成功，更新轴信息
			void updateAxesInformation();
			// 模式切换
			void modeChanged(int);
			// 倍率变化
			void rateChanged(int);
		};
	}
}

#endif // LTP_CLIENT_MACHININGSTATES_H_