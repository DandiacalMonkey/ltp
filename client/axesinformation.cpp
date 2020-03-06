#include "axesinformation.h"
#include "base/systemvariables.hpp"
#include "remotevariables.hpp"
#include "machiningstates.h"

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
	ui.machineCoordinateSymbolA_->hide();
	ui.machiningRemainSymbolA_->hide();
	ui.workpieceCoordinateSymbolA_->hide();
	ui.lineA_->hide();
	
	ui.labelAxesB_->hide();
	ui.machineCoordinateAxesB_->hide();
	ui.machiningRemainAxesB_->hide();
	ui.motorLoadAxesB_->hide();
	ui.workpieceCoordinateAxesB_->hide();
	ui.machineCoordinateSymbolB_->hide();
	ui.machiningRemainSymbolB_->hide();
	ui.workpieceCoordinateSymbolB_->hide();
	ui.lineB_->hide();

	ui.labelAxesC_->hide();
	ui.machineCoordinateAxesC_->hide();
	ui.machiningRemainAxesC_->hide();
	ui.motorLoadAxesC_->hide();
	ui.workpieceCoordinateAxesC_->hide();
	ui.machineCoordinateSymbolC_->hide();
	ui.machiningRemainSymbolC_->hide();
	ui.workpieceCoordinateSymbolC_->hide();
	ui.lineC_->hide();

	ui.labelAxesX_->hide();
	ui.machineCoordinateAxesX_->hide();
	ui.machiningRemainAxesX_->hide();
	ui.motorLoadAxesX_->hide();
	ui.workpieceCoordinateAxesX_->hide();
	ui.machineCoordinateSymbolX_->hide();
	ui.machiningRemainSymbolX_->hide();
	ui.workpieceCoordinateSymbolX_->hide();
	ui.lineX_->hide();

	ui.labelAxesY_->hide();
	ui.machineCoordinateAxesY_->hide();
	ui.machiningRemainAxesY_->hide();
	ui.motorLoadAxesY_->hide();
	ui.workpieceCoordinateAxesY_->hide();
	ui.machineCoordinateSymbolY_->hide();
	ui.machiningRemainSymbolY_->hide();
	ui.workpieceCoordinateSymbolY_->hide();
	ui.lineY_->hide();

	ui.labelAxesZ_->hide();
	ui.machineCoordinateAxesZ_->hide();
	ui.machiningRemainAxesZ_->hide();
	ui.motorLoadAxesZ_->hide();
	ui.workpieceCoordinateAxesZ_->hide();
	ui.machineCoordinateSymbolZ_->hide();
	ui.machiningRemainSymbolZ_->hide();
	ui.workpieceCoordinateSymbolZ_->hide();
	ui.lineZ_->hide();

	ui.labelAxesU_->hide();
	ui.machineCoordinateAxesU_->hide();
	ui.machiningRemainAxesU_->hide();
	ui.motorLoadAxesU_->hide();
	ui.workpieceCoordinateAxesU_->hide();
	ui.machineCoordinateSymbolU_->hide();
	ui.machiningRemainSymbolU_->hide();
	ui.workpieceCoordinateSymbolU_->hide();
	ui.lineU_->hide();

	ui.labelAxesV_->hide();
	ui.machineCoordinateAxesV_->hide();
	ui.machiningRemainAxesV_->hide();
	ui.motorLoadAxesV_->hide();
	ui.workpieceCoordinateAxesV_->hide();
	ui.machineCoordinateSymbolV_->hide();
	ui.machiningRemainSymbolV_->hide();
	ui.workpieceCoordinateSymbolV_->hide();
	ui.lineV_->hide();

	ui.labelAxesW_->hide();
	ui.machineCoordinateAxesW_->hide();
	ui.machiningRemainAxesW_->hide();
	ui.motorLoadAxesW_->hide();
	ui.workpieceCoordinateAxesW_->hide();
	ui.machineCoordinateSymbolW_->hide();
	ui.machiningRemainSymbolW_->hide();
	ui.workpieceCoordinateSymbolW_->hide();
	ui.lineW_->hide();

	// 根据连接控制器判断需要显示的轴信息
	connect(&base::getInstance<MachiningStates>(), SIGNAL(validAxesChanged(std::vector<base::Axis>)), this, SLOT(setValidAxes(std::vector<base::Axis>)));
	
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
			ui.machineCoordinateSymbolX_->show();
			ui.machiningRemainSymbolX_->show();
			ui.workpieceCoordinateSymbolX_->show();
			ui.lineX_->show();
		}
		else if (validAxes.at(i) == ltp::base::Y_AXIS)
		{
			ui.labelAxesY_->show();
			ui.machineCoordinateAxesY_->show();
			ui.machiningRemainAxesY_->show();
			ui.motorLoadAxesY_->show();
			ui.workpieceCoordinateAxesY_->show();
			ui.machineCoordinateSymbolY_->show();
			ui.machiningRemainSymbolY_->show();
			ui.workpieceCoordinateSymbolY_->show();
			ui.lineY_->show();
		}
		else if (validAxes.at(i) == ltp::base::Z_AXIS)
		{
			ui.labelAxesZ_->show();
			ui.machineCoordinateAxesZ_->show();
			ui.machiningRemainAxesZ_->show();
			ui.motorLoadAxesZ_->show();
			ui.workpieceCoordinateAxesZ_->show();
			ui.machineCoordinateSymbolZ_->show();
			ui.machiningRemainSymbolZ_->show();
			ui.workpieceCoordinateSymbolZ_->show();
			ui.lineZ_->show();
		}
		else if (validAxes.at(i) == ltp::base::U_AXIS)
		{
			ui.labelAxesU_->show();
			ui.machineCoordinateAxesU_->show();
			ui.machiningRemainAxesU_->show();
			ui.motorLoadAxesU_->show();
			ui.workpieceCoordinateAxesU_->show();
			ui.machineCoordinateSymbolU_->show();
			ui.machiningRemainSymbolU_->show();
			ui.workpieceCoordinateSymbolU_->show();
			ui.lineU_->show();
		}
		else if (validAxes.at(i) == ltp::base::V_AXIS)
		{
			ui.labelAxesV_->show();
			ui.machineCoordinateAxesV_->show();
			ui.machiningRemainAxesV_->show();
			ui.motorLoadAxesV_->show();
			ui.workpieceCoordinateAxesV_->show();
			ui.machineCoordinateSymbolV_->show();
			ui.machiningRemainSymbolV_->show();
			ui.workpieceCoordinateSymbolV_->show();
			ui.lineV_->show();
		}
		else if (validAxes.at(i) == ltp::base::W_AXIS)
		{
			ui.labelAxesW_->show();
			ui.machineCoordinateAxesW_->show();
			ui.machiningRemainAxesW_->show();
			ui.motorLoadAxesW_->show();
			ui.workpieceCoordinateAxesW_->show();
			ui.machineCoordinateSymbolW_->show();
			ui.machiningRemainSymbolW_->show();
			ui.workpieceCoordinateSymbolW_->show();
			ui.lineW_->show();
		}
		else if (validAxes.at(i) == ltp::base::A_AXIS)
		{
			ui.labelAxesA_->show();
			ui.machineCoordinateAxesA_->show();
			ui.machiningRemainAxesA_->show();
			ui.motorLoadAxesA_->show();
			ui.workpieceCoordinateAxesA_->show();
			ui.machineCoordinateSymbolA_->show();
			ui.machiningRemainSymbolA_->show();
			ui.workpieceCoordinateSymbolA_->show();
			ui.lineA_->show();
		}
		else if (validAxes.at(i) == ltp::base::B_AXIS)
		{
			ui.labelAxesB_->show();
			ui.machineCoordinateAxesB_->show();
			ui.machiningRemainAxesB_->show();
			ui.motorLoadAxesB_->show();
			ui.workpieceCoordinateAxesB_->show();
			ui.machineCoordinateSymbolB_->show();
			ui.machiningRemainSymbolB_->show();
			ui.workpieceCoordinateSymbolB_->show();
			ui.lineB_->show();
		}
		else if (validAxes.at(i) == ltp::base::C_AXIS)
		{
			ui.labelAxesC_->show();
			ui.machineCoordinateAxesC_->show();
			ui.machiningRemainAxesC_->show();
			ui.motorLoadAxesC_->show();
			ui.workpieceCoordinateAxesC_->show();
			ui.machineCoordinateSymbolC_->show();
			ui.machiningRemainSymbolC_->show();
			ui.workpieceCoordinateSymbolC_->show();
			ui.lineC_->show();
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
	ui.machineCoordinateAxesX_->setText(QString::number(fabs(machineCoord[0]), 'f', 3));
	ui.workpieceCoordinateAxesX_->setText(QString::number(fabs(workpieceCoord[0]), 'f', 3));
	ui.machiningRemainAxesX_->setText(QString::number(fabs(machiningRemain[0]), 'f', 3));
	ui.machineCoordinateSymbolX_->setText((machineCoord[0] >= 0)? "+":"-");
	ui.machiningRemainSymbolX_->setText((machiningRemain[0] >= 0)? "+":"-");
	ui.workpieceCoordinateSymbolX_->setText((workpieceCoord[0] >= 0)? "+":"-");
	ui.motorLoadAxesX_->setValue(motorLoad[0]);
	// Y轴
	ui.machineCoordinateAxesY_->setText(QString::number(fabs(machineCoord[1]), 'f', 3));
	ui.workpieceCoordinateAxesY_->setText(QString::number(fabs(workpieceCoord[1]), 'f', 3));
	ui.machiningRemainAxesY_->setText(QString::number(fabs(machiningRemain[1]), 'f', 3));
	ui.machineCoordinateSymbolY_->setText((machineCoord[1] >= 0)? "+":"-");
	ui.machiningRemainSymbolY_->setText((machiningRemain[1] >= 0)? "+":"-");
	ui.workpieceCoordinateSymbolY_->setText((workpieceCoord[1] >= 0)? "+":"-");
	ui.motorLoadAxesY_->setValue(motorLoad[1]);
	// Z轴
	ui.machineCoordinateAxesZ_->setText(QString::number(fabs(machineCoord[2]), 'f', 3));
	ui.workpieceCoordinateAxesZ_->setText(QString::number(fabs(workpieceCoord[2]), 'f', 3));
	ui.machiningRemainAxesZ_->setText(QString::number(fabs(machiningRemain[2]), 'f', 3));
	ui.machineCoordinateSymbolZ_->setText((machineCoord[2] >= 0)? "+":"-");
	ui.machiningRemainSymbolZ_->setText((machiningRemain[2] >= 0)? "+":"-");
	ui.workpieceCoordinateSymbolZ_->setText((workpieceCoord[2] >= 0)? "+":"-");
	ui.motorLoadAxesZ_->setValue(motorLoad[2]);
	// A轴
	ui.machineCoordinateAxesA_->setText(QString::number(fabs(machineCoord[3]), 'f', 3));
	ui.workpieceCoordinateAxesA_->setText(QString::number(fabs(workpieceCoord[3]), 'f', 3));
	ui.machiningRemainAxesA_->setText(QString::number(fabs(machiningRemain[3]), 'f', 3));
	ui.machineCoordinateSymbolA_->setText((machineCoord[3] >= 0)? "+":"-");
	ui.machiningRemainSymbolA_->setText((machiningRemain[3] >= 0)? "+":"-");
	ui.workpieceCoordinateSymbolA_->setText((workpieceCoord[3] >= 0)? "+":"-");
	ui.motorLoadAxesA_->setValue(motorLoad[3]);
	// B轴
	ui.machineCoordinateAxesB_->setText(QString::number(fabs(machineCoord[4]), 'f', 3));
	ui.workpieceCoordinateAxesB_->setText(QString::number(fabs(workpieceCoord[4]), 'f', 3));
	ui.machiningRemainAxesB_->setText(QString::number(fabs(machiningRemain[4]), 'f', 3));
	ui.machineCoordinateSymbolB_->setText((machineCoord[4] >= 0)? "+":"-");
	ui.machiningRemainSymbolB_->setText((machiningRemain[4] >= 0)? "+":"-");
	ui.workpieceCoordinateSymbolB_->setText((workpieceCoord[4] >= 0)? "+":"-");
	ui.motorLoadAxesB_->setValue(motorLoad[4]);
	// C轴
	ui.machineCoordinateAxesC_->setText(QString::number(fabs(machineCoord[5]), 'f', 3));
	ui.workpieceCoordinateAxesC_->setText(QString::number(fabs(workpieceCoord[5]), 'f', 3));
	ui.machiningRemainAxesC_->setText(QString::number(fabs(machiningRemain[5]), 'f', 3));
	ui.machineCoordinateSymbolC_->setText((machineCoord[5] >= 0)? "+":"-");
	ui.machiningRemainSymbolC_->setText((machiningRemain[5] >= 0)? "+":"-");
	ui.workpieceCoordinateSymbolC_->setText((workpieceCoord[5] >= 0)? "+":"-");
	ui.motorLoadAxesC_->setValue(motorLoad[5]);
	// U轴
	ui.machineCoordinateAxesU_->setText(QString::number(fabs(machineCoord[6]), 'f', 3));
	ui.workpieceCoordinateAxesU_->setText(QString::number(fabs(workpieceCoord[6]), 'f', 3));
	ui.machiningRemainAxesU_->setText(QString::number(fabs(machiningRemain[6]), 'f', 3));
	ui.machineCoordinateSymbolU_->setText((machineCoord[6] >= 0)? "+":"-");
	ui.machiningRemainSymbolU_->setText((machiningRemain[6] >= 0)? "+":"-");
	ui.workpieceCoordinateSymbolU_->setText((workpieceCoord[6] >= 0)? "+":"-");
	ui.motorLoadAxesU_->setValue(motorLoad[6]);
	// V轴
	ui.machineCoordinateAxesV_->setText(QString::number(fabs(machineCoord[7]), 'f', 3));
	ui.workpieceCoordinateAxesV_->setText(QString::number(fabs(workpieceCoord[7]), 'f', 3));
	ui.machiningRemainAxesV_->setText(QString::number(fabs(machiningRemain[7]), 'f', 3));
	ui.machineCoordinateSymbolV_->setText((machineCoord[7] >= 0)? "+":"-");
	ui.machiningRemainSymbolV_->setText((machiningRemain[7] >= 0)? "+":"-");
	ui.workpieceCoordinateSymbolV_->setText((workpieceCoord[7] >= 0)? "+":"-");
	ui.motorLoadAxesV_->setValue(motorLoad[7]);
	// W轴
	ui.machineCoordinateAxesW_->setText(QString::number(fabs(machineCoord[8]), 'f', 3));
	ui.workpieceCoordinateAxesW_->setText(QString::number(fabs(workpieceCoord[8]), 'f', 3));
	ui.machiningRemainAxesW_->setText(QString::number(fabs(machiningRemain[8]), 'f', 3));
	ui.machineCoordinateSymbolW_->setText((machineCoord[8] >= 0)? "+":"-");
	ui.machiningRemainSymbolW_->setText((machiningRemain[8] >= 0)? "+":"-");
	ui.workpieceCoordinateSymbolW_->setText((workpieceCoord[8] >= 0)? "+":"-");
	ui.motorLoadAxesW_->setValue(motorLoad[8]);

	// 当前坐标系
	QString str = "G" + QString::number(coord);
	ui.currentWorkpieceCoordinate_->setText(str);
}