#if !defined(AFX_UPLOADADDRESSDLG_H__5FCCBE4D_5DDB_4396_AE52_F2301AE5E372__INCLUDED_)
#define AFX_UPLOADADDRESSDLG_H__5FCCBE4D_5DDB_4396_AE52_F2301AE5E372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UploadAddressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUploadAddressDlg dialog

class CUploadAddressDlg : public CDialog
{
// Construction
public:
	void setDB(sqlite3* sqliteDB);
	void syncShipmentPrintStatusSuccess(CString);
	void setProgress(int);
	void setTotalShipmentNum(int);
	CUploadAddressDlg(CWnd* pParent = NULL);   // standard constructor
	OnInitDialog();
// Dialog Data
	//{{AFX_DATA(CUploadAddressDlg)
	enum { IDD = IDD_UPLOAD_ADDRESS };
	CProgressCtrl m_upload_progress;
	sqlite3* db;
	int shipmentTotalNum;
	CButton	m_button_upload;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUploadAddressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUploadAddressDlg)
	afx_msg void OnUpload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPLOADADDRESSDLG_H__5FCCBE4D_5DDB_4396_AE52_F2301AE5E372__INCLUDED_)
