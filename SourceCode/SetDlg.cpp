// SetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CChessUI.h"
#include "SetDlg.h"


// CSetDlg �Ի���

IMPLEMENT_DYNAMIC(CSetDlg, CDialog)
CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
	, m_Depth(4)
{
}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITDepth, m_Depth);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, &CSetDlg::OnDeltaposSpin)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK, &CSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetDlg ��Ϣ�������

void CSetDlg::OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	//AfxMessageBox("aaa");
	*pResult = 0;
}

int CSetDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}

void CSetDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}

void CSetDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	CSpinButtonCtrl * pSpin = (CSpinButtonCtrl *) GetDlgItem(IDC_SPIN);
	pSpin->SetRange(1,10);
	pSpin->SetPos(m_Depth);
	

}

void CSetDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_Depth = (int)GetDlgItemInt(IDC_EDITDepth);

	OnOK();
}
