
// TCPServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTCPServerApp:
// �� Ŭ������ ������ ���ؼ��� TCPServer.cpp�� �����Ͻʽÿ�.
//

class CTCPServerApp : public CWinApp
{
public:
	CTCPServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTCPServerApp theApp;