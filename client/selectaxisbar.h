#ifndef LTP_CLIENT_SELECTAXISBAR_H_
#define LTP_CLIENT_SELECTAXISBAR_H_

#include <array>
#include <unordered_map>
#include <QtGui/QWidget>
#include <QTimer>
#include "ui_selectaxisbar.h"
#include "base/globals.h"

namespace ltp
{
	namespace client
	{
		class SelectAxisBar : public QWidget
		{
			Q_OBJECT

		public:
			SelectAxisBar(QWidget* parent = 0);
			~SelectAxisBar();

		public slots:
			void setValidAxes(const std::vector<base::Axis> validAxes);

		private:
			//最大显示的进给轴数量
			static const int kMaxFeedAxes = 5;
			Ui::SelectAxisBarClass ui;
			//储存进给轴按钮
			std::array<base::ClickDelayCheckButton*, kMaxFeedAxes> axisButtons_;
			//按钮到轴枚举的映射
			std::unordered_map<base::ClickDelayCheckButton*, base::Axis> buttonsAxisEnumMap_;
			//法向轴按钮
			QPushButton* normalDirectionAxisButton_;
			//刷新状态定时器
			QTimer timer;

		private slots:
			//更新轴选栏状态
			void updateInformation();
			// 右侧外设按键响应
			void plusButtonClicked(int);
			void minusButtonClicked(int);
			void startButtonClicked();
			void stopButtonClicked();
			void resetButtonClicked();
		};
	}
}

#endif // LTP_CLIENT_SELECTAXISBAR_H