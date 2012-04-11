// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ClientSocket.h"
#include "ListenSocket.h"
#include "ChatServerDlg.h"


// CClientSocket

CClientSocket::CClientSocket()
{
	m_pListenSocket = NULL;
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket member functions

void CClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket;
}

void CClientSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);

	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
}

void CClientSocket::OnReceive(int nErrorCode)
{
/*
	

	char *strFileName = NULL;
	int nNameLen;

//	Receive(&nNameLen, 4);
//	Receive(strFileName, nNameLen);
	
	DWORD dwRead;	
	TCHAR szBuffer[4096];
	::ZeroMemory(szBuffer, sizeof(szBuffer));
	
	//받아온 메시지가 있으면 CListBox에 출력
	Receive(szBuffer, sizeof(szBuffer));
	CFile targetFile;
	
	targetFile.Open("123.jpeg", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	
	//targetFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	
	do
	{
		dwRead = Receive(szBuffer, 4096);
		targetFile.Write(szBuffer, dwRead);
	} while(dwRead > 0);
	
	AfxMessageBox(_T("download Complete!"));

	//delete data[4096];
	targetFile.Close();
*/	

	CString strTmp = _T(""), strIPAddress = _T("");
	UINT uPortNumber = 0;
	
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	//클라이언트 ip주소와 포트넘버 변수에 저장
	GetPeerName(strIPAddress, uPortNumber);

	//받아온 메시지가 있으면 CListBox에 출력
	if(Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();
		strTmp.Format(_T("[%s:%d] : %s"), strIPAddress, uPortNumber, szBuffer);
		pMain->m_List.AddString(strTmp);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() -1);

		//받은 메시지를 모든 클라이언트에게 전송 >> 지워도 될듯 수정하거나
		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->SendChatDataAll(szBuffer);
	}
	
	CSocket::OnReceive(nErrorCode);
}
