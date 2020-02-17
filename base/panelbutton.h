#ifndef LTP_BASE_PANELBUTTON_H_
#define LTP_BASE_PANELBUTTON_H_

#include <QtGui/QPushButton>
#include <QtGui/QLabel>

namespace ltp
{
	namespace base
	{
		class PanelButton : public QPushButton
		{
			Q_OBJECT
		 
		public:
			PanelButton(QWidget *parent = 0);
			~PanelButton(); 
			void setButtonText(const QString &text);
			void setButtonPicture(const QPixmap &picture);

		private:
			QLabel *text_;
			QLabel *picture_;

		};
	}
}


#endif // LTP_BASE_PANELBUTTON_H_