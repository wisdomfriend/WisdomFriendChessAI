// SET.cpp : 实现文件
//

#include "stdafx.h"
#include "CChessUI.h"
#include "SET.h"


// CSET 对话框

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


// CSET 消息处理程序
