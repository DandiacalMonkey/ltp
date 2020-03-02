#ifndef LTP_CLIENT_BUTTON_PROCESSOR_H_
#define LTP_CLIENT_BUTTON_PROCESSOR_H_

#include <vector>
#include <memory>
#include <QObject>
#include <QTimer>
#include <QMutex>
#include "base/singleton.hpp"

namespace ltp
{
	namespace base
	{
		class ButtonProcessor : public QObject
		{
			Q_OBJECT
			//添加单例模板函数作为友元函数
			friend ButtonProcessor& getInstance<ButtonProcessor>();
		public:
			class ButtonInterface
			{
			public:
				enum State
				{
					PRESSED,
					HOLD,
					RELEASED
				};
				ButtonInterface();
				~ButtonInterface() {};
				//触发按钮功能接口
				virtual void trigger() = 0;
				//设定按钮状态
				void setState(State state)
				{
					QMutexLocker locker(&mutex_);
					state_ = state;
				}
				//判定按钮是否完成，从列表中删除
				virtual bool isFinished() const;

			private:
				mutable QMutex mutex_;
				State state_;
			};
			~ButtonProcessor() {};

		private:
			//构造函数私有
			ButtonProcessor();
			//处理的调用时间间隔
			const double kProcessInterval_;
			//添加按钮
			void addButton(const std::shared_ptr<ButtonInterface>& button);
			//触发处理函数的定时器
			QTimer processTimer_;
			//防止添加按钮和处理函数冲突
			mutable QMutex mutex_;
			//储存当前按钮列表
			std::vector<std::shared_ptr<ButtonInterface>> buttonsList_;
		
		private slots:
			//处理函数
			void processButton();
		};
	}
}

#endif // LTP_CLIENT_BUTTON_PROCESSOR_H_