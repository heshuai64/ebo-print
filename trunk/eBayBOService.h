struct ShippingAddress {
	char* shipmentId;
	char* shipToName;
	char* shipToEmail;
	char* shipToAddressLine1;
	char* shipToAddressLine2;
	char* shipToCity;
	char* shipToStateOrProvince;
	char* shipToPostalCode;
	char* shipToCountry;
	char* shipToPhoneNo;
};

struct SkuInfo {
	char* id;
	char* title;
	char* chineseTitle;
	char* cost;
	char* weight;
	char* stock;
	char* locatorNumber;
	int printNum;
};

class eBayBOService
{
public:
	CString eBayBO;
	int port;
	CString ActionPath;
	CString Service;
	CDialog* m_pDlg;

	eBayBOService(int, CString, CString);
	void SetParentDlg(CDialog *pDlg);
	void processReceive(CString);
	void login(CString, CString);
	BOOL checkLoginUser(CString);
	void getShippingAddressBySku(CString);
	ShippingAddress* getShippingAddress(CString);
	BOOL printShippingAddress(ShippingAddress*);
	void syncShipmentPrintStatus(CString);
	void getSkuInfoBySku(CString);
	SkuInfo* getSkuInfo(CString);
	BOOL printSkuBarcode(SkuInfo* si);
	CString UTF8ToUnicode(char*);
};
