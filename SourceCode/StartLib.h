#include "CChessDef.h"

/////////////////////////////////////////////////
int nNumOfStep;



CCHESSMOVE UseLibrary()
{
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
}