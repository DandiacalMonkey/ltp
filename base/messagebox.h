#ifndef LTP_BASE_MESSAGEBOX_H_
#define LTP_BASE_MESSAGEBOX_H_

#include <memory>
#include <QDialog>
#include <QMessageBox>
#include "ui_messagebox.h"

namespace ltp
{
	namespace base
	{
		class MessageBox : public QDialog
		{
			Q_OBJECT

		public:
			MessageBox(QDialog*parent = 0);
			~MessageBox();
			//设定中间显示的内容
			void setContentWidget(std::shared_ptr<QWidget> contentWidget);
			//设定标题
			void setTitleName(const QString& text);
			//获取结果
			QPushButton* clickedButton() const
			{
				return clickedButton_;
			}
			//添加下方按钮
			QPushButton* addButton(const QString& text, QMessageBox::ButtonRole role);

		private:
			Ui::MessageBoxClass ui;
			std::shared_ptr<QWidget> contentWidget_;
			QPushButton* clickedButton_;

		private slots:
			//移动窗口
			void moveDialog(QPoint);
			//自定义按钮被按下
			void buttonClick();

		};
	}
}

#endif // LTP_BASE_MESSAGEBOX_H_
