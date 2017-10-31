﻿
// stdAFX.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <AFXwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <AFXext.h>         // MFC 확장입니다.


#include <AFXdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <AFXdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <AFXcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <AFXcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원
#include <AFXcview.h>

// GDI+
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

// Interpreter Need Include
#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>
#include <wincon.h>

// STL
#include <vector>
#include <unordered_map>
#include <memory>
#include <list>
#include <algorithm>

// 폴더 생성
#include <direct.h> 

#include "ObjectFlow.h"

// 심볼 모양들
#define	SYMBOL_XSIZE	80
#define	SYMBOL_YSIZE	40

#define	LABEL_SIZE			17

#define	WINDOW_XSIZE	1024
#define	WINDOW_YSIZE	768

#define	PLAY_DRAWTIME	11256

#include "Shape.h"
#include "Terminal.h"
#include "Decision.h"
#include "Process.h"
#include "DataIO.h"
#include "Prepare.h"
#include "Loop.h"

// 심볼
#include "Symbol.h"
#include "FCStart.h"
#include "FCEnd.h"
#include "FCIf.h"
#include "FCIfEnd.h"
#include "FCSet.h"
#include "FCPrint.h"
#include "FCCreate.h"
#include "FCWhileStart.h"
#include "FCWhileEnd.h"
#include "FCInput.h"
#include "FCOutput.h"


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


