#ifndef LTP_BASE_DIALOGTITLEWIDGET_H_
#define LTP_BASE_DIALOGTITLEWIDGET_H_

#include <QtGui/QWidget>
#include <QPoint>
#include "ui_dialogtitlewidget.h"

namespace ltp
{
	namespace base
	{
		class DialogTitleWidget : public QWidget
		{
			Q_OBJECT

		public:
			DialogTitleWidget(QWidget* parent = 0);
			~DialogTitleWidget();
			void setTitleName(const QString &);

		private:
			Ui::DialogTitleWidgetClass ui;
			bool isMoveFlag_;				// 移动状态标志位
			QPoint mousePressPos_;			// 鼠标按下位置

		protected:
			void mousePressEvent(QMouseEvent *e);
			void mouseReleaseEvent(QMouseEvent *e);
			void mouseMoveEvent(QMouseEvent *e);

		signals:
			void signalClose();				// close按钮按下信号
			void mouseMove(QPoint point);	// 鼠标移动信号，代表移动窗口
		};
	}
}


#endif // LTP_BASE_DIALOGTITLEWIDGET_H_