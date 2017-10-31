#include "stdafx.h"
#include "FCIfEnd.h"


CFCIfEnd::CFCIfEnd()
{
}


CFCIfEnd::~CFCIfEnd()
{
}

BOOL CFCIfEnd::Initialize(Point position, Size size)
{
	this->position = position;
	this->size = size;
	this->label = _T("End");

	return TRUE;
}

VOID CFCIfEnd::Draw(Graphics* graphics, CPoint scrollPosition)
{
	CDecision::DrawSymbol(graphics, position.X - scrollPosition.x, position.Y - scrollPosition.y, bSelected, size);

	CSymbol::DrawLabel(graphics, scrollPosition);
}

std::string CFCIfEnd::InterpreterLabel()
{
	return "}";
}

