#include "stdafx.h"
#include "FCWhileEnd.h"


CFCWhileEnd::CFCWhileEnd()
{
}


CFCWhileEnd::~CFCWhileEnd()
{
}

BOOL CFCWhileEnd::Initialize(Point position, Size size)
{
	this->position = position;
	this->size = size;

	label = _T("End");

	return TRUE;
}

VOID CFCWhileEnd::Draw(Graphics* graphics, CPoint scrollPosition)
{
	CLoop::DrawSymbol(graphics, position.X - scrollPosition.x, position.Y - scrollPosition.y, bSelected, size, FALSE);

	CSymbol::DrawLabel(graphics, scrollPosition);
}

std::string CFCWhileEnd::InterpreterLabel()
{
	return "}";
}
