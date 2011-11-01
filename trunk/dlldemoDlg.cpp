// dlldemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eBayBOService.h"
#include "HTTPSocket.h"
#include "dlldemo.h"
#include "LoginDlg.h"
#include "SKUBarcodeDlg.h"
#include "dlldemoDlg.h"
#include "Print.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlldemoDlg dialog
extern mBPLA_SetSaveFile		BPLA_SetSaveFile		;
extern mBPLA_GetVersion   		BPLA_GetVersion			;
extern mBPLA_OpenCom   			BPLA_OpenCom			;
extern mBPLA_OpenComEx   		BPLA_OpenComEx			;
extern mBPLA_CloseCom			BPLA_CloseCom			;
extern mBPLA_OpenLpt  			BPLA_OpenLpt			;
extern mBPLA_CloseLpt   		BPLA_CloseLpt			;
extern mBPLA_OpenUsb			BPLA_OpenUsb			;
extern mBPLA_OpenUsbByID  		BPLA_OpenUsbByID		;
extern mBPLA_CloseUsb   		BPLA_CloseUsb			;
extern mBPLA_SetTimeOut         BPLA_SetTimeOut			;
extern mBPLA_OpenPrinterDriver	BPLA_OpenPrinterDriver	;
extern mBPLA_ClosePrinterDriver BPLA_ClosePrinterDriver	;
extern mBPLA_StartDoc   		BPLA_StartDoc			;
extern mBPLA_EndDoc             BPLA_EndDoc				;
extern mBPLA_SendCommand  		BPLA_SendCommand		;
extern mBPLA_ReceiveInfo  		BPLA_ReceiveInfo		;
extern mBPLA_SendFile			BPLA_SendFile			;
extern mBPLA_ReceiveFile		BPLA_ReceiveFile		;
extern mBPLA_DownloadImage		BPLA_DownloadImage		;
extern mBPLA_DownloadFont		BPLA_DownloadFont		;
extern mBPLA_DownErase			BPLA_DownErase			;
extern mBPLA_DownEraseAll		BPLA_DownEraseAll		;
extern mBPLA_Set				BPLA_Set				;
extern mBPLA_SetSensor			BPLA_SetSensor			;
extern mBPLA_SetPaperLength		BPLA_SetPaperLength     ;
extern mBPLA_SetEnd				BPLA_SetEnd				;
extern mBPLA_ForBack			BPLA_ForBack			;
extern mBPLA_Reset				BPLA_Reset				;
extern mBPLA_StartArea			BPLA_StartArea			;
extern mBPLA_SetMirror			BPLA_SetMirror			;
extern mBPLA_Print				BPLA_Print				;
extern mBPLA_SaveLabel			BPLA_SaveLabel			;
extern mBPLA_PrintSaveLabel		BPLA_PrintSaveLabel     ;
extern mBPLA_SetCopy			BPLA_SetCopy			;
extern mBPLA_SetAllMirror		BPLA_SetAllMirror		;
extern mBPLA_SetAllRotate		BPLA_SetAllRotate		;
extern mBPLA_PrintLine			BPLA_PrintLine			;
extern mBPLA_PrintBox			BPLA_PrintBox			;
extern mBPLA_PrintCircle		BPLA_PrintCircle		;
extern mBPLA_LoadImage			BPLA_LoadImage			;
extern mBPLA_PrintImage			BPLA_PrintImage			;
extern mBPLA_PrintText			BPLA_PrintText			;
extern mBPLA_PrintOut			BPLA_PrintOut			;
extern mBPLA_PrintTruetype		BPLA_PrintTruetype		;
extern mBPLA_PrintTruetypeEx	BPLA_PrintTruetypeEx	;
extern mBPLA_PrintMixText		BPLA_PrintMixText		;
extern mBPLA_PrintMixTextEx	    BPLA_PrintMixTextEx		;
extern mBPLA_PrintBarcode		BPLA_PrintBarcode		;
extern mBPLA_PrintPDF			BPLA_PrintPDF			;
extern mBPLA_PrintMaxi			BPLA_PrintMaxi			;
extern mBPLA_CheckCom			BPLA_CheckCom			;
extern mBPLA_CheckStatus		BPLA_CheckStatus		;
extern mBPLA_CheckCut			BPLA_CheckCut			;

CDlldemoDlg::CDlldemoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDlldemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlldemoDlg)
	m_drstr = _T("");
	m_time = 0;
	m_pLogindlg = NULL;
	m_pSkuBarcodedlg = NULL;
	m_user = "请先登录,才能打印地址";
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlldemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlldemoDlg)
	DDX_Control(pDX, IDC_EDIT3, m_cesku);
	DDX_Control(pDX, IDC_BUTTONOPENPORT, m_buttonopenport);
	DDX_Control(pDX, IDC_BUTTONCLOSEPORT, m_buttoncloseport);
	DDX_Control(pDX, IDC_BUTTONPRINTADDRESS, m_buttonprintaddress);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlcheck);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Text(pDX, IDC_EDIT3, m_sku);
	DDX_Text(pDX, IDC_CURRENCY_USER, m_user);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlldemoDlg, CDialog)
//{{AFX_MSG_MAP(CDlldemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_BUTTONOPENPORT, OnButtonopenport)
	ON_BN_CLICKED(IDC_BUTTONCLOSEPORT, OnButtoncloseport)
	ON_COMMAND(IDM_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_BUTTONPRINTADDRESS, OnButtonPrintAddress)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeSku)
	ON_COMMAND(IDM_SKU_BARCODE, OnMenuSkuBarcode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlldemoDlg message handlers

BOOL CDlldemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//m_cesku.EnableWindow(FALSE);

	// TODO: Add extra initialization here
	
	//********初始化默认设置
	m_sku = "";
	m_drstr = "BTP-2200E(P)";
	m_time = 1000;
	m_date = CTime::GetCurrentTime();
	LoadDll();
	
	CString m_version = "";
	m_version.Format("一切正常，DLL版本号-----%d",BPLA_GetVersion());
	SetDlgItemText(IDC_STATICPRINTSTATUS,m_version);
	m_buttonprintaddress.EnableWindow(FALSE);

	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlldemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlldemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDlldemoDlg::OnCheck1() 
{
	//int index = m_ctrlcheck.GetCheck(); 
	//if(index == 1)	BPLA_SetSaveFile(true,"test.txt",false);
	//else BPLA_SetSaveFile(false,"test.txt",false);
}

void CDlldemoDlg::OnButtonopenport() 
{
	char driverstr[100];
	int state;

	UpdateData(TRUE);

	memset(driverstr,0,100);
	sprintf(driverstr,"%s",m_drstr);

	state = BPLA_OpenPrinterDriver(driverstr);
	if(state == BPLA_OK)
	{
		SetDlgItemText(IDC_STATICPRINTSTATUS,"驱动打开正确");
		m_buttoncloseport.EnableWindow(TRUE);
		return;
	}
	else
	{
		CString m_info;
		m_info.Format("驱动打开错误，错误值 -- %04d",state);
		SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
		m_buttoncloseport.EnableWindow(FALSE);
		return;
	}	
}

void CDlldemoDlg::OnButtoncloseport()
{
	BPLA_ClosePrinterDriver();//关闭驱动
	SetDlgItemText(IDC_STATICPRINTSTATUS,"驱动关闭");
	m_buttoncloseport.EnableWindow(FALSE);
	UpdateData(FALSE);
	return;
}

void CDlldemoDlg::OnLogin() 
{
	// TODO: Add your command handler code here
	m_pLogindlg = new CLoginDlg();
	m_pLogindlg->SetParentDlg(this);
	m_pLogindlg->i_r = m_pLogindlg->DoModal();
}

void CDlldemoDlg::OnButtonPrintAddress() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	setProgress(10);
	eBayBOService* ebos = new eBayBOService(8888, "/eBayBO/service.php?action=", "getShippingAddressBySku", m_user);
	ebos->SetParentDlg(this);
	CString debug = "0";
	if(m_ctrlcheck.GetCheck() == 1){
		debug = "1";
	}
	ebos->getShippingAddressBySku("&date="+m_date.Format("%Y-%m-%d")+"&sku="+m_sku+"&by="+m_user+"&debug="+debug);
	m_cesku.SetWindowText("");
	m_cesku.SetFocus();
	//delete ebos;
}

BOOL CDlldemoDlg::PreTranslateMessage(MSG* pMsg)
{
	UpdateData(TRUE);
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			OnButtonPrintAddress();
			return TRUE;
		}
		if (pMsg->wParam == VK_ESCAPE) return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlldemoDlg::OnChangeSku() 
{
	// TODO: Add your control notification handler code here
	//UpdateData(TRUE);
	//AfxMessageBox(m_sku);
}

//DEL void CDlldemoDlg::OnExit() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	EndDialog();
//DEL }

void CDlldemoDlg::OnMenuSkuBarcode() 
{
	// TODO: Add your command handler code here
	m_pSkuBarcodedlg = new CSKUBarcodeDlg();
	m_pSkuBarcodedlg->i_r = m_pSkuBarcodedlg->DoModal();
}

void CDlldemoDlg::SetCurrencyUser(CString user) 
{
	SetDlgItemText(IDC_CURRENCY_USER, user);
	m_buttonprintaddress.EnableWindow(TRUE);
}

void CDlldemoDlg::SetPrintStatus(CString status) 
{
	SetDlgItemText(IDC_STATICPRINTSTATUS, status);
}

BOOL CDlldemoDlg::isTest()
{
	int index = m_ctrlcheck.GetCheck(); 
	if(index == 1) return true;
	else return false;
}

void CDlldemoDlg::setProgress(int nPos)
{
	m_progress.SetPos(nPos);
}
