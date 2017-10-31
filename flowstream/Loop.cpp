#include "stdafx.h"
#include "Loop.h"


CLoop::CLoop()
{
}


CLoop::~CLoop()
{
}

VOID CLoop::DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag)
{
	// 선택 상태 표시
	if (selected)
		CShape::RoofRectangle(graphics, SELECTED_COLOR, FALSE, flag, xPos - LOOP_XGAP, yPos - LOOP_YGAP, size.Width + (LOOP_XGAP * 2), size.Height + (LOOP_YGAP * 2), (size.Width + LOOP_XGAP * 2) / 4);

	// 심볼 바탕
	CShape::RoofRectangle(graphics, Gdiplus::Color(255, 255, 255, 255), TRUE, flag, xPos, yPos, size.Width, size.Height, size.Width / 4);
	// 심볼 테두리
	CShape::RoofRectangle(graphics, Gdiplus::Color(255, 89, 247, 152), FALSE, flag, xPos, yPos, size.Width, size.Height, size.Width / 4);
}