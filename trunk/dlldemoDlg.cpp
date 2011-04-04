// dlldemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HTTPSocket.h"
#include "dlldemo.h"  
#include "dlldemoDlg.h"
#include "Print.h"
//#include "eBayBOService.h"

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
	m_port = 0;
	m_label = 0; 
	m_drstr = _T("");
	m_time = 0;
	m_pHTTPSock = NULL;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlldemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlldemoDlg)
	DDX_Control(pDX, IDC_TIMEOUT, m_timeout);
	DDX_Control(pDX, IDC_DRIVER, m_driver);
	DDX_Control(pDX, IDC_COMNAME, m_comname);
	DDX_Control(pDX, IDC_BUTTONSTATUS, m_buttonstatus);
	DDX_Control(pDX, IDC_BUTTONPRINT, m_buttonprint);
	DDX_Control(pDX, IDC_BUTTONOPENPORT, m_buttonopenport);
	DDX_Control(pDX, IDC_BUTTONCLOSEPORT, m_buttoncloseport);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlcheck);
	DDX_Control(pDX, IDC_STATICIMAGE, m_ctrlimage);
	DDX_Control(pDX, IDC_COMBOADDRESS, m_ctrladdress);
	DDX_Control(pDX, IDC_COMBOBAUDRATE, m_ctrlbaudrate);
	DDX_Radio(pDX, IDC_RADIO1, m_port);
	DDX_Radio(pDX, IDC_RADIO4, m_label);
	DDX_Text(pDX, IDC_DRIVER, m_drstr);
	DDX_Text(pDX, IDC_TIMEOUT, m_time);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlldemoDlg, CDialog)
//{{AFX_MSG_MAP(CDlldemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_BUTTONOPENPORT, OnButtonopenport)
	ON_BN_CLICKED(IDC_BUTTONCLOSEPORT, OnButtoncloseport)
	ON_BN_CLICKED(IDC_BUTTONPRINT, OnButtonprint)
	ON_BN_CLICKED(IDC_BUTTONSTATUS, OnButtonstatus)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
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

	m_ctrlbaudrate.EnableWindow(TRUE);
    m_ctrladdress.EnableWindow(FALSE);
	m_driver.EnableWindow(FALSE);	
	
	// TODO: Add extra initialization here
	
	//********初始化默认设置
	SetDlgItemText(IDC_COMBOBAUDRATE,"选择波特率");
	m_ctrlbaudrate.SetCurSel (3);
	m_ctrladdress.SetCurSel(0);
	m_comname.SetCurSel(0);
	m_drstr = "BTP-2300T2(S)";
	m_time = 1000;
	OnRadio4();
	LoadDll();
	
	CString m_version = "";
	m_version.Format("一切正常，DLL版本号-----%d",BPLA_GetVersion());
	SetDlgItemText(IDC_STATICPRINTSTATUS,m_version);

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

void CDlldemoDlg::OnRadio4() 
{
    SetDlgItemText(IDC_EDIT1,"选用TRUETYPE字体打印，数据量较大，请使用并口或USB口通讯。");	
	HBITMAP m_hbmp;
	m_hbmp = (HBITMAP)LoadImage(NULL,"WaterWay.bmp",IMAGE_BITMAP,300,200,LR_DEFAULTSIZE|LR_SHARED|LR_LOADFROMFILE);
	m_ctrlimage.SetBitmap(m_hbmp);
	m_label = 0;
}

void CDlldemoDlg::OnRadio5() 
{
    SetDlgItemText(IDC_EDIT1,"选用内部字体打印，内部支持的ASCII码字体共23种，并可以将外部字库下载到FLASH中作为内部字体使用。");
	HBITMAP m_hbmp;
	m_hbmp = (HBITMAP)LoadImage(NULL,"freeway.bmp",IMAGE_BITMAP,300,200,LR_DEFAULTSIZE|LR_SHARED|LR_LOADFROMFILE);
	m_ctrlimage.SetBitmap(m_hbmp);
	m_label = 1;
}

void CDlldemoDlg::OnCheck1() 
{
	int index = m_ctrlcheck.GetCheck(); 
	if(index == 1)	BPLA_SetSaveFile(true,"test.txt",false);
	else BPLA_SetSaveFile(false,"test.txt",false);
}

void CDlldemoDlg::OnRadio3() 
{
	m_ctrlbaudrate.EnableWindow(FALSE);	
	m_ctrladdress.EnableWindow(TRUE);
	m_comname.EnableWindow(FALSE);
	m_driver.EnableWindow(FALSE);
	m_timeout.EnableWindow(TRUE);
	if(m_port == 0)
	{
		BPLA_CloseCom();//关闭串口
	}
	else if(m_port == 1)
	{
		BPLA_CloseLpt();//关闭并口
	}
	else if(m_port == 2)
	{
		BPLA_CloseUsb();//关闭USB口
	}
	else if(m_port == 3)
	{
		BPLA_ClosePrinterDriver();//关闭驱动
	}
	m_port = 1;
	m_buttoncloseport.EnableWindow(FALSE);
	m_buttonprint.EnableWindow(FALSE);
	m_buttonstatus.EnableWindow(FALSE);
}

void CDlldemoDlg::OnRadio1() 
{
    m_ctrlbaudrate.EnableWindow(TRUE);	
	m_ctrladdress.EnableWindow(FALSE);
	m_comname.EnableWindow(TRUE);
	m_driver.EnableWindow(FALSE);
	m_timeout.EnableWindow(TRUE);
	if(m_port == 0)
	{
		BPLA_CloseCom();//关闭串口
	}
	else if(m_port == 1)
	{
		BPLA_CloseLpt();//关闭并口
	}
	else if(m_port == 2)
	{
		BPLA_CloseUsb();//关闭USB口
	}
	else if(m_port == 3)
	{
		BPLA_ClosePrinterDriver();//关闭驱动
	}
	m_port = 0;
	m_buttoncloseport.EnableWindow(FALSE);
	m_buttonprint.EnableWindow(FALSE);
	m_buttonstatus.EnableWindow(FALSE);

}

void CDlldemoDlg::OnButtonopenport() 
{
	//eBayBOService* ebos = new eBayBOService();
	//ebos->getShippingAddress();
	if((m_pHTTPSock = new HTTPSocket(this, "rich2010.3322.org", 8888)) == NULL)
	{
		AfxMessageBox ("Failed to allocate client socket! Close and restart app.");
		return;
	}
	//CString StrMessage = "GET / HTTP/1.1\r\n\r\n";
	//int sent;
	//sent = m_pHTTPSock->Send(StrMessage, StrMessage.GetLength());
	
	m_pHTTPSock->Get("/eBayBO/");
	//MessageBox("test content", "test", MB_APPLMODAL);

	int comnameindex;
	char* comnamestr;
	int baudrateindex,m_baudrate;
	int addressindex,m_address;
	char driverstr[100];
	int state;

	UpdateData(TRUE);
	
	comnameindex = m_comname.GetCurSel();
	baudrateindex = m_ctrlbaudrate.GetCurSel();
	addressindex = m_ctrladdress.GetCurSel();

	switch(comnameindex){
	case 0:comnamestr = "com1";	break;
	case 1:comnamestr = "com2";	break;
	case 2:comnamestr = "com3";	break;
	case 3:comnamestr = "com4";	break;
	}

	switch(baudrateindex){
	case 0:m_baudrate = 2400;	break;
	case 1:m_baudrate = 9600;	break;
	case 2:m_baudrate = 19200;	break;
	case 3:m_baudrate = 38400;	break;
	case 4:m_baudrate = 56000;	break;
	case 5:m_baudrate = 57600;	break;
	case 6:m_baudrate = 115200;	break;	
	}

	switch(addressindex){
	case 0:m_address = 0x378;	break;
	case 1:m_address = 0x278;	break;
	}
	
	memset(driverstr,0,100);
	sprintf(driverstr,"%s",m_drstr);

	switch(m_port){
	//case 0:state = BPLA_OpenCom(comnamestr,m_baudrate,1);break;  //打开串口。BPLA_OpenCom函数实现打开串口，进行检测串口。
    case 0:state = BPLA_OpenComEx(comnamestr,m_baudrate,1,m_time);break;  //BPLA_OpenComEx函数实现打开串口，但不检测串口。
	case 1:state = BPLA_OpenLpt(m_address,m_time);break;           //打开并口
	case 2:state = BPLA_OpenUsb();break;                         //打开USB口。
	//case 2:state = BPLA_OpenUsbByID(152);break;                //BPLA_OpenUsbByID函数通过内部ID号打开USB口，用于多台USB设备同时连接识别调用。
	case 3:state = BPLA_OpenPrinterDriver(driverstr);            //打开驱动
	}	
	if(state == BPLA_OK)
	{
		int state1;
		if(m_port == 2)//usb口时设置端口超时
		{
			int timeout;
			timeout = m_time;
			state1 = BPLA_SetTimeOut(timeout);
			if(state1 != BPLA_OK)
			{
				CString m_info;
				m_info.Format("设置端口超时错误，错误值 -- %04d",state);
				SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
				m_buttoncloseport.EnableWindow(FALSE);
				m_buttonprint.EnableWindow(FALSE);
				m_buttonstatus.EnableWindow(FALSE);
				return;
			}
		}
		if(m_port == 3)
		{
			SetDlgItemText(IDC_STATICPRINTSTATUS,"驱动打开正确");
			m_buttoncloseport.EnableWindow(TRUE);
			m_buttonprint.EnableWindow(TRUE);
			if(m_port !=3) m_buttonstatus.EnableWindow(TRUE);
			else m_buttonstatus.EnableWindow(FALSE);
			return;
		}				
		SetDlgItemText(IDC_STATICPRINTSTATUS,"端口打开正确");
		m_buttoncloseport.EnableWindow(TRUE);
		m_buttonprint.EnableWindow(TRUE);
		if(m_port !=3&&m_port !=1) m_buttonstatus.EnableWindow(TRUE);
		else m_buttonstatus.EnableWindow(FALSE);	
		return;
	}
	else
	{
		if(m_port == 3)
		{
			CString m_info;
			m_info.Format("驱动打开错误，错误值 -- %04d",state);
			SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
			m_buttoncloseport.EnableWindow(FALSE);
			m_buttonprint.EnableWindow(FALSE);
			m_buttonstatus.EnableWindow(FALSE);
			return;
		}
		else
		{
			CString m_info;
			m_info.Format("端口打开错误，错误值 -- %04d",state);
			SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
			m_buttoncloseport.EnableWindow(FALSE);
			m_buttonprint.EnableWindow(FALSE);
			m_buttonstatus.EnableWindow(FALSE);	
			return;
		}
	}	
}

void CDlldemoDlg::OnButtoncloseport()
{
	if(m_port == 0)
	{
		BPLA_CloseCom();//关闭串口
	}
	else if(m_port == 1)
	{
		BPLA_CloseLpt();//关闭并口
	}
	else if(m_port == 2)
	{
		BPLA_CloseUsb();//关闭USB口
	}
	else if(m_port == 3)
	{
		BPLA_ClosePrinterDriver();//关闭驱动
		SetDlgItemText(IDC_STATICPRINTSTATUS,"驱动关闭");
		m_buttonprint.EnableWindow(FALSE);
		m_buttoncloseport.EnableWindow(FALSE);
		m_buttonstatus.EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}	
	
	SetDlgItemText(IDC_STATICPRINTSTATUS,"端口关闭");
	m_buttonprint.EnableWindow(FALSE);
	m_buttoncloseport.EnableWindow(FALSE);
	m_buttonstatus.EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CDlldemoDlg::OnButtonprint() 
{
	//建议：用户在使用时，最好也是象这样将打印的操作作为一个函数集中处理，
	//上层程序根据此函数的返回值判断打印成功与否，这样更加方便维护。
	m_buttonprint.EnableWindow(FALSE);
	m_buttonstatus.EnableWindow(FALSE);
	m_buttoncloseport.EnableWindow(FALSE);
	m_buttonopenport.EnableWindow(FALSE);
	m_ctrlcheck.EnableWindow(FALSE);
	SetDlgItemText(IDC_STATICPRINTSTATUS,"");
	
	BOOL bstate;
	int start = GetTickCount();
	switch(m_label)
	{
		case 0:bstate = PrintWaterWay();	break;
		case 1:bstate = PrintFreeWay();		break;
	}
	int end = GetTickCount();
	CString mm = "",mm1="";
	GetDlgItemText(IDC_STATICPRINTSTATUS,mm);
	if(bstate) 
	{
		mm1.Format(" 打印成功-%04dms",end-start);
		mm=mm+mm1;
		SetDlgItemText(IDC_STATICPRINTSTATUS,mm);
		m_buttonprint.EnableWindow(TRUE);
		if(m_port != 1 && m_port != 3)
			m_buttonstatus.EnableWindow(TRUE);
		m_buttoncloseport.EnableWindow(TRUE);
		m_buttonopenport.EnableWindow(TRUE);
		m_ctrlcheck.EnableWindow(TRUE);
	}
	else 
	{
		if(mm=="")
			SetDlgItemText(IDC_STATICPRINTSTATUS," 打印失败");
		m_buttonprint.EnableWindow(FALSE);
		if(m_port != 1 && m_port != 3)
			m_buttonstatus.EnableWindow(TRUE);
		m_buttoncloseport.EnableWindow(TRUE);
		m_buttonopenport.EnableWindow(TRUE);
		m_ctrlcheck.EnableWindow(TRUE);
	}

}

void CDlldemoDlg::OnButtonstatus() 
{
	m_buttonprint.EnableWindow(FALSE);
	m_buttonstatus.EnableWindow(FALSE);
	m_buttoncloseport.EnableWindow(FALSE);
	m_buttonopenport.EnableWindow(FALSE);
	m_ctrlcheck.EnableWindow(FALSE);
	//状态查询
	char m_papershort[3],m_ribbionshort[3],m_busy[3],m_pause[3],m_com[3],m_headheat[3],m_headover[3],m_cut[3];
	int state =	BPLA_CheckStatus(m_papershort,m_ribbionshort,m_busy,m_pause,m_com,m_headheat,m_headover,m_cut);
	CString m_info;

	if(state != BPLA_OK)
	{
		m_info = "查询状态失败";
		m_buttonprint.EnableWindow(FALSE);
		//if(m_port != 1 && m_port != 3)
		m_buttonstatus.EnableWindow(FALSE);
		m_buttoncloseport.EnableWindow(FALSE);
		m_buttonopenport.EnableWindow(TRUE);
		m_ctrlcheck.EnableWindow(TRUE);
	}
	else
	{
		m_info = "";
		if(m_papershort[0] != 'N')
			m_info += " 缺纸";
		if(m_ribbionshort[0] != 'N') 
			m_info += " 缺色带";
		if(m_busy[0] != 'N') 
			m_info += " 解释器忙";
		if(m_pause[0] != 'N') 
			m_info += " 暂停";
		if(m_com[0] != 'N')
			m_info += " 通讯错误";
		if(m_headover[0] != 'N')
			m_info += " 打印头抬起";
		if(m_headheat[0] != 'N')
			m_info += " 打印头过热";
		if(m_cut[0] != 'N')
			m_info += " 切刀响应超时";
		if(m_info.GetLength()==0) 
			m_info = "状态正常";
		m_buttonprint.EnableWindow(TRUE);
		if(m_port != 1 && m_port != 3)
			m_buttonstatus.EnableWindow(TRUE);
		m_buttoncloseport.EnableWindow(TRUE);
		m_buttonopenport.EnableWindow(TRUE);
		m_ctrlcheck.EnableWindow(TRUE);
	}
	SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);	  
}

//水运票样完全使用TRUETYPE字体打印，图象为外部图象文件直接打印，条码为128码。
//优点：可以灵活选择字体的大小、风格和图象等；缺点：数据量较大，不太适合串口打印。
BOOL CDlldemoDlg::PrintWaterWay()
{
	char m_papershort[3],m_ribbionshort[3],m_busy[3],m_pause[3],m_com[3],m_headheat[3],m_headover[3],m_cut[3];
	
	//为了准确判断数据发送成功与否，建议对于每个调用的函数均检查其返回值。
	//具体函数的返回值请参考DLL的说明文档。
    //*********驱动启动打印
	if(m_port == 3)
	{
		int state1;

		state1 = BPLA_StartDoc();
		if(state1 != BPLA_OK)
		{
			CString m_info;
			m_info.Format("驱动启动打印失败，错误值 -- %04d",state1);
			SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
			
			return FALSE;
		}
	}

	int state = BPLA_SetPaperLength(600,0);//对于标签纸，则不需要这个函数
	if(state!=BPLA_OK) return FALSE; 
	state = BPLA_SetAllRotate(1);
	if(state!=BPLA_OK) return FALSE; 
	for(int i=0;i<1;i++){
		state = BPLA_StartArea(0,900,0,0,0,0,0,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("A1234567",70,560,"黑体",26,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("烟港售",570,560,"黑体",26,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("中海客轮有限公司",220,510,"黑体",30,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("客票",90,450,"黑体",30,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("航次:739",60,410,"黑体",28,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("三等B",90,350,"黑体",30,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("铺号:",90,240,"黑体",28,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("123",100,185,"黑体",28,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("烟台",250,455,"黑体",40,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintImage("arrow.bmp",380,465,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("大连",540,455,"黑体",40,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("棒棰岛轮",250,400,"黑体",30,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("烟港新站",500,400,"黑体",30,0);
		if(state!=BPLA_OK) return FALSE;

		state = BPLA_PrintTruetype("2002年度03月20日21:30开",250,350,"黑体",30,0);
		if(state!=BPLA_OK) return FALSE;
		//混排打印
		/*
		state = BPLA_PrintMixTextEx("2002年度03月20日21:30开",250,350,0,1,"0003","B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		*/
		/*
		state = BPLA_PrintMixText("2002年度03月20日21:30开",250,350,350,1,3,"B21",20,40,1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		*/
		

		state = BPLA_PrintTruetype("票价:109.00元",350,290,"黑体",30,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("须知：当日当次船有效",290,250,"黑体",28,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintBarcode("345268724325578",270,150,1,4,80,4,2,"000");
		if(state!=BPLA_OK) return FALSE;
		//state = BPLA_PrintTruetype("345268724325578",350,120,"Arial",24,0);
		//if(state!=BPLA_OK) return FALSE;
		state = BPLA_Print(1,1,1);
	}
	if(state!=BPLA_OK) return FALSE;

    if(m_port == 3) //驱动结束打印，退出不查状态
	{
		int state1;

		state1 = BPLA_EndDoc();
		if(state1 != BPLA_OK)
		{
			CString m_info;
			m_info.Format("驱动关闭打印失败，错误值 -- %04d",state1);
			SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);	
			return FALSE;
		}

		return TRUE;
	}

	if(m_port == 1 || m_port == 3)  //并口,驱动不查询状态
	{
		return TRUE;
	}
	
	//打印完毕之后应该进行状态查询，以确认当前票据是否正常打印出来。
	
	Sleep(1800);//由于状态查询属于实时指令，而打印机从接收数据到
	//打印需要一定的时间，所以在此应该进行一定的延时，以
	//保证查询到的状态能够反映打印成功与否的实际情况。这
	//段时间需要用户根据票面的数据来确定。
	state =	BPLA_CheckStatus(m_papershort,m_ribbionshort,m_busy,m_pause,m_com,m_headheat,m_headover,m_cut);
	CString m_info;
	if(state != BPLA_OK)
	{
		m_info = "查询状态失败";
	}
	else
	{
		m_info = "";
		if(m_papershort[0] != 'N') 
			m_info += " 缺纸";
		if(m_ribbionshort[0] != 'N')
			m_info += " 缺色带";
		if(m_busy[0] != 'N')
			m_info += " 解释器忙";
		if(m_pause[0] != 'N') 
			m_info += " 暂停";
		if(m_com[0] != 'N')
			m_info += " 通讯错误";
		if(m_headover[0] != 'N')
			m_info += " 打印头抬起";
		if(m_headheat[0] != 'N') 
			m_info += " 打印头过热";
		if(m_cut[0] != 'N')
			m_info += " 切刀响应超时";
		if(m_info.GetLength()==0)  
			m_info = " 状态正常";
        SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
	}
    if(m_info.Compare(" 状态正常")==0) return TRUE;
	else return FALSE;
}

//公路票样完全使用内部字体或预先下载到打印机的字体、图象等，数据量小，适合串口和并口打印。
//内部ASCII码字体共23种，其它需要使用的字体和图象需要预先下载到FLASH或RAM中，供打印使用。
//由于FLASH中掉电不丢失数据，所以建议将字体和图象下载到FLASH中。
BOOL CDlldemoDlg::PrintFreeWay()
{
	//*************驱动启动打印
	if(m_port == 3)
	{
		int state1;

		state1 = BPLA_StartDoc();
		if(state1 != BPLA_OK)
		{
			CString m_info;
			m_info.Format("驱动启动打印失败，错误值 -- %04d",state1);
			SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
			
			return FALSE;
		}
	}

	int state = BPLA_SetPaperLength(580,0);//对于标签纸，则不需要这个函数
	if(state!=BPLA_OK) return FALSE; 
	for(int k=0;k<1;k++){		
		state = BPLA_SetAllRotate(0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_StartArea(0,800,0,0,0,0,0,0);
		if(state!=BPLA_OK) return FALSE;
	
		state = BPLA_PrintPDF("124578963",150,300,1,3,7,0,0,8,5,0,3,9,"000");
		if(state!=BPLA_OK) return FALSE;
		
		//汉字宋体32点阵字库在此代号为B21，35点阵字库在此代号为B24详细意义请看指令集中有关标签打印、
		//字体打印的说明以及DLL函数库的说明。
		state = BPLA_PrintOut("高速公路车辆通行券",300,450,1,"B21",1,1,"000",0,0);
		//该种字体在打印机内进行了放大，但由于可能影响处理速度，并不建议用户使用这种方式。
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintOut("驶入时间",100,180,1,"B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintOut("车型",100,100,1,"B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintOut("中型",230,100,1,"B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintOut("车号",460,100,1,"B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		//中英文混排打印，下列两种方法都可以
		/*
		state = BPLA_PrintMixTextEx("鲁D210087",570,100,0,1,"0003","B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		*/
		state = BPLA_PrintMixText("鲁D210087",570,100,100,1,3,"B21",20,40,1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		//DLL并没有将所有指令均包装成函数，仅针对用户最容易使用的指令进行包装。
		//对于没有进行包装的指令我们提供了BPLA_SendCommand函数对其进行发送。
		//下面就是发送指令以进行斜杠零和普通零切换的例子。
		char temp[2];
		temp[0] = 'z';
		temp[1] = 0x0d;
		state = BPLA_SendCommand(temp,2);
		if(state!=BPLA_OK) return FALSE;
		
		state = BPLA_PrintText("2001-10-03 18:02:09",350,180,1,3,1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_Print(1,1,1);
		
		if(state!=BPLA_OK) return FALSE;

		if (m_port ==3) {
			state = BPLA_EndDoc();

			if(state != BPLA_OK)
			{
				CString m_info;
				m_info.Format("驱动关闭打印失败，错误值 -- %04d",state);
				SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);	
				return FALSE;
			}

			return TRUE;
		}

		if(m_port == 1 ) return TRUE;
	}	
	//状态查询
	char m_papershort[3],m_ribbionshort[3],m_busy[3],m_pause[3],m_com[3],m_headheat[3],m_headover[3],m_cut[3];
	Sleep(1800);
	state =	BPLA_CheckStatus(m_papershort,m_ribbionshort,m_busy,m_pause,m_com,m_headheat,m_headover,m_cut);
	CString m_info;
	if(state != BPLA_OK)
	{
		m_info = "查询状态失败";
	}
	else
	{
		m_info = "";
		if(m_papershort[0] != 'N')
			m_info += " 缺纸";
		if(m_ribbionshort[0] != 'N')
			m_info += " 缺色带";
		if(m_busy[0] != 'N') 
			m_info += " 解释器忙";
		if(m_pause[0] != 'N')
			m_info += " 暂停";
		if(m_com[0] != 'N')
			m_info += " 通讯错误";
		if(m_headover[0] != 'N')
			m_info += " 打印头抬起";
		if(m_headheat[0] != 'N') 
			m_info += " 打印头过热";
		if(m_cut[0] != 'N') 
			m_info += " 切刀响应超时";
		if(m_info.GetLength()==0) 
			m_info = " 状态正常";
        SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
	}
    if(m_info.Compare(" 状态正常")==0) return TRUE;
	else return FALSE;	
	
}

void CDlldemoDlg::OnRadio6() 
{
	// TODO: Add your control notification handler code here
	m_ctrlbaudrate.EnableWindow(FALSE);	
	m_ctrladdress.EnableWindow(FALSE);
	m_comname.EnableWindow(FALSE);
	m_driver.EnableWindow(FALSE);
	m_timeout.EnableWindow(TRUE);
	
	if(m_port == 0)
	{
		BPLA_CloseCom();//关闭串口
	}
	else if(m_port == 1)
	{
		BPLA_CloseLpt();//关闭并口
	}
	else if(m_port == 2)
	{
		BPLA_CloseUsb();//关闭USB口
	}
	else if(m_port == 3)
	{
		BPLA_ClosePrinterDriver();//关闭驱动
	}
	m_port = 2; 
	m_buttoncloseport.EnableWindow(FALSE);
	m_buttonprint.EnableWindow(FALSE);
	m_buttonstatus.EnableWindow(FALSE);
}

void CDlldemoDlg::OnRadio7() 
{
	// TODO: Add your control notification handler code here
	m_ctrlbaudrate.EnableWindow(FALSE);	
	m_ctrladdress.EnableWindow(FALSE);
	m_comname.EnableWindow(FALSE);
	m_driver.EnableWindow(TRUE);
	m_timeout.EnableWindow(FALSE);
	 
	if(m_port == 0)
	{
		BPLA_CloseCom();//关闭串口
	}
	else if(m_port == 1)
	{
		BPLA_CloseLpt();//关闭并口
	}
	else if(m_port == 2)
	{
		BPLA_CloseUsb();//关闭USB口
	}
	else if(m_port == 3)
	{
		BPLA_ClosePrinterDriver();//关闭驱动
	}
	m_port = 3;
	m_buttoncloseport.EnableWindow(FALSE);
	m_buttonprint.EnableWindow(FALSE);
	m_buttonstatus.EnableWindow(FALSE);
}
