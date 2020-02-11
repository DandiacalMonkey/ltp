#ifndef LTP_CLIENT_SELECTAXISBAR_H_
#define LTP_CLIENT_SELECTAXISBAR_H_

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
			Ui::SelectAxisBarClass ui;
		};
	}
}


#endif // LTP_CLIENT_SELECTAXISBAR_H_