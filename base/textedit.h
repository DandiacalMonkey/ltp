#ifndef LTP_BASE_TEXTEDIT_H_
#define LTP_BASE_TEXTEDIT_H_

#include <QtGui/QWidget>
#include "ui_textedit.h"

namespace ltp
{
	namespace base
	{
		class TextEdit : public QWidget
		{
			Q_OBJECT
		 
		public:
			TextEdit(QWidget *parent = 0);
			~TextEdit();  
			QString getCurrentFileName();			// 获取当前打开文件名
			void checkModified();					// 检查文件是否修改 

		private:
			bool loadFile(const QString& fileName);	// 加载文件

		private:
			Ui::TextEditClass ui;
			QString curFileName_;					// 当前文件名
			int lineTotalNum_;						// 打开文件的总行数

		private slots:
			void onCurrentLineHighLight();			// 当前行高亮
			void cursorChanged();					// 行号信息修改
			void focusLine(int lineNum);

		public slots:
			bool save();
			void saveAs(const QString& fileName);
			void removeLine();						// 删除行
			void copyText();						// 拷贝
			void pasteText();						// 复制
			void cutText();							// 剪切 
			void recoverText();						// 撤销
			void repealText();						// 恢复
			void openFile(const QString& fileName);	// 打开文件
			void closeFile();						// 关闭文件

		signals:
			void signalTips(QString);
			void signalSaved(QString);
		};
	}
}


#endif // LTP_BASE_TEXTEDIT_H_