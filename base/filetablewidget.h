#ifndef LTP_CLIENT_FILETABLEWIDGET_H_
#define LTP_CLIENT_FILETABLEWIDGET_H_

#include <QTableWidget>

namespace ltp
{
	namespace base
	{
		class FileTableWidget : public QTableWidget
		{
			Q_OBJECT

		public:
			FileTableWidget(QWidget* parent = 0);
			~FileTableWidget();

			void showAllFiles(QString path);
			void getInformation(QString path, int &fileNumbers);
			void tableWidgetClear();

		private slots: 
			void headerClicked(int column);


		signals:
			void fileOpened(const QString& filePath, const QString& fileName);
		};
	}
}

#endif // LTP_CLIENT_FILETABLEWIDGET_H_