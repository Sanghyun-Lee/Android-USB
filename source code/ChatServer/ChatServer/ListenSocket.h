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
	void SendChatDataAll(CString pszMessage);
	void SendMsg(CString pszMessage);
	int StringToTChar(CString string, TCHAR* ch);

};


