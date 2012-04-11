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

	//Accept가 성공하면 클라이언트 리스트에 추가
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

// 받은 메시지를 클라이언트로 전송하는 부분 
// 수정해서 안드로이드쪽 전송으로 변경
void CListenSocket::SendChatDataAll(TCHAR* pszMessage)
{
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;

	//클라이언트 리스트를 반복문을 돌면서 하나씩 전송
	while(pos != NULL)
	{
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if(pClient != NULL)
		{
			pClient->Send(pszMessage, lstrlen(pszMessage) * 2);
		}
	}
}
void CListenSocket::SendMsg(CString pszMessage, int len)
//void CListenSocket::SendMsg(TCHAR *pszMessage, int len)
{
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;

	//클라이언트 리스트를 반복문을 돌면서 하나씩 전송
	if(pos != NULL)
	{
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if(pClient != NULL)
		{
			pClient->Send((LPVOID)(LPCTSTR)pszMessage, len * 2);
		}
	}
}

