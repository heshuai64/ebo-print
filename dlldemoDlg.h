// dlldemoDlg.h : header file
//

#if !defined(AFX_DLLDEMODLG_H__8DA9C567_8D97_11D6_8D35_0010DC0DE867__INCLUDED_)
#define AFX_DLLDEMODLG_H__8DA9C567_8D97_11D6_8D35_0010DC0DE867__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDlldemoDlg dialog

class CDlldemoDlg : public CDialog
{
// Construction
public:
	CDlldemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlldemoDlg)
	enum { IDD = IDD_DLLDEMO_DIALOG };
	CEdit	m_timeout;
	CEdit	m_driver;
	CComboBox	m_comname;
	CButton	m_buttonstatus;
	CButton	m_buttonprint;
	CButton	m_buttonopenport;
	CButton	m_buttoncloseport;
	CButton	m_ctrlcheck;
	CStatic	m_ctrlimage;
	CComboBox	m_ctrladdress;
	CComboBox	m_ctrlbaudrate;
	int		m_port;
	int		m_label;
	CString	m_drstr;
	int		m_time;
	CTime   m_date;
	CString m_sku;
	HTTPSocket* m_pHTTPSock;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlldemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	BOOL PrintWaterWay();
	BOOL PrintFreeWay();
	// Generated message map functions
	//{{AFX_MSG(CDlldemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnCheck1();
	afx_msg void OnRadio3();
	afx_msg void OnRadio1();
	afx_msg void OnButtonopenport();
	afx_msg void OnButtoncloseport();
	afx_msg void OnButtonprint();
	afx_msg void OnButtonstatus();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnLogin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLDEMODLG_H__8DA9C567_8D97_11D6_8D35_0010DC0DE867__INCLUDED_)
