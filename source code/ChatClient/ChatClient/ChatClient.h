
// ChatClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CChatClientApp:
// �� Ŭ������ ������ ���ؼ��� ChatClient.cpp�� �����Ͻʽÿ�.
//

class CChatClientApp : public CWinAppEx
{
public:
	CChatClientApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CChatClientApp theApp;