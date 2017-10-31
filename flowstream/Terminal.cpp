#include "stdafx.h"
#include "Terminal.h"


CTerminal::CTerminal()
{
}


CTerminal::~CTerminal()
{
}

VOID CTerminal::DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag)
{
	// 심볼 선택 상태
	if (selected)
		CShape::RoundedRectangle(graphics, SELECTED_COLOR, TRUE, xPos - TERMINAL_XGAP, yPos - TERMINAL_YGAP, size.Width + (TERMINAL_XGAP * 2), size.Height + (TERMINAL_YGAP * 2), 30);

	// 심볼 바탕
	CShape::RoundedRectangle(graphics, Gdiplus::Color(255, 255, 255, 255), TRUE, xPos, yPos, size.Width, size.Height, 30);
	// 심볼 테두리
	CShape::RoundedRectangle(graphics, Gdiplus::Color(255, 232, 151, 12), FALSE, xPos, yPos, size.Width, size.Height, 30);
}
