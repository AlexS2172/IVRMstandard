#if !defined(AFX_LICENSEDLG_H__63A4C839_DAB2_433B_91B4_CC88F3E403E0__INCLUDED_)
#define AFX_LICENSEDLG_H__63A4C839_DAB2_433B_91B4_CC88F3E403E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LicenseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLicenseDlg dialog

class CLicenseDlg : public CDialog
{
// Construction
public:
	CLicenseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLicenseDlg)
	enum { IDD = IDD_LICENSE };
	CString	m_strLicenseKey;
	CString	m_strProductID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicenseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLicenseDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LICENSEDLG_H__63A4C839_DAB2_433B_91B4_CC88F3E403E0__INCLUDED_)
