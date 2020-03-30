#ifndef LTP_CLIENT_MAINCONTAINER_H_
#define LTP_CLIENT_MAINCONTAINER_H_

#include <QtGui/QWidget>
#include "ui_maincontainer.h"

namespace ltp
{
	namespace client
	{
		// 左侧按钮界面
		enum ModuleWidget
		{
			HOME_BUTTONS_WIDGET,			// 主界面
			PROCESS_BUTTONS_WIDGET,			// 加工界面
			FILEMANAGER_BUTTONS_WIDGET,		// 文件管理界面
			PROGRAMEDIT_BUTTONS_WIDGET,		// 程序编辑界面
			TEACHEDIT_BUTTONS_WIDGET,		// 示教编辑界面
			SET_BUTTONS_WIDGET				// 设置界面
		};

		class MainContainer : public QWidget
		{
			Q_OBJECT

		public:
			MainContainer(QWidget* parent = 0);
			~MainContainer();

		public slots:
			void openEditFile(const QString& localFilePath, const QString& remoteFtpFilePath);			// 打开编辑文件
			void openProcessFile(const QString& remoteFtpFilePath);

		private:
			Ui::MainContainerClass ui;
			QWidget* lastModuleButtonsWidget_;				// 储存上一次模块菜单，用于返回
			void initModuleButtonsWidget();					// 初始化左侧按钮模块信息

		signals:
			void signalChangeModules(QString);				// 切换模块，菜单栏信息修改

		private slots:
			void onModule(int);								// 切换主菜单模块
			void onHome();									// 返回主页
			void selectedFile();							// 选中文件
			void selectedFolder();							// 选中文件夹
			void selectedNone();							// 没有选中内容
			void onFileWidgetModule(int);					// 切换文件管理模块
			void onProgrameEditWidgetModule(int);			// 切换编辑模块
			void onProcessWidgetModule(int);				// 切换加工模块
			void onProgramTeachEditModule1(int);			// 切换示教编辑模块1
			void onProgramTeachEditModule2(int);			// 切换示教编辑模块2
			void backProgrameModule();						// 切回编辑模块
			void teachEditOperation(int);					// 示教编辑界面操作
			void backTeachModule();							// 切回示教编程模块选择
			void returnButtonClicked();						// 外设返回按键响应
			void leftButtonClicked(int);					// 左侧外设按钮响应
			void teachIsLastPoint(bool);					// 示教操作界面当前记录点是否为最后一点
			void teachPreviousEnabled(bool);				// 示教操作界面前一点按钮是否有效
		};
	}
}

#endif // LTP_CLIENT_MAINCONTAINER_H_