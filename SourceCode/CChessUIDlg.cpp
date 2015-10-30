// CChessUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CChessUI.h"
#include "CChessUIDlg.h"

#include ".\cchessuidlg.h"
#include <vector>

#include <atlimage.h>
#include <Mmsystem.h>


#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Winmm.lib")

#include "CChessMove.h"
#include "CChessSearch.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE HMutex;
//bool fPaintOver =false;

#define REDWIN		1
#define BLACKWIN	2
#define NOTEND		0


typedef struct{
	BYTE	CChessBoard[9][10];
	POINT	ptChess[32];
	//POINT	ptPreKuang;
	//POINT	ptCurKuang;

} CCChess;	// �����塢��ԭ�����õ���Ϣ�ṹ


RECT rctPreB,rctCurB;
RECT rctPreR,rctCurR;
///////////////////////////////////////////////////////////
CString str;
POINT ptCFrom, ptCTo;
int nObject;
POINT stPoint;
////////////////////////////////////////////
CCChess	temp;


vector<CCChess> vBackQueue;	//���屣�����
vector<CCChess> vForwardQueue;	//��ԭ�������

vector<CString> vNameQueue;

CWinThread * CThinkingThread;	//�����˼���߳�
bool bThreadOver;

HANDLE hhWnd;	//���ڱ��浱ǰ���ھ��


//---��ʱ���ñ���-----
int Second_a = 0;
int Minute_a = 0;
int Hour_a = 0;
float Second_a2 = 0;

int Second_b = 0;
int Minute_b =0;
int Hour_b =0;
float Second_b2=0;
//------------------------


//----װ��bmp�õı���----
HBITMAP bit;
HDC		MemDC;
HDC		DCBak;
HDC		DCKuang;
int		ww,hh;

int		qipan;
CString qzidir;	
CRect	rect;	
//-------------------------

//�������λ��
POINT ptPreKuang;	
POINT ptCurKuang;

const int NOCHESS =33;

//----������ͼλ�õ������±�----
const int RED_K0 =0;		
const int RED_Sl =1;	
const int RED_Sr =2;	
const int RED_Xl =3;	
const int RED_Xr =4;	
const int RED_Ml =5;	
const int RED_Mr =6;	
const int RED_Jl =7;	
const int RED_Jr =8;	
const int RED_Pl =9;		
const int RED_Pr =10;	
const int RED_B1 =11;		
const int RED_B2 =12;		
const int RED_B3 =13;		
const int RED_B4 =14;	
const int RED_B5 =15;		

const int BLACK_K0 =16;		
const int BLACK_Sl =17;		
const int BLACK_Sr =18;		
const int BLACK_Xl =19;	
const int BLACK_Xr =20;		
const int BLACK_Ml =21;		
const int BLACK_Mr =22;	
const int BLACK_Jl =23;	
const int BLACK_Jr =24;	
const int BLACK_Pl =25;	
const int BLACK_Pr =26;	
const int BLACK_B1 =27;		
const int BLACK_B2 =28;	
const int BLACK_B3 =29;		
const int BLACK_B4 =30;	
const int BLACK_B5 =31;
//----------------------------

CListBox *pLB =NULL;

POINT ptChess[32];//32�����ӵ�����λ��

int nHaveSelected =NOCHESS;	//�û���ѡ���ӣ�λ�ã�

CCHESSMOVE cmMove;	//�߷�

bool fGameover =false;

int WhoseTurn =RED;

enum {STQP,SJQP,MTQP};	//������ʽ

enum {STQZ,SJQZ,MTQZ};	//������ʽ

enum {NORMAL,BLIND};	//����ģʽ


int nNumOfStep =0;	//��¼����



////////////////////////// Function Prototype //////////////////////////////

// ˼���߳�
UINT ThinkingThread(LPVOID pParam);

//����
//inline void CCChessUIDlg::Restart();

//��Ϸ����
inline void GameOver();

//���������λ��ת��Ϊ�ض���������
inline POINT GetThePoint( CPoint point );

//���ض���������ת��ΪCChessBoard�������±�
inline POINT PointToCChessBoard( POINT point );

//��CChessBoard�������±�ת��Ϊ�ض���������
inline POINT CChessBoardToPoint( POINT xyPoint );

//�ж��ض��������ص�����״����������RED_B1��ʽ��NOCHESS
inline int JudgeThePoint( POINT point );

//�ж�nA��nB�Ƿ���ͬһ�����ӣ����Ƿ���true�����򷵻�false
inline bool IsTheSameSide( int nA, int nB );

//�ж��Ƿ���Ϸ�Ѿ���������ʤ����REDWIN����ʤ����BLACKWIN��δ��������NOTEND
inline int IsGameOverUI();


//�ж��߷��Ƿ�Ϸ����Ϸ������棬���Ϸ����ؼ�
inline bool CanMOVE(POINT ptfrom, POINT ptto);
//inline bool HaveMan(POINT ptPosition );
//inline bool isred(POINT ptto);
//inline bool isblack(POINT ptto);

//������������ת��Ϊ�й�����
CString ConvertDigit(int nNum);

//ȡ���ŷ�������
CString GetMoveStr(int nFromX,int nFromY,int nToX,int nToY,int nSourceID);

//װ��bmp
inline BOOL loadbmp(CString cc);

//��͸��������bmp
inline void TransparentBlt2( HDC hdc0,	
					POINT point0,
					int nW0,int nH0,
					HDC hdc1,
					int nX1,int nY1,
					int nW1,int nH1,
					UINT Tcol
					);

///////////////////////////////////////////////////////////////////////////////



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCChessUIDlg �Ի���



CCChessUIDlg::CCChessUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCChessUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCChessUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, cb1);
	DDX_Control(pDX, IDC_BUTTON2, cb2);
}

BEGIN_MESSAGE_MAP(CCChessUIDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	//ON_LBN_SELCHANGE(IDC_LISTCCHESS, OnLbnSelchangeListcchess)
	ON_COMMAND(ID_NewGame, OnMenuNewGame)
	ON_COMMAND(ID_Quit, OnMenuQuit)
	ON_COMMAND(ID_About, OnAbout)
	ON_COMMAND(ID_SetE, OnSetEngine)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)


	//ON_UPDATE_COMMAND_UI_RANGE(ID_st_Qipan, ID_mt_Qipan, OnUpdateQipan)
	//ON_UPDATE_COMMAND_UI_RANGE(ID_st_Qizi, ID_mt_Qizi, OnUpdateQizi)
	
	ON_WM_INITMENUPOPUP()

	ON_COMMAND(ID_Normal, &CCChessUIDlg::OnNormal)
	ON_UPDATE_COMMAND_UI(ID_Normal, &CCChessUIDlg::OnUpdateNormal)

	ON_COMMAND(ID_Blind, &CCChessUIDlg::OnBlind)
	ON_UPDATE_COMMAND_UI(ID_Blind, &CCChessUIDlg::OnUpdateBlind)

	ON_COMMAND(ID_st_Qipan, &CCChessUIDlg::OnstQipan)
	ON_UPDATE_COMMAND_UI(ID_st_Qipan, &CCChessUIDlg::OnUpdatestQipan)

	ON_COMMAND(ID_sj_Qipan, &CCChessUIDlg::OnsjQipan)
	ON_UPDATE_COMMAND_UI(ID_sj_Qipan, &CCChessUIDlg::OnUpdatesjQipan)

	ON_COMMAND(ID_mt_Qipan, &CCChessUIDlg::OnmtQipan)
	ON_UPDATE_COMMAND_UI(ID_mt_Qipan, &CCChessUIDlg::OnUpdatemtQipan)

	ON_COMMAND(ID_st_Qizi, &CCChessUIDlg::OnstQizi)
	ON_UPDATE_COMMAND_UI(ID_st_Qizi, &CCChessUIDlg::OnUpdatestQizi)

	ON_COMMAND(ID_sj_Qizi, &CCChessUIDlg::OnsjQizi)
	ON_UPDATE_COMMAND_UI(ID_sj_Qizi, &CCChessUIDlg::OnUpdatesjQizi)

	ON_COMMAND(ID_mt_Qizi, &CCChessUIDlg::OnmtQizi)
	ON_UPDATE_COMMAND_UI(ID_mt_Qizi, &CCChessUIDlg::OnUpdatemtQizi)

	ON_BN_CLICKED(IDC_BUTTON5, &CCChessUIDlg::OnBnClickedButton5)
END_MESSAGE_MAP()

void CCChessUIDlg::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu)
{
    ASSERT(pPopupMenu != NULL);
    // Check the enabled state of various menu items.

    CCmdUI state;
    state.m_pMenu = pPopupMenu;
    ASSERT(state.m_pOther == NULL);
    ASSERT(state.m_pParentMenu == NULL);

    // Determine if menu is popup in top-level menu and set m_pOther to
    // it if so (m_pParentMenu == NULL indicates that it is secondary popup).
    HMENU hParentMenu;
    if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
        state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
    else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
    {
        CWnd* pParent = this;
           // Child windows don't have menus--need to go to the top!
        if (pParent != NULL &&
           (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
        {
           int nIndexMax = ::GetMenuItemCount(hParentMenu);
           for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
           {
            if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
            {
                // When popup is found, m_pParentMenu is containing menu.
                state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
                break;
            }
           }
        }
    }

    state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
    for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
      state.m_nIndex++)
    {
        state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
        if (state.m_nID == 0)
           continue; // Menu separator or invalid cmd - ignore it.

        ASSERT(state.m_pOther == NULL);
        ASSERT(state.m_pMenu != NULL);
        if (state.m_nID == (UINT)-1)
        {
           // Possibly a popup menu, route to first item of that popup.
           state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
           if (state.m_pSubMenu == NULL ||
            (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
            state.m_nID == (UINT)-1)
           {
            continue;       // First item of popup can't be routed to.
           }
           state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
        }
        else
        {
           // Normal menu item.
           // Auto enable/disable if frame window has m_bAutoMenuEnable
           // set and command is _not_ a system command.
           state.m_pSubMenu = NULL;
           state.DoUpdate(this, FALSE);
        }

        // Adjust for menu deletions and additions.
        UINT nCount = pPopupMenu->GetMenuItemCount();
        if (nCount < state.m_nIndexMax)
        {
           state.m_nIndex -= (state.m_nIndexMax - nCount);
           while (state.m_nIndex < nCount &&
            pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
           {
            state.m_nIndex++;
           }
        }
        state.m_nIndexMax = nCount;
    }
} 

// CCChessUIDlg ��Ϣ�������


BOOL CCChessUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	
	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//HMutex = ::CreateMutex(NULL,FALSE,NULL);
	
	ZeroMemory( &temp, sizeof(temp));
	ZeroMemory(&cmMove, sizeof(cmMove));

	srand( (unsigned)time( NULL ) );	//�����ӣ��Թ���ֵ��������

	MemDC =CreateCompatibleDC(0);
	DCBak =CreateCompatibleDC(0);
	DCKuang =CreateCompatibleDC(0);
	GetWindowRect(rect);

	GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);

	pLB = (CListBox*)GetDlgItem(IDC_LISTCCHESS);


	//��ѡ����������ʽ������ģʽ
	m_Qipan = MTQP;
	qipan =IDB_MTQP;

	m_Qizi  = MTQZ;
	qzidir ="Pic/qizi/mutou/";

    m_Mode= NORMAL;

	//*****************************************
	Restart();
	//*****************************************

	hhWnd = this->m_hWnd;	//ȡ�����ھ��


	//���ű�������

	mciSendString("open wav/bgm.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);

	//mciSendString(L"close bgm", NULL, 0, NULL);

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CCChessUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CCChessUIDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCChessUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//::WaitForSingleObject(HMutex,INFINITE);

		CRect rect;
		GetClientRect( &rect );
		CPaintDC pDC(this);
		CClientDC dc(this);	
		CDC dcbak;
		CBitmap bm;
		CBitmap* bmOld;
		dcbak.CreateCompatibleDC( &pDC);

		bm.LoadBitmap(qipan);

		bmOld=dcbak.SelectObject( &bm );
		pDC.BitBlt(0,0,rect.Width(), rect.Height(),&dcbak,0,0,SRCCOPY);
		dcbak.SelectObject( bmOld );


		//װ�ؿ�
		loadbmp("Pic/Kuang.bmp");			
		SelectObject(DCKuang,bit);
		SetBkMode(DCKuang,TRANSPARENT);
	

		//����
		TransparentBlt2(dc.m_hDC,ptPreKuang,ww,hh,DCKuang,0,0,ww,hh,RGB(255,255,255));
		TransparentBlt2(dc.m_hDC,ptCurKuang,ww,hh,DCKuang,0,0,ww,hh,RGB(255,255,255));


		if(m_Mode == NORMAL)
		{
			//������
			loadbmp(qzidir+"RED_K.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[RED_K0],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"RED_S.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[RED_Sl],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[RED_Sr],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"RED_X.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[RED_Xl],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[RED_Xr],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"RED_M.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[RED_Ml],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[RED_Mr],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"RED_J.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[RED_Jl],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[RED_Jr],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"RED_P.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[RED_Pl],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[RED_Pr],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"RED_B.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[RED_B1],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[RED_B2],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[RED_B3],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[RED_B4],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[RED_B5],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			//������
			loadbmp(qzidir+"BLACK_K.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_K0],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"BLACK_S.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_Sl],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_Sr],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"BLACK_X.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_Xl],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_Xr],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"BLACK_M.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_Ml],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_Mr],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"BLACK_J.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_Jl],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_Jr],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"BLACK_P.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_Pl],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_Pr],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			loadbmp(qzidir+"BLACK_B.bmp");			
			SelectObject(MemDC,bit);
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_B1],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_B2],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_B3],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_B4],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));
			TransparentBlt2(dc.m_hDC,ptChess[BLACK_B5],ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

			
		}
		else
		{
			//��ʾ��ǰΪä��ģʽ
			loadbmp("Pic/Blind.bmp");			
			SelectObject(MemDC,bit);
			POINT ptBlind = {205,290};
			TransparentBlt2(dc.m_hDC,ptBlind,ww,hh,MemDC,0,0,ww,hh,RGB(255,255,255));

		}
		
		CDialog::OnPaint();


		//::ReleaseMutex(HMutex);

	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CCChessUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


////////////////// Programmer-Defined Function ///////////////////////////
inline BOOL loadbmp(CString cc)
{	
	DeleteObject(bit);	
	bit=(HBITMAP)LoadImage	
	(	AfxGetInstanceHandle(),
		cc,
		IMAGE_BITMAP,	
		0,	
		0,	
		LR_LOADFROMFILE|LR_CREATEDIBSECTION
	);
	if(bit==NULL) return FALSE;	
	DIBSECTION ds;
	BITMAPINFOHEADER &bm = ds.dsBmih;
	GetObject(bit,sizeof(ds),&ds);	
	ww = bm.biWidth;	
	hh = bm.biHeight;
	return TRUE;
}


inline void TransparentBlt2( HDC hdc0,	
					 POINT point0,
					 int nW0,int nH0,
					 HDC hdc1,
					 int nX1,int nY1,
					 int nW1,int nH1,
					 UINT Tcol
					 )
{	
	int nX0	=point0.x;
	int nY0	=point0.y;
	HBITMAP hBMP   =CreateCompatibleBitmap(hdc0,nW0, nH0);
	HBITMAP mBMP   =CreateBitmap(nW0,nH0,1,1,NULL);	
	HDC		hDC    =CreateCompatibleDC(hdc0);
	HDC		mDC    =CreateCompatibleDC(hdc0);
	HBITMAP oldBMP =(HBITMAP)SelectObject(hDC, hBMP);
	HBITMAP oldmBMP=(HBITMAP)SelectObject(mDC, mBMP);
	if (nW0==nW1&&nH0==nH1)
		BitBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,SRCCOPY);
	else
		StretchBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,nW1,nH1,SRCCOPY);

	SetBkColor(hDC, Tcol);
	BitBlt(mDC,0,0,nW0,nH0,hDC,0,0,SRCCOPY);
	SetBkColor(hDC, RGB(0,0,0));
	SetTextColor(hDC, RGB(255,255,255));
	BitBlt(hDC,0,0,nW0,nH0,mDC,0,0,SRCAND);
	SetBkColor(hdc0,RGB(255,255,255));
	SetTextColor(hdc0,RGB(0,0,0));

	BitBlt(hdc0,nX0,nY0,nW0,nH0,mDC,0,0,SRCAND);
	BitBlt(hdc0,nX0,nY0,nW0,nH0,hDC,0,0,SRCPAINT);

	SelectObject(hDC, oldBMP);				
	DeleteDC(hDC);
	SelectObject(mDC, oldmBMP);
	DeleteDC(mDC);
	DeleteObject(hBMP);
	DeleteObject(mBMP);
}

void CCChessUIDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if( WhoseTurn != RED )//��û�ֵ��췽����
	{
		return;
	}

	if( point.x>=5 && point.x<=545 && point.y>=5 && point.y<=605 )
	{

		SetTimer(1,100,NULL);

		if( fGameover == true )
		{
			MessageBox("�����������ˡ�","��Ϸ����",MB_OK);
		}
		else 
		{
			//��ñ�׼�ض�����
			stPoint = GetThePoint( point );

			//ȡ�õ�ǰҪ������
			/*
			RECT rctCur	={	stPoint.x,
				stPoint.y,
				stPoint.x+60,
				stPoint.y+60 };

			rctPreR.left	=	stPoint.x;
			rctPreR.top	=	stPoint.y;
			rctPreR.right	=stPoint.x+60;
			rctPreR.bottom	=stPoint.y+60 ;
*/
			

			//if( nHaveSelected != NOCHESS )//�Ѿ�ѡ������
			if( nHaveSelected <= 15 )//ֻ��ѡ����//�Ѿ�ѡ������
			{
				
				nObject =NOCHESS;
				nObject = JudgeThePoint( stPoint );

				if( IsTheSameSide(nHaveSelected,nObject) )//��ѡ��ͬһ��������
				{
					nHaveSelected = nObject;
					ptPreKuang = ptCurKuang = stPoint;

					rctPreR = rctCurR;

					rctCurR.left	=	stPoint.x;
					rctCurR.top		=	stPoint.y;
					rctCurR.right	=stPoint.x+60;
					rctCurR.bottom	=stPoint.y+60 ;

					//�ػ���Ļ
					InvalidateRect(&rctCurR,FALSE);
					InvalidateRect(&rctPreR,FALSE);
					//InvalidateRect(&rctCurB,FALSE);
					//InvalidateRect(&rctPreB,FALSE);
					//UpdateWindow();
				}
				else 
				{
					ptCFrom = PointToCChessBoard(ptChess[nHaveSelected]);
					ptCTo = PointToCChessBoard(stPoint);

					if( CanMOVE( ptCFrom, ptCTo ) == true )//�ŷ��Ϸ�
					{
						rctPreR = rctCurR;

						rctCurR.left	=	stPoint.x;
						rctCurR.top		=	stPoint.y;
						rctCurR.right	=stPoint.x+60;
						rctCurR.bottom	=stPoint.y+60 ;

						for (int i = 0; i<9; i++)
						{
							for (int j = 0; j<10;j++)
							{
								temp.CChessBoard[i][j] = CChessBoard[i][j];
							} 
						}

						for (int i=0; i<32;i++)
						{
							temp.ptChess[i] = ptChess[i];
						}
						//temp.ptCurKuang = ptCurKuang;
						//temp.ptPreKuang = ptPreKuang;

						vBackQueue.push_back(temp);

						cb1.EnableWindow(!vBackQueue.empty());
						//cb2.EnableWindow(!vForwardQueue.empty());



						//ȡ����һ��������
						/*
						RECT rctPre	={	ptChess[nHaveSelected].x,
							ptChess[nHaveSelected].y,
							ptChess[nHaveSelected].x+60,
							ptChess[nHaveSelected].y+60 };

						rctPreR.left	=	ptChess[nHaveSelected].x;
						rctPreR.top	=	ptChess[nHaveSelected].y;
						rctPreR.right	=ptChess[nHaveSelected].x+60;
						rctPreR.bottom	=ptChess[nHaveSelected].y+60 ;
						*/

						if( nObject != NOCHESS )
						{//Ҫ����
							ptChess[nObject].x = -100;
							ptChess[nObject].y = -100;

							//���ų�����
							if(nHaveSelected == RED_Pl
								|| nHaveSelected == RED_Pr
								|| nHaveSelected == BLACK_Pl
								|| nHaveSelected == BLACK_Pr)
							{
								//�ڳ���
								sndPlaySound("wav/ceat.wav",SND_SYNC);
							}
							else
							{
								//�����ӳ���
								sndPlaySound("wav/eat.wav",SND_SYNC);
							}
						}
						else
						{
							//����������
							sndPlaySound("wav/put.wav",SND_SYNC);
						}

						ptChess[nHaveSelected] = stPoint;

						//CChessBoard[ptCTo.x][ptCTo.y]=CChessBoard[ptCFrom.x][ptCFrom.y];
						//CChessBoard[ptCFrom.x][ptCFrom.y] = 0;

						///////////// GO ///////////////////////
						cmMove.ptFrom = ptCFrom;
						cmMove.ptTo = ptCTo;

						DoMove( & cmMove );

						///////// ���ŷ������Լ���ظ� /////////////

						nNumOfStep++;
						////////////////////////////////////

						
						str.Format( "%d - %s", nNumOfStep,
							GetMoveStr(ptCFrom.x,ptCFrom.y,ptCTo.x,ptCTo.y,nHaveSelected));


						//AfxMessageBox(str);
						//lstChessRecord.AddString(str);//    ->AddString(str);
						//lstChessRecord.PostMessage(WM_VSCROLL,SB_BOTTOM,0);
						//lstChessRecord.SetCurSel(1);


						//CListBox *pLB = (CListBox*)GetDlgItem(IDC_LISTCCHESS);
						//pLB ->InsertString(-1,str);
						pLB->AddString(str);
						pLB->PostMessage(WM_VSCROLL,SB_BOTTOM,0);


						if( ! vForwardQueue.empty() )
						{
							vForwardQueue.clear();
						}

						ptCurKuang =stPoint;

						nHaveSelected = NOCHESS;

						//�ػ���Ļ
						InvalidateRect(&rctPreR,FALSE);
						InvalidateRect(&rctCurR,FALSE);
						InvalidateRect(&rctPreB,FALSE);
						InvalidateRect(&rctCurB,FALSE);
						//UpdateWindow();

						//��ˢһ�飬�����ˢ�²���ȫ���Ĵ���
						//InvalidateRect(&rctPreR,FALSE);

						if( nObject != NOCHESS )
						{
							if(IsGameOverUI() == REDWIN)
							{
								MessageBox("��������������С�ܸʰ��·磡","��Ϸ����",MB_OK);
								GameOver();
							}
							if(IsGameOverUI() == BLACKWIN)
							{
								MessageBox("���֣������㲻���","��Ϸ����",MB_OK);
								GameOver();
							}
						}
						
						//PushMoveStack(ptCFrom,ptCTo,)

						WhoseTurn = BLACK ;


						KillTimer(1);
						SetTimer(2,100,NULL);
						

						if( fGameover == false )
						{
							//��������
							nMaxSearchDepth = m_SetDlg.GetDepth();

							bThreadOver = false;
							CThinkingThread = AfxBeginThread(ThinkingThread,&m_hWnd,0,0,0,NULL);

							//Sleep( 8000);
							

							//��ջ�ԭ���У������û�ԭ��ť
							vForwardQueue.clear();
							cb2.EnableWindow(!vForwardQueue.empty());
							
						}

					}
					else	//�ŷ����Ϸ�
					{
						//rctPreR = rctCurR;

						//rctCurR.left	=	stPoint.x;
						//rctCurR.top		=	stPoint.y;
						//rctCurR.right	=stPoint.x+60;
						//rctCurR.bottom	=stPoint.y+60 ;

						//�ػ���Ļ
						//InvalidateRect(&rctCurR,FALSE);
						InvalidateRect(&rctPreR,FALSE);
						//InvalidateRect(&rctCurB,FALSE);
						//InvalidateRect(&rctPreB,FALSE);
						//UpdateWindow();

					}

				}

			}
			else //��δѡ����
			{
				if( (nHaveSelected = JudgeThePoint( stPoint )) != NOCHESS )
				{
					if( nHaveSelected <= 15 )//ֻ��ѡ����
					{
						//�ÿ��λ��
						ptPreKuang = ptCurKuang = stPoint;

						rctCurR.left	=	stPoint.x;
						rctCurR.top		=	stPoint.y;
						rctCurR.right	=stPoint.x+60;
						rctCurR.bottom	=stPoint.y+60;

						//�ػ���Ļ
						InvalidateRect(&rctCurR,FALSE);
						InvalidateRect(&rctCurB,FALSE);
						InvalidateRect(&rctPreB,FALSE);
						//UpdateWindow();
					}

				}

			}
		}
		
	}

	CDialog::OnLButtonDown(nFlags, point);
}

/////////// ˼���߳� //////////////////////////////////////////
UINT ThinkingThread(LPVOID pParam)
{
	//SetTimer((HWND)hhWnd,2,1000,NULL);
	/*
	CString str;
	str.Format("%x",hhWnd);
	AfxMessageBox(str);*/
	//::WaitForSingleObject(HMutex,INFINITE);
	//////////////////////////////////////////////////////

	if( nNumOfStep == 1 )
	{//��һ���鿪�ֿ�
		cmMove =UseLibrary();
		if( cmMove.ptFrom.x != -1 )
		{
			DoMove( &cmMove );
		}
		else
		{
			cmMove = SearchAGoodMove();
		}
	}
	else
	{
		cmMove = SearchAGoodMove();
	}

	////////// ���ŷ������Լ���ظ������� ///////////

	ptCFrom = CChessBoardToPoint( cmMove.ptFrom );
	ptCTo = CChessBoardToPoint( cmMove.ptTo );


	rctPreB.left	=	ptCFrom.x;
	rctPreB.top		=	ptCFrom.y;
	rctPreB.right	=	ptCFrom.x+60;
	rctPreB.bottom	=	ptCFrom.y+60 ;

	rctCurB.left	=	ptCTo.x;
	rctCurB.top		=	ptCTo.y;
	rctCurB.right	=	ptCTo.x+60;
	rctCurB.bottom	=	ptCTo.y+60 ;

	/*
	RECT rctB;
	
	if( rctPreB.left < rctCurB.left )
	{
		rctB.left	= rctPreB.left;
		rctB.right	= rctCurB.right;
	}
	else
	{
		rctB.left	= rctCurB.left;
		rctB.right	= rctPreB.right;
	}

	if( rctPreB.top < rctCurB.top )
	{
		rctB.top	= rctPreB.top;
		rctB.bottom	= rctCurB.bottom;
	}
	else
	{
		rctB.top	= rctCurB.top;
		rctB.bottom	= rctPreB.bottom;
	}
	*/

	nHaveSelected = JudgeThePoint( ptCFrom );
	nObject = JudgeThePoint( ptCTo );

	ptChess[nHaveSelected] = ptCTo;
	
	ptPreKuang	= ptCFrom; 
	ptCurKuang	= ptCTo;

	/*
	CString ssstr;
	ssstr.Format("%d---%d",ptChess[nHaveSelected].x,ptChess[nHaveSelected].y);
	
	if(MessageBox((HWND)hhWnd,ssstr,"OO",MB_OKCANCEL)==IDOK)
	{
		InvalidateRect((HWND)hhWnd,&rctPreR,FALSE);
		InvalidateRect((HWND)hhWnd,&rctCurR,FALSE);
		InvalidateRect((HWND)hhWnd,&rctPreB,FALSE);
		InvalidateRect((HWND)hhWnd,&rctCurB,FALSE);
	}
	*/

	////////////////////////////////////////////////////////
	//::ReleaseMutex(HMutex);

	str.Format( "%d - %s", nNumOfStep, 
		GetMoveStr(cmMove.ptFrom.x,cmMove.ptFrom.y,cmMove.ptTo.x,cmMove.ptTo.y,nHaveSelected));

	pLB->AddString(str);
	pLB->PostMessage(WM_VSCROLL,SB_BOTTOM,0);


	if( nObject != NOCHESS )
	{//Ҫ����
		ptChess[nObject].x = -100;
		ptChess[nObject].y = -100;

		//���ų�����
		if(nHaveSelected == RED_Pl
			|| nHaveSelected == RED_Pr
			|| nHaveSelected == BLACK_Pl
			|| nHaveSelected == BLACK_Pr)
		{
			//�ڳ���
			sndPlaySound("wav/ceat.wav",SND_ASYNC);
		}
		else
		{
			//�����ӳ���
			sndPlaySound("wav/eat.wav",SND_ASYNC);
		}
	}
	else
	{
		//����������
		sndPlaySound("wav/put.wav",SND_ASYNC);
	}

	
	nHaveSelected = NOCHESS;

	//Sleep(500);	//����!!!!!!!!!!�����ˢ�²���ȫ���Ĵ���
	//�÷����ѱ�֤����Ч

	//RECT rctB1 = rctCurB;
	//RECT rctB2 = rctPreB;

	//�ػ���Ļ
	//InvalidateRect((HWND)hhWnd,&rctPreR,FALSE);
	//InvalidateRect((HWND)hhWnd,&rctCurR,FALSE);

	//InvalidateRect((HWND)hhWnd,&rctB1,FALSE);
	//InvalidateRect((HWND)hhWnd,&rctB2,FALSE);

	//InvalidateRect((HWND)hhWnd,&rctPreB,FALSE);
	//InvalidateRect((HWND)hhWnd,&rctCurB,FALSE);
	//InvalidateRect((HWND)hhWnd,&rctB,FALSE);	//�����ϳ�һ��ˢ

	
	//��ˢһ�飬�����ˢ�²���ȫ���Ĵ���
	//InvalidateRect((HWND)hhWnd,&rctPreB,FALSE);

	//InvalidateRect((HWND)hhWnd,NULL,FALSE);
	//UpdateWindow((HWND)hhWnd);


	WhoseTurn = RED ;
	//	KillTimer((HWND)hhWnd,2);
	SetTimer((HWND)hhWnd,1,100,NULL);
	
	bThreadOver = true;

	return 0;
}
/////////////////////////////////////////////////////////////////////

//��Ϸ����
inline void GameOver()
{
	fGameover = true;

	KillTimer((HWND)hhWnd,1);
	KillTimer((HWND)hhWnd,2);
}

//���������λ��ת��Ϊ�ض���������
inline POINT GetThePoint( CPoint point )
{
	POINT ptTemp;

	ptTemp.x = ((int)((point.x-5)/60))*60+5;
	ptTemp.y = ((int)((point.y-5)/60))*60+5;

	return ptTemp;
}

//���ض���������ת��ΪCChessBoard�������±�
inline POINT PointToCChessBoard( POINT point )
{
	POINT xyTemp;

	xyTemp.x = (point.x-5)/60;
	xyTemp.y = 9 - (point.y-5)/60;

	return xyTemp;
}

//��CChessBoard�������±�ת��Ϊ�ض���������
inline POINT CChessBoardToPoint( POINT xyPoint )
{
	POINT ptTemp;

	ptTemp.x = xyPoint.x*60 + 5;
	ptTemp.y = (9 - xyPoint.y)*60 +5;

	return ptTemp;
}

//�ж��ض��������ص�����״����������RED_B1��ʽ��NOCHESS
inline int JudgeThePoint( POINT point )
{
	int i;
	for( i=0; i<32; i++ )
	{
		if( point.x == ptChess[i].x && point.y == ptChess[i].y )
		{
			return i;
		}
	}

	return NOCHESS;
}

//�ж�nA��nB�Ƿ���ͬһ�����ӣ����Ƿ���true�����򷵻�false
inline bool IsTheSameSide( int nA, int nB )
{
	if( nB == NOCHESS )
	{
		return false;
	}
	if( nA>=16 && nB>=16 )
	{
		return true;
	}
	if( nA<=15 && nB<=15 )
	{
		return true;
	}

	return false;
}

//�ж��Ƿ���Ϸ�Ѿ���������ʤ����REDWIN����ʤ����BLACKWIN��δ��������NOTEND
inline int IsGameOverUI()
{
	if( ptChess[RED_K0].x == -100 )
	{
		return BLACKWIN;
	}
	if( ptChess[BLACK_K0].x == -100 )
	{
		return REDWIN;
	}
	return NOTEND;
}

//�ж��߷��Ƿ�Ϸ����Ϸ������棬���Ϸ����ؼ�
inline bool CanMOVE(POINT ptfrom, POINT ptto)
{
	int x1 = ptfrom.x;
	int y1 = ptfrom.y;
	int x2 = ptto.x;
	int y2 = ptto.y;
	int chnum = 0;

	int chessid = CChessBoard[x1][y1];
	switch (chessid)
	{
	case RED_K:
		if (x2 > 5 || x2 < 3 || y2 > 2)
			return false;
		if (abs(x2 - x1) > 1 || abs(y2 - y1) > 1)
			return false;
		if (abs(x2 - x1) == 1 && abs(y2 - y1) == 1)
			return false;
		//if ( HaveMan(ptto) && isred(ptto))
		//	return false;
		break;

	case BLACK_K:
		if (x2 > 5 || x2 < 3 || y2 < 7)
			return false;
		if (abs(x2 - x1) > 1 || abs(y2 - y1) > 1)
			return false;
		if (abs(x2 - x1) == 1 && abs(y2 - y1) == 1)
			return false;
		//if ( HaveMan(ptto) && isblack(ptto))
		//	return false;
		break;

	case RED_J:
	case BLACK_J:
		if (x2 - x1 != 0 && y2 - y1 != 0)
			return false;
		/*if (HaveMan(ptto))
		{
			if (CChessBoard[x1][y1] == RED_J && isred(ptto))
				return false;
			if (CChessBoard[x1][y1] == BLACK_J && isblack(ptto))
				return false;
		}*/
		if (x2 > x1)
		{
			for (int i = 1; i < x2 - x1; i++)
			{	
				if (CChessBoard[x1 + i][y1] != 0)
					return false;
			}	
			return true;
		}
		if (x2 < x1)
		{
			for (int i = 1; i < x1 - x2; i++)
			{	
				if (CChessBoard[x1 - i][y1] != 0)
					return false;
			}
			return true;	
		}
		if (y2 > y1)
		{
			for (int i = 1; i < y2 - y1; i++)
			{	
				if (CChessBoard[x1][y1 + i] != 0)
					return false;
			} 
			return true;
		}
		if (y2 < y1)
		{
			for (int i = 1; i < y1 - y2; i++)
			{	
				if (CChessBoard[x1][y1 - i] != 0)
					return false;
			}  
			return true;
		}
		break;

	case RED_S:
		if (x2 > 5 || x2 < 3 || y2 > 2)
			return false;
		if (abs(x2 - x1) == 1 && abs(y2 - y1) == 1)
		{
			//if (HaveMan(ptto) && isred(ptto))
			//	return false;
			//else
				return true;
		}
		else
		{
			return false;
		}
		break;

	case BLACK_S:
		if (x2 > 5 || x2 < 3 || y2 < 7)
			return false;
		if (abs(x2 - x1) == 1 && abs(y2 - y1) == 1)
		{
			//if (HaveMan(ptto) && isblack(ptto))
			//	return false;
			//else
				return true;
		}
		else
		{
			return false;
		}
		break;

	case RED_M:
	case BLACK_M:

		if	(abs(x2 - x1) >2 || abs(y2 - y1) >2)
			return false;
		if (abs(x2 - x1) ==0 && abs(y2 - y1) >=1) 
			return false;
		if (abs(x2 - x1) == 1 && abs(y2 - y1) != 2)
			return false;
		if (abs(x2 - x1) == 2 && abs(y2 - y1) != 1)
			return false;
		if ( abs(x2 - x1) == 1)
		{
	
			if (y2 > y1 && CChessBoard[x1][y1 + 1] != 0)
				return false;
			if (y2 < y1 && CChessBoard[x1][y1 - 1] != 0)
				return false;
		}
		else if ( abs(y2 - y1) == 1)
		{
			if (x2 > x1 && CChessBoard[x1 + 1][y1] != 0)
				return false;
			if (x2 < x1 && CChessBoard[x1 - 1][y1] != 0)
				return false;
		}

		break;

	case RED_P:
	case BLACK_P:
		if (x2 - x1 != 0 && y2 - y1 != 0)
			return false;
		/*if (HaveMan(ptto))
		{
			if (CChessBoard[x1][y1] == RED_P && isred(ptto))
				return false;
			if (CChessBoard[x1][y1] == BLACK_P && isblack(ptto))
				return false;
		}*/
		if (y2 > y1 && !HaveMan(ptto))
		{
			for (int i = 1; i < y2 - y1; i++)
			{	
				if (CChessBoard[x1][y1 + i] != 0)
					return false;
			}
			return true;
		}
		if (y2 > y1 && HaveMan(ptto))
		{
			chnum =0;
			for (int i = 1; i < y2 - y1; i++)
			{
				if (CChessBoard[x1][y1 + i] != 0)
					chnum++;
			}
			if (chnum != 1 )
				return false;
			else
				return true;
		}
		if (y2 < y1 && !HaveMan(ptto))
		{
			for (int i = 1; i < y1 - y2; i++)
			{
				if (CChessBoard[x1][y1 - i] != 0)
					return false;
			}
			return true;
		}
		if (y2 < y1 && HaveMan(ptto))
		{
			chnum =0;
			for (int i = 1; i < y1 - y2; i++)
			{
				if (CChessBoard[x1][y1 - i] != 0)
					chnum++;
			}
			if (chnum != 1)
				return false;
			else
				return true;
		}
		if (x2 > x1 && !HaveMan(ptto))
		{
			for (int i = 1; i < x2 - x1; i++)
			{
				if (CChessBoard[x1 + i][y1] != 0)
					return false;
			}
			return true;
		}
		if (x2 > x1 && HaveMan(ptto))
		{
			chnum =0;
			for (int i = 1; i < x2 - x1; i++)
			{
				if (CChessBoard[x1 + i][y1] != 0)
					chnum++;
			}
			if (chnum != 1)
				return false;
			else
				return true;
		}
		if (x2 < x1 && !HaveMan(ptto))
		{
			for (int i = 1; i < x1 - x2; i++)
			{
				if (CChessBoard[x1 - i][y1] != 0)
					return false;
			}
			return true;
		}
		if (x2 < x1 && HaveMan(ptto))
		{
			chnum =0;
			for (int i = 1; i < x1 - x2; i++)
			{
				if (CChessBoard[x1 - i][y1] != 0)
					chnum++;
			}
			if (chnum != 1)
				return false;	
			else
				return true;
		}
		break;

	case RED_X:
		if (y2 > 4)
			return false;
		if (abs(x2 - x1) != 2 || abs(y2 - y1) != 2)
			return false;
		//if (HaveMan(ptto) && isred(ptto))
		//	return false;
		if (CChessBoard[(x1 + x2) / 2][(y2 + y1) / 2] != 0)
			return false;
		break;

	case BLACK_X:
		if (y2 < 5)
			return false;
		if (abs(x2 - x1) != 2 || abs(y2 - y1) != 2)
			return false;
		//if (HaveMan(ptto) && isblack(ptto))
		//	return false;
		if (CChessBoard[(x1 + x2) / 2][(y2 + y1) / 2] != 0)
			return false;
		break;

	case RED_B:
		if (y2 < y1)
			return false;
		//if (HaveMan(ptto) && isred(ptto))
		//	return false;
		if (abs(x2 - x1) + abs(y2 - y1) != 1)
			return false;
		if (y1 <= 4 && abs(x2-x1) != 0)
			return false;
		break;

	case BLACK_B:
		if (y2 > y1)
			return false;
		//if (HaveMan(ptto) && isblack(ptto))
		//	return false;
		if (abs(x2 - x1) + abs(y2 - y1) != 1)
			return false;
		if (y1 >= 5 && abs(x2-x1) != 0)
			return false;
		break;

	default:
		return true;
	}

	return true;
}

/*
inline bool HaveMan(POINT ptPosition )
{
	if (CChessBoard[ptPosition.x][ptPosition.y] == 0)
		return false;
	else
		return true;
}

inline bool isred(POINT ptto)
{
	if (SideOfMan[CChessBoard[ptto.x][ptto.y]] == RED)
		return true;
	return false;
}

inline bool isblack(POINT ptto)
{
	if (SideOfMan[CChessBoard[ptto.x][ptto.y]] == RED)
		return true;
	return false;
}
*/

void CCChessUIDlg::OnBnClickedButton3()//�˳�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox("��ȷ��Ҫ�˳���","ȷ��",MB_OKCANCEL)==IDOK)
	{
		EndDialog(IDCANCEL);
	}
	
}

void CCChessUIDlg::OnBnClickedButton4()//�¾�
{
	KillTimer(1);
	GetDlgItem(IDC_STATIC3)->SetWindowText("00:00:00");
	GetDlgItem(IDC_STATIC4)->SetWindowText("00:00:00");
	Second_a =Minute_a =Hour_a = 0;
	Second_b =Minute_b =Hour_b = 0;
	Second_a2 = 0;
	Second_b2 = 0;

	Restart();

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

//����
void CCChessUIDlg::Restart()
{
	//����ŷ������б�
	int nCount=pLB->GetCount();
	for(int i=0;i< nCount ;i++)
	{
		pLB->DeleteString(0);
	}

	//���û��塢��ԭ��ť����ն���
	cb1.EnableWindow(FALSE);
	cb2.EnableWindow(FALSE);

	vBackQueue.clear();
	vForwardQueue.clear();

	vNameQueue.clear();

	//nMoveStackCount =0;

	nNumOfStep =0;

	nHaveSelected = NOCHESS;

	//���λ��
	ptCurKuang.x = -100;
	ptCurKuang.y = -100;
	ptPreKuang = ptCurKuang;

	//�췽����λ��
	ptChess[RED_K0].x	= 245 ;	
	ptChess[RED_K0].y	= 545 ;
	ptChess[RED_Sl].x	= 185 ;	
	ptChess[RED_Sl].y	= 545 ;
	ptChess[RED_Sr].x	= 305 ;	
	ptChess[RED_Sr].y	= 545 ;	
	ptChess[RED_Xl].x	= 125 ;	
	ptChess[RED_Xl].y	= 545 ;
	ptChess[RED_Xr].x	= 365 ;	
	ptChess[RED_Xr].y	= 545 ;	
	ptChess[RED_Ml].x	= 65 ;
	ptChess[RED_Ml].y	= 545 ;	
	ptChess[RED_Mr].x	= 425 ;	
	ptChess[RED_Mr].y	= 545 ;	
	ptChess[RED_Jl].x	= 5 ;
	ptChess[RED_Jl].y	= 545 ;	
	ptChess[RED_Jr].x	= 485 ;	
	ptChess[RED_Jr].y	= 545 ;
	ptChess[RED_Pl].x	= 65 ;
	ptChess[RED_Pl].y	= 425 ;
	ptChess[RED_Pr].x	= 425 ;	
	ptChess[RED_Pr].y	= 425 ;
	ptChess[RED_B1].x	= 5 ;	
	ptChess[RED_B1].y	= 365 ;
	ptChess[RED_B2].x	= 125 ;	
	ptChess[RED_B2].y	= 365 ;
	ptChess[RED_B3].x	= 245 ;	
	ptChess[RED_B3].y	= 365 ;
	ptChess[RED_B4].x	= 365 ;	
	ptChess[RED_B4].y	= 365 ;
	ptChess[RED_B5].x	= 485 ;	
	ptChess[RED_B5].y	= 365 ;

	//�ڷ�����λ��
	ptChess[BLACK_K0].x	= 245 ;		
	ptChess[BLACK_K0].y	= 5 ;
	ptChess[BLACK_Sl].x	= 185 ;
	ptChess[BLACK_Sl].y	= 5 ;
	ptChess[BLACK_Sr].x	= 305 ;
	ptChess[BLACK_Sr].y	= 5 ;
	ptChess[BLACK_Xl].x	= 125 ;
	ptChess[BLACK_Xl].y	= 5 ;
	ptChess[BLACK_Xr].x	= 365 ;
	ptChess[BLACK_Xr].y	= 5 ;
	ptChess[BLACK_Ml].x	= 65 ;
	ptChess[BLACK_Ml].y	= 5 ;
	ptChess[BLACK_Mr].x	= 425 ;
	ptChess[BLACK_Mr].y	= 5 ;
	ptChess[BLACK_Jl].x	= 5 ;	
	ptChess[BLACK_Jl].y	= 5 ;
	ptChess[BLACK_Jr].x	= 485 ;
	ptChess[BLACK_Jr].y	= 5 ;
	ptChess[BLACK_Pl].x	= 65 ;
	ptChess[BLACK_Pl].y	= 125 ;
	ptChess[BLACK_Pr].x	= 425 ;
	ptChess[BLACK_Pr].y	= 125 ;
	ptChess[BLACK_B1].x	= 5 ;	
	ptChess[BLACK_B1].y	= 185 ;
	ptChess[BLACK_B2].x	= 125 ;
	ptChess[BLACK_B2].y	= 185 ;
	ptChess[BLACK_B3].x	= 245 ;
	ptChess[BLACK_B3].y	= 185 ;
	ptChess[BLACK_B4].x	= 365 ;	
	ptChess[BLACK_B4].y	= 185 ;
	ptChess[BLACK_B5].x	= 485 ;	
	ptChess[BLACK_B5].y	= 185 ;	
/*
	//�ڷ�����λ��
	//FOR TEST.................................
	ptChess[BLACK_K0].x	= 245 ;		
	ptChess[BLACK_K0].y	= 5 ;
	ptChess[BLACK_Sl].x	= -100 ;
	ptChess[BLACK_Sl].y	= -100 ;
	ptChess[BLACK_Sr].x	= -100 ;
	ptChess[BLACK_Sr].y	= -100 ;
	ptChess[BLACK_Xl].x	= -100 ;
	ptChess[BLACK_Xl].y	= -100 ;
	ptChess[BLACK_Xr].x	= -100 ;
	ptChess[BLACK_Xr].y	= -100 ;
	ptChess[BLACK_Ml].x	= -100 ;
	ptChess[BLACK_Ml].y	= -100 ;
	ptChess[BLACK_Mr].x	= -100 ;
	ptChess[BLACK_Mr].y	= -100 ;
	ptChess[BLACK_Jl].x	= -100 ;	
	ptChess[BLACK_Jl].y	= -100 ;
	ptChess[BLACK_Jr].x	= -100 ;
	ptChess[BLACK_Jr].y	= -100 ;
	ptChess[BLACK_Pl].x	= -100 ;
	ptChess[BLACK_Pl].y	= -100 ;
	ptChess[BLACK_Pr].x	= -100 ;
	ptChess[BLACK_Pr].y	= -100 ;
	ptChess[BLACK_B1].x	= 5 ;	
	ptChess[BLACK_B1].y	= 185 ;
	ptChess[BLACK_B2].x	= 125 ;
	ptChess[BLACK_B2].y	= 185 ;
	ptChess[BLACK_B3].x	= 245 ;
	ptChess[BLACK_B3].y	= 185 ;
	ptChess[BLACK_B4].x	= 365 ;	
	ptChess[BLACK_B4].y	= 185 ;
	ptChess[BLACK_B5].x	= 485 ;	
	ptChess[BLACK_B5].y	= 185 ;	
*/	

	//��ʼ������
	for( int i=0; i<9; i++ )
	{
		for( int j=0; j<9; j++ )
		{
			CChessBoard[i][j] =0;
		}
	}
	CChessBoard[0][0] = R;
	CChessBoard[1][0] = H;
	CChessBoard[2][0] = E;
	CChessBoard[3][0] = A;
	CChessBoard[4][0] = K;
	CChessBoard[5][0] = A;
	CChessBoard[6][0] = E;
	CChessBoard[7][0] = H;
	CChessBoard[8][0] = R;

	CChessBoard[1][2] = C;
	CChessBoard[7][2] = C;

	CChessBoard[0][3] = P;
	CChessBoard[2][3] = P;
	CChessBoard[4][3] = P;
	CChessBoard[6][3] = P;
	CChessBoard[8][3] = P;


	CChessBoard[0][6] = p;
	CChessBoard[2][6] = p;
	CChessBoard[4][6] = p;
	CChessBoard[6][6] = p;
	CChessBoard[8][6] = p;

	CChessBoard[1][7] = c;
	CChessBoard[7][7] = c;

	CChessBoard[0][9] = r;
	CChessBoard[1][9] = h;
	CChessBoard[2][9] = e;
	CChessBoard[3][9] = a;
	CChessBoard[4][9] = k;
	CChessBoard[5][9] = a;
	CChessBoard[6][9] = e;
	CChessBoard[7][9] = h;
	CChessBoard[8][9] = r;
/*
	//FOR TEST..............................
	CChessBoard[0][6] = p;
	CChessBoard[2][6] = p;
	CChessBoard[4][6] = p;
	CChessBoard[6][6] = p;
	CChessBoard[8][6] = p;

	CChessBoard[1][7] = 0;
	CChessBoard[7][7] = 0;

	CChessBoard[0][9] = 0;
	CChessBoard[1][9] = 0;
	CChessBoard[2][9] = 0;
	CChessBoard[3][9] = 0;
	CChessBoard[4][9] = k;
	CChessBoard[5][9] = 0;
	CChessBoard[6][9] = 0;
	CChessBoard[7][9] = 0;
	CChessBoard[8][9] = 0;
*/

	WhoseTurn = RED ;
	fGameover = false;

	nMaxSearchDepth = m_SetDlg.GetDepth();	

}

//������������ת��Ϊ�й�����
CString ConvertDigit(int nNum)
{
	switch(nNum)
	{
	case 0:
		return "һ";
	case 1:
		return "��";
	case 2:
		return "��";
	case 3:
		return "��";
	case 4:
		return "��";
	case 5:
		return "��";
	case 6:
		return "��";
	case 7:
		return "��";
	case 8:
		return "��";
	default:
		return "";
	}
}

// ȡ���ŷ�������
CString GetMoveStr(int nFromX,int nFromY,int nToX,int nToY,int nSourceID)
{
	/*	
	bool bIsAgain;
	int i;
	int nCount;
	int nPos[5];
	int j=0;
	*/	

	CString Str;
	int nCur,nOther;
	int Other[4];
	//�ͱ��йص�
	int count_X = 1;    //������һ���ϵ��ӵ���Ŀ
	int count_Y = 0;	//��¼�м������ڵ�ǰ�ӵ�ǰ��
	int i;

	switch(nSourceID)
	{
		//��˧
		case RED_K0:
			if( nFromX == nToX )
			{
				if( nToY > nFromY )
					Str="�죺˧"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(nToY-nFromY-1);
				else
					Str="�죺˧"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(nFromY-nToY-1);
			}
			else
				Str="�죺˧"+ConvertDigit(8-nFromX)+"ƽ"+ConvertDigit(8-nToX);

		break;

		//�ڽ�
		case BLACK_K0:
			if ( nFromX == nToX ) 
			{
				if( nToY < nFromY )
					Str.Format("�ڣ���%d��%d",nFromX+1,nFromY-nToY);
				else
					Str.Format("�ڣ���%d��%d",nFromX+1,nToY-nFromY);
			}
			else
				Str.Format("�ڣ���%dƽ%d",nFromX+1,nToX+1);
		break;


		//����
		case RED_Sl:
		case RED_Sr:
			if( nToY>nFromY )
				Str="�죺��"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(8-nToX);
			else
				Str="�죺��"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(8-nToX);
		break;

		//��ʿ
		case BLACK_Sl:
		case BLACK_Sr:	
			if( nToY<nFromY )
				Str.Format("�ڣ�ʿ%d��%d",nFromX+1,nToX+1);
			else
				Str.Format("�ڣ�ʿ%d��%d",nFromX+1,nToX+1);
		break;

		//����
		case RED_Xl:
		case RED_Xr:
			if( nToY > nFromY )
				Str="�죺��"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(8-nToX);
			else
				Str="�죺��"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(8-nToX);
		break;

		//����
		case BLACK_Xl:
		case BLACK_Xr:
			if( nToY < nFromY )
				Str.Format("�ڣ���%d��%d",nFromX+1,nToX+1);
			else
				Str.Format("�ڣ���%d��%d",nFromX+1,nToX+1);
		break;


		//����
		case RED_Pl:
		case RED_Pr:
			if( RED_Pl == nSourceID )
			{
				nCur	= RED_Pl;
				nOther	= RED_Pr;
			}
			else
			{
				nCur	= RED_Pr;
				nOther	= RED_Pl;
			}

			if(ptChess[nCur].x == ptChess[nOther].x)
			{
				if(ptChess[nCur].y < ptChess[nOther].y)
				{
					if(nToY<nFromY)
					{
						Str="�죺ǰ����"+ConvertDigit(nFromY-nToY-1);
					}
					if(nToY>nFromY)
					{
						Str="�죺ǰ�ڽ�"+ConvertDigit(nToY-nFromY-1);
					}
					if(nToY == nFromY)
					{
						Str="�죺ǰ��ƽ"+ConvertDigit(8-nToX);
					}
				}
				else
				{
					if(nToY<nFromY)
					{
						Str="�죺������"+ConvertDigit(nFromY-nToY-1);
					}
					if(nToY>nFromY)
					{
						Str="�죺���ڽ�"+ConvertDigit(nToY-nFromY-1);
					}
					if(nToY == nFromY)
					{
						Str="�죺����ƽ"+ConvertDigit(8-nToX);
					}
				}
			}
			else
			{
				if(nToY<nFromY)
				{
					Str="�죺��"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(nFromY-nToY-1);
				}
				if(nToY>nFromY)
				{
					Str="�죺��"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(nToY-nFromY-1);
				}
				if(nToY == nFromY)
				{
					Str="�죺��"+ConvertDigit(8-nFromX)+"ƽ"+ConvertDigit(8-nToX);
				}
			}
		break;

		//����
		case BLACK_Pl:
		case BLACK_Pr:
			if( BLACK_Pl == nSourceID )
			{
				nCur	= BLACK_Pl;
				nOther	= BLACK_Pr;
			}
			else
			{
				nCur	= BLACK_Pr;
				nOther	= BLACK_Pl;
			}

			if(ptChess[nCur].x == ptChess[nOther].x)
			{
				if(ptChess[nCur].y > ptChess[nOther].y)
				{
					if(nToY<nFromY)
					{
						Str.Format("�ڣ�ǰ�ڽ�%d",nFromY-nToY);
					}
					if(nToY>nFromY)
					{
						Str.Format("�ڣ�ǰ����%d",nToY-nFromY);
					}
					if(nToY == nFromY)
					{
						Str.Format("�ڣ�ǰ��ƽ%d",nToX+1);
					}
				}
				else
				{
					if(nToY<nFromY)
					{
						Str.Format("�ڣ����ڽ�%d",nFromY-nToY);
					}
					if(nToY>nFromY)
					{
						Str.Format("�ڣ�������%d",nToY-nFromY);
					}
					if(nToY == nFromY)
					{
						Str.Format("�ڣ�����ƽ%d",nToX+1);
					}
				}
			}
			else
			{
				if(nToY<nFromY)
				{
					Str.Format("�ڣ���%d��%d",nFromX+1,nFromY-nToY);
				}
				if(nToY>nFromY)
				{
					Str.Format("�ڣ���%d��%d",nFromX+1,nToY-nFromY);
				}
				if(nToY == nFromY)
				{
					Str.Format("�ڣ���%dƽ%d",nFromX+1,nToX+1);
				}
			}
			break;
		
		//����
		case RED_Ml:
		case RED_Mr:
			if( RED_Ml == nSourceID )
			{
				nCur	= RED_Ml;
				nOther	= RED_Mr;
			}
			else
			{
				nCur	= RED_Mr;
				nOther	= RED_Ml;
			}
			if(ptChess[nCur].x == ptChess[nOther].x)
			{
				if(ptChess[nCur].y < ptChess[nOther].y)
				{
					if( nToY<nFromY )
					{
						Str="�죺ǰ����"+ConvertDigit(8-nToX);
					}
					if(nToY>nFromY)
					{
						Str="�죺ǰ���"+ConvertDigit(8-nToX);
					}
				}
				else
				{
					if(nToY<nFromY)
					{
						Str="�죺������"+ConvertDigit(8-nToX);
					}
					if(nToY>nFromY)
					{
						Str="�죺�����"+ConvertDigit(8-nToX);
					}
				}
			}
			else
			{
				if(nToY<nFromY)
				{
					Str="�죺��"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(8-nToX);
				}
				if(nToY>nFromY)
				{
					Str="�죺��"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(8-nToX);
				}
			}
			break;

		//����
		case BLACK_Ml:
		case BLACK_Mr:
			if( BLACK_Ml == nSourceID )
			{
				nCur	= BLACK_Ml;
				nOther = BLACK_Mr;
			}
			else
			{
				nCur	= BLACK_Mr;
				nOther= BLACK_Ml;
			}
			if(ptChess[nCur].x == ptChess[nOther].x)
			{
				if(ptChess[nCur].y > ptChess[nOther].y)
				{
					if(nToY<nFromY)
					{
						Str.Format("�ڣ�ǰ���%d",nToX+1);
					}
					if(nToY>nFromY)
					{
						Str.Format("�ڣ�ǰ����%d",nToX+1);
					}
				}
				else
				{
					if(nToY<nFromY)
					{
						Str.Format("�ڣ������%d",nToX+1);
					}
					if(nToY>nFromY)
					{
						Str.Format("�ڣ�������%d",nToX+1);
					}
				}
			}
			else
			{
				if(nToY<nFromY)
				{
					Str.Format("�ڣ���%d��%d",nFromX+1,nToX+1);
				}
				if(nToY>nFromY)
				{
					Str.Format("�ڣ���%d��%d",nFromX+1,nToX+1);
				}
			}
			break;


		//�쳵
		case RED_Jl:
		case RED_Jr:
			if( RED_Jl == nSourceID )
			{
				nCur	= RED_Jl;
				nOther	= RED_Jr;
			}
			else
			{
				nCur	= RED_Jr;
				nOther	= RED_Jl;
			}

			if(ptChess[nCur].x == ptChess[nOther].x)
			{
				if(ptChess[nCur].y < ptChess[nOther].y)
				{
					if(nToY<nFromY)
					{
						Str="�죺ǰ����"+ConvertDigit(nFromY-nToY-1);
					}
					if(nToY>nFromY)
					{
						Str="�죺ǰ����"+ConvertDigit(nToY-nFromY-1);
					}
					if(nToY == nFromY)
					{
						Str="�죺ǰ��ƽ"+ConvertDigit(8-nToX);
					}
				}
				else
				{
					if(nToY<nFromY)
					{
						Str="�죺����"+ConvertDigit(nFromY-nToY-1);
					}
					if(nToY>nFromY)
					{
						Str="�죺�󳵽�"+ConvertDigit(nToY-nFromY-1);
					}
					if(nToY == nFromY)
					{
						Str="�죺��ƽ"+ConvertDigit(8-nToX);
					}
				}
			}
			else
			{
				if(nToY<nFromY)
				{
					Str="�죺��"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(nFromY-nToY-1);
				}
				if(nToY>nFromY)
				{
					Str="�죺��"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(nToY-nFromY-1);
				}
				if(nToY == nFromY)
				{
					Str="�죺��"+ConvertDigit(8-nFromX)+"ƽ"+ConvertDigit(8-nToX);
				}
			}
			break;

		//�ڳ�
		case BLACK_Jl:
		case BLACK_Jr:

			if( BLACK_Pl == nSourceID )
			{
				nCur	= BLACK_Jl;
				nOther	= BLACK_Jr;
			}
			else
			{
				nCur	= BLACK_Jr;
				nOther	= BLACK_Jl;
			}

			if(ptChess[nCur].x == ptChess[nOther].x)
			{
				if(ptChess[nCur].y > ptChess[nOther].y)
				{
					if(nToY<nFromY)
					{
						Str.Format("�ڣ�ǰ����%d",nFromY-nToY);
					}
					if(nToY>nFromY)
					{
						Str.Format("�ڣ�ǰ����%d",nToY-nFromY);
					}
					if(nToY == nFromY)
					{
						Str.Format("�ڣ�ǰ��ƽ%d",nToX+1);
					}
				}
				else
				{
					if(nToY<nFromY)
					{
						Str.Format("�ڣ��󳵽�%d",nFromY-nToY);
					}
					if(nToY>nFromY)
					{
						Str.Format("�ڣ�����%d",nToY-nFromY);
					}
					if(nToY == nFromY)
					{
						Str.Format("�ڣ���ƽ%d",nToX+1);
					}
				}
			}
			else
			{
				if(nToY<nFromY)
				{
					Str.Format("�ڣ���%d��%d",nFromX+1,nFromY-nToY);
				}
				if(nToY>nFromY)
				{
					Str.Format("�ڣ���%d��%d",nFromX+1,nToY-nFromY);
				}
				if(nToY == nFromY)
				{
					Str.Format("�ڣ���%dƽ%d",nFromX+1,nToX+1);
				}
			}
			break;

			//���
		case RED_B1:
		case RED_B2:
		case RED_B3:
		case RED_B4:
		case RED_B5:
			if( RED_B1 == nSourceID )
			{
				nCur	= RED_B1;
				Other[0]= RED_B2;
				Other[1]= RED_B3;
				Other[2]= RED_B4;
				Other[3]= RED_B5;
			}
			if( RED_B2 == nSourceID )
			{
				nCur	= RED_B2;
				Other[0]= RED_B1;
				Other[1]= RED_B3;
				Other[2]= RED_B4;
				Other[3]= RED_B5;
			}
			if( RED_B3 == nSourceID )
			{
				nCur	= RED_B3;
				Other[0]= RED_B1;
				Other[1]= RED_B2;
				Other[2]= RED_B4;
				Other[3]= RED_B5;
			}
			if( RED_B4 == nSourceID )
			{
				nCur	= RED_B4;
				Other[0]= RED_B1;
				Other[1]= RED_B2;
				Other[2]= RED_B3;
				Other[3]= RED_B5;
			}
			if( RED_B5 == nSourceID )
			{
				nCur	= RED_B5;
				Other[0]= RED_B1;
				Other[1]= RED_B2;
				Other[2]= RED_B3;
				Other[3]= RED_B4;
			}
			for(i=0;i<4;i++)
			{
				if(ptChess[nCur].x == ptChess[Other[i]].x)
					count_X++;
				if(ptChess[nCur].y < ptChess[Other[i]].y)
					count_Y++;
				if( 2 == count_X)   //ֻ������������ͬ������
				{
					if(ptChess[nCur].y < ptChess[Other[i]].y)
					{
						if(nToY > nFromY)
						{
							Str="�죺ǰ����"+ConvertDigit(0);
						}
						if(nToY == nFromY)
						{
							Str="�죺ǰ��ƽ"+ConvertDigit(8-nToX);
						}
					}
					else
					{
						if(nToY > nFromY)
						{
							Str="�죺�����"+ConvertDigit(0);
						}
						if(nToY == nFromY)
						{
							Str="�죺���ƽ"+ConvertDigit(8-nToX);
						}
					}
					break;
				}
			}
			if( count_X > 2 )  //���������������ϵı�����ͬ������
			{
				if(nToY > nFromY)
					Str="�죺"+ConvertDigit(count_Y-1)+"����"+ConvertDigit(0);
				if(nFromY==nToY)
					Str="�죺"+ConvertDigit(count_Y-1)+"��ƽ"+ConvertDigit(8-nToX);
			}
			if( 1 == count_X )   //���еı����ڲ�ͬ��������
			{
				if(nFromY==nToY)
					Str="�죺��"+ConvertDigit(8-nFromX)+"ƽ"+ConvertDigit(8-nToX);
				else
					Str="�죺��"+ConvertDigit(8-nFromX)+"��"+ConvertDigit(0);
			}
			break;


			//����
		case BLACK_B1:
		case BLACK_B2:
		case BLACK_B3:
		case BLACK_B4:
		case BLACK_B5:
			count_X = 1;
			count_Y = 0;
			if( BLACK_B1 == nSourceID )
			{
				nCur	= BLACK_B1;
				Other[0]= BLACK_B2;
				Other[1]= BLACK_B3;
				Other[2]= BLACK_B4;
				Other[3]= BLACK_B5;
			}
			if( BLACK_B2 == nSourceID )
			{
				nCur	= BLACK_B2;
				Other[0]= BLACK_B1;
				Other[1]= BLACK_B3;
				Other[2]= BLACK_B4;
				Other[3]= BLACK_B5;
			}
			if( BLACK_B3 == nSourceID )
			{
				nCur	= BLACK_B3;
				Other[0]= BLACK_B1;
				Other[1]= BLACK_B2;
				Other[2]= BLACK_B4;
				Other[3]= BLACK_B5;
			}
			if( BLACK_B4 == nSourceID )
			{
				nCur	= BLACK_B4;
				Other[0]= BLACK_B1;
				Other[1]= BLACK_B2;
				Other[2]= BLACK_B3;
				Other[3]= BLACK_B5;
			}
			if( BLACK_B5 == nSourceID )
			{
				nCur	= BLACK_B5;
				Other[0]= BLACK_B1;
				Other[1]= BLACK_B2;
				Other[2]= BLACK_B3;
				Other[3]= BLACK_B4;
			}
			for(i=0;i<4;i++)
			{
				if(ptChess[nCur].x == ptChess[Other[i]].x)
					count_X++;
				if(ptChess[nCur].y < ptChess[Other[i]].y)
					count_Y++;
				if( 2 == count_X)   //ֻ������������ͬ������
				{
					if(ptChess[nCur].y < ptChess[Other[i]].y)
					{
						if(nToY > nFromY)
						{
							Str.Format("�ڣ�ǰ���1");
						}
						if(nToY == nFromY)
						{
							Str.Format("�ڣ�ǰ��ƽ%d",nToX+1);
						}
					}
					else
					{
						if(nToY > nFromY)
						{
							Str.Format("�ڣ������1");
						}
						if(nToY == nFromY)
						{
							Str.Format("�ڣ�����ƽ%d",nToX+1);
						}
					}
					break;
				}
			}
			if( count_X > 2 )  //���������������ϵı�����ͬ������
			{
				if(nToY > nFromY)
					Str.Format("�ڣ�%d���1",count_Y-1);
				if(nFromY==nToY)
					Str.Format("�ڣ�%d��ƽ%d",count_Y-1,nToX+1);
			}
			if( 1 == count_X )   //���еı����ڲ�ͬ��������
			{
				if(nFromY==nToY)
					Str.Format("�ڣ���%dƽ%d",nFromX+1,nToX+1);
				else
					Str.Format("�ڣ���%d��1",nFromX+1);
			}
			break;

	default:
		break;
	}

	return Str;
}

/*
inline void PushMoveStack(POINT ptFrom, POINT ptTo, int nChessID)
{
	MOVESTACK[nMoveStackCount].nChessID =nChessID;
	MOVESTACK[nMoveStackCount].ptFrom =ptFrom;
	MOVESTACK[nMoveStackCount].ptTo =ptTo;

	nMoveStackCount++;
}
*/

void CCChessUIDlg::OnMenuNewGame()
{
	// TODO: �ڴ���������������
	Restart();
	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();

}

void CCChessUIDlg::OnMenuQuit()
{
	// TODO: �ڴ���������������
	if(MessageBox("��ȷ��Ҫ�˳���","ȷ��",MB_OKCANCEL)==IDOK)
	{
		EndDialog(IDCANCEL);
	}
}

void CCChessUIDlg::OnAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg dlg;

	dlg.DoModal();
}

void CCChessUIDlg::OnSetEngine()
{
	// TODO: �ڴ���������������

	m_SetDlg.DoModal();
}


void CCChessUIDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 1)
	{
		Second_a2++;
		Second_a= (int)Second_a2/10;
		if (Second_a>=60)
		{
			Minute_a = Second_a/60;
			Second_a = Second_a%60;
			if(Minute_a>=60)
				Hour_a = Minute_a/60;
			Minute_a= Minute_a%60;
		}
		CString SSecond_a;
		CString MMinute_a;
		CString HHour_a;
		SSecond_a.Format("%02d",Second_a);
		MMinute_a.Format("%02d",Minute_a);
		HHour_a.Format("%02d",Hour_a);
		GetDlgItem(IDC_STATIC3)->SetWindowText(HHour_a+":"+MMinute_a+":"+SSecond_a);
	}

	if(nIDEvent ==2)
	{
		if( !fSearchOver  )
		{
			Second_b2++;
			Second_b= (int)Second_b2/10;
			if (Second_b>=60)
			{
				Minute_b = Second_b/60;
				Second_b = Second_b%60;
				if(Minute_b>=60)
					Hour_b = Minute_b/60;
				Minute_b=Minute_b%60;
			}
			CString SSecond_b;
			CString MMinute_b;
			CString HHour_b;
			SSecond_b.Format("%02d",Second_b);
			MMinute_b.Format("%02d",Minute_b);
			HHour_b.Format("%02d",Hour_b);
			GetDlgItem(IDC_STATIC4)->SetWindowText(HHour_b+":"+MMinute_b+":"+SSecond_b);
		}
		if( bThreadOver == true )
		{
			bThreadOver = false;
			//ˢ����Ļ
			InvalidateRect(&rctPreR,FALSE);
			InvalidateRect(&rctCurR,FALSE);
			InvalidateRect(&rctPreB,FALSE);
			InvalidateRect(&rctCurB,FALSE);

			if( nObject != NOCHESS )
			{
				if(IsGameOverUI() == REDWIN)
				{
					MessageBox("��������������С�ܸʰ��·磡","��Ϸ����",MB_OK);
					GameOver();
				}
				if(IsGameOverUI() == BLACKWIN)
				{
					MessageBox("���֣������㲻���","��Ϸ����",MB_OK);
					GameOver();
				}
			}
		}

	}

	CDialog::OnTimer(nIDEvent);
}

void CCChessUIDlg::OnBnClickedButton1()//����
{	
	if( WhoseTurn != RED )
	{
		return;
	}

	CString strTemp;
	pLB->GetText( pLB->GetCount()-1, strTemp );

	vNameQueue.push_back( strTemp );

	pLB->DeleteString(pLB->GetCount()-1);
	pLB->PostMessage(WM_VSCROLL,SB_BOTTOM,0);



	pLB->GetText( pLB->GetCount()-1, strTemp );

	vNameQueue.push_back( strTemp );

	pLB->DeleteString(pLB->GetCount()-1);
	pLB->PostMessage(WM_VSCROLL,SB_BOTTOM,0);


	nNumOfStep--;
	//////////////////////////////////////////
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<10;j++)
		{
			temp.CChessBoard[i][j] = CChessBoard[i][j];
		} 
	}


	for (int i=0; i<32;i++)
	{
		temp.ptChess[i] = ptChess[i];
	}
	//temp.ptCurKuang = ptCurKuang;
	//temp.ptPreKuang = ptPreKuang;
	/*
	temp.ptCurKuang.x = -100;
	temp.ptCurKuang.y = -100;
	temp.ptPreKuang.x = -100;
	temp.ptPreKuang.y = -100;
	*/

	vForwardQueue.push_back(temp);

	///////////////////////////////////////
	temp = vBackQueue.back();
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<10;j++)
		{
			CChessBoard[i][j] = temp.CChessBoard[i][j];
		} 
	}

	for (int i=0; i<32;i++)
	{
		ptChess[i] = temp.ptChess[i];
	}
	//ptPreKuang = temp.ptPreKuang;
	//ptCurKuang = temp.ptCurKuang;
	ptPreKuang.x = -100;
	ptPreKuang.y = -100;
	ptCurKuang.x = -100;
	ptCurKuang.y = -100;

	vBackQueue.pop_back();


	cb1.EnableWindow(!vBackQueue.empty());
	cb2.EnableWindow(!vForwardQueue.empty());

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
	//BackMove();
	//BackMove();
}

void CCChessUIDlg::OnBnClickedButton2()//��ԭ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( WhoseTurn != RED )
	{
		return;
	}

	nNumOfStep++;
	//////////////////////////////////////////
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<10;j++)
		{
			temp.CChessBoard[i][j] = CChessBoard[i][j];
		} 
	}

	for (int i=0; i<32;i++)
	{
		temp.ptChess[i] = ptChess[i];
	}
	//temp.ptCurKuang = ptCurKuang;
	//temp.ptPreKuang = ptPreKuang;

	vBackQueue.push_back(temp);

	///////////////////////////////
	temp = vForwardQueue.back();
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<10;j++)
		{
			CChessBoard[i][j] = temp.CChessBoard[i][j];
		} 
	}

	for (int i=0; i<32;i++)
	{
		ptChess[i] = temp.ptChess[i];
	}
	//ptPreKuang = temp.ptPreKuang;
	//ptCurKuang = temp.ptCurKuang;
	ptPreKuang.x = -100;
	ptPreKuang.y = -100;
	ptCurKuang.x = -100;
	ptCurKuang.y = -100;

	vForwardQueue.pop_back();
	
	cb1.EnableWindow(!vBackQueue.empty());
	cb2.EnableWindow(!vForwardQueue.empty());

	pLB->AddString(vNameQueue.back());
	pLB->PostMessage(WM_VSCROLL,SB_BOTTOM,0);

	vNameQueue.pop_back();

	pLB->AddString(vNameQueue.back());
	pLB->PostMessage(WM_VSCROLL,SB_BOTTOM,0);

	vNameQueue.pop_back();

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}


void CCChessUIDlg::OnNormal()
{
	// TODO: Add your command handler code here
	m_Mode = NORMAL;
	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CCChessUIDlg::OnUpdateNormal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Mode==NORMAL);
}

void CCChessUIDlg::OnBlind()
{
	// TODO: Add your command handler code here
	m_Mode =BLIND;
	
	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
	
	MessageBox("��ѡ����ä��ģʽ��\n��ä��ģʽ�����巽��������ͨģʽ����ͬ��\nֻ��������������ϵ���Ӧλ�ü��ɡ�"
		,"ä��ģʽ", MB_ICONASTERISK );
}

void CCChessUIDlg::OnUpdateBlind(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Mode==BLIND);
}

void CCChessUIDlg::OnstQipan()
{
	// TODO: Add your command handler code here
	m_Qipan =STQP;
	qipan= IDB_STQP;
	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CCChessUIDlg::OnUpdatestQipan(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Qipan==STQP);
}

void CCChessUIDlg::OnsjQipan()
{
	// TODO: Add your command handler code here
	m_Qipan =SJQP;
	qipan= IDB_SJQP;
	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CCChessUIDlg::OnUpdatesjQipan(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Qipan==SJQP);
}

void CCChessUIDlg::OnmtQipan()
{
	// TODO: Add your command handler code here
	m_Qipan =MTQP;
	qipan= IDB_MTQP;
	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CCChessUIDlg::OnUpdatemtQipan(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Qipan==MTQP);
}

void CCChessUIDlg::OnstQizi()
{
	// TODO: Add your command handler code here
	m_Qizi =STQZ;
	qzidir ="Pic/qizi/shitou/";
	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CCChessUIDlg::OnUpdatestQizi(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Qizi==STQZ);
}

void CCChessUIDlg::OnsjQizi()
{
	// TODO: Add your command handler code here
	m_Qizi =SJQZ;
	qzidir ="Pic/qizi/shuijing/";
	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CCChessUIDlg::OnUpdatesjQizi(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Qizi==SJQZ);
}

void CCChessUIDlg::OnmtQizi()
{
	// TODO: Add your command handler code here
	m_Qizi =MTQZ;
	qzidir ="Pic/qizi/mutou/";
	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CCChessUIDlg::OnUpdatemtQizi(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Qizi==MTQZ);
}


void CCChessUIDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mciSendString("open wav/bgm.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
}
