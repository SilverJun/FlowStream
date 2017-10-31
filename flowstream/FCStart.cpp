#include "stdafx.h"
#include "FCStart.h"


CFCStart::CFCStart()
{
}


CFCStart::~CFCStart()
{
}

BOOL CFCStart::Initialize(Point position, Size size)
{
	this->position	= position;
	this->size			= size;
	
	label = _T("Start");

	return TRUE;
}

VOID CFCStart::Draw(Graphics* graphics, CPoint scrollPosition)
{
	CTerminal::DrawSymbol(graphics, position.X - scrollPosition.x, position.Y - scrollPosition.y, bSelected, size);

	CSymbol::DrawLabel(graphics, scrollPosition);
}

std::string CFCStart::InterpreterLabel()
{
	return "// Ω√¿€";
}

