// CChessUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CCChessUIApp:
// �йش����ʵ�֣������ CChessUI.cpp
//

class CCChessUIApp : public CWinApp
{
public:
	CCChessUIApp();

	HACCEL m_haccel;
	
// ��д
	public:
	virtual BOOL InitInstance();
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCChessUIApp theApp;
