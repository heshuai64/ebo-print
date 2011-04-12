#include "stdafx.h"
#include "eBayBOService.h"
#include "HTTPSocket.h"
//#include "dlldemo.h"
//#include "dlldemoDlg.h"

HTTPSocket::HTTPSocket(eBayBOService* service, CString strHost, int nport)
{
	pService = service;
	Host = strHost;
	Port = nport;

	if (!HTTPSocket::Create())
	{
		wsprintf(m_szError, "Failed to create client socket: %d! Close and restart app.", HTTPSocket::GetLastError());
		AfxMessageBox (m_szError);
		return;
	}

	if (!HTTPSocket::Connect(Host, Port))
	{
		wsprintf(m_szError, "Failed to connect: %d.", HTTPSocket::GetLastError());
		AfxMessageBox (m_szError);
		HTTPSocket::Close();
		return;
	}
}

HTTPSocket::~HTTPSocket()
{
}


void HTTPSocket::Get(CString StrService)
{
	char StrPort[5];
	_itoa(Port, StrPort, 10);
	CString StrMessage = "GET " + StrService + " HTTP/1.1\r\n";
	StrMessage += CString("Host: ") + Host + ":" + StrPort + "\r\n\r\n";
	//int sent;
	AfxMessageBox(StrMessage);
	if (HTTPSocket::Send(StrMessage, StrMessage.GetLength()) == SOCKET_ERROR)
	{
		wsprintf(m_szError, "Failed to send on client socket: %d", HTTPSocket::GetLastError());
		AfxMessageBox (m_szError);
		HTTPSocket::Close();
		return;
	}
}

void HTTPSocket::OnAccept(int nErrorCode) 
{
	CSocket::OnAccept(nErrorCode);
}

void HTTPSocket::OnClose(int nErrorCode) 
{
	//((CDlldemoDlg*)m_pDlg)->m_pHTTPSock = NULL;
	CSocket::OnClose(nErrorCode);
}

void HTTPSocket::OnConnect(int nErrorCode) 
{
	CSocket::OnConnect(nErrorCode);
}

void HTTPSocket::OnOutOfBandData(int nErrorCode) 
{
	CSocket::OnOutOfBandData(nErrorCode);
}

void HTTPSocket::OnReceive(int nErrorCode) 
{
	char *pBuf = new char[1025];
	int iBuf = 1024;
	int iRcvd;

	iRcvd = HTTPSocket::Receive(pBuf, iBuf);
	pService->getShippingAddress(pBuf);

	CSocket::OnReceive(nErrorCode);
}

void HTTPSocket::OnSend(int nErrorCode) 
{
	CSocket::OnSend(nErrorCode);
}

int HTTPSocket::Receive(void* lpBuf, int nBufLen, int nFlags) 
{
	return CSocket::Receive(lpBuf, nBufLen, nFlags);
}

int HTTPSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	return CSocket::Send(lpBuf, nBufLen, nFlags);
}

void HTTPSocket::Post()
{

}

