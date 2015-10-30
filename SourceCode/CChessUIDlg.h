// CChessUIDlg.h : ͷ�ļ�
//


#pragma once
#include "afxwin.h"
#include "SetDlg.h"


// CCChessUIDlg �Ի���
class CCChessUIDlg : public CDialog
{
// ����
public:
	CCChessUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CCHESSUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	CSetDlg m_SetDlg;

	

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	//afx_msg void OnLbnSelchangeListcchess();
	afx_msg void OnMenuNewGame();
	afx_msg void OnMenuQuit();
	afx_msg void OnAbout();
	afx_msg void OnSetEngine();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedButton2();

public:
	afx_msg void Restart();//////////////////////////////////////////
	
public:	
	CButton cb1;
	CButton cb2;

	//afx_msg void OnUpdateQipan(CCmdUI *pCmdUI);
	int m_Qipan;

	afx_msg void OnstQipan();
	afx_msg void OnUpdatestQipan(CCmdUI *pCmdUI);

	afx_msg void OnsjQipan();
	afx_msg void OnUpdatesjQipan(CCmdUI *pCmdUI);

	afx_msg void OnmtQipan();
	afx_msg void OnUpdatemtQipan(CCmdUI *pCmdUI);

	//afx_msg void OnUpdateQizi(CCmdUI *pCmdUI);
	int m_Qizi;

	afx_msg void OnstQizi();
	afx_msg void OnUpdatestQizi(CCmdUI *pCmdUI);

	afx_msg void OnsjQizi();
	afx_msg void OnUpdatesjQizi(CCmdUI *pCmdUI);

	afx_msg void OnmtQizi();
	afx_msg void OnUpdatemtQizi(CCmdUI *pCmdUI);
	
	//bool m_bPattern;
public:
	bool m_Mode;

	afx_msg void OnNormal();
	afx_msg void OnUpdateNormal(CCmdUI *pCmdUI);

	afx_msg void OnBlind();
	afx_msg void OnUpdateBlind(CCmdUI *pCmdUI);

	
	afx_msg void OnBnClickedButton5();
};

