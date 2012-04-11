#pragma once

// CListenSocket command target

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	CPtrList		m_ptrClientSocketList;
	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pClient);
	void SendChatDataAll(TCHAR* pszMessage);
	void SendMsg(CString pszMessage, int len);
//	void SendMsg(TCHAR *pszMessage, int len);

};


