#include "stdafx.h"
#include "FCSet.h"


CFCSet::CFCSet()
{
}


CFCSet::~CFCSet()
{
}

BOOL CFCSet::Initialize(Point position, Size size)
{
	this->position = position;
	this->size = size;

	return TRUE;
}

VOID CFCSet::Draw(Graphics* graphics, CPoint scrollPosition)
{
	CProcess::DrawSymbol(graphics, position.X - scrollPosition.x, position.Y - scrollPosition.y, bSelected, size);

	CSymbol::DrawLabel(graphics, scrollPosition);
}

std::string CFCSet::InterpreterLabel()
{
	CAllocation*	symbolDialog = dynamic_cast<CAllocation*>(dialog);

	CT2CA convertedlabel(label);

	return convertedlabel;
}

