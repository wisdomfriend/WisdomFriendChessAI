// CChessSearch.h


#include "HistoryHeuristic.h"
#include "SortMove.h"
#include "CChessEvaluate.h"



/////////////////// Data Define ////////////////////////////////////////////////

int nMaxSearchDepth;	// ����������
CCHESSMOVE cmBestMove;	// �洢����߷�

bool fSearchOver =false;	//���ڼ�¼�����Ƿ����

/////////////////// Function Prototype /////////////////////////////////////////

// ͨ��AlphaBeta����+��ʷ���������õ�һ������ŷ���ִ��֮
CCHESSMOVE SearchAGoodMove();

// AlphaBeta����+��ʷ������nDepthΪ������ȣ�alpha��ʼΪ��Сֵ��beta��ʼΪ����ֵ
int AlphaBeta_HH( int nDepth, int alpha, int beta );

// �ж���Ϸ�Ƿ����������������ݵ�ǰ���巽������Ӧ�ļ�ֵ�����򷵻�0
//	��ǰ���巽ʤ�򷵻ؼ���ֵ����ǰ���巽���򷵻ؼ�Сֵ�����巽׷�󼫴�ֵ��
int IsGameOver( int fWhoseTurn );

// ִ���ŷ�������ptToλ�õ�����״���������Ե��ӷ��ر��Ե����ӣ���û�г����򷵻�0
BYTE DoMove( CCHESSMOVE * move );

// ����ִ���ŷ����ָ�ԭλ�õ�����״����nCChessIDΪԭptToλ�õ�����״��
void UndoMove( CCHESSMOVE * move, BYTE nCChessID );

// ʹ�ÿ��ֿ�
inline CCHESSMOVE UseLibrary();


////////////////// Programmer-Defined Function //////////////////////////////////

inline CCHESSMOVE UseLibrary()
{
	fSearchOver =false;

	CCHESSMOVE cmMove;
	cmMove.ptFrom.x	= -1;	//�����Ժ��ж��Ƿ��ڿ��ֿ����ҵ���Ӧ��

	//srand( (unsigned)time( NULL ) );

	if( CChessBoard[4][2] == RED_P )//��ͷ��
	{
		if( CChessBoard[1][2] == 0 )//����
		{
			cmMove.ptFrom.x = 1;
			cmMove.ptFrom.y	= 9;
			cmMove.ptTo.x	= 2;
			cmMove.ptTo.y	= 7;
		}
		else						//����
		{
			cmMove.ptFrom.x = 7;
			cmMove.ptFrom.y	= 9;
			cmMove.ptTo.x	= 6;
			cmMove.ptTo.y	= 7;
		}
	}
	else if( CChessBoard[2][2] == RED_P )//��
	{
		cmMove.ptFrom.x = 7;	//��ͷ��
		cmMove.ptFrom.y	= 7;
		cmMove.ptTo.x	= 4;
		cmMove.ptTo.y	= 7;
	}
	else if( CChessBoard[6][2] == RED_P )//��
	{
		cmMove.ptFrom.x = 1;	//��ͷ��
		cmMove.ptFrom.y	= 7;
		cmMove.ptTo.x	= 4;
		cmMove.ptTo.y	= 7;
	}
	else if( CChessBoard[3][2] == RED_P )//��
	{
		if( CChessBoard[1][2] == 0 )
		{
			cmMove.ptFrom.x = 7;	//��ͷ��
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
				cmMove.ptFrom.x = 7;	//��ͷ��
				cmMove.ptFrom.y	= 7;
				cmMove.ptTo.x	= 4;
				cmMove.ptTo.y	= 7;
				break;

			case 2:
				cmMove.ptFrom.x = 6;	//��
				cmMove.ptFrom.y	= 6;
				cmMove.ptTo.x	= 6;
				cmMove.ptTo.y	= 5;
				break;
			}
		}
	}
	else if( CChessBoard[5][2] == RED_P )//��
	{
		if( CChessBoard[7][2] == 0 )
		{
			cmMove.ptFrom.x = 1;	//��ͷ��
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
				cmMove.ptFrom.x = 1;	//��ͷ��
				cmMove.ptFrom.y	= 7;
				cmMove.ptTo.x	= 4;
				cmMove.ptTo.y	= 7;
				break;

			case 2:
				cmMove.ptFrom.x = 2;	//��
				cmMove.ptFrom.y	= 6;
				cmMove.ptTo.x	= 2;
				cmMove.ptTo.y	= 5;
				break;
			}
		}
	}
	else if( CChessBoard[4][2] == RED_X )//����
	{
		switch( rand()%8 )
		{
		case 0:
		case 1:
		case 2:
			cmMove.ptFrom.x = 7;	//����
			cmMove.ptFrom.y	= 9;
			cmMove.ptTo.x	= 6;
			cmMove.ptTo.y	= 7;
			break;

		case 3:
		case 4:
		case 5:
			cmMove.ptFrom.x = 6;	//����
			cmMove.ptFrom.y	= 9;
			cmMove.ptTo.x	= 4;
			cmMove.ptTo.y	= 7;
			break;

		case 6:
		case 7:
			cmMove.ptFrom.x = 1;	//��֧ʿ��
			cmMove.ptFrom.y	= 7;
			cmMove.ptTo.x	= 5;
			cmMove.ptTo.y	= 7;
			break;

		}
	}
	else if( CChessBoard[2][2] == RED_M )//����
	{
		cmMove.ptFrom.x = 2;	//����
		cmMove.ptFrom.y	= 6;
		cmMove.ptTo.x	= 2;
		cmMove.ptTo.y	= 5;
	}
	else if( CChessBoard[6][2] == RED_M )//����
	{
		cmMove.ptFrom.x = 6;	//����
		cmMove.ptFrom.y	= 6;
		cmMove.ptTo.x	= 6;
		cmMove.ptTo.y	= 5;
	}
	else if( CChessBoard[2][4] == RED_B )//����
	{
		switch( rand()%3 )
		{
		case 0:
		case 1:
			cmMove.ptFrom.x = 1;	//�ڶ�
			cmMove.ptFrom.y	= 7;
			cmMove.ptTo.x	= 2;
			cmMove.ptTo.y	= 7;
			break;

		case 2:
			cmMove.ptFrom.x = 2;	//����
			cmMove.ptFrom.y	= 9;
			cmMove.ptTo.x	= 4;
			cmMove.ptTo.y	= 7;
			break;
		}
	}
	else if( CChessBoard[6][4] == RED_B )//����
	{
		switch( rand()%3 )
		{
		case 0:
		case 1:
			cmMove.ptFrom.x = 7;	//�ڶ�
			cmMove.ptFrom.y	= 7;
			cmMove.ptTo.x	= 6;
			cmMove.ptTo.y	= 7;
			break;

		case 2:
			cmMove.ptFrom.x = 6;	//����
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
	if( i != 0 )	// ��Ϸ����
		return i;

	if( nDepth == 0 )	// Ҷ�ӽڵ�
		return Eveluate( ( nMaxSearchDepth - nDepth ) % 2 );

	nCount = GenerateMove( ( nMaxSearchDepth - nDepth ) % 2 , nDepth );

	
	if( nDepth == nMaxSearchDepth )//��cmBestMove��һ����ֵ���Ա���˴�����һ����Ҳ�ò���
	{
		cmBestMove = MoveList[nDepth][0];
	}
	

	for( i = 0; i < nCount; i ++ ) // ȡ��ʷ��÷�
	{
		MoveList[nDepth][i].nScore = GetHistoryScore( & MoveList[nDepth][i] );
	}

	MergeSort( MoveList[nDepth], nCount );	// ���ŷ����н�������

	int iBestmove = -1;

	for( i = 0; i < nCount; i ++ ) 
	{

		nCChessID = DoMove( & MoveList[nDepth][i] );	// ִ���ŷ��������½ڵ㣩
		nScore = - AlphaBeta_HH( nDepth - 1, -beta, -alpha );	// �ݹ����AlphaBeta_HH����
		UndoMove( & MoveList[nDepth][i], nCChessID );	// ����ִ�У�ɾ���ڵ㣩

		if( nScore > alpha )
		{
			alpha = nScore;		// �������ֵ

			if( nDepth == nMaxSearchDepth )
				cmBestMove = MoveList[nDepth][i];

			iBestmove = i;	// ��������߷������
		}
		if( alpha >= beta ) 
		{
			iBestmove = i;	// ��������߷������
			break;
		}

	}
	if( iBestmove != -1 )
		EnterHistoryScore( & MoveList[nDepth][iBestmove], nDepth );	// ��¼��ʷ�÷�

	return alpha;
} 

int IsGameOver( int fWhoseTurn )
{
	int x, y ;

	if( fWhoseTurn == RED )	// �ֵ��췽���壬ֻ�����Ǻ�˧�Ѿ�����
	{
		// �췽�Ź�
		for( x = 3; x <= 5; x ++ )
			for( y = 0; y <= 2; y ++ )
			{
				if( CChessBoard[x][y] == RED_K )
				{
					return 0;	// ��˧û���ԣ���˵����Ϸ��δ����
				}
			}
	
		return -MaxValue ;	// ����ʧ�ܼ�ֵ������֤ӦΪ -MaxValue ��

	}
	else // �ֵ��ڷ����壬ֻ�����Ǻڽ��Ѿ�����
	{
		// �ڷ��Ź�
		for( x = 3; x <= 5; x ++ )
			for( y = 9; y >= 7; y -- )
			{
				if( CChessBoard[x][y] == BLACK_K )
				{
					return 0;	// �ڽ�û���ԣ���˵����Ϸ��δ����
				}
			}

		return -MaxValue ;	// ����ʧ�ܼ�ֵ������֤ӦΪ -MaxValue ��

	}

}

BYTE DoMove( CCHESSMOVE * move )
{
	BYTE nCChessID;

	//����Ŀ��λ�õ�����״��
	nCChessID = CChessBoard[ move->ptTo.x ][ move->ptTo.y ] ;

	//�ƶ��ӵ�Ŀ��λ��
	CChessBoard[ move->ptTo.x ][ move->ptTo.y ] = CChessBoard[ move->ptFrom.x ][ move->ptFrom.y ] ;
	CChessBoard[ move->ptFrom.x ][ move->ptFrom.y ] = 0 ;

	return nCChessID;
}

void UndoMove( CCHESSMOVE * move, BYTE nCChessID )
{
	//�����ƶ���ԭ��
	CChessBoard[ move->ptFrom.x ][ move->ptFrom.y ] = CChessBoard[ move->ptTo.x ][ move->ptTo.y ] ;

	//�ָ�Ŀ��λ�õ���
	CChessBoard[ move->ptTo.x ][ move->ptTo.y ] = nCChessID ;
}
