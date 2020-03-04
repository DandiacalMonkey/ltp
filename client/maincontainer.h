#ifndef LTP_CLIENT_MAINCONTAINER_H_
#define LTP_CLIENT_MAINCONTAINER_H_

#include <QtGui/QWidget>
#include "ui_maincontainer.h"

namespace ltp
{
	namespace client
	{
		class MainContainer : public QWidget
		{
			Q_OBJECT

		public:
			MainContainer(QWidget* parent = 0);
			~MainContainer();

		private:
			Ui::MainContainerClass ui;

		signals:
			void signalChangeProcessFileName(QString);		// ��ǰ�ӹ��ļ����ı�
			void signalChangeModules(QString);				// �л�ģ�飬�˵�����Ϣ�޸�

		private slots:
			void onModule(int);								// �л�ģ��
			void onHome();									// ������ҳ
			void onEditModule();							// �е�����༭ģ��
			void onProcessModule(QString);					// �е��ӹ�ģ��
		};
	}
}


#endif // LTP_CLIENT_MAINCONTAINER_H_