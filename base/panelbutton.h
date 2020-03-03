#ifndef LTP_BASE_PANELBUTTON_H_
#define LTP_BASE_PANELBUTTON_H_

#include <QLabel>
#include "base/clickdelaycheckbutton.h"

namespace ltp
{
	namespace base
	{
		class PanelButton : public ClickDelayCheckButton
		{
			Q_OBJECT
		 
		public:
			PanelButton(QWidget *parent = 0);
			~PanelButton(); 
			void setButtonText(const QString &text);			// 添加按钮文字
			void setButtonPicture(const QPixmap &picture);		// 添加按钮图片

		private:
			QLabel *text_;
			QLabel *picture_;
		};
	}
}


#endif // LTP_BASE_PANELBUTTON_H_