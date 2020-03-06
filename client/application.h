#ifndef LTP_CLIENT_APPLICATION_H_
#define LTP_CLIENT_APPLICATION_H_

#include <QApplication>

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
		};
	}
}

#endif // !LTP_CLIENT_APPLICATION_H_
