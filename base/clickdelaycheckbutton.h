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

			//�趨check��麯���Լ����Ƶ��
			void setCheckFunction(const std::function<void()>& function, int milliseconds);
			//�趨������������ʱʱ�䡢��ʱ��麯��
			void setClickDelayCheck(const std::function<void()>& clickFunction, 
				int miliseconds, const std::function<void()>& delayCheckFunction);

		protected:
			virtual void nextCheckState();

		private:
			//�Ƿ��Զ�����checked״̬
			bool isAutoChecked_;
			//���ʱʹ�õļ�麯��
			std::function<void()> checkFunction_;
			//��麯����ʱ��
			QTimer* timer_;
			//��ť�����Ӧ����
			std::function<void()> clickFunction_;
			//�������ʱʱ��
			int delayMilliseconds_;
			//��ʱȷ�Ϻ���
			std::function<void()> delayCheckFunction_;

		private slots:
			void checkState();
			void onClick();
			void checkClick();
		};
	}
}




#endif // LTP_BASE_CLICKDELAYCHECKBUTTON_H_