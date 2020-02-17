#include "operationpanel.h"

using ltp::client::OperationPanel;

OperationPanel::OperationPanel(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

OperationPanel::~OperationPanel()
{
}
