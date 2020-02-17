#include "panelbutton.h"

#include <QVBoxLayout>

using ltp::base::PanelButton;

PanelButton::PanelButton(QWidget *parent)
	: QPushButton(parent)
{
    picture_ = new QLabel();			// 按钮上图片
    picture_->setStyleSheet(QString("background:transparent;"));
	picture_->setPixmap(QPixmap("C:/Users/huaguolin/Desktop/skip.png"));
	picture_->setAlignment(Qt::AlignHCenter);

	text_ = new QLabel();				// 按钮上文字
    text_->setStyleSheet(QString("font:12px SIMHEI;background:transparent;"));
    text_->setText("跳过");
	text_->setAlignment(Qt::AlignHCenter);

    QVBoxLayout* myLayout = new QVBoxLayout();		// 按钮内嵌布局
    myLayout->addWidget(picture_);
    myLayout->addWidget(text_);
    myLayout->addStretch(0);
    myLayout->setMargin(3);
    myLayout->setSpacing(3);
    this->setLayout(myLayout);
	this->setStyleSheet("QPushButton{background:#F0F0F0; font:12px SIMHEI;width:52px;height:46px;}");
}

PanelButton::~PanelButton()
{
}


void PanelButton::setButtonPicture(const QPixmap &pixmap)
{
    picture_->setPixmap(pixmap);		// 设置按钮图片
}
 
void PanelButton::setButtonText(const QString &text)
{
    text_->setText(text);				// 设置按钮文字
}