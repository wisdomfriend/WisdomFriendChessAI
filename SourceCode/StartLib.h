#include "CChessDef.h"

/////////////////////////////////////////////////
int nNumOfStep;



CCHESSMOVE UseLibrary()
{
	CCHESSMOVE cmMove;
	cmMove.ptFrom.x	= -1;	//用于以后判断是否在开局库中找到了应着

	//srand( (unsigned)time( NULL ) );

	if( CChessBoard[4][2] == RED_P )//当头炮
	{
		if( CChessBoard[1][2] == 0 )//左炮
		{
			cmMove.ptFrom.x = 1;
			cmMove.ptFrom.y	= 9;
			cmMove.ptTo.x	= 2;
			cmMove.ptTo.y	= 7;
		}
		else						//右炮
		{
			cmMove.ptFrom.x = 7;
			cmMove.ptFrom.y	= 9;
			cmMove.ptTo.x	= 6;
			cmMove.ptTo.y	= 7;
		}
	}
	else if( CChessBoard[4][2] == RED_X )//飞象
	{
		switch( rand()%8 )
		{
		case 0:
		case 1:
		case 2:
			cmMove.ptFrom.x = 7;	//跳马
			cmMove.ptFrom.y	= 9;
			cmMove.ptTo.x	= 6;
			cmMove.ptTo.y	= 7;
			break;

		case 3:
		case 4:
		case 5:
			cmMove.ptFrom.x = 6;	//飞象
			cmMove.ptFrom.y	= 9;
			cmMove.ptTo.x	= 4;
			cmMove.ptTo.y	= 7;
			break;

		case 6:
		case 7:
			cmMove.ptFrom.x = 1;	//炮支士角
			cmMove.ptFrom.y	= 7;
			cmMove.ptTo.x	= 5;
			cmMove.ptTo.y	= 7;
			break;

		}
	}
}