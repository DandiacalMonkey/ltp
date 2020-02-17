#include "textedit.h"

using ltp::base::TextEdit;

TextEdit::TextEdit(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

TextEdit::~TextEdit()
{
}
