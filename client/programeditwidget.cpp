#include "programeditwidget.h"
#include "hintwidgetproxy.h"
#include "hintbar.h"
#include "machiningstates.h"
#include "base/systemvariables.hpp"
#include "remotevariables.hpp"
#include "base/globals.h"

using ltp::client::ProgramEditWidget;

ProgramEditWidget::ProgramEditWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	onEditBarModule(base::LEFTBUTTON1);

	// 初始隐藏全部坐标信息
	ui.axesLabelA_->hide();
	ui.workpieceCoordinateAxesA_->hide();
	ui.workpieceCoordinateSymbolA_->hide();
	ui.axesLabelB_->hide();
	ui.workpieceCoordinateAxesB_->hide();
	ui.workpieceCoordinateSymbolB_->hide();
	ui.axesLabelC_->hide();
	ui.workpieceCoordinateAxesC_->hide();
	ui.workpieceCoordinateSymbolC_->hide();
	ui.axesLabelX_->hide();
	ui.workpieceCoordinateAxesX_->hide();
	ui.workpieceCoordinateSymbolX_->hide();
	ui.axesLabelY_->hide();
	ui.workpieceCoordinateAxesY_->hide();
	ui.workpieceCoordinateSymbolY_->hide();
	ui.axesLabelZ_->hide();
	ui.workpieceCoordinateAxesZ_->hide();
	ui.workpieceCoordinateSymbolZ_->hide();
	ui.axesLabelU_->hide();
	ui.workpieceCoordinateAxesU_->hide();
	ui.workpieceCoordinateSymbolU_->hide();
	ui.axesLabelV_->hide();
	ui.workpieceCoordinateAxesV_->hide();
	ui.workpieceCoordinateSymbolV_->hide();
	ui.axesLabelW_->hide();
	ui.workpieceCoordinateAxesW_->hide();
	ui.workpieceCoordinateSymbolW_->hide();

	// 根据连接控制器判断需要显示的轴信息
	connect(&base::getInstance<MachiningStates>(), SIGNAL(validAxesChanged(std::vector<base::Axis>)), this, SLOT(setValidAxes(std::vector<base::Axis>)));

	// 未实现的行查找，查找替换先disable
	ui.findAndReplaceButton_->setEnabled(false);
	ui.fineLineButton_->setEnabled(false);

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
	connect(ui.textEdit_, SIGNAL(signalTips(QString)), this, SLOT(onHint(QString)));
	// 文件已经保存
	connect(ui.textEdit_, SIGNAL(signalSaved(QString)), this, SIGNAL(signalSaved(QString)));

	// 定时器每0.5s更新一次数据
	QTimer *timer_ = new QTimer();
	connect(timer_, SIGNAL(timeout()), this, SLOT(onTimer()));
	timer_->start(500);
}

ProgramEditWidget::~ProgramEditWidget()
{

}

void ProgramEditWidget::onTimer()
{
	// 工件坐标
	auto workpieceCoord = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().workpieceCoordinates(1);
	// 当前坐标系
	double coord = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().macroVariable(ltp::base::COORDINATE);

	// X轴
	ui.workpieceCoordinateAxesX_->setText(QString::number(fabs(workpieceCoord[0]), 'f', 3));
	ui.workpieceCoordinateSymbolX_->setText((workpieceCoord[0] >= 0)? "+":"-");
	// Y轴
	ui.workpieceCoordinateAxesY_->setText(QString::number(fabs(workpieceCoord[1]), 'f', 3));
	ui.workpieceCoordinateSymbolY_->setText((workpieceCoord[1] >= 0)? "+":"-");
	// Z轴
	ui.workpieceCoordinateAxesZ_->setText(QString::number(fabs(workpieceCoord[2]), 'f', 3));
	ui.workpieceCoordinateSymbolZ_->setText((workpieceCoord[2] >= 0)? "+":"-");
	// A轴
	ui.workpieceCoordinateAxesA_->setText(QString::number(fabs(workpieceCoord[3]), 'f', 3));
	ui.workpieceCoordinateSymbolA_->setText((workpieceCoord[3] >= 0)? "+":"-");
	// B轴
	ui.workpieceCoordinateAxesB_->setText(QString::number(fabs(workpieceCoord[4]), 'f', 3));
	ui.workpieceCoordinateSymbolB_->setText((workpieceCoord[4] >= 0)? "+":"-");
	// C轴
	ui.workpieceCoordinateAxesC_->setText(QString::number(fabs(workpieceCoord[5]), 'f', 3));
	ui.workpieceCoordinateSymbolC_->setText((workpieceCoord[5] >= 0)? "+":"-");
	// U轴
	ui.workpieceCoordinateAxesU_->setText(QString::number(fabs(workpieceCoord[6]), 'f', 3));
	ui.workpieceCoordinateSymbolU_->setText((workpieceCoord[6] >= 0)? "+":"-");
	// V轴
	ui.workpieceCoordinateAxesV_->setText(QString::number(fabs(workpieceCoord[7]), 'f', 3));
	ui.workpieceCoordinateSymbolV_->setText((workpieceCoord[7] >= 0)? "+":"-");
	// W轴
	ui.workpieceCoordinateAxesW_->setText(QString::number(fabs(workpieceCoord[8]), 'f', 3));
	ui.workpieceCoordinateSymbolW_->setText((workpieceCoord[8] >= 0)? "+":"-");

	// 当前坐标系
	QString str = "G" + QString::number(coord);
	ui.currentWorkpieceCoordinate_->setText(str);
}

void ProgramEditWidget::onHint(QString str)
{
	base::getInstance<HintWidgetProxy<HintBar>>().setHint(str);
}

void ProgramEditWidget::setValidAxes(const std::vector<ltp::base::Axis> &validAxes)
{
	for (int i = 0; i < validAxes.size(); ++i)			// 对系统轴信息进行显示
	{
		if (validAxes.at(i) == ltp::base::X_AXIS)
		{
			ui.axesLabelX_->show();
			ui.workpieceCoordinateAxesX_->show();
			ui.workpieceCoordinateSymbolX_->show();
		}
		else if (validAxes.at(i) == ltp::base::Y_AXIS)
		{
			ui.axesLabelY_->show();
			ui.workpieceCoordinateAxesY_->show();
			ui.workpieceCoordinateSymbolY_->show();
		}
		else if (validAxes.at(i) == ltp::base::Z_AXIS)
		{
			ui.axesLabelZ_->show();
			ui.workpieceCoordinateAxesZ_->show();
			ui.workpieceCoordinateSymbolZ_->show();
		}
		else if (validAxes.at(i) == ltp::base::U_AXIS)
		{
			ui.axesLabelU_->show();
			ui.workpieceCoordinateAxesU_->show();
			ui.workpieceCoordinateSymbolU_->show();
		}
		else if (validAxes.at(i) == ltp::base::V_AXIS)
		{
			ui.axesLabelV_->show();
			ui.workpieceCoordinateAxesV_->show();
			ui.workpieceCoordinateSymbolV_->show();
		}
		else if (validAxes.at(i) == ltp::base::W_AXIS)
		{
			ui.axesLabelW_->show();
			ui.workpieceCoordinateAxesW_->show();
			ui.workpieceCoordinateSymbolW_->show();
		}
		else if (validAxes.at(i) == ltp::base::A_AXIS)
		{
			ui.axesLabelA_->show();
			ui.workpieceCoordinateAxesA_->show();
			ui.workpieceCoordinateSymbolA_->show();
		}
		else if (validAxes.at(i) == ltp::base::B_AXIS)
		{
			ui.axesLabelB_->show();
			ui.workpieceCoordinateAxesB_->show();
			ui.workpieceCoordinateSymbolB_->show();
		}
		else if (validAxes.at(i) == ltp::base::C_AXIS)
		{
			ui.axesLabelC_->show();
			ui.workpieceCoordinateAxesC_->show();
			ui.workpieceCoordinateSymbolC_->show();
		}
	}
}

void ProgramEditWidget::onProgrameEdit()
{
	// 程序编程
	ui.sideBarWidget_->hide();
	ui.buttonWidget_->show();
}

void ProgramEditWidget::onTeachEdit()
{
	// 示教编程
	ui.sideBarWidget_->show();
	ui.buttonWidget_->hide();
}

void ProgramEditWidget::onEditTeach()
{
	// 编辑示教
}

void ProgramEditWidget::onEditBarModule(int nModule)
{
	switch(nModule)
	{
	case base::LEFTBUTTON1:
		onProgrameEdit();	// 程序编程
		break;
	case base::LEFTBUTTON2:
		onTeachEdit();		// 示教编程
		onTeachEditModule(base::LEFTBUTTON1);
		break;
	case base::LEFTBUTTON3:
		onEditTeach();		// 编辑示教
		break;
	default:
		break;
	}
}

void ProgramEditWidget::onOpenFile(QString fileName)
{
	// 打开文件
	ui.textEdit_->openFile(fileName);
	// 更新当前打开文件名
	updateFileName();
}

void ProgramEditWidget::closeFile()
{
	ui.textEdit_->closeFile();
	// 更新当前打开文件名
	updateFileName();
}

void ProgramEditWidget::updateFileName()
{
	// 更新当前打开文件名
	QString currentFileName = ui.textEdit_->getCurrentFileName();
	QString str = QString(tr("本地存储器：")) + currentFileName;
	ui.programTitleLabel_->setText(str);
}

void ProgramEditWidget::onTeachEditModule(int editModule)
{
	switch (editModule)
	{
	case base::LEFTBUTTON1:						// G114
		ui.teachTitle_->setText(QString("G114"));
		//ui.teachSchematicDiagram_->
		break;
	case base::LEFTBUTTON2:						// G00
		ui.teachTitle_->setText(QString("G00"));
		//ui.teachSchematicDiagram_->setPixmap(QPixmap((":/LtpClient/image/skip_rest.png")));
		break;
	case base::LEFTBUTTON3:						// G01
		ui.teachTitle_->setText(QString("G01"));
		break;
	case base::LEFTBUTTON4:						// G02
		ui.teachTitle_->setText(QString("G02"));
		break;
	case base::LEFTBUTTON5:						// G102
		ui.teachTitle_->setText(QString("G102"));
		break;
	default:
		break;
	}
}