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
			void initModuleButtonsWidget();					// ��ʼ����ఴťģ����Ϣ

		signals:
			void signalChangeProcessFileName(QString);		// ��ǰ�ӹ��ļ����ı�
			void signalChangeModules(QString);				// �л�ģ�飬�˵�����Ϣ�޸�

		private slots:
			void onModule(int);								// �л����˵�ģ��
			void onHome();									// ������ҳ
			void enableFileButtons(bool);					// ʹ���ļ�����򿪡�ִ�а�ť
			void onFileWidgetModule(int);					// �л��ļ�����ģ��
			void onProgrameEditWidgetModule(int);			// �л��༭ģ��
			void backProgrameModule();						// �лر༭ģ��
		};
	}
}


#endif // LTP_CLIENT_MAINCONTAINER_H_