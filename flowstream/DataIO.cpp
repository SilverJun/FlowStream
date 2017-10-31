#include "stdafx.h"
#include "DataIO.h"


CDataIO::CDataIO()
{
}


CDataIO::~CDataIO()
{
}

VOID CDataIO::DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag)
{
	// 심볼 선택 상태
	if (selected)
		CShape::Parallelogram(graphics, SELECTED_COLOR, TRUE, xPos - DATAIO_XGAP, yPos - DATAIO_YGAP, size.Width + (DATAIO_XGAP * 2), size.Height + (DATAIO_YGAP * 2));

	// 심볼 바탕
	CShape::Parallelogram(graphics, Gdiplus::Color(255, 255, 255, 255), TRUE, xPos, yPos, size.Width, size.Height);
	// 심볼 테두리
	CShape::Parallelogram(graphics, Gdiplus::Color(255, 248, 74, 74), FALSE, xPos, yPos, size.Width, size.Height);
}