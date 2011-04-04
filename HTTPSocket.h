class HTTPSocket : public CAsyncSocket
{
public:
	CDialog*	m_pDlg;
public:
	CString URL;
	int Port;
	TCHAR	m_szError[255];

	HTTPSocket(CDialog*, CString, int);
	void Get(CString);
	void Post();

public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
};