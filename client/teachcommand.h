#ifndef LTP_CLIENT_TEACHCOMMAND_H_
#define LTP_CLIENT_TEACHCOMMAND_H_

#include <array>
#include <vector>
#include <QString>
#include <QObject>
#include <QEventLoop>
#include "base/globals.h"
#include "base/ltpmath.h"
#include "base/systemvariables.hpp"
#include "remotevariables.hpp"

namespace ltp
{
	namespace client
	{
		class TeachCommand
		{
		public:
			typedef std::array<double, base::AXIS_MAX> Point;
			//示教出现错误，如两点相同等问题
			class TeachCommandException : public std::exception
			{
			public:
				virtual QString hint() const = 0;
			};
			//示教点中有重复点
			class RepeatPointException : public TeachCommandException
			{
			public:
				virtual QString hint() const
				{
					return QObject::tr("记录点重复，请移动后重新取点");
				}
			};
			//修改示教模式失败
			class ChangeTeachModeFail : public TeachCommandException
			{
			public:
				virtual QString hint() const
				{
					return QObject::tr("修改示教模式失败");
				}
			};
			//无法修改示教模式
			class CannotChangeTeachMode : public TeachCommandException
			{
			public:
				virtual QString hint() const
				{
					return QObject::tr("当前坐标有变化，请移动到起点或点击取消，再修改模式");
				}
			};
			//生成代码的默认精度
			static const int kPrecision_ = 4;
			explicit TeachCommand(const QString& teachTitle, int pointNumber);
			//确认当前点，返回是否示教完成
			virtual bool checkPoint() = 0;
			//前一点
			virtual void previousPoint();
			//是否能退回前一点
			virtual bool hasPreviousPoint() const = 0;
			//是否能切换刀尖坐标和绝对坐标
			virtual bool canChangeMode() const = 0;
			//进行坐标切换
			virtual bool changeMode() throw (ChangeTeachModeFail, CannotChangeTeachMode);
			//获取指令
			virtual QString getCommand() const = 0;
			//是否为最后一点
			virtual bool isLastPoint() const;
			//重置
			virtual void reset() = 0;
			//示教上一点坐标
			virtual Point previousPointPosition() const;
			//将输入的轴和坐标转换为指令
			QString generateCommand(const std::vector<base::Axis> axes,
				const Point& point, const std::function<char(base::Axis)>& axisEnumToChar, 
				int precision = kPrecision_) const;
			QString generateCommand(const std::vector<base::Axis> axes, 
				const base::Math::Line<Point>& line, 
				const std::function<char (base::Axis)>& axisEnumToChar,
				int precision = kPrecision_) const;
			//获取标题
			QString teachTitle() const
			{
				return kTeachTitle_;
			}
			//获取示教示意图路径
			QString schematicDiagramsPath() const
			{
				return schematicDiagramsPath_.at(points_.size());
			}
			//获取示教提示
			QString hint() const
			{
				return hints_.at(points_.size());
			}
			QString previousPointLabel() const
			{
				return previousPointLabel_.at(points_.size());
			}
			//确认是否有重复点，start表示要检测的坐标起始索引，end表示索引的尾后
			bool hasSamePoint(Point point, int start, int end);
			//确认轴坐标是否变化，start表示要检测的坐标起始索引，end表示索引的尾后
			bool isCoordinateChanged(Point point, int start, int end);

		protected:
			//示教标题
			const QString kTeachTitle_;
			//示教最大点数量
			const int kPointNumber_;
			//用于获取系统变量
			base::SystemVariables<RemoteVariables>& systemVariables_;
			//示教上一点的标签
			std::vector<QString> previousPointLabel_;
			//示教示意图路径
			std::vector<QString> schematicDiagramsPath_;
			//示教提示
			std::vector<QString> hints_;
			//示教储存的结果点
			std::vector<Point> points_;

		};
	}
}


#endif // !LTP_CLIENT_TEACHCOMMAND_H_