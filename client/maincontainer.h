#ifndef LTP_CLIENT_MAINCONTAINER_H_
#define LTP_CLIENT_MAINCONTAINER_H_

#include <QtGui/QWidget>
#include "ui_maincontainer.h"

namespace ltp
{
	namespace client
	{
		class MainContainer : public QWidget
		{
			Q_OBJECT

		public:
			MainContainer(QWidget* parent = 0);
			~MainContainer();

		private:
			Ui::MainContainerClass ui;
		};
	}
}


#endif // LTP_CLIENT_MAINCONTAINER_H_