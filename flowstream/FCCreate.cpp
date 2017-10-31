#include "stdafx.h"
#include "FCCreate.h"


CFCCreate::CFCCreate()
{
}


CFCCreate::~CFCCreate()
{
}

BOOL CFCCreate::Initialize(Point position, Size size)
{
	this->position = position;
	this->size = size;

	return TRUE;
}

VOID CFCCreate::Draw(Graphics* graphics, CPoint scrollPosition)
{
	CPrepare::DrawSymbol(graphics, position.X - scrollPosition.x, position.Y - scrollPosition.y, bSelected, size);

	CSymbol::DrawLabel(graphics, scrollPosition);
}

std::string CFCCreate::InterpreterLabel()
{
	CCreateVariable*	symbolDialog = dynamic_cast<CCreateVariable*>(dialog);

	CT2CA convertedType(symbolDialog->type);
	CT2CA convertedName(symbolDialog->name);

	std::string label;

	label += convertedType;
	label += " ";
	label += convertedName;


	return label;
}

