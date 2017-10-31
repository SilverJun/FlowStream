#include "stdafx.h"
#include "FCInput.h"

#include "DataInput.h"

CFCInput::CFCInput()
{
}


CFCInput::~CFCInput()
{
}

BOOL CFCInput::Initialize(Point position, Size size)
{
	this->position = position;
	this->size = size;

	return TRUE;
}

VOID CFCInput::Draw(Graphics * graphics, CPoint scrollPosition)
{
	CDataIO::DrawSymbol(graphics, position.X - scrollPosition.x, position.Y - scrollPosition.y, bSelected, size);

	CSymbol::DrawLabel(graphics, scrollPosition);
}

std::string CFCInput::InterpreterLabel()
{
	CDataInput*	symbolDialog = dynamic_cast<CDataInput*>(dialog);

	CT2CA convertedVar(symbolDialog->VariableName);

	std::string label;

	label = "input ";
	label += convertedVar;

	return label;
}
