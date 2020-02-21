#include "axesinformation.h"

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
	setValidAxes(tempAxis);
	ui.gridLayout->update();
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