#include "stdafx.h"
#include "FCEnd.h"


CFCEnd::CFCEnd()
{
}


CFCEnd::~CFCEnd()
{
}

BOOL CFCEnd::Initialize(Point position, Size size)
{
	this->position = position;
	this->size = size;

	label = _T("End");

	return TRUE;
}

VOID CFCEnd::Draw(Graphics* graphics, CPoint scrollPosition)
{
	CTerminal::DrawSymbol(graphics, position.X - scrollPosition.x, position.Y - scrollPosition.y, bSelected, size);

	CSymbol::DrawLabel(graphics, scrollPosition);
}

std::string CFCEnd::InterpreterLabel()
{
	return "// Á¾·á";
}

