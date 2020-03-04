#ifndef LTP_CLIENT_MACHININGSTATES_H_
#define LTP_CLIENT_MACHININGSTATES_H_

#include <vector>
#include <QString>
#include <QObject>
#include <QTimer>
#include "base/globals.h"
#include "base/singleton.hpp"

namespace ltp
{
	namespace client
	{
		class MachiningStates : public QObject
		{
			Q_OBJECT
			friend MachiningStates& base::getInstance<MachiningStates>();

		public:
			//��ȡԶ��ģʽ
			base::Mode mode() const;
			//��ȡԶ�̼ӹ�״̬
			base::MachiningState machiningState() const;
			//��ȡԶ�̼��ص��ļ���(����·��)
			QString machiningFilePath() const;
			//��ȡԶ�̼��ص��ļ���(������·��)
			QString machiningFileName() const;
			//��ȡ�����ȼ�
			base::ErrorLevel errorLevel() const;
			//��ȡ��Ч��
			const std::vector<char>& validAxes() const;

		signals:
			//��⵽ģʽ�л�ʱ�����ź�
			void modeChanged(base::Mode mode);
			//��⵽�ӹ�״̬�л������ź�
			void machiningStateChanged(base::MachiningState machiningState);
			//����ȼ��仯�ź�
			void errorLevelChanged(base::ErrorLevel errorLevel);
			//��⵽���ڼӹ����ļ���(��·��)�仯
			void machiningFilePathChanged(QString filePath);
			//��⵽���ڼӹ����ļ���(����·��)�仯����·���仯ʱ������
			void machiningFileNameChanged(QString filePath);
			//��Ч��仯�ź�
			void validAxesChanged(const std::vector<char>& validAxes);

		private:
			base::Mode mode_;
			base::MachiningState machiningState_;
			base::ErrorLevel errorLevel_;
			QString filePath_;
			QString fileName_;
			//��Ч��
			std::vector<char> validAxes_;
			//����״̬ʹ�õĶ�ʱ��
			QTimer timer_;
			//��Ϊ����ʹ��
			MachiningStates(QObject* parent = nullptr);
			~MachiningStates();

		private slots:
			//����״̬��ȷ���Ƿ�仯��������Ӧ�ź�
			void updateState();
			//ȷ����Ч��
			void checkValidAxes();
		};
	}
}

#endif // LTP_CLIENT_MACHININGSTATES_H_