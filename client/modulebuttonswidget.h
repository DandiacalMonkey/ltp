#ifndef LTP_CLIENT_MODULEBUTTONSWIDGET_H_
#define LTP_CLIENT_MODULEBUTTONSWIDGET_H_

#include <QtGui/QWidget>
#include "ui_modulebuttonswidget.h"

namespace ltp
{
	namespace client
	{
		class ModuleButtonsWidget : public QWidget
		{
			Q_OBJECT

		public:
			ModuleButtonsWidget(QWidget* parent = 0);
			~ModuleButtonsWidget();

			void setButtonEnabled(int id, bool enabled);
			void setReturnButtonEnabled(bool enabled);
			void setCommandButtonName(int id, QString name);
			void setCheckedButton(int id, bool checked);
			void setExclusive(bool);
			void setCheckableButton(bool);

		signals:
			void signalButtonClicked(int id);
			void signalButtonPressed(int id);
			void signalButtonReleased(int id);
			void signalReturnButtonClicked();

		private:
			Ui::ModuleButtonsWidgetClass ui;
			QButtonGroup *buttonGroup_;
		};
	}
}


#endif // LTP_CLIENT_MODULEBUTTONSWIDGET_H_