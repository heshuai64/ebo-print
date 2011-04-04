#include "stdafx.h"
#include "HTTPSocket.h"
#include "dlldemo.h"
#include "dlldemoDlg.h"

HTTPSocket::HTTPSocket(CDialog* pDlg, CString strURL, int nport)
{
	m_pDlg = pDlg;
	URL = strURL;
	Port = nport;

	if (!HTTPSocket::Create())
	{
		wsprintf(m_szError, "Failed to create client socket: %d! Close and restart app.", HTTPSocket::GetLastError());
		AfxMessageBox (m_szError);
		return;
	}

	HTTPSocket::Connect(URL, Port);
}

void HTTPSocket::Get(CString StrService)
{
	CString StrMessage = "GET " + StrService + " HTTP/1.1\r\n\r\n";
	int sent;
	sent = HTTPSocket::Send(StrMessage, StrMessage.GetLength());
}

void HTTPSocket::OnAccept(int nErrorCode) 
{
	CAsyncSocket::OnAccept(nErrorCode);
}

void HTTPSocket::OnClose(int nErrorCode) 
{
	((CDlldemoDlg*)m_pDlg)->m_pHTTPSock = NULL;
	CAsyncSocket::OnClose(nErrorCode);
}

void HTTPSocket::OnConnect(int nErrorCode) 
{
	CAsyncSocket::OnConnect(nErrorCode);
}

void HTTPSocket::OnOutOfBandData(int nErrorCode) 
{
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void HTTPSocket::OnReceive(int nErrorCode) 
{
	char *pBuf = new char[1025];
	int iBuf = 1024;
	int iRcvd;

	iRcvd = HTTPSocket::Receive(pBuf, iBuf);
	MessageBox(NULL, pBuf, "test", MB_APPLMODAL);

	CAsyncSocket::OnReceive(nErrorCode);
}

void HTTPSocket::OnSend(int nErrorCode) 
{
	CAsyncSocket::OnSend(nErrorCode);
}

int HTTPSocket::Receive(void* lpBuf, int nBufLen, int nFlags) 
{
	return CAsyncSocket::Receive(lpBuf, nBufLen, nFlags);
}

int HTTPSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	return CAsyncSocket::Send(lpBuf, nBufLen, nFlags);
}

void HTTPSocket::Post()
{

}

