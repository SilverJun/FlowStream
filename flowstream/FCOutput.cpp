#include "stdafx.h"
#include "FCOutput.h"

#include "DataOutput.h"

CFCOutput::CFCOutput()
{
}


CFCOutput::~CFCOutput()
{
}

BOOL CFCOutput::Initialize(Point position, Size size)
{
	this->position = position;
	this->size = size;

	return TRUE;
}

VOID CFCOutput::Draw(Graphics * graphics, CPoint scrollPosition)
{
	CDataIO::DrawSymbol(graphics, position.X - scrollPosition.x, position.Y - scrollPosition.y, bSelected, size);

	CSymbol::DrawLabel(graphics, scrollPosition);
}

std::string CFCOutput::InterpreterLabel()
{
	CDataOutput*	symbolDialog = dynamic_cast<CDataOutput*>(dialog);

	CT2CA convertedExp(symbolDialog->ExpressionText);

	std::string label;

	label = "output ";
	label += convertedExp;

	return label;
}
