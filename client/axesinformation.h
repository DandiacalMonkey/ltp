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

		private:
			Ui::AxesInformationClass ui;
			QTimer timer_;
			void hideAll();

		private slots:
			void onTimer();
			void setValidAxes(const std::vector<base::Axis> &validAxes);		// 设置需要显示的轴

		};
	}
}


#endif // LTP_CLIENT_AXESINFORMATION_H_