#include "physicalbuttonsprocessor.h"

PhysicalButtonsProcessor::PhysicalButtonsProcessor(QObject *parent)
	: QObject(parent)
{

}

PhysicalButtonsProcessor::~PhysicalButtonsProcessor()
{

}

bool PhysicalButtonsProcessor::isPhysicalButtonsProcessor(QKeyEvent* event) const
{
	if (event->modifiers() == Qt::ControlModifier && 
		keyValueSignalMap_.find(event->key()) != keyValueSignalMap_.end())
	{
		return true;
	}
	return false;
}
