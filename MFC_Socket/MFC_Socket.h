
// MFC_Socket.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFC_SocketApp: 
// �аѾ\��@�����O�� MFC_Socket.cpp
//

class CMFC_SocketApp : public CWinApp
{
public:
	CMFC_SocketApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMFC_SocketApp theApp;