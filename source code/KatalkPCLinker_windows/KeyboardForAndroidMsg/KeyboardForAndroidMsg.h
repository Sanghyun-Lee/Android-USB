
// KeyboardForAndroidMsg.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CKeyboardForAndroidMsgApp:
// �� Ŭ������ ������ ���ؼ��� KeyboardForAndroidMsg.cpp�� �����Ͻʽÿ�.
//

class CKeyboardForAndroidMsgApp : public CWinApp
{
public:
	CKeyboardForAndroidMsgApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CKeyboardForAndroidMsgApp theApp;