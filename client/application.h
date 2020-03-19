#ifndef LTP_CLIENT_APPLICATION_H_
#define LTP_CLIENT_APPLICATION_H_

#include <QApplication>
#include <QKeyEvent>

namespace ltp
{
	namespace client
	{
		class Application : public QApplication
		{
			Q_OBJECT

		public:
			Application(int& argc, char** argv);
			virtual bool notify(QObject* receiver, QEvent* event);

		private slots:
			void receiveKeyboardEvent(QKeyEvent*);

		private:
			QWidget *currentWidget_;         // 当前焦点的对象
			QString currentEditType_;        // 当前焦点控件的类型
		};
	}
}

#endif // !LTP_CLIENT_APPLICATION_H_
