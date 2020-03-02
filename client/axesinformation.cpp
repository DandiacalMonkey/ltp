#include "axesinformation.h"
#include "base/systemvariables.hpp"
#include "remotevariables.hpp"

using ltp::client::AxesInformation;

AxesInformation::AxesInformation(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 初始将所有轴信息隐藏
	ui.labelAxesA_->hide();
	ui.machineCoordinateAxesA_->hide();
	ui.machiningRemainAxesA_->hide();
	ui.motorLoadAxesA_->hide();
	ui.workpieceCoordinateAxesA_->hide();
	
	ui.labelAxesB_->hide();
	ui.machineCoordinateAxesB_->hide();
	ui.machiningRemainAxesB_->hide();
	ui.motorLoadAxesB_->hide();
	ui.workpieceCoordinateAxesB_->hide();

	ui.labelAxesC_->hide();
	ui.machineCoordinateAxesC_->hide();
	ui.machiningRemainAxesC_->hide();
	ui.motorLoadAxesC_->hide();
	ui.workpieceCoordinateAxesC_->hide();

	ui.labelAxesX_->hide();
	ui.machineCoordinateAxesX_->hide();
	ui.machiningRemainAxesX_->hide();
	ui.motorLoadAxesX_->hide();
	ui.workpieceCoordinateAxesX_->hide();

	ui.labelAxesY_->hide();
	ui.machineCoordinateAxesY_->hide();
	ui.machiningRemainAxesY_->hide();
	ui.motorLoadAxesY_->hide();
	ui.workpieceCoordinateAxesY_->hide();

	ui.labelAxesZ_->hide();
	ui.machineCoordinateAxesZ_->hide();
	ui.machiningRemainAxesZ_->hide();
	ui.motorLoadAxesZ_->hide();
	ui.workpieceCoordinateAxesZ_->hide();

	ui.labelAxesU_->hide();
	ui.machineCoordinateAxesU_->hide();
	ui.machiningRemainAxesU_->hide();
	ui.motorLoadAxesU_->hide();
	ui.workpieceCoordinateAxesU_->hide();

	ui.labelAxesV_->hide();
	ui.machineCoordinateAxesV_->hide();
	ui.machiningRemainAxesV_->hide();
	ui.motorLoadAxesV_->hide();
	ui.workpieceCoordinateAxesV_->hide();

	ui.labelAxesW_->hide();
	ui.machineCoordinateAxesW_->hide();
	ui.machiningRemainAxesW_->hide();
	ui.motorLoadAxesW_->hide();
	ui.workpieceCoordinateAxesW_->hide();

	// 根据连接一起判断需要显示的轴信息
	std::vector<base::Axis> tempAxis;
	tempAxis.push_back(base::X_AXIS);
	tempAxis.push_back(ltp::base::Y_AXIS);
	tempAxis.push_back(ltp::base::Z_AXIS);
	tempAxis.push_back(ltp::base::U_AXIS);
	tempAxis.push_back(ltp::base::V_AXIS);
	tempAxis.push_back(ltp::base::W_AXIS);
	shownAxis = tempAxis;
	setValidAxes(tempAxis);
	ui.gridLayout->update();
	
	// 定时器每0.5s更新一次数据
	QTimer *timer_ = new QTimer();
	connect(timer_, SIGNAL(timeout()), this, SLOT(onTimer()));
	timer_->start(500);
}

AxesInformation::~AxesInformation()
{

}

void AxesInformation::setValidAxes(const std::vector<ltp::base::Axis> &validAxes)
{
	for (int i = 0; i < validAxes.size(); ++i)			// 对系统轴信息进行显示
	{
		if (validAxes.at(i) == ltp::base::X_AXIS)
		{
			ui.labelAxesX_->show();
			ui.machineCoordinateAxesX_->show();
			ui.machiningRemainAxesX_->show();
			ui.motorLoadAxesX_->show();
			ui.workpieceCoordinateAxesX_->show();
		}
		else if (validAxes.at(i) == ltp::base::Y_AXIS)
		{
			ui.labelAxesY_->show();
			ui.machineCoordinateAxesY_->show();
			ui.machiningRemainAxesY_->show();
			ui.motorLoadAxesY_->show();
			ui.workpieceCoordinateAxesY_->show();
		}
		else if (validAxes.at(i) == ltp::base::Z_AXIS)
		{
			ui.labelAxesZ_->show();
			ui.machineCoordinateAxesZ_->show();
			ui.machiningRemainAxesZ_->show();
			ui.motorLoadAxesZ_->show();
			ui.workpieceCoordinateAxesZ_->show();
		}
		else if (validAxes.at(i) == ltp::base::U_AXIS)
		{
			ui.labelAxesU_->show();
			ui.machineCoordinateAxesU_->show();
			ui.machiningRemainAxesU_->show();
			ui.motorLoadAxesU_->show();
			ui.workpieceCoordinateAxesU_->show();
		}
		else if (validAxes.at(i) == ltp::base::V_AXIS)
		{
			ui.labelAxesV_->show();
			ui.machineCoordinateAxesV_->show();
			ui.machiningRemainAxesV_->show();
			ui.motorLoadAxesV_->show();
			ui.workpieceCoordinateAxesV_->show();
		}
		else if (validAxes.at(i) == ltp::base::W_AXIS)
		{
			ui.labelAxesW_->show();
			ui.machineCoordinateAxesW_->show();
			ui.machiningRemainAxesW_->show();
			ui.motorLoadAxesW_->show();
			ui.workpieceCoordinateAxesW_->show();
		}
		else if (validAxes.at(i) == ltp::base::A_AXIS)
		{
			ui.labelAxesA_->show();
			ui.machineCoordinateAxesA_->show();
			ui.machiningRemainAxesA_->show();
			ui.motorLoadAxesA_->show();
			ui.workpieceCoordinateAxesA_->show();
		}
		else if (validAxes.at(i) == ltp::base::B_AXIS)
		{
			ui.labelAxesB_->show();
			ui.machineCoordinateAxesB_->show();
			ui.machiningRemainAxesB_->show();
			ui.motorLoadAxesB_->show();
			ui.workpieceCoordinateAxesB_->show();
		}
		else if (validAxes.at(i) == ltp::base::C_AXIS)
		{
			ui.labelAxesC_->show();
			ui.machineCoordinateAxesC_->show();
			ui.machiningRemainAxesC_->show();
			ui.motorLoadAxesC_->show();
			ui.workpieceCoordinateAxesC_->show();
		}
	}
}

void AxesInformation::onTimer()
{
	// 机械坐标
	auto machineCoord = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().mechanicalCoordinates(1);
	// 工件坐标
	auto workpieceCoord = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().workpieceCoordinates(1);
	// 加工余量
	auto machiningRemain = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().machiningRemains(1);
	// 马达负载
	auto motorLoad = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().motorLoads(1);
	// 当前坐标系
	double coord = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().macroVariable(ltp::base::COORDINATE);

	// X轴
	ui.machineCoordinateAxesX_->setText(QString::number(machineCoord[0]));
	ui.workpieceCoordinateAxesX_->setText(QString::number(workpieceCoord[0]));
	ui.machiningRemainAxesX_->setText(QString::number(machiningRemain[0]));
	ui.motorLoadAxesX_->setValue(motorLoad[0]);
	// Y轴
	ui.machineCoordinateAxesY_->setText(QString::number(machineCoord[1]));
	ui.workpieceCoordinateAxesY_->setText(QString::number(workpieceCoord[1]));
	ui.machiningRemainAxesY_->setText(QString::number(machiningRemain[1]));
	ui.motorLoadAxesY_->setValue(motorLoad[1]);
	// Z轴
	ui.machineCoordinateAxesZ_->setText(QString::number(machineCoord[2]));
	ui.workpieceCoordinateAxesZ_->setText(QString::number(workpieceCoord[2]));
	ui.machiningRemainAxesZ_->setText(QString::number(machiningRemain[2]));
	ui.motorLoadAxesZ_->setValue(motorLoad[2]);
	// A轴
	ui.machineCoordinateAxesA_->setText(QString::number(machineCoord[3]));
	ui.workpieceCoordinateAxesA_->setText(QString::number(workpieceCoord[3]));
	ui.machiningRemainAxesA_->setText(QString::number(machiningRemain[3]));
	ui.motorLoadAxesA_->setValue(motorLoad[3]);
	// B轴
	ui.machineCoordinateAxesB_->setText(QString::number(machineCoord[4]));
	ui.workpieceCoordinateAxesB_->setText(QString::number(workpieceCoord[4]));
	ui.machiningRemainAxesB_->setText(QString::number(machiningRemain[4]));
	ui.motorLoadAxesB_->setValue(motorLoad[4]);
	// C轴
	ui.machineCoordinateAxesC_->setText(QString::number(machineCoord[5]));
	ui.workpieceCoordinateAxesC_->setText(QString::number(workpieceCoord[5]));
	ui.machiningRemainAxesC_->setText(QString::number(machiningRemain[5]));
	ui.motorLoadAxesC_->setValue(motorLoad[5]);
	// U轴
	ui.machineCoordinateAxesU_->setText(QString::number(machineCoord[6]));
	ui.workpieceCoordinateAxesU_->setText(QString::number(workpieceCoord[6]));
	ui.machiningRemainAxesU_->setText(QString::number(machiningRemain[6]));
	ui.motorLoadAxesU_->setValue(motorLoad[6]);
	// V轴
	ui.machineCoordinateAxesV_->setText(QString::number(machineCoord[7]));
	ui.workpieceCoordinateAxesV_->setText(QString::number(workpieceCoord[7]));
	ui.machiningRemainAxesV_->setText(QString::number(machiningRemain[7]));
	ui.motorLoadAxesV_->setValue(motorLoad[7]);
	// W轴
	ui.machineCoordinateAxesW_->setText(QString::number(machineCoord[8]));
	ui.workpieceCoordinateAxesW_->setText(QString::number(workpieceCoord[8]));
	ui.machiningRemainAxesW_->setText(QString::number(machiningRemain[8]));
	ui.motorLoadAxesW_->setValue(motorLoad[8]);

	// 当前坐标系
	QString str = "G" + QString::number(coord);
	ui.currentWorkpieceCoordinate_->setText(str);
}