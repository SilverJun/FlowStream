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
	// ���� ���� ǥ��
	if (selected)
		CShape::RoofRectangle(graphics, SELECTED_COLOR, FALSE, flag, xPos - LOOP_XGAP, yPos - LOOP_YGAP, size.Width + (LOOP_XGAP * 2), size.Height + (LOOP_YGAP * 2), (size.Width + LOOP_XGAP * 2) / 4);

	// �ɺ� ����
	CShape::RoofRectangle(graphics, Gdiplus::Color(255, 255, 255, 255), TRUE, flag, xPos, yPos, size.Width, size.Height, size.Width / 4);
	// �ɺ� �׵θ�
	CShape::RoofRectangle(graphics, Gdiplus::Color(255, 89, 247, 152), FALSE, flag, xPos, yPos, size.Width, size.Height, size.Width / 4);
}