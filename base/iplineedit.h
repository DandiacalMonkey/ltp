#ifndef LTP_BASE_IPLINEDIT_H_
#define LTP_BASE_IPLINEDIT_H_

#include <QtGui/QWidget>
#include "ui_iplineedit.h"

namespace ltp
{
	namespace base
	{
		class IPLineEdit : public QWidget
		{
			Q_OBJECT

		public:
			IPLineEdit(QWidget* parent = 0);
			~IPLineEdit();
			QString getIP();				// 获取ip地址

		private:
			Ui::IPLineEditClass ui;
			QString stringIP_;				// ip地址

		private slots:
			void textChanged(const QString&);
			void setIP(const QString&);		// 设置ip地址
			void clear();					// 清空

		protected:
			bool eventFilter(QObject *watched, QEvent *event);

		signals:
			void hasFinished(bool);
		};
	}
}


#endif // LTP_BASE_IPLINEDIT_H_