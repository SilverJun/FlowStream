#pragma once

//===============================================
// CListObject : 오브젝트를 리스트의 오브젝트.


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

