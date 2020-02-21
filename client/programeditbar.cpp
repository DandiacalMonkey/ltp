#include "programeditbar.h"

using ltp::client::ProgramEditBar;

ProgramEditBar::ProgramEditBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 初始隐藏全部坐标信息
	ui.axesLabelA_->hide();
	ui.workpieceCoordinateAxesA_->hide();
	ui.axesLabelB_->hide();
	ui.workpieceCoordinateAxesB_->hide();
	ui.axesLabelC_->hide();
	ui.workpieceCoordinateAxesC_->hide();
	ui.axesLabelX_->hide();
	ui.workpieceCoordinateAxesX_->hide();
	ui.axesLabelY_->hide();
	ui.workpieceCoordinateAxesY_->hide();
	ui.axesLabelZ_->hide();
	ui.workpieceCoordinateAxesZ_->hide();
	ui.axesLabelU_->hide();
	ui.workpieceCoordinateAxesU_->hide();
	ui.axesLabelV_->hide();
	ui.workpieceCoordinateAxesV_->hide();
	ui.axesLabelW_->hide();
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

	// 删除行
	connect(ui.removeLineButton_, SIGNAL(clicked()), ui.textEdit_, SLOT(removeLine()));
	// 复制
	connect(ui.copyButton_, SIGNAL(clicked()), ui.textEdit_, SLOT(copyText()));
	// 粘贴
	connect(ui.pasteButton_, SIGNAL(clicked()), ui.textEdit_, SLOT(pasteText()));
	// 剪切
	connect(ui.cutButton_, SIGNAL(clicked()), ui.textEdit_, SLOT(cutText()));
	// 撤销
	connect(ui.recoverButton_, SIGNAL(clicked()), ui.textEdit_, SLOT(recoverText()));
	// 恢复
	connect(ui.repealButton_, SIGNAL(clicked()), ui.textEdit_, SLOT(repealText()));
}

ProgramEditBar::~ProgramEditBar()
{

}

void ProgramEditBar::setValidAxes(const std::vector<ltp::base::Axis> &validAxes)
{
	for (int i = 0; i < validAxes.size(); ++i)			// 对系统轴信息进行显示
	{
		if (validAxes.at(i) == ltp::base::X_AXIS)
		{
			ui.axesLabelX_->show();
			ui.workpieceCoordinateAxesX_->show();
		}
		else if (validAxes.at(i) == ltp::base::Y_AXIS)
		{
			ui.axesLabelY_->show();
			ui.workpieceCoordinateAxesY_->show();
		}
		else if (validAxes.at(i) == ltp::base::Z_AXIS)
		{
			ui.axesLabelZ_->show();
			ui.workpieceCoordinateAxesZ_->show();
		}
		else if (validAxes.at(i) == ltp::base::U_AXIS)
		{
			ui.axesLabelU_->show();
			ui.workpieceCoordinateAxesU_->show();
		}
		else if (validAxes.at(i) == ltp::base::V_AXIS)
		{
			ui.axesLabelV_->show();
			ui.workpieceCoordinateAxesV_->show();
		}
		else if (validAxes.at(i) == ltp::base::W_AXIS)
		{
			ui.axesLabelW_->show();
			ui.workpieceCoordinateAxesW_->show();
		}
		else if (validAxes.at(i) == ltp::base::A_AXIS)
		{
			ui.axesLabelA_->show();
			ui.workpieceCoordinateAxesA_->show();
		}
		else if (validAxes.at(i) == ltp::base::B_AXIS)
		{
			ui.axesLabelB_->show();
			ui.workpieceCoordinateAxesB_->show();
		}
		else if (validAxes.at(i) == ltp::base::C_AXIS)
		{
			ui.axesLabelC_->show();
			ui.workpieceCoordinateAxesC_->show();
		}
	}
}