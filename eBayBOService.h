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
	CString User;
	CDialog* m_pDlg;
	sqlite3* db;
	CString debug;

	eBayBOService(int, CString, CString, CString);
	void setParentDlg(CDialog *pDlg);
	void setDB(sqlite3* sqliteDB);
	void processReceive(CString);
	void login(CString, CString);
	CString checkLoginUser(CString);
	void getShippingAddressBySku(CString);
	void printShipmentAddressSuccessByShipmentId(CString);
	ShippingAddress* getShippingAddress(CString);
	BOOL printShippingAddress(ShippingAddress*);
	void syncShipmentPrintStatus(CString, CString, CString);
	void getSkuInfoBySku(CString);
	SkuInfo* getSkuInfo(CString);
	BOOL printSkuBarcode(SkuInfo* si);
	CString UTF8ToUnicode(char*);
	void setDebug(CString);
};

