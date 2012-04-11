#pragma once

// CClientSocket command target

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	CAsyncSocket*	m_pListenSocket;

	void SetListenSocket(CAsyncSocket* pSocket);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


