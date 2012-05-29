// UploadAddressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dlldemo.h"
#include "sqlite3.h"
#include "URLEncode.h"
#include "eBayBOService.h"
#include "UploadAddressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUploadAddressDlg dialog


CUploadAddressDlg::CUploadAddressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUploadAddressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUploadAddressDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUploadAddressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUploadAddressDlg)
		DDX_Control(pDX, IDC_UPLOAD_ADDRESS_PROGRESS, m_upload_progress);
		DDX_Control(pDX, IDC_BUTTON_UPLOAD, m_button_upload);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUploadAddressDlg, CDialog)
	//{{AFX_MSG_MAP(CUploadAddressDlg)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, OnUpload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUploadAddressDlg message handlers
int getPackedShipmentNum(void* data, int n_columns, char** column_values, char** column_names)
{
	((CUploadAddressDlg*)data)->setTotalShipmentNum(atoi(column_values[0]));
	((CUploadAddressDlg*)data)->SetDlgItemText(IDC_PACK_NUM,column_values[0]);
	return 0;
}

BOOL CUploadAddressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	char *errMsg = NULL;
	int rc;
	rc = sqlite3_exec(db, "select count(*) as num from packed_shipment;", getPackedShipmentNum, this, &errMsg); 
	return true;
}

int syncPackedShipment(void* data, int n_columns, char** column_values, char** column_names)
{
	//AfxMessageBox (column_values[0]);
	eBayBOService* ebos = new eBayBOService(8888, "/eBayBO/service.php?action=", "syncShipmentPrintStatus", "");
	ebos->setDebug("1");
	ebos->setParentDlg((CUploadAddressDlg*)data);
	ebos->syncShipmentPrintStatus(column_values[0], column_values[1], column_values[2]);
	return 0;
}

void CUploadAddressDlg::OnUpload() 
{
	m_button_upload.EnableWindow(FALSE);
	char *errMsg = NULL;
	int rc;
	rc = sqlite3_exec(db, "select * from packed_shipment;", syncPackedShipment, this, &errMsg); 
}

void CUploadAddressDlg::syncShipmentPrintStatusSuccess(CString shipmentId)
{
	//AfxMessageBox (shipmentId);
	char *errMsg = NULL;
	int rc;
	rc = sqlite3_exec(db, "delete from packed_shipment where shipmentId = '"+shipmentId+"';", NULL, this, &errMsg);
	int currentNum = GetDlgItemInt(IDC_UPLOAD_SUCCESS_NUM)+1;
	SetDlgItemInt(IDC_UPLOAD_SUCCESS_NUM, currentNum);
	setProgress(currentNum/shipmentTotalNum*100);
}

void CUploadAddressDlg::setDB(sqlite3* sqliteDB)
{
	db = sqliteDB;
}

void CUploadAddressDlg::setProgress(int nPos)
{
	m_upload_progress.SetPos(nPos);
}

void CUploadAddressDlg::setTotalShipmentNum(int total)
{
	shipmentTotalNum = total;
}
