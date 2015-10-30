// CChessDef.h


////////////////////// 基本类型定义 ////////////////////////////////////////
/*
typedef char BYTE;

typedef struct _point{

	BYTE x;
	BYTE y;

} POINT ;			// 棋盘上的点的结构
*/
typedef struct _cchessmove{

	POINT ptFrom;	// 起点
	POINT ptTo;		// 目标点
	int nScore;		// 该走法的历史得分

} CCHESSMOVE ;		// 走法结构



////////////////////// 下棋方定义 /////////////////////////////////////////////
						
const int HUMAN		= 1;	// 人
const int COMPUTER	= 0;	// 电脑

const int RED	= 1;	// 红方
const int BLACK	= 0;	// 黑方



////////////////////// 棋子定义 ////////////////////////////////////////////////

//红方棋子定义		红
const BYTE K =	1;	// 帅
const BYTE A =	2;	// 仕
const BYTE E =	3;	// 相
const BYTE H =	4;	// 马
const BYTE R =	5;	// 车
const BYTE C =	6;	// 炮
const BYTE P =	7;	// 兵

//黑方棋子定义		黑
const BYTE k =	8;	// 将
const BYTE a =	9;	// 士
const BYTE e =	10;	// 象
const BYTE h =	11;	// 马
const BYTE r =	12;	// 车
const BYTE c =	13;	// 炮
const BYTE p =	14;	// 卒

//红方棋子定义
#define RED_K	K
#define RED_S	A
#define RED_X	E
#define RED_M	H
#define RED_J	R
#define RED_P	C
#define RED_B	P

//黑方棋子定义
#define BLACK_K	k
#define BLACK_S	a
#define BLACK_X	e
#define BLACK_M	h
#define BLACK_J	r
#define BLACK_P	c
#define BLACK_B	p


//判断该棋子为哪一方
const int SideOfMan[15] ={0, RED,   RED,   RED,   RED,   RED,   RED,   RED,
						BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, };
//此数组将作为一个“函数”来使用。类似 int SideOfMan( BYTE );



/////////////////////// 棋局定义 //////////////////////////////////////////////////////

// 棋盘上棋子分布
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
