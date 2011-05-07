#if !defined(AFX_SKUBARCODEDLG_H__C0E1ED3A_82E8_4583_926E_5D305BD7F4A5__INCLUDED_)
#define AFX_SKUBARCODEDLG_H__C0E1ED3A_82E8_4583_926E_5D305BD7F4A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SKUBarcodeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSKUBarcodeDlg dialog

class CSKUBarcodeDlg : public CDialog
{
// Construction
public:
	CSKUBarcodeDlg(CWnd* pParent = NULL);   // standard constructor
	void setSkuInfo(CString, CString);
	
// Dialog Data
	//{{AFX_DATA(CSKUBarcodeDlg)
	enum { IDD = IDD_SKU_BARCODE };
	CString sku;
	CString sku_title;
	int sku_stock;
	int print_num;
	
	int i_r;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSKUBarcodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSKUBarcodeDlg)
	afx_msg void OnGetSkuInfo();
	afx_msg void OnSkuBarcodePrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKUBARCODEDLG_H__C0E1ED3A_82E8_4583_926E_5D305BD7F4A5__INCLUDED_)
