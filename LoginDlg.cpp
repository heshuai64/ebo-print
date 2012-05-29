// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sqlite3.h"
#include "URLEncode.h"
#include "eBayBOService.h"
#include "HTTPSocket.h"
#include "dlldemo.h"
#include "LoginDlg.h"
#include "SKUBarcodeDlg.h"
#include "UploadAddressDlg.h"
#include "dlldemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
		m_user = "";
		m_password = "";
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
		DDX_Text(pDX, IDC_EDIT1, m_user);
		DDX_Text(pDX, IDC_EDIT2, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnLogin)
	ON_BN_CLICKED(IDC_BUTTON2, OnLoginClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnLogin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//MessageBox(m_user + ":" + m_password);
	eBayBOService* ebos = new eBayBOService(8888, "/eBayBO/service.php?action=", "remoteLogin", "");
	ebos->setParentDlg(this);
	ebos->login(m_user, m_password);
	//((CDlldemoDlg*)m_pDlg)->SetCurrencyUser("test");
	this->EndDialog(i_r);
}

void CLoginDlg::OnLoginClose() 
{
	// TODO: Add your control notification handler code here
	this->EndDialog(i_r);
}

void CLoginDlg::SetParentDlg(CDialog *pDlg)
{
	m_pDlg=pDlg;
}

void CLoginDlg::SetCurrencyUser(CString user)
{
	((CDlldemoDlg*)m_pDlg)->SetCurrencyUser(user);
}
