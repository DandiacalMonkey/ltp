#ifndef LTP_CLIENT_SETWIDGET_H_
#define LTP_CLIENT_SETWIDGET_H_

#include <QtGui/QWidget>
#include "ui_setwidget.h"

namespace ltp
{
	namespace client
	{
		class SetWidget : public QWidget
		{
			Q_OBJECT
		 
		public:
			SetWidget(QWidget *parent = 0);
			~SetWidget();

		private:
			Ui::SetWidgetClass ui;
			void connectState(bool);
			void readIPSetting();		// 断电保存读取ip
			void writeIPSetting();		// 断电保存写入ip
			QString getTeachIP();			// 获取当前示教器ip地址
			void changeTeachIP();		// 修改当前示教器ip地址
			QString str_Analysis(QString line);

		private slots:
			void connectClicked(bool);
			void setConnected();
			void setDisconnected();
		
		};
	}
}
#endif // LTP_CLIENT_SETWIDGET_H_