// CChessUI.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "CChessUI.h"
#include "CChessUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCChessUIApp

BEGIN_MESSAGE_MAP(CCChessUIApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCChessUIApp ����

CCChessUIApp::CCChessUIApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCChessUIApp ����

CCChessUIApp theApp;


// CCChessUIApp ��ʼ��

BOOL CCChessUIApp::InitInstance()
{
	m_haccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�

	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CCChessUIDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL CCChessUIApp::ProcessMessageFilter(int code, LPMSG lpMsg)
{
	if ( m_haccel )
	{
		if ( ::TranslateAccelerator(m_pMainWnd->m_hWnd, m_haccel, lpMsg) )
			return TRUE;
	}
	return CWinApp::ProcessMessageFilter(code, lpMsg);
}