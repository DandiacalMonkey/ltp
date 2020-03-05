#ifndef LTP_CLIENT_SELECTAXISBAR_H_
#define LTP_CLIENT_SELECTAXISBAR_H_

#include <array>
#include <QtGui/QWidget>
#include "ui_selectaxisbar.h"

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

		private:
			//最大显示的进给轴数量
			static const int kMaxFeedAxes = 5;
			Ui::SelectAxisBarClass ui;
			//储存进给轴按钮
			std::array<base::ClickDelayCheckButton*, kMaxFeedAxes> axisButtons_;
			//法向轴按钮
			QPushButton* normalDirectionAxisButton_;
		};
	}
}


#endif // LTP_CLIENT_SELECTAXISBAR_H_