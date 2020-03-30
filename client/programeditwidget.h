#ifndef LTP_CLIENT_PROGRAMEDITWIDGET_H_
#define LTP_CLIENT_PROGRAMEDITWIDGET_H_

#include <memory>
#include <array>
#include <QtGui/QWidget>
#include <QTimer>
#include "base/globals.h"
#include "ui_programeditwidget.h"
#include "teachcommand.h"

namespace ltp
{
	namespace client
	{
		class TeachCommand;

		class ProgramEditWidget : public QWidget
		{
			Q_OBJECT
		 
		public:
			//用于储存轴坐标显示的控件指针，便于统一操作
			struct AxisInformation
			{
				QLabel* axisName_;
				QLabel* workpieceCoordinateSymbol_;
				QLabel* workpieceCoordinateValue_;
				QLabel* previousPositionSymbol_;
				QLabel* previousPositionValue_;
			};
			ProgramEditWidget(QWidget *parent = 0);
			~ProgramEditWidget();
			void onEditBarModule(int);			// 切换编辑内部模块
			void closeFile();					// 关闭文件
			QString getCurrentFileName(){return ui.textEdit_->getCurrentFileName();}	// 获取当前文件名
			void checkCurrentFileModified(){ui.textEdit_->checkModified();}				// 检查文件是否修改
			void setRemoteFilePath(const QString& filePath);							// 设定显示的文件名

		public slots:
			void onOpenFile(QString fileName);											// 打开文件
			void saveFile();															// 保存文件
			void onTeachEditModule(std::shared_ptr<TeachCommand> teachCommand);			// 切换示教编辑模块
			void modeChange();															// 切换刀尖坐标和工件坐标
			void checkPoint();															// 记录点，确定
			void previousPoint();														// 前一点
			void cancelTeach();															// 取消示教

		signals:
			void signalSaved(QString);
			void signalTeachIsLastPoint(bool);
			void signalTeachPreviousEnabled(bool);

		private:
			Ui::ProgramEditWidgetClass ui;
			QTimer timer_;
			std::shared_ptr<TeachCommand> teachCommand_;
			std::array<AxisInformation, base::AXIS_COUNT> axisInformationArray_;
			void onProgrameEdit();			// 程序编辑
			void onTeachEdit();				// 示教编辑
			void onEditTeach();				// 编辑示教
			void updateTeachInformation();	// 示教操作后，需要更新显示图片等内容
			void hideAxisInformation();		// 隐藏所有轴信息

		private slots:
			void setValidAxes(const std::vector<base::Axis> &validAxes);
			void onHint(QString);
			void onTimer();
			void fileClosed();

		};
	}
}
#endif // LTP_CLIENT_PROGRAMEDITBAR_H_