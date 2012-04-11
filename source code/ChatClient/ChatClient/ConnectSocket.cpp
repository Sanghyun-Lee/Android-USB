// ConnectSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ConnectSocket.h"
#include "ChatClientDlg.h"

// CConnectSocket

CConnectSocket::CConnectSocket()
{
}

CConnectSocket::~CConnectSocket()
{
}


// CConnectSocket member functions

void CConnectSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR: Disconnected from server!"));
	::PostQuitMessage(0);
}

void CConnectSocket::OnReceive(int nErrorCode)
{
	TCHAR szBuffer[4096];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	if(Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		CChatClientDlg* pMain = (CChatClientDlg*)AfxGetMainWnd();
		pMain->m_List.AddString(szBuffer);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() -1);
	}

	CSocket::OnReceive(nErrorCode);
}
