
// TCPClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTCPClientApp:
// �� Ŭ������ ������ ���ؼ��� TCPClient.cpp�� �����Ͻʽÿ�.
//

class CTCPClientApp : public CWinApp
{
public:
	CTCPClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTCPClientApp theApp;