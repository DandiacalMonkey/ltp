#ifndef LTP_CLIENT_TEACHCOMMAND_H_
#define LTP_CLIENT_TEACHCOMMAND_H_

#include <array>
#include <vector>
#include <QString>
#include <QObject>
#include "base/globals.h"
#include "base/ltpmath.h"

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
			//生成代码的默认精度
			static const int kPrecision_ = 4;
			explicit TeachCommand(const QString& teachTitle, int pointNumber);
			//确认当前点，返回是否示教完成
			virtual bool checkPoint() = 0;
			//前一点
			virtual void previousPoint();
			//是否能退回前一点
			virtual bool hasPreviousPoint() const = 0;
			//获取指令
			virtual QString getCommand() const = 0;
			//是否为最后一点
			virtual bool isLastPoint() const;
			//重置
			virtual void reset() = 0;
			//将输入的轴和坐标转换为指令
			QString generateCommand(const std::vector<base::Axis> axes, 
				std::array<double, base::AXIS_MAX> position, int precision = kPrecision_) const;
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
			//确认是否有重复点
			template <typename Point>
			bool hasSamePoint(Point point)
			{
				//输入点和当前所有点对比，确认是否有重复
				for (int i = 0; i < points_.size(); i++)
				{
					auto tempPoint = base::Math::makePoint<Point>(points_[i].begin());
					if (base::Math::isSamePoint(point, tempPoint))
					{
						return true;
					}
				}
				return false;
			}

		protected:
			//示教标题
			const QString kTeachTitle_;
			//示教最大点数量
			const int kPointNumber_;
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