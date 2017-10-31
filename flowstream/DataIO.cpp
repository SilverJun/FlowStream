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
	// �ɺ� ���� ����
	if (selected)
		CShape::Parallelogram(graphics, SELECTED_COLOR, TRUE, xPos - DATAIO_XGAP, yPos - DATAIO_YGAP, size.Width + (DATAIO_XGAP * 2), size.Height + (DATAIO_YGAP * 2));

	// �ɺ� ����
	CShape::Parallelogram(graphics, Gdiplus::Color(255, 255, 255, 255), TRUE, xPos, yPos, size.Width, size.Height);
	// �ɺ� �׵θ�
	CShape::Parallelogram(graphics, Gdiplus::Color(255, 248, 74, 74), FALSE, xPos, yPos, size.Width, size.Height);
}