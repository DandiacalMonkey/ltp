#ifndef LTP_CLIENT_BUTTON_PROCESSOR_H_
#define LTP_CLIENT_BUTTON_PROCESSOR_H_

#include <vector>
#include <memory>
#include <functional>
#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QAtomicInt>
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
					state_ = state;
				}
				//判定按钮是否完成，从列表中删除
				virtual bool isFinished() const;

			protected:
				QAtomicInt state_;
			};
			class FunctionalButton : public ButtonInterface
			{
			public:
				FunctionalButton(const std::function<void (ButtonInterface* buttonInterface)>& trigger1, 
					const std::function<void (ButtonInterface * buttonInterface)>& trigger2,
					const std::function<void (ButtonInterface * buttonInterface)>& trigger3);
				virtual void trigger();
			private:
				//分别为按下，持续，松开触发的不同函数
				std::function<void (ButtonInterface * buttonInterface)> trigger1_;
				std::function<void (ButtonInterface * buttonInterface)> trigger2_;
				std::function<void (ButtonInterface * buttonInterface)> trigger3_;
			};
			~ButtonProcessor() {};
			//添加按钮
			void addButton(std::shared_ptr<ButtonInterface>& button);

		private:
			//处理的调用时间间隔
			const double kProcessInterval_;
			//触发处理函数的定时器
			QTimer processTimer_;
			//防止添加按钮和处理函数冲突
			mutable QMutex mutex_;
			//储存当前按钮列表
			std::vector<std::shared_ptr<ButtonInterface>> buttonsList_;
			//构造函数私有
			ButtonProcessor();
		
		private slots:
			//处理函数
			void processButton();
		};
	}
}

#endif // LTP_CLIENT_BUTTON_PROCESSOR_H_