// ListenSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TCPServer.h"
#include "ListenSocket.h"


// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket ��� �Լ�


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	AfxGetMainWnd()->SendMessage(UM_ACCEPT_MESSAGE, (WPARAM)this);

	CSocket::OnAccept(nErrorCode);
}
