#include "stdafx.h"
#include "ListObject.h"

#include "FlowStreamDoc.h"

CListObject::CListObject()
{
}


CListObject::~CListObject()
{
}

BOOL CListObject::CreateImage(CString imageName, CString imagePath, INT xSize, INT ySize)
{
	CMainFrame*	mainFrame = (CMainFrame*)AfxGetMainWnd();
	
	name = imageName;

	CFlowStreamDoc* pDoc = (CFlowStreamDoc*)mainFrame->GetActiveDocument();

	CT2CA convertedProjectName(pDoc->projectName);
	std::string directoryPath;

	if (!(pDoc->projectName == ""))		//빈문서 처리.
	{
		CT2CA convertedPath = pDoc->filePath;
		directoryPath = convertedPath;
		directoryPath += "Resource\\";
	}
	else
	{
		directoryPath = "Resource\\";
	}

	CT2CA convertedName(imageName);

	directoryPath += convertedName;

	if (mkdir(directoryPath.c_str()) == 0)
	{
		originImage.Load(imagePath);

		originImagePath = directoryPath.c_str();
		originImagePath += "\\";
		originImagePath += imageName;
		originImagePath += ".bmp";

		originImage.Save(originImagePath, Gdiplus::ImageFormatBMP);

		// Object
		objectImage.Create(xSize, ySize, 32);

		HDC objectDC = objectImage.GetDC();

		::SetStretchBltMode(objectDC, COLORONCOLOR);

		originImage.StretchBlt(objectDC, 0, 0, xSize, ySize);

		objectImagePath = directoryPath.c_str();
		objectImagePath += "\\";
		objectImagePath += "Object";
		objectImagePath += ".bmp";

		objectImage.Save(objectImagePath, Gdiplus::ImageFormatBMP);

		objectImage.ReleaseDC();

		// Icon
		iconImage.Create(50, 50, 32);

		HDC resizeDC = iconImage.GetDC();

		::SetStretchBltMode(resizeDC, COLORONCOLOR);

		originImage.StretchBlt(resizeDC, 0, 0, 50, 50);

		iconImagePath = directoryPath.c_str();
		iconImagePath += "\\";
		iconImagePath += "resize";
		iconImagePath += imageName;
		iconImagePath += ".bmp";

		iconImage.Save(iconImagePath, Gdiplus::ImageFormatBMP);

		iconImage.ReleaseDC();

		return TRUE;
	}
	else
	{
		AfxMessageBox(_T("오브젝트 이름을 확인해주세요."));
	}

	return FALSE;
}

BOOL CListObject::LoadImage(CString imageName, CString imagePath, INT xSize, INT ySize)
{
	name = imageName;

	CT2CA convertedPath(imagePath);
	CT2CA convertedName(imageName);

	std::string directoryPath = convertedPath;
	
	//error handling
	HRESULT result;

	//이미 디렉터리가 존재해야 한다.
	if (mkdir(directoryPath.c_str()) == -1)
	{
		originImagePath = directoryPath.c_str();
		originImagePath += "\\";
		originImagePath += imageName;
		originImagePath += ".bmp";

		result = originImage.Load(originImagePath);
		if (FAILED(result))
		{
			AfxMessageBox(_T("원본 이미지 불러오기 실패!"));
			return FALSE;
		}

		objectImagePath = directoryPath.c_str();
		objectImagePath += "\\";
		objectImagePath += "Object";
		objectImagePath += ".bmp";

		result = objectImage.Load(objectImagePath);
		if (FAILED(result))
		{
			AfxMessageBox(_T("오브젝트 이미지 불러오기 실패!"));
			return FALSE;
		}

		// Icon
	
		iconImagePath = directoryPath.c_str();
		iconImagePath += "\\";
		iconImagePath += "resize";
		iconImagePath += imageName;
		iconImagePath += ".bmp";

		result = iconImage.Load(iconImagePath);
		if (FAILED(result))
		{
			AfxMessageBox(_T("아이콘 이미지 불러오기 실패!"));
			return FALSE;
		}

		return TRUE;
	}
	else
	{
		AfxMessageBox(_T("이미지 불러오기 실패!"));
	}

	return FALSE;
}
