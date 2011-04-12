#include "stdafx.h"
#include "eBayBOService.h"
#include "HTTPSocket.h"
#include "json.h"

eBayBOService::eBayBOService(CString cActionPath, CString cService)
{
	ActionPath = cActionPath;
	Service = cService;
}


void eBayBOService::getShippingAddressBySku(CString arg)
{
	HTTPSocket* m_pHTTPSock;
	
	if((m_pHTTPSock = new HTTPSocket(this, "rich2010.3322.org", 8888)) == NULL)
	{
		AfxMessageBox ("Failed to allocate client socket! Close and restart app.");
	}

	m_pHTTPSock->Get(ActionPath+Service+arg);

}

ShippingAddress* eBayBOService::getShippingAddress(CString AddressString)
{
	//MessageBox(NULL, AddressString, "test", MB_APPLMODAL);
	//char *source = "{\"RootA\":\"Value in parent node\",\"ChildNode\":\"String Value\"}"; 
	int pos = AddressString.Find('{');
	//AddressString = AddressString.Left(pos);
	char StrPort[5];
	_itoa(pos, StrPort, 10);
	//AddressString.Right(AddressString.GetLength()-pos)
	//MessageBox(NULL, StrPort, "test", MB_APPLMODAL);
	//_itoa(AddressString.GetLength(), StrPort, 10);
	//MessageBox(NULL, StrPort, "test", MB_APPLMODAL);
	AddressString = AddressString.Right(AddressString.GetLength()-pos);
	MessageBox(NULL, AddressString, "test", MB_APPLMODAL);
	
	char *source = AddressString.GetBuffer( 100 );
	MessageBox(NULL, source, "test", MB_APPLMODAL);
	char *errorPos = 0;
	char *errorDesc = 0;
	int errorLine = 0;
	block_allocator allocator(1 << 10); // 1 KB per block
    
	//char *source = "{\"RootA\":\"Value in parent node\",\"ChildNode\":\"String Value\"}"; 
	json_value *root = json_parse(source, &errorPos, &errorDesc, &errorLine, &allocator);
	for (json_value *value = root->first_child; value; value = value->next_sibling)
	{
			if (value->name)
			{
				//printf("%s = ", value->name);
				MessageBox(NULL, value->name, "test", MB_APPLMODAL);
			}

			switch(value->type)
			{
			case JSON_NULL:
					printf("null\n");
					break;
			case JSON_STRING:
					//printf("\"%s\"\n", value->string_value);
					MessageBox(NULL, value->string_value, "test", MB_APPLMODAL);
					break;
			case JSON_INT:
					printf("%d\n", value->int_value);
					break;
			case JSON_FLOAT:
					printf("%f\n", value->float_value);
					break;
			case JSON_BOOL:
					printf(value->int_value ? "true\n" : "false\n");
					break;
			}
	}
	
	return NULL;
}