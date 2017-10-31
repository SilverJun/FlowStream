#include "stdafx.h"
#include "FCWhileStart.h"


CFCWhileStart::CFCWhileStart()
{
}


CFCWhileStart::~CFCWhileStart()
{
}

BOOL CFCWhileStart::Initialize(Point position, Size size)
{
	this->position = position;
	this->size = size;

	return TRUE;
}

VOID CFCWhileStart::Draw(Graphics* graphics, CPoint scrollPosition)
{
	CLoop::DrawSymbol(graphics, position.X - scrollPosition.x, position.Y - scrollPosition.y, bSelected, size, TRUE);

	CSymbol::DrawLabel(graphics, scrollPosition);
}

std::string CFCWhileStart::InterpreterLabel()
{
	CConditionCheck*	symbolDialog = dynamic_cast<CConditionCheck*>(dialog);

	//symbolDialog->UpdateData();

	CString	str;

	str += "while ";

	str += symbolDialog->label;

	str += "\n{";

	CT2CA convertedString(str);
	std::string label = convertedString;

	return convertedString;
}

