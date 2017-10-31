#include "stdafx.h"
#include "Process.h"


CProcess::CProcess()
{
}


CProcess::~CProcess()
{
}

VOID CProcess::DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag)
{
	// 심볼 선택 상태
	if (selected)
		CShape::Rectangle(graphics, SELECTED_COLOR, TRUE, xPos - PROCESS_XGAP, yPos - PROCESS_YGAP, size.Width + (PROCESS_XGAP * 2), size.Height + (PROCESS_YGAP * 2));

	// 심볼 바탕
	CShape::Rectangle(graphics, Gdiplus::Color(255, 255, 255, 255), TRUE, xPos, yPos, size.Width, size.Height);
	// 심볼 테두리
	CShape::Rectangle(graphics, Gdiplus::Color(255, 97, 28, 161), FALSE, xPos, yPos, size.Width, size.Height);
}