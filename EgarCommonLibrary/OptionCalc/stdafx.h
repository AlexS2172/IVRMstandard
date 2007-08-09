// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6DE6CC33_6877_4CCA_BA17_64D7E0537F1E__INCLUDED_)
#define AFX_STDAFX_H__6DE6CC33_6877_4CCA_BA17_64D7E0537F1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Windows stuff
#include <windows.h>
#include <windef.h>
#include <wtypes.h>
#include <oleauto.h>

// CRT
#include <crtdbg.h>
#include <math.h>
#include <tchar.h>
#include <float.h>

#pragma warning (disable : 4786)
// STL
#include <vector>
#include <map>

// Option Price Model
#include "OptionPriceModels.h"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6DE6CC33_6877_4CCA_BA17_64D7E0537F1E__INCLUDED_)
