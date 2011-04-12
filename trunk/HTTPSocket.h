class HTTPSocket : public CSocket
{
public:
	eBayBOService*	pService;
public:
	CString Host;
	int Port;
	TCHAR	m_szError[255];

	HTTPSocket(eBayBOService*, CString, int);
	virtual ~HTTPSocket();

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