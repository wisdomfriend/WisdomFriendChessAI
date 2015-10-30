// CChessMove.h


#include "CChessDef.h"



/////////////////// Data Define ////////////////////////////////////////////////

CCHESSMOVE MoveList[12][80] ;	// �洢�������ŷ�����
int nMoveCount  ;				// �洢��ǰ��������Ѳ������ŷ���



/////////////////// Function Prototype /////////////////////////////////////////

// �ж�ptPosition���Ƿ���ͬһ�����ӣ����з���true�����򷵻�false
inline bool HaveFriend( POINT ptPosition, int fSide );

// �ж� x, y ���Ƿ���ͬһ�����ӣ����з���true�����򷵻�false
inline bool HaveFriend( BYTE x, BYTE y, int fSide );

// �ж�ptPosition���Ƿ����ӣ����з���true�����򷵻�false
inline bool HaveMan( POINT ptPosition );

// �ж� x, y ���Ƿ����ӣ����з���true�����򷵻�false
inline bool HaveMan( BYTE x, BYTE y );

// ��齫˧�Ƿ����棬�����淵�ضԷ����� y ֵ���꣬�������򷵻�-1��
//  ����x, y�ֱ�Ϊ��ǰ���巽��������λ�����꣬fSideΪ��ǰ���巽
int IsKingFaceToFace( int x, int y, int fSide );

// ����fSide�������ŷ������ز������ŷ�������nDepthΪ��ǰ������ȣ����ڴ���AddMoveToQueue����
int GenerateMove( int fSide, int nDepth );

// ���������ŷ������ŷ����С�nDepthΪ��ǰ�������
inline void AddMoveToQueue( POINT ptFrom, POINT ptTo, int nDepth );

// ���������ŷ������ŷ����С�nDepthΪ��ǰ�������
inline void AddMoveToQueue( POINT ptFrom, BYTE x, BYTE y, int nDepth );



////////////////// Programmer-Defined Function //////////////////////////////////

inline bool HaveFriend( POINT ptPosition, int fSide )
{
	if( CChessBoard[ptPosition.x][ptPosition.y] == 0 )
		return false;
	else if( SideOfMan[ CChessBoard[ptPosition.x][ptPosition.y] ] == fSide )
		return true;
	else
		return false;
}

inline bool HaveFriend( BYTE x, BYTE y, int fSide )
{
	if( CChessBoard[x][y] == 0 )
		return false;
	else if( SideOfMan[ CChessBoard[x][y] ] == fSide )
		return true;
	else
		return false;
}

inline bool HaveMan( POINT ptPosition )
{
	if( CChessBoard[ptPosition.x][ptPosition.y] == 0 )
		return false;
	else
		return true;
}

inline bool HaveMan( BYTE x, BYTE y )
{
	if( CChessBoard[x][y] == 0 )
		return false;
	else
		return true;
}

int IsKingFaceToFace( int x, int y, int fSide )
{
	bool bMayKingFaceToFace = false;
	int i, j ;

	if( fSide == RED )
	{
		for( i = 9; i >= 7; i -- )	// ���ڽ��Ƿ���ͬ��
		{
			if(  CChessBoard[x][i] == BLACK_K )
			{
				bMayKingFaceToFace = true;
				break;
			}
		}

		if( bMayKingFaceToFace == false )
			return -1;
			
		for( j = y + 1; j <= i - 1 ; j ++ )	// �ڽ���ͬ�У�����м��Ƿ��и���
		{
			if( CChessBoard[x][j] != 0 )	// ��������
				return -1;
		}

		return i;	// ��˧���棬���غڽ��� y ֵ����
	}
	else // fSide == BLACK
	{
		for( i = 0; i <= 2; i ++ )	// ����˧�Ƿ���ͬ��
		{
			if(  CChessBoard[x][i] == RED_K )
			{
				bMayKingFaceToFace = true;
				break;
			}
		}

		if( bMayKingFaceToFace == false )
			return -1;

		for( j = y - 1; j >= i + 1 ; j -- )	// ��˧��ͬ�У�����м��Ƿ��и���
		{
			if( CChessBoard[x][j] != 0 )	// ��������
				return -1;
		}

		return i;	// ��˧���棬���غ�˧�� y ֵ����
	}

}

int GenerateMove( int fSide, int nDepth )
{
	BYTE    nCChessID ;
	POINT	ptFrom , ptTo , ptHalf ;
	int i;
	
	nMoveCount = 0;

	int x, y;
	for( x = 0; x <= 8; x ++ )
		for( y = 0; y <= 9; y ++ )
		{
			if( CChessBoard[x][y] != 0 )
			{
				nCChessID = CChessBoard[x][y];
				if( SideOfMan[ nCChessID ] != fSide )	//������ɫ����Ҫ�����ŷ�����ɫ��ͬ
					continue;

				ptFrom.x = x ;
				ptFrom.y = y ;

				switch( nCChessID )
				{

//==========���ɺ�˧���ŷ�
				case RED_K:

					// ��˧����
					i = IsKingFaceToFace( ptFrom.x, ptFrom.y, fSide );
					if( i != -1 )
						AddMoveToQueue( ptFrom, ptFrom.x, i, nDepth );

					//����
					ptTo.x = ptFrom.x ;
					
					//��ǰ
					ptTo.y = ptFrom.y + 1 ;
					if(( ptTo.y <= 2 ) && ( ! HaveFriend( ptTo, fSide ) ))
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//���
					ptTo.y = ptFrom.y - 1 ;
					if(( ptTo.y >= 0 ) && ( ! HaveFriend( ptTo, fSide ) ))
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//����
					ptTo.y = ptFrom.y ;

					//����
					ptTo.x = ptFrom.x - 1 ;
					if(( ptTo.x >= 3 ) && ( ! HaveFriend( ptTo, fSide ) )
						&& ( IsKingFaceToFace( ptTo.x, ptTo.y, fSide ) == -1 ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//����
					ptTo.x = ptFrom.x + 1 ;
					if(( ptTo.x <= 5 ) && ( ! HaveFriend( ptTo, fSide ) )
						&& ( IsKingFaceToFace( ptTo.x, ptTo.y, fSide ) == -1 ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					break;


//==========���ɺڽ����ŷ�
				case BLACK_K:

					// ��˧����
					i = IsKingFaceToFace( ptFrom.x, ptFrom.y, fSide );
					if( i != -1 )
						AddMoveToQueue( ptFrom, ptFrom.x, i, nDepth );
					
					//����
					ptTo.x = ptFrom.x ;

					//��ǰ
					ptTo.y = ptFrom.y - 1 ;
					if(( ptTo.y >= 7 ) && ( ! HaveFriend( ptTo, fSide ) ))
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//���
					ptTo.y = ptFrom.y + 1 ;
					if(( ptTo.y <= 9 ) && ( ! HaveFriend( ptTo, fSide ) ))
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//����
					ptTo.y = ptFrom.y ;

					//����
					ptTo.x = ptFrom.x + 1 ;
					if(( ptTo.x <= 5 ) && ( ! HaveFriend( ptTo, fSide ) )
						&& ( IsKingFaceToFace( ptTo.x, ptTo.y, fSide ) == -1 ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//����
					ptTo.x = ptFrom.x - 1 ;
					if(( ptTo.x >= 3 ) && ( ! HaveFriend( ptTo, fSide ) )
						&& ( IsKingFaceToFace( ptTo.x, ptTo.y, fSide ) == -1 ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					break;


//==========���ɺ쳵���ŷ�
				case RED_J:	
					
					//����
					ptTo.x = ptFrom.x ;

					//��ǰ
					for( ptTo.y = ptFrom.y + 1; ptTo.y <= 9; ptTo.y ++ )
					{
						if( HaveMan( ptTo ) )
						{
							if( ! HaveFriend( ptTo, fSide ) )
								AddMoveToQueue( ptFrom, ptTo, nDepth );

							break;
						}
						AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					//���
					for( ptTo.y = ptFrom.y - 1; ptTo.y >= 0; ptTo.y -- )
					{
						if( HaveMan( ptTo ) )
						{
							if( ! HaveFriend( ptTo, fSide ) )
								AddMoveToQueue( ptFrom, ptTo, nDepth );

							break;
						}
						AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					//����
					ptTo.y = ptFrom.y ;

					//����
					for( ptTo.x = ptFrom.x - 1; ptTo.x >= 0; ptTo.x -- )
					{
						if( HaveMan( ptTo ) )
						{
							if( ! HaveFriend( ptTo, fSide ) )
								AddMoveToQueue( ptFrom, ptTo, nDepth );

							break;
						}
						AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					//����
					for( ptTo.x = ptFrom.x + 1; ptTo.x <= 8; ptTo.x ++ )
					{
						if( HaveMan( ptTo ) )
						{
							if( ! HaveFriend( ptTo, fSide ) )
								AddMoveToQueue( ptFrom, ptTo, nDepth );

							break;
						}
						AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					break;


//==========���ɺڳ����ŷ�
				case BLACK_J:
					
					//����
					ptTo.x = ptFrom.x ;

					//��ǰ
					for( ptTo.y = ptFrom.y - 1; ptTo.y >= 0; ptTo.y -- )
					{
						if( HaveMan( ptTo ) )
						{
							if( ! HaveFriend( ptTo, fSide ) )
								AddMoveToQueue( ptFrom, ptTo, nDepth );

							break;
						}
						AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					//���
					for( ptTo.y = ptFrom.y + 1; ptTo.y <= 9; ptTo.y ++ )
					{
						if( HaveMan( ptTo ) )
						{
							if( ! HaveFriend( ptTo, fSide ) )
								AddMoveToQueue( ptFrom, ptTo, nDepth );

							break;
						}
						AddMoveToQueue( ptFrom, ptTo, nDepth );
					}


					//����
					ptTo.y = ptFrom.y ;

					//����
					for( ptTo.x = ptFrom.x + 1; ptTo.x <= 8; ptTo.x ++ )
					{
						if( HaveMan( ptTo ) )
						{
							if( ! HaveFriend( ptTo, fSide ) )
								AddMoveToQueue( ptFrom, ptTo, nDepth );

							break;
						}
						AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					//����
					for( ptTo.x = ptFrom.x - 1; ptTo.x >= 0; ptTo.x -- )
					{
						if( HaveMan( ptTo ) )
						{
							if( ! HaveFriend( ptTo, fSide ) )
								AddMoveToQueue( ptFrom, ptTo, nDepth );

							break;
						}
						AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					break;


//==========���ɺ�����ŷ�
				case RED_M:
					
					//ptHalf�����洢���ȵ�λ�ã����жϸ�λ���Ƿ����ӱ�����

					ptHalf.x = ptFrom.x ;
					ptHalf.y = ptFrom.y + 1 ;
					if( ptHalf.y <= 8 && ! HaveMan( ptHalf ) )
					{
						//11�㷽��
						ptTo.x = ptFrom.x - 1 ;
						ptTo.y = ptFrom.y + 2 ;
						if( ptTo.x >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//1�㷽��
						ptTo.x = ptFrom.x + 1 ;
						ptTo.y = ptFrom.y + 2 ;
						if( ptTo.x <= 8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x + 1 ;
					ptHalf.y = ptFrom.y ;
					if( ptHalf.x <= 7 && ! HaveMan( ptHalf ) )
					{
						//2�㷽��
						ptTo.x = ptFrom.x + 2 ;
						ptTo.y = ptFrom.y + 1 ;
						if( ptTo.y <= 9 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//4�㷽��
						ptTo.x = ptFrom.x + 2 ;
						ptTo.y = ptFrom.y - 1 ;
						if( ptTo.y >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x ;
					ptHalf.y = ptFrom.y - 1 ;
					if( ptHalf.y >= 1 && ! HaveMan( ptHalf ) )
					{
						//5�㷽��
						ptTo.x = ptFrom.x + 1 ;
						ptTo.y = ptFrom.y - 2 ;
						if( ptTo.x <= 8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//7�㷽��
						ptTo.x = ptFrom.x - 1 ;
						ptTo.y = ptFrom.y - 2 ;
						if( ptTo.x >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x - 1 ;
					ptHalf.y = ptFrom.y ;
					if( ptHalf.x >= 1 && ! HaveMan( ptHalf ) )
					{
						//8�㷽��
						ptTo.x = ptFrom.x - 2 ;
						ptTo.y = ptFrom.y - 1 ;
						if( ptTo.y >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//10�㷽��
						ptTo.x = ptFrom.x - 2 ;
						ptTo.y = ptFrom.y + 1 ;
						if( ptTo.y <= 9 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					break;


//==========���ɺ�����ŷ�
				case BLACK_M:
					
					//ptHalf�����洢���ȵ�λ�ã����жϸ�λ���Ƿ����ӱ�����

					ptHalf.x = ptFrom.x ;
					ptHalf.y = ptFrom.y + 1 ;
					if( ptHalf.y <= 8 && ! HaveMan( ptHalf ) )
					{
						//5�㷽��
						ptTo.x = ptFrom.x - 1 ;
						ptTo.y = ptFrom.y + 2 ;
						if( ptTo.x >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//7�㷽��
						ptTo.x = ptFrom.x + 1 ;
						ptTo.y = ptFrom.y + 2 ;
						if( ptTo.x <= 8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x + 1 ;
					ptHalf.y = ptFrom.y ;
					if( ptHalf.x <= 7 && ! HaveMan( ptHalf ) )
					{
						//8�㷽��
						ptTo.x = ptFrom.x + 2 ;
						ptTo.y = ptFrom.y + 1 ;
						if( ptTo.y <= 9 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//10�㷽��
						ptTo.x = ptFrom.x + 2 ;
						ptTo.y = ptFrom.y - 1 ;
						if( ptTo.y >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x ;
					ptHalf.y = ptFrom.y - 1 ;
					if( ptHalf.y >= 1 && ! HaveMan( ptHalf ) )
					{
						//11�㷽��
						ptTo.x = ptFrom.x + 1 ;
						ptTo.y = ptFrom.y - 2 ;
						if( ptTo.x <= 8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//1�㷽��
						ptTo.x = ptFrom.x - 1 ;
						ptTo.y = ptFrom.y - 2 ;
						if( ptTo.x >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x - 1 ;
					ptHalf.y = ptFrom.y ;
					if( ptHalf.x >= 1 && ! HaveMan( ptHalf ) )
					{
						//2�㷽��
						ptTo.x = ptFrom.x - 2 ;
						ptTo.y = ptFrom.y - 1 ;
						if( ptTo.y >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//4�㷽��
						ptTo.x = ptFrom.x - 2 ;
						ptTo.y = ptFrom.y + 1 ;
						if( ptTo.y <= 9 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					break;


//==========���ɺ��ڵ��ŷ�
				case RED_P:

					//ptHalf�����洢���Ƿ��и��Ӵ��ӵ��м���

					//����
					ptTo.x = ptFrom.x ;

					//��ǰ
					ptHalf.x = -1;	//��־��δ�����м���
					for( ptTo.y = ptFrom.y + 1; ptTo.y <= 9; ptTo.y ++ )
					{
						if( ptHalf.x == -1 ) // ���м���
						{
							if( ! HaveMan( ptTo ) )
							{
								AddMoveToQueue( ptFrom, ptTo, nDepth );
							}
							else // if( HaveMan( ptTo ) )
							{
								ptHalf.x = ptTo.x ;
								ptHalf.y = ptTo.y ;
							}
						}
						else // �����м���
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//���
					ptHalf.x = -1;	//��־��δ�����м���
					for( ptTo.y = ptFrom.y - 1; ptTo.y >= 0; ptTo.y -- )
					{
						if( ptHalf.x == -1 ) // ���м���
						{
							if( ! HaveMan( ptTo ) )
							{
								AddMoveToQueue( ptFrom, ptTo, nDepth );
							}
							else // if( HaveMan( ptTo ) )
							{
								ptHalf.x = ptTo.x ;
								ptHalf.y = ptTo.y ;
							}
						}
						else // �����м���
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//����
					ptTo.y = ptFrom.y ;

					//����
					ptHalf.x = -1;	//��־��δ�����м���
					for( ptTo.x = ptFrom.x - 1; ptTo.x >= 0; ptTo.x -- )
					{
						if( ptHalf.x == -1 ) // ���м���
						{
							if( ! HaveMan( ptTo ) )
							{
								AddMoveToQueue( ptFrom, ptTo, nDepth );
							}
							else // if( HaveMan( ptTo ) )
							{
								ptHalf.x = ptTo.x ;
								ptHalf.y = ptTo.y ;
							}
						}
						else // �����м���
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//����
					ptHalf.x = -1;	//��־��δ�����м���
					for( ptTo.x = ptFrom.x + 1; ptTo.x <= 8; ptTo.x ++ )
					{
						if( ptHalf.x == -1 ) // ���м���
						{
							if( ! HaveMan( ptTo ) )
							{
								AddMoveToQueue( ptFrom, ptTo, nDepth );
							}
							else // if( HaveMan( ptTo ) )
							{
								ptHalf.x = ptTo.x ;
								ptHalf.y = ptTo.y ;
							}
						}
						else // �����м���
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					break;


//==========���ɺ��ڵ��ŷ�
				case BLACK_P:

					//ptHalf�����洢���Ƿ��и��Ӵ��ӵ��м���

					//����
					ptTo.x = ptFrom.x ;

					//���
					ptHalf.x = -1;	//��־��δ�����м���
					for( ptTo.y = ptFrom.y + 1; ptTo.y <= 9; ptTo.y ++ )
					{
						if( ptHalf.x == -1 ) // ���м���
						{
							if( ! HaveMan( ptTo ) )
							{
								AddMoveToQueue( ptFrom, ptTo, nDepth );
							}
							else // if( HaveMan( ptTo ) )
							{
								ptHalf.x = ptTo.x ;
								ptHalf.y = ptTo.y ;
							}
						}
						else // �����м���
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//��ǰ
					ptHalf.x = -1;	//��־��δ�����м���
					for( ptTo.y = ptFrom.y - 1; ptTo.y >= 0; ptTo.y -- )
					{
						if( ptHalf.x == -1 ) // ���м���
						{
							if( ! HaveMan( ptTo ) )
							{
								AddMoveToQueue( ptFrom, ptTo, nDepth );
							}
							else // if( HaveMan( ptTo ) )
							{
								ptHalf.x = ptTo.x ;
								ptHalf.y = ptTo.y ;
							}
						}
						else // �����м���
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//����
					ptTo.y = ptFrom.y ;

					//����
					ptHalf.x = -1;	//��־��δ�����м���
					for( ptTo.x = ptFrom.x - 1; ptTo.x >= 0; ptTo.x -- )
					{
						if( ptHalf.x == -1 ) // ���м���
						{
							if( ! HaveMan( ptTo ) )
							{
								AddMoveToQueue( ptFrom, ptTo, nDepth );
							}
							else // if( HaveMan( ptTo ) )
							{
								ptHalf.x = ptTo.x ;
								ptHalf.y = ptTo.y ;
							}
						}
						else // �����м���
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//����
					ptHalf.x = -1;	//��־��δ�����м���
					for( ptTo.x = ptFrom.x + 1; ptTo.x <= 8; ptTo.x ++ )
					{
						if( ptHalf.x == -1 ) // ���м���
						{
							if( ! HaveMan( ptTo ) )
							{
								AddMoveToQueue( ptFrom, ptTo, nDepth );
							}
							else // if( HaveMan( ptTo ) )
							{
								ptHalf.x = ptTo.x ;
								ptHalf.y = ptTo.y ;
							}
						}
						else // �����м���
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					break;


//==========���ɺ�����ŷ�
				case RED_X:
				
					if( ptFrom.x == 0 )
					{
						if( ! HaveFriend(2, 4, fSide) && ! HaveMan(1, 3) )
							AddMoveToQueue( ptFrom, 2, 4, nDepth );

						if( ! HaveFriend(2, 0, fSide) && ! HaveMan(1, 1) )
							AddMoveToQueue( ptFrom, 2, 0, nDepth );
					}
					else if( ptFrom.x == 2 )
					{
						if( ptFrom.y == 4 )
						{
							if( ! HaveFriend(0, 2, fSide) && ! HaveMan(1, 3) )
								AddMoveToQueue( ptFrom, 0, 2, nDepth );

							if( ! HaveFriend(4, 2, fSide) && ! HaveMan(3, 3) )
								AddMoveToQueue( ptFrom, 4, 2, nDepth );
						}
						else // ptFrom.y == 0 
						{
							if( ! HaveFriend(0, 2, fSide) && ! HaveMan(1, 1) )
								AddMoveToQueue( ptFrom, 0, 2, nDepth );

							if( ! HaveFriend(4, 2, fSide) && ! HaveMan(3, 1) )
								AddMoveToQueue( ptFrom, 4, 2, nDepth );
						}	
					}
					else if( ptFrom.x == 4 )
					{
						if( ! HaveFriend(2, 4, fSide) && ! HaveMan(3, 3) )
							AddMoveToQueue( ptFrom, 2, 4, nDepth );

						if( ! HaveFriend(2, 0, fSide) && ! HaveMan(3, 1) )
							AddMoveToQueue( ptFrom, 2, 0, nDepth );

						if( ! HaveFriend(6, 4, fSide) && ! HaveMan(5, 3) )
							AddMoveToQueue( ptFrom, 6, 4, nDepth );

						if( ! HaveFriend(6, 0, fSide) && ! HaveMan(5, 1) )
							AddMoveToQueue( ptFrom, 6, 0, nDepth );
					}
					else if( ptFrom.x == 6 )
					{
						if( ptFrom.y == 4 )
						{
							if( ! HaveFriend(4, 2, fSide) && ! HaveMan(5, 3) )
								AddMoveToQueue( ptFrom, 4, 2, nDepth );

							if( ! HaveFriend(8, 2, fSide) && ! HaveMan(7, 3) )
								AddMoveToQueue( ptFrom, 8, 2, nDepth );
						}
						else // ptFrom.y == 0 
						{
							if( ! HaveFriend(4, 2, fSide) && ! HaveMan(5, 1) )
								AddMoveToQueue( ptFrom, 4, 2, nDepth );

							if( ! HaveFriend(8, 2, fSide) && ! HaveMan(7, 1) )
								AddMoveToQueue( ptFrom, 8, 2, nDepth );
						}	
					}
					else // x == 8
					{
						if( ! HaveFriend(6, 4, fSide) && ! HaveMan(7, 3) )
							AddMoveToQueue( ptFrom, 6, 4, nDepth );

						if( ! HaveFriend(6, 0, fSide) && ! HaveMan(7, 1) )
							AddMoveToQueue( ptFrom, 6, 0, nDepth );
					}

					break;


//==========���ɺ�����ŷ�
				case BLACK_X:
					
					if( ptFrom.x == 0 )
					{
						if( ! HaveFriend(2, 5, fSide) && ! HaveMan(1, 6) )
							AddMoveToQueue( ptFrom, 2, 5, nDepth );

						if( ! HaveFriend(2, 9, fSide) && ! HaveMan(1, 8) )
							AddMoveToQueue( ptFrom, 2, 9, nDepth );
					}
					else if( ptFrom.x == 2 )
					{
						if( ptFrom.y == 5 )
						{
							if( ! HaveFriend(0, 7, fSide) && ! HaveMan(1, 6) )
								AddMoveToQueue( ptFrom, 0, 7, nDepth );

							if( ! HaveFriend(4, 7, fSide) && ! HaveMan(3, 6) )
								AddMoveToQueue( ptFrom, 4, 7, nDepth );
						}
						else // ptFrom.y == 9 
						{
							if( ! HaveFriend(0, 7, fSide) && ! HaveMan(1, 8) )
								AddMoveToQueue( ptFrom, 0, 7, nDepth );

							if( ! HaveFriend(4, 7, fSide) && ! HaveMan(3, 8) )
								AddMoveToQueue( ptFrom, 4, 7, nDepth );
						}	
					}
					else if( ptFrom.x == 4 )
					{
						if( ! HaveFriend(2, 5, fSide) && ! HaveMan(3, 6) )
							AddMoveToQueue( ptFrom, 2, 5, nDepth );

						if( ! HaveFriend(2, 9, fSide) && ! HaveMan(3, 8) )
							AddMoveToQueue( ptFrom, 2, 9, nDepth );

						if( ! HaveFriend(6, 5, fSide) && ! HaveMan(5, 6) )
							AddMoveToQueue( ptFrom, 6, 5, nDepth );

						if( ! HaveFriend(6, 9, fSide) && ! HaveMan(5, 8) )
							AddMoveToQueue( ptFrom, 6, 9, nDepth );
					}
					else if( ptFrom.x == 6 )
					{
						if( ptFrom.y == 5 )
						{
							if( ! HaveFriend(4, 7, fSide) && ! HaveMan(5, 6) )
								AddMoveToQueue( ptFrom, 4, 7, nDepth );

							if( ! HaveFriend(8, 7, fSide) && ! HaveMan(7, 6) )
								AddMoveToQueue( ptFrom, 8, 7, nDepth );
						}
						else // ptFrom.y == 9 
						{
							if( ! HaveFriend(4, 7, fSide) && ! HaveMan(5, 8) )
								AddMoveToQueue( ptFrom, 4, 7, nDepth );

							if( ! HaveFriend(8, 7, fSide) && ! HaveMan(7, 8) )
								AddMoveToQueue( ptFrom, 8, 7, nDepth );
						}	
					}
					else // x == 8
					{
						if( ! HaveFriend(6, 5, fSide) && ! HaveMan(7, 6) )
							AddMoveToQueue( ptFrom, 6, 5, nDepth );

						if( ! HaveFriend(6, 9, fSide) && ! HaveMan(7, 8) )
							AddMoveToQueue( ptFrom, 6, 9, nDepth );
					}

					break;


//==========���ɺ��˵��ŷ�
				case RED_S:
					
					if( ptFrom.x == 3 )
					{
						if( ! HaveFriend( 4, 1, fSide ) )
							AddMoveToQueue( ptFrom,  4, 1, nDepth );
					}
					else if( ptFrom.x == 4 )
					{
						if( ! HaveFriend( 3, 2, fSide ) )
							AddMoveToQueue( ptFrom,  3, 2, nDepth );

						if( ! HaveFriend( 3, 0, fSide ) )
							AddMoveToQueue( ptFrom,  3, 0, nDepth );

						if( ! HaveFriend( 5, 2, fSide ) )
							AddMoveToQueue( ptFrom,  5, 2, nDepth );

						if( ! HaveFriend( 5, 0, fSide ) )
							AddMoveToQueue( ptFrom,  5, 0, nDepth );
					}
					else //  ptFrom.x == 5
					{
						if( ! HaveFriend( 4, 1, fSide ) )
							AddMoveToQueue( ptFrom,  4, 1, nDepth );
					}

					break;


//==========���ɺ�ʿ���ŷ�
				case BLACK_S:
					
					if( ptFrom.x == 3 )
					{
						if( ! HaveFriend( 4, 8, fSide ) )
							AddMoveToQueue( ptFrom,  4, 8, nDepth );
					}
					else if( ptFrom.x == 4 )
					{
						if( ! HaveFriend( 3, 7, fSide ) )
							AddMoveToQueue( ptFrom,  3, 7, nDepth );

						if( ! HaveFriend( 3, 9, fSide ) )
							AddMoveToQueue( ptFrom,  3, 9, nDepth );

						if( ! HaveFriend( 5, 7, fSide ) )
							AddMoveToQueue( ptFrom,  5, 7, nDepth );

						if( ! HaveFriend( 5, 9, fSide ) )
							AddMoveToQueue( ptFrom,  5, 9, nDepth );
					}
					else //  ptFrom.x == 5
					{
						if( ! HaveFriend( 4, 8, fSide ) )
							AddMoveToQueue( ptFrom,  4, 8, nDepth );
					}

					break;


//==========���ɺ�����ŷ�
				case RED_B:

					//��ǰ
					ptTo.x = ptFrom.x ;
					ptTo.y = ptFrom.y + 1 ;
					if( ptTo.y <=9 && ! HaveFriend( ptTo, fSide ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					if( ptFrom.y >= 5 ) //���ѹ���
					{
						ptTo.y = ptFrom.y ;

						//����
						ptTo.x = ptFrom.x - 1 ;
						if( ptTo.x >=0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//����
						ptTo.x = ptFrom.x + 1 ;
						if( ptTo.x <=8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					break;


//==========���ɺ�����ŷ�
				case BLACK_B:
					
					//��ǰ
					ptTo.x = ptFrom.x ;
					ptTo.y = ptFrom.y - 1 ;
					if( ptTo.y >=0 && ! HaveFriend( ptTo, fSide ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					if( ptFrom.y <= 4 ) //���ѹ���
					{
						ptTo.y = ptFrom.y ;

						//����
						ptTo.x = ptFrom.x - 1 ;
						if( ptTo.x >=0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//����
						ptTo.x = ptFrom.x + 1 ;
						if( ptTo.x <=8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					break;

				}	// end switch
			
			}	// end if( CChessBoard[x][y] != 0 )

		}	// end for x 0 to 8, y 0 to 9

	return nMoveCount;	// ���ص�ǰ��ȵ��߷�����
}

inline void AddMoveToQueue( POINT ptFrom, POINT ptTo, int nDepth )
{
	MoveList[nDepth][nMoveCount].ptFrom.x = ptFrom.x ;
	MoveList[nDepth][nMoveCount].ptFrom.y = ptFrom.y ;
	MoveList[nDepth][nMoveCount].ptTo.x = ptTo.x ;
	MoveList[nDepth][nMoveCount].ptTo.y = ptTo.y ;
	
	nMoveCount ++;
}

inline void AddMoveToQueue( POINT ptFrom, BYTE x, BYTE y, int nDepth )
{
	MoveList[nDepth][nMoveCount].ptFrom.x = ptFrom.x ;
	MoveList[nDepth][nMoveCount].ptFrom.y = ptFrom.y ;
	MoveList[nDepth][nMoveCount].ptTo.x = x ;
	MoveList[nDepth][nMoveCount].ptTo.y = y ;

	nMoveCount ++;
}
