﻿#ifndef LTP_BASE_LOADBAR_H_
#define LTP_BASE_LOADBAR_H_

#include <QtGui/QProgressBar>

namespace ltp
{
	namespace base
	{
		class LoadBar : public QProgressBar
		{
			Q_OBJECT
		 
		public:
			LoadBar(QWidget *parent = 0);
			~LoadBar(); 

		private slots:
			void colorChanged(int);
		};
	}
}


#endif // LTP_BASE_LOADBAR_H_