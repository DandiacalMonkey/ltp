#ifndef LTP_BASE_CLICKDELAYCHECKBUTTON_H_
#define LTP_BASE_CLICKDELAYCHECKBUTTON_H_

#include <functional>
#include <QPushButton>
#include <QTimer>

namespace ltp
{
	namespace base
	{
		class ClickDelayCheckButton : public QPushButton
		{
			Q_OBJECT

		public:
			explicit ClickDelayCheckButton(QWidget* parent = nullptr);
			~ClickDelayCheckButton();

			//设定check检查函数以及检查频率
			void setCheckFunction(const std::function<void()>& function, int milliseconds);
			//设定触发函数和延时时间、延时检查函数
			void setClickDelayCheck(const std::function<void()>& clickFunction, 
				int miliseconds, const std::function<void()>& delayCheckFunction);

		protected:
			virtual void nextCheckState();

		private:
			//是否自动设置checked状态
			bool isAutoChecked_;
			//检查时使用的检查函数
			std::function<void()> checkFunction_;
			//检查函数定时器
			QTimer* timer_;
			//按钮点击响应函数
			std::function<void()> clickFunction_;
			//点击后延时时间
			int delayMilliseconds_;
			//延时确认函数
			std::function<void()> delayCheckFunction_;

		private slots:
			void checkState();
			void onClick();
			void checkClick();
		};
	}
}




#endif // LTP_BASE_CLICKDELAYCHECKBUTTON_H_