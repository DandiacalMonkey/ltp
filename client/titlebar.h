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

		private:
			Ui::TitleBarClass ui;
			QTimer* updateTimeTimer_;

		private slots:
			void updateTime();									// 更新时间
			void setMode(base::Mode modeType);					// 设置模式信息
			void setModuleName(const QString &name);			// 设置模块信息
			void setMachiningState(base::MachiningState state);	// 设置加工状态
			void setCurrentNCName(const QString &name);			// 设置当前加工文件
			void setErrorMessages(base::ErrorLevel errlevel);	// 设置报错信息
			void setConnectState(bool isConnect);				// 设置连接状态
		};
	}
}


#endif // LTP_CLIENT_TITLEBAR_H_