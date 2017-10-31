#include "stdafx.h"
#include "FCIf.h"


CFCIf::CFCIf()
{
}


CFCIf::~CFCIf()
{
}

BOOL CFCIf::Initialize(Point position, Size size)
{
	this->position = position;
	this->size = size;

	return TRUE;
}

VOID CFCIf::Draw(Graphics* graphics, CPoint scrollPosition)
{
	CDecision::DrawSymbol(graphics, position.X - scrollPosition.x, position.Y - scrollPosition.y, bSelected, size);

	CSymbol::DrawLabel(graphics, scrollPosition);
}

std::string CFCIf::InterpreterLabel()
{
	CConditionCheck*	symbolDialog = dynamic_cast<CConditionCheck*>(dialog);

	//symbolDialog->UpdateData();

	CString	str;

	str += "if ";

	str += symbolDialog->label;

	str += "\n{";

	CT2CA convertedString(str);
	std::string label = convertedString;

	return label;
}

