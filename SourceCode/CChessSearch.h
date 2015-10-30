// CChessSearch.h


#include "HistoryHeuristic.h"
#include "SortMove.h"
#include "CChessEvaluate.h"



/////////////////// Data Define ////////////////////////////////////////////////

int nMaxSearchDepth;	// 最大搜索深度
CCHESSMOVE cmBestMove;	// 存储最佳走法

bool fSearchOver =false;	//用于记录搜索是否完成

/////////////////// Function Prototype /////////////////////////////////////////

// 通过AlphaBeta搜索+历史启发搜索得到一部最佳着法并执行之
CCHESSMOVE SearchAGoodMove();

// AlphaBeta搜索+历史启发，nDepth为搜索深度，alpha初始为极小值，beta初始为极大值
int AlphaBeta_HH( int nDepth, int alpha, int beta );

// 判断游戏是否结束，若结束则根据当前下棋方返回相应的极值，否则返回0
//	当前下棋方胜则返回极大值，当前下棋方败则返回极小值（下棋方追求极大值）
int IsGameOver( int fWhoseTurn );

// 执行着法，返回ptTo位置的棋子状况。即若吃掉子返回被吃掉的子，若没有吃子则返回0
BYTE DoMove( CCHESSMOVE * move );

// 撤销执行着法，恢复原位置的棋子状况。nCChessID为原ptTo位置的棋子状况
void UndoMove( CCHESSMOVE * move, BYTE nCChessID );

// 使用开局库
inline CCHESSMOVE UseLibrary();


////////////////// Programmer-Defined Function //////////////////////////////////

inline CCHESSMOVE UseLibrary()
{
	fSearchOver =false;

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
	else if( CChessBoard[2][2] == RED_P )//炮
	{
		cmMove.ptFrom.x = 7;	//当头炮
		cmMove.ptFrom.y	= 7;
		cmMove.ptTo.x	= 4;
		cmMove.ptTo.y	= 7;
	}
	else if( CChessBoard[6][2] == RED_P )//炮
	{
		cmMove.ptFrom.x = 1;	//当头炮
		cmMove.ptFrom.y	= 7;
		cmMove.ptTo.x	= 4;
		cmMove.ptTo.y	= 7;
	}
	else if( CChessBoard[3][2] == RED_P )//炮
	{
		if( CChessBoard[1][2] == 0 )
		{
			cmMove.ptFrom.x = 7;	//当头炮
			cmMove.ptFrom.y	= 7;
			cmMove.ptTo.x	= 4;
			cmMove.ptTo.y	= 7;
		}
		else
		{
			switch( rand()%3 )
			{
			case 0:
			case 1:
				cmMove.ptFrom.x = 7;	//当头炮
				cmMove.ptFrom.y	= 7;
				cmMove.ptTo.x	= 4;
				cmMove.ptTo.y	= 7;
				break;

			case 2:
				cmMove.ptFrom.x = 6;	//卒
				cmMove.ptFrom.y	= 6;
				cmMove.ptTo.x	= 6;
				cmMove.ptTo.y	= 5;
				break;
			}
		}
	}
	else if( CChessBoard[5][2] == RED_P )//炮
	{
		if( CChessBoard[7][2] == 0 )
		{
			cmMove.ptFrom.x = 1;	//当头炮
			cmMove.ptFrom.y	= 7;
			cmMove.ptTo.x	= 4;
			cmMove.ptTo.y	= 7;
		}
		else
		{
			switch( rand()%3 )
			{
			case 0:
			case 1:
				cmMove.ptFrom.x = 1;	//当头炮
				cmMove.ptFrom.y	= 7;
				cmMove.ptTo.x	= 4;
				cmMove.ptTo.y	= 7;
				break;

			case 2:
				cmMove.ptFrom.x = 2;	//卒
				cmMove.ptFrom.y	= 6;
				cmMove.ptTo.x	= 2;
				cmMove.ptTo.y	= 5;
				break;
			}
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
	else if( CChessBoard[2][2] == RED_M )//跳马
	{
		cmMove.ptFrom.x = 2;	//走卒
		cmMove.ptFrom.y	= 6;
		cmMove.ptTo.x	= 2;
		cmMove.ptTo.y	= 5;
	}
	else if( CChessBoard[6][2] == RED_M )//跳马
	{
		cmMove.ptFrom.x = 6;	//走卒
		cmMove.ptFrom.y	= 6;
		cmMove.ptTo.x	= 6;
		cmMove.ptTo.y	= 5;
	}
	else if( CChessBoard[2][4] == RED_B )//走卒
	{
		switch( rand()%3 )
		{
		case 0:
		case 1:
			cmMove.ptFrom.x = 1;	//炮顶
			cmMove.ptFrom.y	= 7;
			cmMove.ptTo.x	= 2;
			cmMove.ptTo.y	= 7;
			break;

		case 2:
			cmMove.ptFrom.x = 2;	//飞象
			cmMove.ptFrom.y	= 9;
			cmMove.ptTo.x	= 4;
			cmMove.ptTo.y	= 7;
			break;
		}
	}
	else if( CChessBoard[6][4] == RED_B )//走卒
	{
		switch( rand()%3 )
		{
		case 0:
		case 1:
			cmMove.ptFrom.x = 7;	//炮顶
			cmMove.ptFrom.y	= 7;
			cmMove.ptTo.x	= 6;
			cmMove.ptTo.y	= 7;
			break;

		case 2:
			cmMove.ptFrom.x = 6;	//飞象
			cmMove.ptFrom.y	= 9;
			cmMove.ptTo.x	= 4;
			cmMove.ptTo.y	= 7;
			break;
		}
	}

	//Sleep(1100);
	fSearchOver =true;

	return cmMove;
}

CCHESSMOVE SearchAGoodMove()
{
	ResetHistoryTable();
	fSearchOver =false;

	int i;
	i = AlphaBeta_HH( nMaxSearchDepth, -MaxValue, MaxValue );

	DoMove( &cmBestMove );
	
	fSearchOver =true;

	return cmBestMove;
}

int AlphaBeta_HH( int nDepth, int alpha, int beta ) 
{ 
	int nScore;
	int nCount;
	BYTE nCChessID;

	int i;
	i = IsGameOver( ( nMaxSearchDepth - nDepth ) % 2 );
	if( i != 0 )	// 游戏结束
		return i;

	if( nDepth == 0 )	// 叶子节点
		return Eveluate( ( nMaxSearchDepth - nDepth ) % 2 );

	nCount = GenerateMove( ( nMaxSearchDepth - nDepth ) % 2 , nDepth );

	
	if( nDepth == nMaxSearchDepth )//给cmBestMove赋一个初值，以避免此次搜索一步棋也得不到
	{
		cmBestMove = MoveList[nDepth][0];
	}
	

	for( i = 0; i < nCount; i ++ ) // 取历史表得分
	{
		MoveList[nDepth][i].nScore = GetHistoryScore( & MoveList[nDepth][i] );
	}

	MergeSort( MoveList[nDepth], nCount );	// 对着法进行降序排序

	int iBestmove = -1;

	for( i = 0; i < nCount; i ++ ) 
	{

		nCChessID = DoMove( & MoveList[nDepth][i] );	// 执行着法（生成新节点）
		nScore = - AlphaBeta_HH( nDepth - 1, -beta, -alpha );	// 递归调用AlphaBeta_HH搜索
		UndoMove( & MoveList[nDepth][i], nCChessID );	// 撤销执行（删除节点）

		if( nScore > alpha )
		{
			alpha = nScore;		// 保留最大值

			if( nDepth == nMaxSearchDepth )
				cmBestMove = MoveList[nDepth][i];

			iBestmove = i;	// 保存最佳走法的序号
		}
		if( alpha >= beta ) 
		{
			iBestmove = i;	// 保存最佳走法的序号
			break;
		}

	}
	if( iBestmove != -1 )
		EnterHistoryScore( & MoveList[nDepth][iBestmove], nDepth );	// 记录历史得分

	return alpha;
} 

int IsGameOver( int fWhoseTurn )
{
	int x, y ;

	if( fWhoseTurn == RED )	// 轮到红方下棋，只可能是红帅已经被吃
	{
		// 红方九宫
		for( x = 3; x <= 5; x ++ )
			for( y = 0; y <= 2; y ++ )
			{
				if( CChessBoard[x][y] == RED_K )
				{
					return 0;	// 红帅没被吃，则说明游戏尚未结束
				}
			}
	
		return -MaxValue ;	// 返回失败极值（已验证应为 -MaxValue ）

	}
	else // 轮到黑方下棋，只可能是黑将已经被吃
	{
		// 黑方九宫
		for( x = 3; x <= 5; x ++ )
			for( y = 9; y >= 7; y -- )
			{
				if( CChessBoard[x][y] == BLACK_K )
				{
					return 0;	// 黑将没被吃，则说明游戏尚未结束
				}
			}

		return -MaxValue ;	// 返回失败极值（已验证应为 -MaxValue ）

	}

}

BYTE DoMove( CCHESSMOVE * move )
{
	BYTE nCChessID;

	//保留目标位置的棋子状况
	nCChessID = CChessBoard[ move->ptTo.x ][ move->ptTo.y ] ;

	//移动子到目标位置
	CChessBoard[ move->ptTo.x ][ move->ptTo.y ] = CChessBoard[ move->ptFrom.x ][ move->ptFrom.y ] ;
	CChessBoard[ move->ptFrom.x ][ move->ptFrom.y ] = 0 ;

	return nCChessID;
}

void UndoMove( CCHESSMOVE * move, BYTE nCChessID )
{
	//将子移动回原处
	CChessBoard[ move->ptFrom.x ][ move->ptFrom.y ] = CChessBoard[ move->ptTo.x ][ move->ptTo.y ] ;

	//恢复目标位置的子
	CChessBoard[ move->ptTo.x ][ move->ptTo.y ] = nCChessID ;
}
