#ifndef LTP_CLIENT_PLUSMINUSWIDGET_H_
#define LTP_CLIENT_PLUSMINUSWIDGET_H_

#include <QtGui/QWidget>
#include "ui_plusminuswidget.h"

namespace ltp
{
	namespace base
	{
		class PlusMinusWidget : public QWidget
		{
			Q_OBJECT

		public:
			PlusMinusWidget(QWidget* parent = 0);
			~PlusMinusWidget();

			void setValue(int value);			// 数值改变
			void setIntervalValue(int value) {intervalValue_ = value;}		// 设置档位值
			void getCurrentLevel(int level) {currentLevel_ = level;}		// 获取当前档位值，加减后需要修改的值
			void setRange(int lowestLevel, int highestLevel) {highestLevel_ = highestLevel; lowestLevel_ = lowestLevel;}
		private:
			Ui::PlusMinusWidgetClass ui;
			int intervalValue_;					// 每次加减的数值
			int currentLevel_;					// 当前档位，加减后修改的值
			int highestLevel_;
			int lowestLevel_;

		private slots:
			void plusClicked();
			void minusClicked();

		signals:
			void valueChanged(int value);
		};
	}
}


#endif // LTP_CLIENT_PLUSMINUSWIDGET_H_