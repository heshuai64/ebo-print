struct ShippingAddress {
	char shipToName[50];
	char shipToEmail[150];
	char shipToAddressLine1[250];
	char shipToAddressLine2[50];
	char shipToCity[30];
	char shipToStateOrProvince[50];
	char shipToPostalCode[9];
	char shipToCountry[50];
	char shipToPhoneNo[50];
};

class eBayBOService
{
public:
	eBayBOService(CString, CString);

	CString ActionPath;
	CString Service;
	void getShippingAddressBySku(CString);
	ShippingAddress* getShippingAddress(CString);
};

