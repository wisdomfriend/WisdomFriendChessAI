// SET.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CChessUI.h"
#include "SET.h"


// CSET �Ի���

IMPLEMENT_DYNAMIC(CSET, CDialog)
CSET::CSET(CWnd* pParent /*=NULL*/)
	: CDialog(CSET::IDD, pParent)
{
}

CSET::~CSET()
{
}

void CSET::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSET, CDialog)
END_MESSAGE_MAP()


// CSET ��Ϣ�������
