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
			void setButtonPicture(const QString&, const QString&, const QString&, const QString&);
		};
	}
}


#endif // LTP_BASE_PANELBUTTON_H_