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

	// 初始化储存控件指针的变量
	axisInformationArray_[base::X_AXIS].axisName_ = ui.axesLabelX_;
	axisInformationArray_[base::X_AXIS].workpieceCoordinateSymbol_ = ui.workpieceCoordinateSymbolX_;
	axisInformationArray_[base::X_AXIS].workpieceCoordinateValue_ = ui.workpieceCoordinateAxesX_;
	axisInformationArray_[base::X_AXIS].previousPositionSymbol_ = ui.previousPositionSymbolX_;
	axisInformationArray_[base::X_AXIS].previousPositionValue_ = ui.previousPositionValueX_;
	axisInformationArray_[base::Y_AXIS].axisName_ = ui.axesLabelY_;
	axisInformationArray_[base::Y_AXIS].workpieceCoordinateSymbol_ = ui.workpieceCoordinateSymbolY_;
	axisInformationArray_[base::Y_AXIS].workpieceCoordinateValue_ = ui.workpieceCoordinateAxesY_;
	axisInformationArray_[base::Y_AXIS].previousPositionSymbol_ = ui.previousPositionSymbolY_;
	axisInformationArray_[base::Y_AXIS].previousPositionValue_ = ui.previousPositionValueY_;
	axisInformationArray_[base::Z_AXIS].axisName_ = ui.axesLabelZ_;
	axisInformationArray_[base::Z_AXIS].workpieceCoordinateSymbol_ = ui.workpieceCoordinateSymbolZ_;
	axisInformationArray_[base::Z_AXIS].workpieceCoordinateValue_ = ui.workpieceCoordinateAxesZ_;
	axisInformationArray_[base::Z_AXIS].previousPositionSymbol_ = ui.previousPositionSymbolZ_;
	axisInformationArray_[base::Z_AXIS].previousPositionValue_ = ui.previousPositionValueZ_;
	axisInformationArray_[base::A_AXIS].axisName_ = ui.axesLabelA_;
	axisInformationArray_[base::A_AXIS].workpieceCoordinateSymbol_ = ui.workpieceCoordinateSymbolA_;
	axisInformationArray_[base::A_AXIS].workpieceCoordinateValue_ = ui.workpieceCoordinateAxesA_;
	axisInformationArray_[base::A_AXIS].previousPositionSymbol_ = ui.previousPositionSymbolA_;
	axisInformationArray_[base::A_AXIS].previousPositionValue_ = ui.previousPositionValueA_;
	axisInformationArray_[base::B_AXIS].axisName_ = ui.axesLabelB_;
	axisInformationArray_[base::B_AXIS].workpieceCoordinateSymbol_ = ui.workpieceCoordinateSymbolB_;
	axisInformationArray_[base::B_AXIS].workpieceCoordinateValue_ = ui.workpieceCoordinateAxesB_;
	axisInformationArray_[base::B_AXIS].previousPositionSymbol_ = ui.previousPositionSymbolB_;
	axisInformationArray_[base::B_AXIS].previousPositionValue_ = ui.previousPositionValueB_;
	axisInformationArray_[base::C_AXIS].axisName_ = ui.axesLabelC_;
	axisInformationArray_[base::C_AXIS].workpieceCoordinateSymbol_ = ui.workpieceCoordinateSymbolC_;
	axisInformationArray_[base::C_AXIS].workpieceCoordinateValue_ = ui.workpieceCoordinateAxesC_;
	axisInformationArray_[base::C_AXIS].previousPositionSymbol_ = ui.previousPositionSymbolC_;
	axisInformationArray_[base::C_AXIS].previousPositionValue_ = ui.previousPositionValueC_;
	axisInformationArray_[base::U_AXIS].axisName_ = ui.axesLabelU_;
	axisInformationArray_[base::U_AXIS].workpieceCoordinateSymbol_ = ui.workpieceCoordinateSymbolU_;
	axisInformationArray_[base::U_AXIS].workpieceCoordinateValue_ = ui.workpieceCoordinateAxesU_;
	axisInformationArray_[base::U_AXIS].previousPositionSymbol_ = ui.previousPositionSymbolU_;
	axisInformationArray_[base::U_AXIS].previousPositionValue_ = ui.previousPositionValueU_;
	axisInformationArray_[base::V_AXIS].axisName_ = ui.axesLabelV_;
	axisInformationArray_[base::V_AXIS].workpieceCoordinateSymbol_ = ui.workpieceCoordinateSymbolV_;
	axisInformationArray_[base::V_AXIS].workpieceCoordinateValue_ = ui.workpieceCoordinateAxesV_;
	axisInformationArray_[base::V_AXIS].previousPositionSymbol_ = ui.previousPositionSymbolV_;
	axisInformationArray_[base::V_AXIS].previousPositionValue_ = ui.previousPositionValueV_;
	axisInformationArray_[base::W_AXIS].axisName_ = ui.axesLabelW_;
	axisInformationArray_[base::W_AXIS].workpieceCoordinateSymbol_ = ui.workpieceCoordinateSymbolW_;
	axisInformationArray_[base::W_AXIS].workpieceCoordinateValue_ = ui.workpieceCoordinateAxesW_;
	axisInformationArray_[base::W_AXIS].previousPositionSymbol_ = ui.previousPositionSymbolW_;
	axisInformationArray_[base::W_AXIS].previousPositionValue_ = ui.previousPositionValueW_;

	// 初始隐藏全部坐标信息
	hideAxisInformation();

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
	connect(ui.textEdit_, SIGNAL(signalTips(QString)), SLOT(onHint(QString)));
	// 文件已经保存
	connect(ui.textEdit_, SIGNAL(signalSaved(QString)), SIGNAL(signalSaved(QString)));

	// 定时器每0.2s更新一次数据
	connect(&timer_, SIGNAL(timeout()), this, SLOT(onTimer()));
	timer_.setInterval(200);
}

ProgramEditWidget::~ProgramEditWidget()
{

}

void ProgramEditWidget::onTimer()
{
	// 示教坐标
	auto workpieceCoord = base::getInstance<base::SystemVariables<RemoteVariables>>().teachPosition(1);
	// 上一点坐标
	auto previousPoint = teachCommand_->previousPointPosition();
	for (size_t i = 0; i < axisInformationArray_.size(); i++)
	{
		axisInformationArray_[i].workpieceCoordinateSymbol_->setText((workpieceCoord[i] >= 0) ? "+" : "-");
		axisInformationArray_[i].workpieceCoordinateValue_->setText(QString::number(fabs(workpieceCoord[i]), 'f', 3));
		axisInformationArray_[i].previousPositionSymbol_->setText((previousPoint[i] >= 0) ? "+" : "-");
		axisInformationArray_[i].previousPositionValue_->setText(QString::number(fabs(previousPoint[i]), 'f', 3));
	}
	// 示教模式
	auto teachMode = base::getInstance<base::SystemVariables<RemoteVariables>>().macroVariable(base::TEACH_MODE);
	if (teachMode == 0)
	{
		ui.workpieceCoordinateLabel_->setText(tr("工件坐标"));
	}
	else
	{
		ui.workpieceCoordinateLabel_->setText(tr("刀尖坐标"));
	}
	// 当前坐标系
	double coord = base::getInstance<base::SystemVariables<RemoteVariables>>().macroVariable(base::COORDINATE);
	QString str = "G" + QString::number(coord);
	ui.currentWorkpieceCoordinate_->setText(str);
}

void ltp::client::ProgramEditWidget::checkPoint()
{
	try
	{
		//记录点
		if (teachCommand_->checkPoint())
		{
			//定位到行首
			ui.textEdit_->gotoLineBegin();
			ui.textEdit_->insertPlainText(teachCommand_->getCommand() + '\n');
			teachCommand_->reset();
		}
		updateTeachInformation();
	}
	catch (TeachCommand::TeachCommandException& exception)
	{
		base::getInstance<HintWidgetProxy<HintBar>>().setHint(exception.hint());
	}
}

void ltp::client::ProgramEditWidget::previousPoint()
{
	teachCommand_->previousPoint();
	updateTeachInformation();
}

void ltp::client::ProgramEditWidget::cancelTeach()
{
	teachCommand_->reset();
	updateTeachInformation();
}

void ProgramEditWidget::onHint(QString str)
{
	base::getInstance<HintWidgetProxy<HintBar>>().setHint(str);
}

void ProgramEditWidget::setValidAxes(const std::vector<ltp::base::Axis> &validAxes)
{
	// 有效轴变化时，先隐藏
	hideAxisInformation();
	// 对系统轴信息进行显示
	for (size_t i = 0; i < validAxes.size(); ++i)
	{
		axisInformationArray_[validAxes[i]].axisName_->show();
		axisInformationArray_[validAxes[i]].workpieceCoordinateSymbol_->show();
		axisInformationArray_[validAxes[i]].workpieceCoordinateValue_->show();
		axisInformationArray_[validAxes[i]].previousPositionSymbol_->show();
		axisInformationArray_[validAxes[i]].previousPositionValue_->show();
	}
}

void ProgramEditWidget::onProgrameEdit()
{
	// 程序编程
	ui.sideBarWidget_->hide();
	ui.buttonWidget_->show();
	ui.expandWidget_->show();
	// 关闭坐标刷新
	timer_.stop();
}

void ProgramEditWidget::onTeachEdit()
{
	// 示教编程
	ui.sideBarWidget_->show();
	ui.buttonWidget_->hide();
	ui.expandWidget_->hide();
	// 启动坐标刷新
	QTimer::singleShot(0, &timer_, SIGNAL(timeout()));
	timer_.start();
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
		onProgrameEdit();	// 模块选择，但右侧显示程序编程
		break;
	case base::LEFTBUTTON3:
		onEditTeach();		// 编辑示教
		break;
	default:
		break;
	}
}

void ltp::client::ProgramEditWidget::setRemoteFilePath(const QString& filePath)
{
	//区分如果第一个字符不是/，表示传过来的只有文件名，需要加个/
	QString tempPath;
	tempPath = tr("控制器") + ":/" + tr("用户盘");
	if (filePath.at(0) != '/')
	{
		tempPath += "/";
	}
	ui.programTitleLabel_->setText(tempPath + filePath);
}

bool ProgramEditWidget::onOpenFile(QString fileName)
{
	// 打开文件
	auto result = ui.textEdit_->openFile(fileName);
	if (result == true)
	{
		//文件打开信号
		emit signalFileOpened();
	}
	return result;
}

bool ltp::client::ProgramEditWidget::saveFile()
{
	return ui.textEdit_->save();
}

bool ProgramEditWidget::closeFile()
{
	//关闭文件
	auto result = ui.textEdit_->closeFile();
	if (result == true)
	{
		//文件名更新
		ui.programTitleLabel_->clear();
		//文件关闭信号
		emit signalFileClosed();
	}
	return result;	
}

void ProgramEditWidget::onTeachEditModule(std::shared_ptr<ltp::client::TeachCommand> teachCommand)
{
	onTeachEdit();
	teachCommand_ = teachCommand;
	ui.teachTitle_->setText(teachCommand_->teachTitle());
	updateTeachInformation();
}

void ProgramEditWidget::modeChange()
{
	try
	{
		teachCommand_->changeMode();
	}
	catch (TeachCommand::TeachCommandException& exception)
	{
		base::getInstance<HintWidgetProxy<HintBar>>().setHint(exception.hint());
	}
}

void ProgramEditWidget::updateTeachInformation()
{
	//操作提示
	onHint(teachCommand_->hint());
	//获取示意图并缩放
	QPixmap pixmap = QPixmap(teachCommand_->schematicDiagramsPath());
	pixmap = pixmap.scaled(ui.teachSchematicDiagram_->width(), ui.teachSchematicDiagram_->height(),
		Qt::KeepAspectRatio, Qt::SmoothTransformation);
	//示意图更新
	ui.teachSchematicDiagram_->setPixmap(pixmap);
	//上一点的标签更新
	ui.previousPositionLabel_->setText(teachCommand_->previousPointLabel());
	//最后一点，需要将按钮改为确定
	emit signalTeachIsLastPoint(teachCommand_->isLastPoint());
	//能否退回上一点
	emit signalTeachPreviousEnabled(teachCommand_->hasPreviousPoint());
}

void ProgramEditWidget::hideAxisInformation()
{
	for (auto iterator = axisInformationArray_.begin(); iterator != axisInformationArray_.end(); iterator++)
	{
		iterator->axisName_->hide();
		iterator->workpieceCoordinateSymbol_->hide();
		iterator->workpieceCoordinateValue_->hide();
		iterator->previousPositionSymbol_->hide();
		iterator->previousPositionValue_->hide();
	}
}

