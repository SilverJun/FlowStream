#include "stdafx.h"
#include "Shape.h"


CShape::CShape()
{
}


CShape::~CShape()
{
}

VOID CShape::Rectangle(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height)
{
	Rect			rect = Rect(xPos, yPos, width, height);
	SolidBrush	solidBrush(color);
	Pen				pen(color, SYMBOL_XSIZE / 20);

	if (fill)
		graphics->FillRectangle(&solidBrush, rect);
	else
		graphics->DrawRectangle(&pen, rect);
}

VOID CShape::RoofRectangle(Graphics* graphics, Color color, BOOL fill, BOOL roof, INT xPos, INT yPos, INT width, INT height, INT gap)
{
	Point			points[6];
	SolidBrush	solidBrush(color);
	Pen				pen(color, SYMBOL_XSIZE / 20);

	if (roof)
	{
		points[0] = Point(xPos, yPos + gap);
		points[1] = Point(xPos + gap, yPos);
		points[2] = Point(xPos + width - gap, yPos);
		points[3] = Point(xPos + width, yPos + gap);
		points[4] = Point(xPos + width, yPos + height);
		points[5] = Point(xPos, yPos + height);
	}
	else
	{
		points[0] = Point(xPos, yPos);
		points[1] = Point(xPos + width, yPos);
		points[2] = Point(xPos + width, yPos + height - gap);
		points[3] = Point(xPos + width - gap, yPos + height);
		points[4] = Point(xPos + gap, yPos + height);
		points[5] = Point(xPos, yPos + height - gap);
	}

	if (fill)
		graphics->FillPolygon(&solidBrush, points, 6);
	else
		graphics->DrawPolygon(&pen, points, 6);
}

VOID CShape::RoundedRectangle(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height, INT radius)
{
	GraphicsPath path;
	SolidBrush		solidBrush(color);
	Pen				pen(color, SYMBOL_XSIZE / 20);

	path.AddLine(xPos + radius, yPos, xPos + width - radius, yPos);
	path.AddArc(xPos + width - radius, yPos, radius, radius, 270, 90);
	path.AddLine(xPos + width, yPos + radius, xPos + width, yPos + height - radius);
	path.AddArc(xPos + width - radius, yPos + height - radius, radius, radius, 0, 90);
	path.AddLine(xPos + width - radius, yPos + height, xPos + radius, yPos + height);
	path.AddArc(xPos, yPos + height - radius, radius, radius, 90, 90);
	path.AddLine(xPos, yPos + height - radius, xPos, yPos + radius);
	path.AddArc(xPos, yPos, radius, radius, 180, 90);

	path.CloseFigure();

	if (fill)
		graphics->FillPath(&solidBrush, &path);
	else
		graphics->DrawPath(&pen, &path);
}

VOID CShape::Parallelogram(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height)
{
	Point			points[4];
	SolidBrush	solidBrush(color);
	Pen				pen(color, SYMBOL_XSIZE / 20);

	points[0] = Point(xPos + (width / 10), yPos);
	points[1] = Point(xPos + width, yPos);
	points[2] = Point(xPos + width - (width / 10), yPos + height);
	points[3] = Point(xPos, yPos + height);

	if (fill)
		graphics->FillPolygon(&solidBrush, points, 4);
	else
		graphics->DrawPolygon(&pen, points, 4);
}

VOID CShape::Hexagon(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height, INT gap, BOOL edge)
{
	INT penSize = SYMBOL_XSIZE / 20;

	//if (edge)
	//	penSize = SYMBOL_XSIZE / 15;
	//else
		penSize = SYMBOL_XSIZE / 20;

	Point			points[6];
	SolidBrush	solidBrush(color);
	Pen				pen(color, penSize);

	points[0] = Point(xPos, yPos + (height / 2));
	points[1] = Point(xPos + gap, yPos);
	points[2] = Point(xPos + (gap * 3), yPos);
	points[3] = Point(xPos + width, yPos + (height / 2));
	points[4] = Point(xPos + (gap * 3), yPos + height);
	points[5] = Point(xPos + gap, yPos + height);

	if (fill)
		graphics->FillPolygon(&solidBrush, points, 6);
	else
		graphics->DrawPolygon(&pen, points, 6);
}

VOID CShape::Rhombus(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height)
{
	Point			points[4];
	SolidBrush	solidBrush(color);
	Pen				pen(color, SYMBOL_XSIZE / 20);

	points[0] = Point(xPos, yPos + height / 2);
	points[1] = Point(xPos + width / 2, yPos);
	points[2] = Point(xPos + width, yPos + height / 2);
	points[3] = Point(xPos + width / 2, yPos + height);

	if (fill)
		graphics->FillPolygon(&solidBrush, points, 4);
	else
		graphics->DrawPolygon(&pen, points, 4);
}

VOID CShape::Circle(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height)
{
	Rect			rect = Rect(xPos, yPos, width, height);
	SolidBrush	solidBrush(color);
	Pen				pen(color, SYMBOL_XSIZE / 20);

	if (fill)
		graphics->FillEllipse(&solidBrush, rect);
	else
		graphics->DrawEllipse(&pen, rect);
}
