#include "stdafx.h"
#include "eBayBOService.h"
#include "HTTPSocket.h"

eBayBOService::eBayBOService()
{

}

void eBayBOService::setActionPath(char* lpactionPath)
{
	strcpy(ActionPath, lpactionPath);
}

void eBayBOService::setService(char* lpservice)
{
	strcpy(Service, lpservice);
}


ShippingAddress* eBayBOService::getShippingAddress()
{
	
	//HTTPSocket* httpSocket = new HTTPSocket("rich2010.3322.org", 8888);
	//setActionPath("/eBayBO/service.php?action=");
	//setService("getShippingAddress");

	//httpSocket->Get(strcat(ActionPath, Service));

	return NULL;
}

