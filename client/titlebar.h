#ifndef LTP_CLIENT_TITLEBAR_H_
#define LTP_CLIENT_TITLEBAR_H_

#include <QtGui/QWidget>
#include "ui_titlebar.h"
#include "base/globals.h"

#include <QTimer>
#include <QLabel>

namespace ltp
{
	namespace client
	{
		class TitleBar : public QWidget
		{
			Q_OBJECT
		 
		public:
			TitleBar(QWidget *parent = 0);
			~TitleBar();  

			void setMode(ltp::base::Mode modeType);
			void setModuleName(const QString &name);
			void setMachiningState(ltp::base::MachiningState state);
			void setCurrentNCName(const QString &name);
			void setErrorMessages(const std::vector<std::string> &errorMessages);

		private:
			Ui::TitleBarClass ui;
			QTimer* updateTimeTimer_;

		private slots:
			void updateTime();

		};
	}
}


#endif // LTP_CLIENT_TITLEBAR_H_