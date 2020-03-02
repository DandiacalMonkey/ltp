#ifndef LTP_CLIENT_AXESINFORMATION_H_
#define LTP_CLIENT_AXESINFORMATION_H_

#include <QtGui/QWidget>
#include <QTimer>
#include "ui_axesinformation.h"
#include "base/globals.h"

namespace ltp
{
	namespace client
	{
		class AxesInformation : public QWidget
		{
			Q_OBJECT
		 
		public:
			AxesInformation(QWidget *parent = 0);
			~AxesInformation();  

			void setValidAxes(const std::vector<ltp::base::Axis> &validAxes);		// 设置需要显示的轴

		private:
			Ui::AxesInformationClass ui;
			QTimer timer_;
			std::vector<ltp::base::Axis> shownAxis;		// 显示轴

		private slots:
			void onTimer();

		};
	}
}


#endif // LTP_CLIENT_AXESINFORMATION_H_