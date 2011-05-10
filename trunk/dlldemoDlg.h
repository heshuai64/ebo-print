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
	BOOL PreTranslateMessage(MSG* pMsg);
	void SetCurrencyUser(CString);
// Dialog Data
	//{{AFX_DATA(CDlldemoDlg)
	enum { IDD = IDD_DLLDEMO_DIALOG };
	CEdit	m_cesku;
	CButton	m_buttonopenport;
	CButton	m_buttoncloseport;
	CButton	m_buttonprintaddress;
	CButton	m_ctrlcheck;
	int		m_port;
	int		m_label;
	CString	m_drstr;
	int		m_time;
	CTime   m_date;
	CString m_sku;
	CString m_user;
	HTTPSocket* m_pHTTPSock;
	CLoginDlg* m_pLogindlg;
	CSKUBarcodeDlg* m_pSkuBarcodedlg;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlldemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CDlldemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheck1();
	afx_msg void OnButtonopenport();
	afx_msg void OnButtoncloseport();
	afx_msg void OnLogin();
	afx_msg void OnButtonPrintAddress();
	afx_msg void OnChangeSku();
	afx_msg void OnMenuSkuBarcode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLDEMODLG_H__8DA9C567_8D97_11D6_8D35_0010DC0DE867__INCLUDED_)
