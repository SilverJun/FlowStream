#include "stdafx.h"
#include "FCPrint.h"


CFCPrint::CFCPrint()
{
}


CFCPrint::~CFCPrint()
{
}

BOOL CFCPrint::Initialize(Point position, Size size)
{
	this->position = position;
	this->size = size;

	return TRUE;
}

VOID CFCPrint::Draw(Graphics* graphics, CPoint scrollPosition)
{
	CDataIO::DrawSymbol(graphics, position.X - scrollPosition.x, position.Y - scrollPosition.y, bSelected, size);

	CSymbol::DrawLabel(graphics, scrollPosition);
}

std::string CFCPrint::InterpreterLabel()
{
	return "PRINT";
}

