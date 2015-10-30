// CChessDef.h


////////////////////// �������Ͷ��� ////////////////////////////////////////
/*
typedef char BYTE;

typedef struct _point{

	BYTE x;
	BYTE y;

} POINT ;			// �����ϵĵ�Ľṹ
*/
typedef struct _cchessmove{

	POINT ptFrom;	// ���
	POINT ptTo;		// Ŀ���
	int nScore;		// ���߷�����ʷ�÷�

} CCHESSMOVE ;		// �߷��ṹ



////////////////////// ���巽���� /////////////////////////////////////////////
						
const int HUMAN		= 1;	// ��
const int COMPUTER	= 0;	// ����

const int RED	= 1;	// �췽
const int BLACK	= 0;	// �ڷ�



////////////////////// ���Ӷ��� ////////////////////////////////////////////////

//�췽���Ӷ���		��
const BYTE K =	1;	// ˧
const BYTE A =	2;	// ��
const BYTE E =	3;	// ��
const BYTE H =	4;	// ��
const BYTE R =	5;	// ��
const BYTE C =	6;	// ��
const BYTE P =	7;	// ��

//�ڷ����Ӷ���		��
const BYTE k =	8;	// ��
const BYTE a =	9;	// ʿ
const BYTE e =	10;	// ��
const BYTE h =	11;	// ��
const BYTE r =	12;	// ��
const BYTE c =	13;	// ��
const BYTE p =	14;	// ��

//�췽���Ӷ���
#define RED_K	K
#define RED_S	A
#define RED_X	E
#define RED_M	H
#define RED_J	R
#define RED_P	C
#define RED_B	P

//�ڷ����Ӷ���
#define BLACK_K	k
#define BLACK_S	a
#define BLACK_X	e
#define BLACK_M	h
#define BLACK_J	r
#define BLACK_P	c
#define BLACK_B	p


//�жϸ�����Ϊ��һ��
const int SideOfMan[15] ={0, RED,   RED,   RED,   RED,   RED,   RED,   RED,
						BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, };
//�����齫��Ϊһ������������ʹ�á����� int SideOfMan( BYTE );



/////////////////////// ��ֶ��� //////////////////////////////////////////////////////

// ���������ӷֲ�
BYTE CChessBoard[9][10] = { 
	R,  0,  0,  P,  0,  0,  p,  0,  0,  r,
	H,  0,  C,  0,  0,  0,  0,  c,  0,  h,
	E,  0,  0,  P,  0,  0,  p,  0,  0,  e,
	A,  0,  0,  0,  0,  0,  0,  0,  0,  a,
	K,  0,  0,  P,  0,  0,  p,  0,  0,  k,
	A,  0,  0,  0,  0,  0,  0,  0,  0,  a,
	E,  0,  0,  P,  0,  0,  p,  0,  0,  e,
	H,  0,  C,  0,  0,  0,  0,  c,  0,  h,
	R,  0,  0,  P,  0,  0,  p,  0,  0,  r
};
