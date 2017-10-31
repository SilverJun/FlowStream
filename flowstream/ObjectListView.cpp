// ObjectList.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ObjectListView.h"
#include "resource.h"
#include "ListObject.h"
#include "ObjectListDialog.h"
#include "FlowObject.h"

#include "FlowStreamDoc.h"

// CObjectListView

IMPLEMENT_DYNCREATE(CObjectListView, CListView)

CObjectListView::CObjectListView()
{

}

CObjectListView::~CObjectListView()
{
}

BEGIN_MESSAGE_MAP(CObjectListView, CListView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MEASUREITEM()
	ON_WM_NCPAINT()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CObjectListView::OnNMDblclk)
	ON_NOTIFY_REFLECT(NM_CLICK, &CObjectListView::OnNMClick)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CObjectListView �����Դϴ�.
CImageList imageList;

#ifdef _DEBUG
void CObjectListView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CObjectListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CObjectListView �޽��� ó�����Դϴ�.

INT CObjectListView::DeleteAllFiles(LPCWSTR szDir, int recur)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	int res = 1;

	TCHAR DelPath[MAX_PATH];
	TCHAR FullPath[MAX_PATH];
	TCHAR TempPath[MAX_PATH];

	lstrcpy(DelPath, szDir);
	lstrcpy(TempPath, szDir);
	if (lstrcmp(DelPath + lstrlen(DelPath) - 4, _T("\\*.*")) != 0)
		lstrcat(DelPath, _T("\\*.*"));

	hSrch = FindFirstFile(DelPath, &wfd);
	if (hSrch == INVALID_HANDLE_VALUE)
	{
		if (recur > 0)
			RemoveDirectory(TempPath);

		return -1;
	}
	while (res)
	{
		wsprintf(FullPath, _T("%s\\%s"), TempPath, wfd.cFileName);

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
		{
			SetFileAttributes(FullPath, FILE_ATTRIBUTE_NORMAL);
		}

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (lstrcmp(wfd.cFileName, _T(".")) && lstrcmp(wfd.cFileName, _T("..")))
			{
				recur++;
				DeleteAllFiles(FullPath, recur);
				recur--;
			}
		}
		else
		{
			INT result = DeleteFile(FullPath);

			if (result == 0)
			{
				TRACE("Error! %d\n", GetLastError());
			}
		}
		res = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);

	if (recur > 0)
		RemoveDirectory(TempPath);

	return 0;
}

VOID CObjectListView::DeleteObject(CString name)
{
	CListCtrl& list = GetListCtrl();

	INT itemIndex = 1;

	for each (CListObject* object in objects)
	{
		if (object->name == name)
		{
			CMainFrame*	mainFrame = (CMainFrame*)AfxGetMainWnd();

			std::vector<CListObject*>::iterator iter = std::find(objects.begin(), objects.end(), object);

			objects.erase(iter);

			CFlowStreamDoc* pDoc = (CFlowStreamDoc*)mainFrame->GetActiveDocument();

			CString directory = pDoc->filePath;

			directory += object->name;

			DeleteAllFiles(directory, 1);

			list.DeleteItem(itemIndex);
			list.DeleteColumn(itemIndex);

			ImagePositionRevision();

			mainFrame->objectFlow->ChangeFlow(nullptr);

			Invalidate();

			break;
		}

		itemIndex++;
	}
}

VOID CObjectListView::ImagePositionRevision()
{
	CListCtrl& list = GetListCtrl();

	CRect clientRect;
	GetClientRect(&clientRect);

	int rowItemCount = clientRect.Width() / IMAGE_XDISTANCE;

	for (int i = 0; i < list.GetItemCount(); i++)
	{
		POINT pt;
		pt.x = IMAGE_XDISTANCE * (i % rowItemCount);
		pt.y = (i / rowItemCount) * IMAGE_YDISTANCE;

		list.SetItemPosition(i, pt);
	}
	
}

int CObjectListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	CListCtrl& list = GetListCtrl();
	CBitmap bitmap;

	list.SetExtendedStyle(LVS_EX_AUTOAUTOARRANGE | LVS_EX_AUTOSIZECOLUMNS);

	imageList.Create(50, 50, ILC_COLOR32, 1, 1);

	bitmap.LoadBitmapW(IDB_BITMAP_ADDOBJECT);

	imageList.Add(&bitmap, RGB(0, 0, 0));

	list.SetImageList(&imageList, LVSIL_NORMAL);

	list.InsertItem(0, _T("Add"), 0);

	list.SetBkColor(RGB(80, 80, 80));
	list.SetTextBkColor(RGB(80, 80, 80));
	list.SetTextColor(RGB(255, 255, 255));
	return 0;
}


void CObjectListView::OnSize(UINT nType, int cx, int cy)
{
	CListView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CObjectListView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CListView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


void CObjectListView::OnNcPaint()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CListView::OnNcPaint()��(��) ȣ������ ���ʽÿ�.
}



void CObjectListView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int itemIndex = pNMItemActivate->iItem;

	if (itemIndex == 0)
	{
		CFileDialog fileDialog(TRUE, _T("BMP | PNG | JPG"), NULL,
			OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
			_T("Image Files (BMP,JPEG,GIF,PNG,JPG...)|*.BMP;*.JPEG;*.JPG;*.GIF;*.PNG|"));

		if (fileDialog.DoModal() == IDOK)
		{
			CObjectListDialog name(this);
			CString objectName;

			if (name.DoModal() == IDOK)
			{
				if (name.xSize.GetLength() <= 0 || name.xSize.GetLength() >= 5 ||
					name.ySize.GetLength() <= 0 || name.ySize.GetLength() >= 5)
				{
					AfxMessageBox(_T("�̹����� ũ�⸦ Ȯ�����ּ���."));

					return;
				}

				objectName = name.objectName;
			}
			else
			{
				return;
			}

			CListCtrl& list = GetListCtrl();
			CString strPathName = fileDialog.GetPathName();
			CClientDC dc(this);

			CListObject* obj = new CListObject;

			CT2CA convertedXSize(name.xSize);
			CT2CA convertedYSize(name.ySize);

			if (obj->CreateImage(objectName, strPathName, atoi(convertedXSize), atoi(convertedYSize)))
			{
				CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

				// ������Ʈ ����
				CFlowObject*	object = new CFlowObject();
				object->Initialize(objectName);

				object->objectFlow = mainFrame->objectFlow->CreateFlow(object);

				mainFrame->play->PushObject(object);
				mainFrame->play->ChangeSelectedObject(object);
				mainFrame->play->Invalidate();

				// ������ �̹��� ����
				HANDLE hbitmap;
				hbitmap = LoadImageW(NULL, obj->iconImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

				CBitmap bitmap;
				bitmap.Attach(hbitmap);

				BITMAP	bmpInfo;
				bitmap.GetBitmap(&bmpInfo);

				imageList.Add(&bitmap, RGB(0, 0, 0));

				list.SetImageList(&imageList, LVSIL_NORMAL);

				INT imageCount = imageList.GetImageCount() - 1;

				list.InsertItem(imageCount, objectName, imageCount);

				ImagePositionRevision();

				objects.push_back(obj);
			}
		}
	}

	*pResult = 0;
}

void CObjectListView::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	CListCtrl& list = GetListCtrl();

	CMainFrame*		mainFrame = (CMainFrame*)AfxGetMainWnd();

	int itemIndex = pNMItemActivate->iItem;

	// ������Ʈ �߰� ��ư
	if (itemIndex <= 0)
	{
		return;
	}

	if (mainFrame->play->selectedObject == nullptr)
	{
		for each (CFlowObject* flowObject in mainFrame->play->objects)
		{
			if (flowObject->name == objects[itemIndex - 1]->name)
			{
				mainFrame->objectFlow->ChangeFlow(flowObject->objectFlow);
				mainFrame->play->ChangeSelectedObject(flowObject);

				return;
			}
		}
	}

	// ���õ� ������Ʈ�� ������Ų��.
	if (objects[itemIndex - 1]->name != mainFrame->play->selectedObject->name)
	{
		for each (CFlowObject* flowObject in mainFrame->play->objects)
		{
			if (flowObject->name == objects[itemIndex - 1]->name)
			{
				mainFrame->objectFlow->ChangeFlow(flowObject->objectFlow);
				mainFrame->play->ChangeSelectedObject(flowObject);
			}
		}
	}
}


void CObjectListView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	// ���� ��ư
	if (nChar == VK_DELETE || nChar == VK_BACK)
	{
		CString name = mainFrame->play->selectedObject->name;

		mainFrame->play->DeleteObject(name);
		DeleteObject(name);
	}

	CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}
