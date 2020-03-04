#ifndef LTP_CLIENT_MACHININGSTATES_H_
#define LTP_CLIENT_MACHININGSTATES_H_

#include <vector>
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
			const std::vector<char>& validAxes() const;

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
			void validAxesChanged(const std::vector<char>& validAxes);

		private:
			base::Mode mode_;
			base::MachiningState machiningState_;
			base::ErrorLevel errorLevel_;
			QString filePath_;
			QString fileName_;
			//有效轴
			std::vector<char> validAxes_;
			//更新状态使用的定时器
			QTimer timer_;
			//作为单例使用
			MachiningStates(QObject* parent = nullptr);
			~MachiningStates();

		private slots:
			//更新状态，确定是否变化，发送相应信号
			void updateState();
			//确认有效轴
			void checkValidAxes();
		};
	}
}

#endif // LTP_CLIENT_MACHININGSTATES_H_