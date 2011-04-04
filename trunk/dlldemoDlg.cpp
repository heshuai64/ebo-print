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
	
	//********��ʼ��Ĭ������
	SetDlgItemText(IDC_COMBOBAUDRATE,"ѡ������");
	m_ctrlbaudrate.SetCurSel (3);
	m_ctrladdress.SetCurSel(0);
	m_comname.SetCurSel(0);
	m_drstr = "BTP-2300T2(S)";
	m_time = 1000;
	OnRadio4();
	LoadDll();
	
	CString m_version = "";
	m_version.Format("һ��������DLL�汾��-----%d",BPLA_GetVersion());
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
    SetDlgItemText(IDC_EDIT1,"ѡ��TRUETYPE�����ӡ���������ϴ���ʹ�ò��ڻ�USB��ͨѶ��");	
	HBITMAP m_hbmp;
	m_hbmp = (HBITMAP)LoadImage(NULL,"WaterWay.bmp",IMAGE_BITMAP,300,200,LR_DEFAULTSIZE|LR_SHARED|LR_LOADFROMFILE);
	m_ctrlimage.SetBitmap(m_hbmp);
	m_label = 0;
}

void CDlldemoDlg::OnRadio5() 
{
    SetDlgItemText(IDC_EDIT1,"ѡ���ڲ������ӡ���ڲ�֧�ֵ�ASCII�����干23�֣������Խ��ⲿ�ֿ����ص�FLASH����Ϊ�ڲ�����ʹ�á�");
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
		BPLA_CloseCom();//�رմ���
	}
	else if(m_port == 1)
	{
		BPLA_CloseLpt();//�رղ���
	}
	else if(m_port == 2)
	{
		BPLA_CloseUsb();//�ر�USB��
	}
	else if(m_port == 3)
	{
		BPLA_ClosePrinterDriver();//�ر�����
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
		BPLA_CloseCom();//�رմ���
	}
	else if(m_port == 1)
	{
		BPLA_CloseLpt();//�رղ���
	}
	else if(m_port == 2)
	{
		BPLA_CloseUsb();//�ر�USB��
	}
	else if(m_port == 3)
	{
		BPLA_ClosePrinterDriver();//�ر�����
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
	//case 0:state = BPLA_OpenCom(comnamestr,m_baudrate,1);break;  //�򿪴��ڡ�BPLA_OpenCom����ʵ�ִ򿪴��ڣ����м�⴮�ڡ�
    case 0:state = BPLA_OpenComEx(comnamestr,m_baudrate,1,m_time);break;  //BPLA_OpenComEx����ʵ�ִ򿪴��ڣ�������⴮�ڡ�
	case 1:state = BPLA_OpenLpt(m_address,m_time);break;           //�򿪲���
	case 2:state = BPLA_OpenUsb();break;                         //��USB�ڡ�
	//case 2:state = BPLA_OpenUsbByID(152);break;                //BPLA_OpenUsbByID����ͨ���ڲ�ID�Ŵ�USB�ڣ����ڶ�̨USB�豸ͬʱ����ʶ����á�
	case 3:state = BPLA_OpenPrinterDriver(driverstr);            //������
	}	
	if(state == BPLA_OK)
	{
		int state1;
		if(m_port == 2)//usb��ʱ���ö˿ڳ�ʱ
		{
			int timeout;
			timeout = m_time;
			state1 = BPLA_SetTimeOut(timeout);
			if(state1 != BPLA_OK)
			{
				CString m_info;
				m_info.Format("���ö˿ڳ�ʱ���󣬴���ֵ -- %04d",state);
				SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
				m_buttoncloseport.EnableWindow(FALSE);
				m_buttonprint.EnableWindow(FALSE);
				m_buttonstatus.EnableWindow(FALSE);
				return;
			}
		}
		if(m_port == 3)
		{
			SetDlgItemText(IDC_STATICPRINTSTATUS,"��������ȷ");
			m_buttoncloseport.EnableWindow(TRUE);
			m_buttonprint.EnableWindow(TRUE);
			if(m_port !=3) m_buttonstatus.EnableWindow(TRUE);
			else m_buttonstatus.EnableWindow(FALSE);
			return;
		}				
		SetDlgItemText(IDC_STATICPRINTSTATUS,"�˿ڴ���ȷ");
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
			m_info.Format("�����򿪴��󣬴���ֵ -- %04d",state);
			SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
			m_buttoncloseport.EnableWindow(FALSE);
			m_buttonprint.EnableWindow(FALSE);
			m_buttonstatus.EnableWindow(FALSE);
			return;
		}
		else
		{
			CString m_info;
			m_info.Format("�˿ڴ򿪴��󣬴���ֵ -- %04d",state);
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
		BPLA_CloseCom();//�رմ���
	}
	else if(m_port == 1)
	{
		BPLA_CloseLpt();//�رղ���
	}
	else if(m_port == 2)
	{
		BPLA_CloseUsb();//�ر�USB��
	}
	else if(m_port == 3)
	{
		BPLA_ClosePrinterDriver();//�ر�����
		SetDlgItemText(IDC_STATICPRINTSTATUS,"�����ر�");
		m_buttonprint.EnableWindow(FALSE);
		m_buttoncloseport.EnableWindow(FALSE);
		m_buttonstatus.EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}	
	
	SetDlgItemText(IDC_STATICPRINTSTATUS,"�˿ڹر�");
	m_buttonprint.EnableWindow(FALSE);
	m_buttoncloseport.EnableWindow(FALSE);
	m_buttonstatus.EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CDlldemoDlg::OnButtonprint() 
{
	//���飺�û���ʹ��ʱ�����Ҳ������������ӡ�Ĳ�����Ϊһ���������д���
	//�ϲ������ݴ˺����ķ���ֵ�жϴ�ӡ�ɹ�����������ӷ���ά����
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
		mm1.Format(" ��ӡ�ɹ�-%04dms",end-start);
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
			SetDlgItemText(IDC_STATICPRINTSTATUS," ��ӡʧ��");
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
	//״̬��ѯ
	char m_papershort[3],m_ribbionshort[3],m_busy[3],m_pause[3],m_com[3],m_headheat[3],m_headover[3],m_cut[3];
	int state =	BPLA_CheckStatus(m_papershort,m_ribbionshort,m_busy,m_pause,m_com,m_headheat,m_headover,m_cut);
	CString m_info;

	if(state != BPLA_OK)
	{
		m_info = "��ѯ״̬ʧ��";
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
			m_info += " ȱֽ";
		if(m_ribbionshort[0] != 'N') 
			m_info += " ȱɫ��";
		if(m_busy[0] != 'N') 
			m_info += " ������æ";
		if(m_pause[0] != 'N') 
			m_info += " ��ͣ";
		if(m_com[0] != 'N')
			m_info += " ͨѶ����";
		if(m_headover[0] != 'N')
			m_info += " ��ӡͷ̧��";
		if(m_headheat[0] != 'N')
			m_info += " ��ӡͷ����";
		if(m_cut[0] != 'N')
			m_info += " �е���Ӧ��ʱ";
		if(m_info.GetLength()==0) 
			m_info = "״̬����";
		m_buttonprint.EnableWindow(TRUE);
		if(m_port != 1 && m_port != 3)
			m_buttonstatus.EnableWindow(TRUE);
		m_buttoncloseport.EnableWindow(TRUE);
		m_buttonopenport.EnableWindow(TRUE);
		m_ctrlcheck.EnableWindow(TRUE);
	}
	SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);	  
}

//ˮ��Ʊ����ȫʹ��TRUETYPE�����ӡ��ͼ��Ϊ�ⲿͼ���ļ�ֱ�Ӵ�ӡ������Ϊ128�롣
//�ŵ㣺�������ѡ������Ĵ�С������ͼ��ȣ�ȱ�㣺�������ϴ󣬲�̫�ʺϴ��ڴ�ӡ��
BOOL CDlldemoDlg::PrintWaterWay()
{
	char m_papershort[3],m_ribbionshort[3],m_busy[3],m_pause[3],m_com[3],m_headheat[3],m_headover[3],m_cut[3];
	
	//Ϊ��׼ȷ�ж����ݷ��ͳɹ���񣬽������ÿ�����õĺ���������䷵��ֵ��
	//���庯���ķ���ֵ��ο�DLL��˵���ĵ���
    //*********����������ӡ
	if(m_port == 3)
	{
		int state1;

		state1 = BPLA_StartDoc();
		if(state1 != BPLA_OK)
		{
			CString m_info;
			m_info.Format("����������ӡʧ�ܣ�����ֵ -- %04d",state1);
			SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
			
			return FALSE;
		}
	}

	int state = BPLA_SetPaperLength(600,0);//���ڱ�ǩֽ������Ҫ�������
	if(state!=BPLA_OK) return FALSE; 
	state = BPLA_SetAllRotate(1);
	if(state!=BPLA_OK) return FALSE; 
	for(int i=0;i<1;i++){
		state = BPLA_StartArea(0,900,0,0,0,0,0,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("A1234567",70,560,"����",26,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("�̸���",570,560,"����",26,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("�к��������޹�˾",220,510,"����",30,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("��Ʊ",90,450,"����",30,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("����:739",60,410,"����",28,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("����B",90,350,"����",30,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("�̺�:",90,240,"����",28,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("123",100,185,"����",28,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("��̨",250,455,"����",40,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintImage("arrow.bmp",380,465,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("����",540,455,"����",40,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("��颵���",250,400,"����",30,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("�̸���վ",500,400,"����",30,0);
		if(state!=BPLA_OK) return FALSE;

		state = BPLA_PrintTruetype("2002���03��20��21:30��",250,350,"����",30,0);
		if(state!=BPLA_OK) return FALSE;
		//���Ŵ�ӡ
		/*
		state = BPLA_PrintMixTextEx("2002���03��20��21:30��",250,350,0,1,"0003","B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		*/
		/*
		state = BPLA_PrintMixText("2002���03��20��21:30��",250,350,350,1,3,"B21",20,40,1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		*/
		

		state = BPLA_PrintTruetype("Ʊ��:109.00Ԫ",350,290,"����",30,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintTruetype("��֪�����յ��δ���Ч",290,250,"����",28,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintBarcode("345268724325578",270,150,1,4,80,4,2,"000");
		if(state!=BPLA_OK) return FALSE;
		//state = BPLA_PrintTruetype("345268724325578",350,120,"Arial",24,0);
		//if(state!=BPLA_OK) return FALSE;
		state = BPLA_Print(1,1,1);
	}
	if(state!=BPLA_OK) return FALSE;

    if(m_port == 3) //����������ӡ���˳�����״̬
	{
		int state1;

		state1 = BPLA_EndDoc();
		if(state1 != BPLA_OK)
		{
			CString m_info;
			m_info.Format("�����رմ�ӡʧ�ܣ�����ֵ -- %04d",state1);
			SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);	
			return FALSE;
		}

		return TRUE;
	}

	if(m_port == 1 || m_port == 3)  //����,��������ѯ״̬
	{
		return TRUE;
	}
	
	//��ӡ���֮��Ӧ�ý���״̬��ѯ����ȷ�ϵ�ǰƱ���Ƿ�������ӡ������
	
	Sleep(1800);//����״̬��ѯ����ʵʱָ�����ӡ���ӽ������ݵ�
	//��ӡ��Ҫһ����ʱ�䣬�����ڴ�Ӧ�ý���һ������ʱ����
	//��֤��ѯ����״̬�ܹ���ӳ��ӡ�ɹ�����ʵ���������
	//��ʱ����Ҫ�û�����Ʊ���������ȷ����
	state =	BPLA_CheckStatus(m_papershort,m_ribbionshort,m_busy,m_pause,m_com,m_headheat,m_headover,m_cut);
	CString m_info;
	if(state != BPLA_OK)
	{
		m_info = "��ѯ״̬ʧ��";
	}
	else
	{
		m_info = "";
		if(m_papershort[0] != 'N') 
			m_info += " ȱֽ";
		if(m_ribbionshort[0] != 'N')
			m_info += " ȱɫ��";
		if(m_busy[0] != 'N')
			m_info += " ������æ";
		if(m_pause[0] != 'N') 
			m_info += " ��ͣ";
		if(m_com[0] != 'N')
			m_info += " ͨѶ����";
		if(m_headover[0] != 'N')
			m_info += " ��ӡͷ̧��";
		if(m_headheat[0] != 'N') 
			m_info += " ��ӡͷ����";
		if(m_cut[0] != 'N')
			m_info += " �е���Ӧ��ʱ";
		if(m_info.GetLength()==0)  
			m_info = " ״̬����";
        SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
	}
    if(m_info.Compare(" ״̬����")==0) return TRUE;
	else return FALSE;
}

//��·Ʊ����ȫʹ���ڲ������Ԥ�����ص���ӡ�������塢ͼ��ȣ�������С���ʺϴ��ںͲ��ڴ�ӡ��
//�ڲ�ASCII�����干23�֣�������Ҫʹ�õ������ͼ����ҪԤ�����ص�FLASH��RAM�У�����ӡʹ�á�
//����FLASH�е��粻��ʧ���ݣ����Խ��齫�����ͼ�����ص�FLASH�С�
BOOL CDlldemoDlg::PrintFreeWay()
{
	//*************����������ӡ
	if(m_port == 3)
	{
		int state1;

		state1 = BPLA_StartDoc();
		if(state1 != BPLA_OK)
		{
			CString m_info;
			m_info.Format("����������ӡʧ�ܣ�����ֵ -- %04d",state1);
			SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
			
			return FALSE;
		}
	}

	int state = BPLA_SetPaperLength(580,0);//���ڱ�ǩֽ������Ҫ�������
	if(state!=BPLA_OK) return FALSE; 
	for(int k=0;k<1;k++){		
		state = BPLA_SetAllRotate(0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_StartArea(0,800,0,0,0,0,0,0);
		if(state!=BPLA_OK) return FALSE;
	
		state = BPLA_PrintPDF("124578963",150,300,1,3,7,0,0,8,5,0,3,9,"000");
		if(state!=BPLA_OK) return FALSE;
		
		//��������32�����ֿ��ڴ˴���ΪB21��35�����ֿ��ڴ˴���ΪB24��ϸ�����뿴ָ����йر�ǩ��ӡ��
		//�����ӡ��˵���Լ�DLL�������˵����
		state = BPLA_PrintOut("���ٹ�·����ͨ��ȯ",300,450,1,"B21",1,1,"000",0,0);
		//���������ڴ�ӡ���ڽ����˷Ŵ󣬵����ڿ���Ӱ�촦���ٶȣ����������û�ʹ�����ַ�ʽ��
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintOut("ʻ��ʱ��",100,180,1,"B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintOut("����",100,100,1,"B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintOut("����",230,100,1,"B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		state = BPLA_PrintOut("����",460,100,1,"B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		//��Ӣ�Ļ��Ŵ�ӡ���������ַ���������
		/*
		state = BPLA_PrintMixTextEx("³D210087",570,100,0,1,"0003","B21",1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		*/
		state = BPLA_PrintMixText("³D210087",570,100,100,1,3,"B21",20,40,1,1,"000",0,0);
		if(state!=BPLA_OK) return FALSE;
		//DLL��û�н�����ָ�����װ�ɺ�����������û�������ʹ�õ�ָ����а�װ��
		//����û�н��а�װ��ָ�������ṩ��BPLA_SendCommand����������з��͡�
		//������Ƿ���ָ���Խ���б�������ͨ���л������ӡ�
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
				m_info.Format("�����رմ�ӡʧ�ܣ�����ֵ -- %04d",state);
				SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);	
				return FALSE;
			}

			return TRUE;
		}

		if(m_port == 1 ) return TRUE;
	}	
	//״̬��ѯ
	char m_papershort[3],m_ribbionshort[3],m_busy[3],m_pause[3],m_com[3],m_headheat[3],m_headover[3],m_cut[3];
	Sleep(1800);
	state =	BPLA_CheckStatus(m_papershort,m_ribbionshort,m_busy,m_pause,m_com,m_headheat,m_headover,m_cut);
	CString m_info;
	if(state != BPLA_OK)
	{
		m_info = "��ѯ״̬ʧ��";
	}
	else
	{
		m_info = "";
		if(m_papershort[0] != 'N')
			m_info += " ȱֽ";
		if(m_ribbionshort[0] != 'N')
			m_info += " ȱɫ��";
		if(m_busy[0] != 'N') 
			m_info += " ������æ";
		if(m_pause[0] != 'N')
			m_info += " ��ͣ";
		if(m_com[0] != 'N')
			m_info += " ͨѶ����";
		if(m_headover[0] != 'N')
			m_info += " ��ӡͷ̧��";
		if(m_headheat[0] != 'N') 
			m_info += " ��ӡͷ����";
		if(m_cut[0] != 'N') 
			m_info += " �е���Ӧ��ʱ";
		if(m_info.GetLength()==0) 
			m_info = " ״̬����";
        SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
	}
    if(m_info.Compare(" ״̬����")==0) return TRUE;
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
		BPLA_CloseCom();//�رմ���
	}
	else if(m_port == 1)
	{
		BPLA_CloseLpt();//�رղ���
	}
	else if(m_port == 2)
	{
		BPLA_CloseUsb();//�ر�USB��
	}
	else if(m_port == 3)
	{
		BPLA_ClosePrinterDriver();//�ر�����
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
		BPLA_CloseCom();//�رմ���
	}
	else if(m_port == 1)
	{
		BPLA_CloseLpt();//�رղ���
	}
	else if(m_port == 2)
	{
		BPLA_CloseUsb();//�ر�USB��
	}
	else if(m_port == 3)
	{
		BPLA_ClosePrinterDriver();//�ر�����
	}
	m_port = 3;
	m_buttoncloseport.EnableWindow(FALSE);
	m_buttonprint.EnableWindow(FALSE);
	m_buttonstatus.EnableWindow(FALSE);
}
