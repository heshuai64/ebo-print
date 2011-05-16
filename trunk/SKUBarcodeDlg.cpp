// SKUBarcodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dlldemo.h"
#include "eBayBOService.h"
#include "SKUBarcodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSKUBarcodeDlg dialog


CSKUBarcodeDlg::CSKUBarcodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSKUBarcodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSKUBarcodeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSKUBarcodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSKUBarcodeDlg)
		DDX_Text(pDX, IDC_BARCODE_SKU, sku);
		DDX_Text(pDX, IDC_SKU_TITLE, sku_title);
		DDX_Text(pDX, IDC_PRINT_NUM, print_num);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSKUBarcodeDlg, CDialog)
	//{{AFX_MSG_MAP(CSKUBarcodeDlg)
	ON_BN_CLICKED(IDC_GET_SKU_INFO, OnGetSkuInfo)
	ON_BN_CLICKED(IDC_SKU_BARCODE_PRINT, OnSkuBarcodePrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSKUBarcodeDlg message handlers

void CSKUBarcodeDlg::OnGetSkuInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	eBayBOService* ebos = new eBayBOService(8080, "/inventory/service.php?action=", "getSkuInfo", "");
	ebos->SetParentDlg(this);
	ebos->getSkuInfoBySku(sku);
}

void CSKUBarcodeDlg::OnSkuBarcodePrint() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char buffer[20];
	itoa( print_num, buffer, 10 );
	//MessageBox(sku + ":" + sku_title + ":" + buffer);

	//SkuInfo* si = new SkuInfo();
	//GetDlgItemText(IDC_BARCODE_SKU, CString(si->id));
	//GetDlgItemText(IDC_SKU_TITLE,  CString(si->chineseTitle));
	//si->printNum = GetDlgItemInt(IDC_PRINT_NUM);
	
	eBayBOService* ebos = new eBayBOService(8080, "/inventory/service.php?action=", "getSkuInfo", "");
	SkuInfo* si = new SkuInfo();
	si->id = (LPSTR)(LPCTSTR) sku;
	si->chineseTitle = (LPSTR)(LPCTSTR) sku_title;
	si->printNum = print_num;
	ebos->printSkuBarcode(si);
	delete ebos;
	delete si;
}

void CSKUBarcodeDlg::setSkuInfo(CString title, CString stock)
{
	//AfxMessageBox (title);
	SetDlgItemText(IDC_SKU_TITLE, title);
	SetDlgItemText(IDC_SKU_STOCK, stock);
}