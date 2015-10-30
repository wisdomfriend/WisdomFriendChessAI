#pragma once


// CSET 对话框

class CSET : public CDialog
{
	DECLARE_DYNAMIC(CSET)

public:
	CSET(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSET();

// 对话框数据
	enum { IDD = IDD_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
