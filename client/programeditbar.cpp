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
	// 保存
	connect(ui.saveButton_, SIGNAL(clicked()), ui.textEdit_, SLOT(save()));
	// 提示信息
	connect(ui.textEdit_, SIGNAL(signalTips(QString)), this, SIGNAL(signalTips(QString)));

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

void ProgramEditBar::onProgrameEdit()
{
	// 程序编程
	ui.sideBarWidget_->hide();
	ui.buttonWidget_->show();
}

void ProgramEditBar::onTeachEdit()
{
	// 示教编程
	ui.sideBarWidget_->show();
	ui.buttonWidget_->hide();
}

void ProgramEditBar::onEditTeach()
{
	// 编辑示教
}

void ProgramEditBar::onEditBarModule(int nModule)
{
	switch(nModule)
	{
	case 0:
		onProgrameEdit();	// 程序编程
		break;
	case 1:
		onTeachEdit();		// 示教编程
		break;
	case 2:
		onEditTeach();		// 编辑示教
		break;
	default:
		break;
	}
}

void ProgramEditBar::onOpenFile(QString fileName)
{
	// 打开文件
	ui.textEdit_->openFile(fileName);
	// 更新当前打开文件名
	updateFileName();
}

void ProgramEditBar::closeFile()
{
	ui.textEdit_->closeFile();
	// 更新当前打开文件名
	updateFileName();
}

void ProgramEditBar::updateFileName()
{
	// 更新当前打开文件名
	QString currentFileName = ui.textEdit_->getCurrentFileName();
	QString str = QString(tr("本地存储器：")) + currentFileName;
	ui.programTitleLabel_->setText(str);
}

void ProgramEditBar::onTeachEditModule(int editModule)
{
	switch (editModule)
	{
	case 0:						// G114
		ui.teachTitle_->setText(QString("G114"));
		//ui.teachSchematicDiagram_->
		break;
	case 1:						// G00
		ui.teachTitle_->setText(QString("G00"));
		//ui.teachSchematicDiagram_->setPixmap(QPixmap((":/LtpClient/image/skip_rest.png")));
		break;
	case 2:						// G01
		ui.teachTitle_->setText(QString("G01"));
		break;
	case 3:						// G02
		ui.teachTitle_->setText(QString("G02"));
		break;
	case 4:						// G102
		ui.teachTitle_->setText(QString("G102"));
		break;
	default:
		break;
	}
}