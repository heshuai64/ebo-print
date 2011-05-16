#include "stdafx.h"
#include "Resource.h"
#include "LoginDlg.h"
#include "SKUBarcodeDlg.h"
#include "eBayBOService.h"
#include "HTTPSocket.h"
#include "json.h"
#include "Print.h"


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

eBayBOService::eBayBOService(int iPort, CString cActionPath, CString cService, CString cUser)
{	
	eBayBO = "rich2010.3322.org";
	port = iPort;
	ActionPath = cActionPath;
	Service = cService;
	User = cUser;
}

//DEL void eBayBOService::setEdit(CEdit *p)
//DEL {
//DEL 	pEdit = p;
//DEL }

void eBayBOService::getShippingAddressBySku(CString arg)
{
	HTTPSocket* m_pHTTPSock;
	
	if((m_pHTTPSock = new HTTPSocket(this, eBayBO, port)) == NULL)
	{
		AfxMessageBox ("Failed to allocate client socket! Close and restart app.");
	}

	m_pHTTPSock->Get(ActionPath+Service+arg);

}

ShippingAddress* eBayBOService::getShippingAddress(CString AddressString)
{
	//MessageBox(NULL, AddressString, "AddressString", MB_APPLMODAL);
	if(!AddressString.IsEmpty()){
		int startPos = AddressString.Find('{');
		int endPos = AddressString.Find('}');
		int length = endPos - startPos + 1;

		AddressString = AddressString.Mid(startPos, length);

		char *source = NULL;
		source = (LPSTR)(LPCTSTR) AddressString;
		char *errorPos = 0;
		char *errorDesc = 0;
		int errorLine = 0;
		block_allocator allocator(1 << 10); // 1 KB per block

		//MessageBox(NULL, source, "getShippingAddress2", MB_APPLMODAL);
		//char *source = "{\"RootA\":\"Value in parent node\",\"ChildNode\":\"String Value\"}"; 
		json_value *root = json_parse(source, &errorPos, &errorDesc, &errorLine, &allocator);
		if(root == NULL){
			return NULL;
		}
		ShippingAddress* sa = new ShippingAddress();
		for (json_value *value = root->first_child; value; value = value->next_sibling)
		{
			if (value->name)
			{
				//printf("%s = ", value->name);
				//MessageBox(NULL, value->name, "test", MB_APPLMODAL);
			}

			switch(value->type){
				case JSON_NULL:
					printf("null\n");
				break;

				case JSON_STRING:
					//printf("\"%s\"\n", value->string_value);
					if(strcmp(value->name, "id") == 0){
						sa->shipmentId = value->string_value;
					}

					if(strcmp(value->name, "shipToName") == 0){
						sa->shipToName = value->string_value;
					}

					if(strcmp(value->name, "shipToEmail") == 0){
						sa->shipToEmail = value->string_value;
					}

					if(strcmp(value->name, "shipToAddressLine1") == 0){
						sa->shipToAddressLine1 = value->string_value;
					}

					if(strcmp(value->name, "shipToAddressLine2") == 0){
						sa->shipToAddressLine2 = value->string_value;
					}

					if(strcmp(value->name, "shipToCity") == 0){
						sa->shipToCity = value->string_value;
					}

					if(strcmp(value->name, "shipToStateOrProvince") == 0){
						sa->shipToStateOrProvince = value->string_value;
					}

					if(strcmp(value->name, "shipToPostalCode") == 0){
						sa->shipToPostalCode = value->string_value;
					}

					if(strcmp(value->name, "shipToCountry") == 0){
						sa->shipToCountry = value->string_value;
					}

					if(strcmp(value->name, "shipToPhoneNo") == 0){
						sa->shipToPhoneNo = value->string_value;
					}

				break;

				case JSON_INT:
					//printf("%d\n", value->int_value);
				break;

				case JSON_FLOAT:
					//printf("%f\n", value->float_value);
				break;

				case JSON_BOOL:
					//printf(value->int_value ? "true\n" : "false\n");
				break;
			}
		}
		
		value = NULL;
		root = NULL;
		return sa;
	}else{
		return NULL;
	}
}


void eBayBOService::login(CString user, CString password)
{
	HTTPSocket* m_pHTTPSock;
	
	if((m_pHTTPSock = new HTTPSocket(this, eBayBO, port)) == NULL)
	{
		AfxMessageBox ("Failed to allocate client socket! Close and restart app.");
	}

	m_pHTTPSock->Get(ActionPath+Service+"&user="+user+"&password="+password);
}

BOOL eBayBOService::printShippingAddress(ShippingAddress* sa)
{
	//为了准确判断数据发送成功与否，建议对于每个调用的函数均检查其返回值。
	//具体函数的返回值请参考DLL的说明文档。
    //*********驱动启动打印
	int state1 = BPLA_StartDoc();
	if(state1 != BPLA_OK)
	{
		CString m_info;
		m_info.Format("驱动启动打印失败，错误值 -- %04d",state1);
		//SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
		AfxMessageBox (m_info);
		return FALSE;
	}
	
	//AfxMessageBox ("test1");
	//int state = BPLA_SetPaperLength(600,0);//对于标签纸，则不需要这个函数
	//if(state!=BPLA_OK) return FALSE; 
	int state = BPLA_SetAllRotate(1);
	if(state!=BPLA_OK) {
		AfxMessageBox ("BPLA_SetAllRotate");
		return FALSE; 
	}

	state = BPLA_StartArea(0,900,0,0,0,0,0,0);
	if(state!=BPLA_OK) {
		AfxMessageBox ("BPLA_StartArea");
		return FALSE;
	}

	//AfxMessageBox ("test2");
	//char* shipToName = "Attn:";
	//strcat(shipToName, sa->shipToName);
	state = BPLA_PrintText(sa->shipToName,2,320,1,16,1,1,"000",0,0);
	//state = BPLA_PrintTruetype(sa->shipToName,2,320,"黑体",30,0);
	if(state!=BPLA_OK) {
		AfxMessageBox ("shipToName");
		return FALSE;
	}
	//AfxMessageBox ("test3");

	state = BPLA_PrintText(sa->shipToAddressLine1,2,280,1,16,1,1,"000",0,0);
	//state = BPLA_PrintTruetype(sa->shipToAddressLine1,2,280,"黑体",30,0);
	if(state!=BPLA_OK) {
		AfxMessageBox ("shipToAddressLine1");
		return FALSE;
	}
	
	//AfxMessageBox (strlen(sa->shipToAddressLine2));
	if(strlen(sa->shipToAddressLine2) > 1){
		state = BPLA_PrintText(sa->shipToAddressLine2,2,240,1,16,1,1,"000",0,0);
		//state = BPLA_PrintTruetype(sa->shipToAddressLine2,2,240,"黑体",30,0);
		if(state!=BPLA_OK) {
			AfxMessageBox ("shipToAddressLine2");
			return FALSE;
		}
	}
	
	state = BPLA_PrintText(sa->shipToCity,2,200,1,16,1,1,"000",0,0);
	//state = BPLA_PrintTruetype(sa->shipToCity,2,200,"黑体",30,0);
	if(state!=BPLA_OK) {
		AfxMessageBox ("shipToCity");
		return FALSE;
	}
	
	state = BPLA_PrintText(strcat(strcat(sa->shipToStateOrProvince, ", "), sa->shipToPostalCode),2,160,1,16,1,1,"000",0,0);
	//state = BPLA_PrintTruetype(strcat(strcat(sa->shipToStateOrProvince, ", "), sa->shipToPostalCode),2,160,"黑体",30,0);
	if(state!=BPLA_OK) {
		AfxMessageBox ("shipToStateOrProvince, shipToPostalCode");
		return FALSE;
	}
	
	state = BPLA_PrintText(sa->shipToCountry,2,120,1,16,1,1,"000",0,0);
	//state = BPLA_PrintTruetype(sa->shipToCountry,2,120,"黑体",30,0);
	if(state!=BPLA_OK) {
		AfxMessageBox ("shipToCountry");
		return FALSE;
	}
	
	if(strlen(sa->shipToPhoneNo) > 1){
		state = BPLA_PrintText(strcat("Tel:", sa->shipToPhoneNo),2,80,1,16,1,1,"000",0,0);
		//state = BPLA_PrintTruetype(sa->shipToPhoneNo,2,80,"黑体",30,0);
		if(state!=BPLA_OK) {
			AfxMessageBox ("shipToPhoneNo");
			return FALSE;
		}
	}

	state = BPLA_PrintBarcode(sa->shipmentId,470,5,1,4,80,4,2,"000");
	if(state!=BPLA_OK) {
		AfxMessageBox ("shipmentId");
		return FALSE;
	}

	state = BPLA_Print(1,1,1);
	if(state!=BPLA_OK) {
		AfxMessageBox ("BPLA_Print");
		return FALSE;
	}

	state1 = BPLA_EndDoc();
	if(state1 != BPLA_OK)
	{
		CString m_info;
		m_info.Format("驱动关闭打印失败，错误值 -- %04d",state1);
		//SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);	
		AfxMessageBox (m_info);
		return FALSE;
	}
	
	return TRUE;
}

CString eBayBOService::checkLoginUser(CString LoginResult)
{

	int startPos = LoginResult.Find('{');
	int endPos = LoginResult.Find('}');
	int length = endPos - startPos + 1;
	LoginResult = LoginResult.Mid(startPos, length);

	char *source = NULL;
	source = (LPSTR)(LPCTSTR) LoginResult;
	char *errorPos = 0;
	char *errorDesc = 0;
	int errorLine = 0;
	block_allocator allocator(1 << 10); // 1 KB per block
	//MessageBox(NULL, source, "LoginResult", MB_APPLMODAL);

	//char *source = "{\"RootA\":\"Value in parent node\",\"ChildNode\":\"String Value\"}"; 
	json_value *root = json_parse(source, &errorPos, &errorDesc, &errorLine, &allocator);
	if(root == NULL){
		return "";
	}
	
	for (json_value *value = root->first_child; value; value = value->next_sibling)
	{
		switch(value->type){
			case JSON_NULL:
				printf("null\n");
			break;

			case JSON_STRING:
				//printf("\"%s\"\n", value->string_value);
				if(strcmp(value->name, "user") == 0){
					return value->string_value;
				}
			break;

			case JSON_INT:
				//printf("%d\n", value->int_value);
			break;

			case JSON_FLOAT:
				//printf("%f\n", value->float_value);
			break;

			case JSON_BOOL:
				//printf(value->int_value ? "true\n" : "false\n");
				if(strcmp(value->name, "success") == 0){
					if(!value->string_value){
						return "";
					}
				}
			break;
		}
	}
	
	value = NULL;
	root = NULL;
	return "";
}

void eBayBOService::syncShipmentPrintStatus(CString shipmentId)
{
	HTTPSocket* m_pHTTPSock;

	if((m_pHTTPSock = new HTTPSocket(this, "rich2010.3322.org", 8888)) == NULL)
	{
		AfxMessageBox ("Failed to allocate client socket! Close and restart app.");
	}

	m_pHTTPSock->Get("/eBayBO/service.php?action=syncShipmentPrintStatus&shipmentId="+shipmentId+"&by="+User);
}

void eBayBOService::processReceive(CString c_data)
{
	if(Service.Compare("getShippingAddressBySku") == 0)
	{
		//MessageBox(NULL, c_data, "getShippingAddressBySku", MB_APPLMODAL);
		ShippingAddress* sa = getShippingAddress(c_data);
		if(sa != NULL){
			if(printShippingAddress(sa))
			{
				syncShipmentPrintStatus(sa->shipmentId);
			}
		}
		delete sa;
	}else if(Service.Compare("remoteLogin") == 0)
	{
		//MessageBox(NULL, c_data, "remoteLogin", MB_APPLMODAL);
		CString user = checkLoginUser(c_data);
		if(user.GetLength() > 2){
			((CLoginDlg*)m_pDlg)->SetCurrencyUser(user);
		}
	}else if(Service.Compare("syncShipmentPrintStatus") == 0)
	{
		
	}else if(Service.Compare("getSkuInfo") == 0)
	{
		//MessageBox(NULL, c_data, "getSkuInfo", MB_APPLMODAL);
		SkuInfo* si = getSkuInfo(c_data);
		if(si != NULL){
			//AfxMessageBox (si->chineseTitle);
			CString title = CString(si->chineseTitle);
			CString stock = CString(si->stock);
			((CSKUBarcodeDlg*)m_pDlg)->setSkuInfo(title, stock);
		}
		delete si;
	}
}

void eBayBOService::getSkuInfoBySku(CString sku)
{
	HTTPSocket* m_pHTTPSock;
	
	if((m_pHTTPSock = new HTTPSocket(this, eBayBO, port)) == NULL)
	{
		AfxMessageBox ("Failed to allocate client socket! Close and restart app.");
	}

	m_pHTTPSock->Get(ActionPath+Service+"&data="+sku);
}

SkuInfo* eBayBOService::getSkuInfo(CString SkuInfoString)
{
	int startPos = SkuInfoString.Find('{');
	int endPos = SkuInfoString.Find('}');
	int length = endPos - startPos + 1;
	SkuInfoString = SkuInfoString.Mid(startPos, length);

	char *source = NULL;
	source = (LPSTR)(LPCTSTR) SkuInfoString;
	char *errorPos = 0;
	char *errorDesc = 0;
	int errorLine = 0;
	block_allocator allocator(1 << 10); // 1 KB per block
	//MessageBox(NULL, source, "getSkuInfo", MB_APPLMODAL);

	//char *source = "{\"RootA\":\"Value in parent node\",\"ChildNode\":\"String Value\"}"; 
	json_value *root = json_parse(source, &errorPos, &errorDesc, &errorLine, &allocator);
	if(root == NULL){
		return false;
	}
	
	SkuInfo* si = new SkuInfo();
	for (json_value *value = root->first_child; value; value = value->next_sibling)
	{
		switch(value->type){
			case JSON_NULL:
				printf("null\n");
			break;

			case JSON_STRING:
				if(strcmp(value->name, "skuTitle") == 0){
					si->title = value->string_value;
				}

				if(strcmp(value->name, "skuChineseTitle") == 0){
					//si->chineseTitle = value->string_value;
					si->chineseTitle = (LPSTR)(LPCTSTR) UTF8ToUnicode(value->string_value);
				}

				if(strcmp(value->name, "skuCost") == 0){
					si->cost = value->string_value;
				}

				if(strcmp(value->name, "skuWeight") == 0){
					si->weight = value->string_value;
				}

				if(strcmp(value->name, "skuStock") == 0){
					si->stock = value->string_value;
				}

				if(strcmp(value->name, "locatorNumber") == 0){
					si->locatorNumber = value->string_value;
				}
				//printf("\"%s\"\n", value->string_value);
			break;

			case JSON_INT:
				//printf("%d\n", value->int_value);
			break;

			case JSON_FLOAT:
				//printf("%f\n", value->float_value);
			break;

			case JSON_BOOL:
				//printf(value->int_value ? "true\n" : "false\n");
			break;
		}
	}
	
	value = NULL;
	root = NULL;
	return si;
}

BOOL eBayBOService::printSkuBarcode(SkuInfo* si)
{
	int state1 = BPLA_StartDoc();
	if(state1 != BPLA_OK)
	{
		CString m_info;
		m_info.Format("驱动启动打印失败，错误值 -- %04d",state1);
		//SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);
		AfxMessageBox (m_info);
		return FALSE;
	}
	
	//int state = BPLA_SetPaperLength(600,0);//对于标签纸，则不需要这个函数
	//if(state!=BPLA_OK) return FALSE; 
	int state = BPLA_SetAllRotate(1);
	if(state!=BPLA_OK) {
		AfxMessageBox ("BPLA_SetAllRotate");
		return FALSE; 
	}

	for(int i=0;i<si->printNum;i++){
		state = BPLA_StartArea(0,900,0,0,0,0,0,0);
		if(state!=BPLA_OK) {
			AfxMessageBox ("BPLA_StartArea");
			return FALSE;
		}

		state = BPLA_PrintTruetype(si->id,2,320,"黑体",30,0);
		if(state!=BPLA_OK) {
			AfxMessageBox ("id");
			return FALSE;
		}
		
		//char* t = g_f_wctou8(t, (wchar_t) si->chineseTitle);
		//(LPSTR)(LPCTSTR) UTF8ToUnicode(si->chineseTitle)
		state = BPLA_PrintTruetype(si->chineseTitle,2,280,"黑体",30,0);
		if(state!=BPLA_OK) {
			AfxMessageBox ("chineseTitle");
			return FALSE;
		}

		//AfxMessageBox (si->id);
		state = BPLA_PrintBarcode(si->id,470,10,1,0,80,4,2,"000");
		if(state!=BPLA_OK) {
			AfxMessageBox ("id");
			return FALSE;
		}

		state = BPLA_Print(1,1,1);
		if(state!=BPLA_OK) {
			AfxMessageBox ("BPLA_Print");
			return FALSE;
		}
	}

	state1 = BPLA_EndDoc();
	if(state1 != BPLA_OK)
	{
		CString m_info;
		m_info.Format("驱动关闭打印失败，错误值 -- %04d",state1);
		//SetDlgItemText(IDC_STATICPRINTSTATUS,m_info);	
		AfxMessageBox (m_info);
		return FALSE;
	}

	return TRUE;
}

void eBayBOService::SetParentDlg(CDialog *pDlg)
{
	m_pDlg=pDlg;
}

CString eBayBOService::UTF8ToUnicode(char* UTF8)
{
	int dwUnicodeLen;        //转换后Unicode的长度
	WCHAR *pwText;           //保存Unicode的指针
	CString strUnicode;        //返回值
	//获得转换后的长度，并分配内存
	dwUnicodeLen = MultiByteToWideChar(CP_UTF8,0,UTF8,-1,NULL,0);
	pwText = new WCHAR[dwUnicodeLen];
	if (!pwText)
	{
	 return strUnicode;
	}
	//转为Unicode
	MultiByteToWideChar(CP_UTF8,0,UTF8,-1,pwText,dwUnicodeLen);
	strUnicode = CString(pwText);
	//AfxMessageBox (strUnicode);
	//转为CString
	//strUnicode.Format(_T("%s"),pwText);
	//清除内存
	delete []pwText;
	//返回转换好的Unicode字串
	return strUnicode;
}
