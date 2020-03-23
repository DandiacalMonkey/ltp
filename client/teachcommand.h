#ifndef LTP_CLIENT_TEACHCOMMAND_H_
#define LTP_CLIENT_TEACHCOMMAND_H_

#include <array>
#include <vector>
#include <QString>
#include "base/globals.h"

namespace ltp
{
	namespace client
	{
		class TeachCommand
		{
		public:
			typedef std::array<double, base::AXIS_MAX> Point;
			//示教出现错误，如两点相同等问题
			class TeachCommandException : public std::exception {};
			explicit TeachCommand(const QString& teachTitle, int pointNumber);
			//确认当前点，返回是否示教完成
			virtual bool checkPoint() = 0;
			//前一点，返回是否还能向前
			virtual bool previousPoint();
			//获取指令
			virtual QString getCommand() = 0;
			//是否为最后一点
			virtual bool isLastPoint();
			//重置
			virtual void reset() = 0;
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