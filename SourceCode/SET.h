#pragma once


// CSET �Ի���

class CSET : public CDialog
{
	DECLARE_DYNAMIC(CSET)

public:
	CSET(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSET();

// �Ի�������
	enum { IDD = IDD_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
