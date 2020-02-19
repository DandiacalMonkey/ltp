#ifndef LTP_CLIENT_MODULEBUTTONSWIDGET_H_
#define LTP_CLIENT_MODULEBUTTONSWIDGET_H_

#include <QtGui/QWidget>
#include "ui_modulebuttonswidget.h"

namespace ltp
{
	namespace client
	{
		//��ťö��
		enum BUTTONID
		{
			BUTTON1,
			BUTTON2,
			BUTTON3,
			BUTTON4,
			BUTTON5,
			BUTTON6
		};

		class ModuleButtonsWidget : public QWidget
		{
			Q_OBJECT

		public:
			ModuleButtonsWidget(QWidget* parent = 0);
			~ModuleButtonsWidget();

			void setButtonEnabled(bool enabled);
			void setReturnButtonEnabled(bool enabled);

		private:
			Ui::ModuleButtonsWidgetClass ui;
			QButtonGroup *buttonGroup_;

		private slots:
			void buttonClicked(int id);
			void buttonPressed(int id);
			void buttonReleased(int id);
			void returnButtonClicked();
		};
	}
}


#endif // LTP_CLIENT_MODULEBUTTONSWIDGET_H_