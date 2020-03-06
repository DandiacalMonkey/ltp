#ifndef LTP_CLIENT_PHYSICALBUTTONSPROCESSOR_H_
#define LTP_CLIENT_PHYSICALBUTTONSPROCESSOR_H_

#include <QObject>
#include <QKeyEvent>
#include <unordered_map>
#include <functional>

class PhysicalButtonsProcessor : public QObject
{
	Q_OBJECT

public:
	PhysicalButtonsProcessor(QObject *parent);
	~PhysicalButtonsProcessor();

	bool isPhysicalButtonsProcessor(QKeyEvent* event) const;

signals:
	//���
	void leftButton1Clicked();
	void leftButton2Clicked();
	void leftButton3Clicked();
	void leftButton4Clicked();
	void leftButton5Clicked();
	void leftButton6Clicked();
	void leftButton7Clicked();

private:
	//��ť��ֵ������¼���ӳ��
	std::unordered_map<int, std::function<void()>> keyValueSignalMap_;
};

#endif // LTP_CLIENT_PHYSICALBUTTONSPROCESSOR_H_
