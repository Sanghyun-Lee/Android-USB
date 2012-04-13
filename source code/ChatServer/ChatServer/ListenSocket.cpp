// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ListenSocket.h"
#include "ClientSocket.h"

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket member functions

void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClient = new CClientSocket;

	//Accept�� �����ϸ� Ŭ���̾�Ʈ ����Ʈ�� �߰�
	if(Accept(*pClient))
	{
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);
	//	AfxMessageBox(_T("Succesed to accept new client!"));
	}
	else
	{
		delete pClient;
		AfxMessageBox(_T("ERROR: Failed to accept new client!"));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

void CListenSocket::CloseClientSocket(CSocket* pClient)
{
	POSITION pos;
	pos = m_ptrClientSocketList.Find(pClient);
	if(pos != NULL)
	{
		if(pClient != NULL)
		{
			pClient->ShutDown();
			pClient->Close();
		}

		m_ptrClientSocketList.RemoveAt(pos);
		delete pClient;
	}
}

// ���� �޽����� Ŭ���̾�Ʈ�� �����ϴ� �κ� 
// �����ؼ� �ȵ���̵��� �������� ����

void CListenSocket::SendChatDataAll(CString pszMessage)
{
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;

	//Ŭ���̾�Ʈ ����Ʈ�� �ݺ����� ���鼭 �ϳ��� ����
	while(pos != NULL)
	{
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if(pClient != NULL)
		{
			pClient->Send(pszMessage, lstrlen(pszMessage) * 2);
		}
	}
}
void CListenSocket::SendMsg(CString pszMessage)
//void CListenSocket::SendMsg(TCHAR *pszMessage, int len)
{
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;
	TCHAR msg[4096];
//	::ZeroMemory(msg, sizeof(msg));

	int len = StringToTChar(pszMessage, msg);
	//Ŭ���̾�Ʈ ����Ʈ�� �ݺ����� ���鼭 �ϳ��� ����
	if(pos != NULL)
	{
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if(pClient != NULL)
		{
		//	pClient->Send((LPVOID)(LPCTSTR)pszMessage, len * 2);
			pClient->Send(msg, len * 2);
		}
	}
}


int CListenSocket::StringToTChar(CString string, TCHAR* ch)
{
	int STR_LENGTH = string.GetLength();
	int i;
	TCHAR a[4096];	
	::ZeroMemory(a, sizeof(a));

	for(i = 0; i < STR_LENGTH ; i++){
		a[i] = (TCHAR)string.GetAt(i);
	}
	a[i] = '\0';

	strcpy(ch, a);

	return i+1;
}