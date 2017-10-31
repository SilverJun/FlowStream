#pragma once

//===============================================
// CListObject : ������Ʈ�� ����Ʈ�� ������Ʈ.


#undef LoadImage
class CListObject
{
public:
	CListObject();
	virtual ~CListObject();

private :
	CImage	originImage;
	CImage	iconImage;
	CImage	objectImage;

public :
	CString	originImagePath;
	CString	iconImagePath;
	CString	objectImagePath;

	CString	name;

public :
	BOOL		CreateImage(CString imageName, CString imagePath, INT xSize, INT ySize);
	BOOL		LoadImage(CString imageName, CString imagePath, INT xSize, INT ySize);

};

