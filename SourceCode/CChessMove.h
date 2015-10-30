// CChessMove.h


#include "CChessDef.h"



/////////////////// Data Define ////////////////////////////////////////////////

CCHESSMOVE MoveList[12][80] ;	// 存储产生的着法队列
int nMoveCount  ;				// 存储当前搜索深度已产生的着法数



/////////////////// Function Prototype /////////////////////////////////////////

// 判断ptPosition处是否有同一方的子，若有返回true，否则返回false
inline bool HaveFriend( POINT ptPosition, int fSide );

// 判断 x, y 处是否有同一方的子，若有返回true，否则返回false
inline bool HaveFriend( BYTE x, BYTE y, int fSide );

// 判断ptPosition处是否有子，若有返回true，否则返回false
inline bool HaveMan( POINT ptPosition );

// 判断 x, y 处是否有子，若有返回true，否则返回false
inline bool HaveMan( BYTE x, BYTE y );

// 检查将帅是否碰面，若碰面返回对方王的 y 值坐标，不碰面则返回-1。
//  其中x, y分别为当前走棋方的王所在位置坐标，fSide为当前走棋方
int IsKingFaceToFace( int x, int y, int fSide );

// 产生fSide方所有着法，返回产生的着法总数。nDepth为当前搜索深度，用于传给AddMoveToQueue函数
int GenerateMove( int fSide, int nDepth );

// 将产生的着法加入着法队列。nDepth为当前搜索深度
inline void AddMoveToQueue( POINT ptFrom, POINT ptTo, int nDepth );

// 将产生的着法加入着法队列。nDepth为当前搜索深度
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
		for( i = 9; i >= 7; i -- )	// 检查黑将是否在同列
		{
			if(  CChessBoard[x][i] == BLACK_K )
			{
				bMayKingFaceToFace = true;
				break;
			}
		}

		if( bMayKingFaceToFace == false )
			return -1;
			
		for( j = y + 1; j <= i - 1 ; j ++ )	// 黑将在同列，检查中间是否有隔挡
		{
			if( CChessBoard[x][j] != 0 )	// 有其他子
				return -1;
		}

		return i;	// 将帅碰面，返回黑将的 y 值坐标
	}
	else // fSide == BLACK
	{
		for( i = 0; i <= 2; i ++ )	// 检查红帅是否在同列
		{
			if(  CChessBoard[x][i] == RED_K )
			{
				bMayKingFaceToFace = true;
				break;
			}
		}

		if( bMayKingFaceToFace == false )
			return -1;

		for( j = y - 1; j >= i + 1 ; j -- )	// 红帅在同列，检查中间是否有隔挡
		{
			if( CChessBoard[x][j] != 0 )	// 有其他子
				return -1;
		}

		return i;	// 将帅碰面，返回红帅的 y 值坐标
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
				if( SideOfMan[ nCChessID ] != fSide )	//该子颜色与所要生成着法的颜色不同
					continue;

				ptFrom.x = x ;
				ptFrom.y = y ;

				switch( nCChessID )
				{

//==========生成红帅的着法
				case RED_K:

					// 将帅碰面
					i = IsKingFaceToFace( ptFrom.x, ptFrom.y, fSide );
					if( i != -1 )
						AddMoveToQueue( ptFrom, ptFrom.x, i, nDepth );

					//纵向
					ptTo.x = ptFrom.x ;
					
					//向前
					ptTo.y = ptFrom.y + 1 ;
					if(( ptTo.y <= 2 ) && ( ! HaveFriend( ptTo, fSide ) ))
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//向后
					ptTo.y = ptFrom.y - 1 ;
					if(( ptTo.y >= 0 ) && ( ! HaveFriend( ptTo, fSide ) ))
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//横向
					ptTo.y = ptFrom.y ;

					//向左
					ptTo.x = ptFrom.x - 1 ;
					if(( ptTo.x >= 3 ) && ( ! HaveFriend( ptTo, fSide ) )
						&& ( IsKingFaceToFace( ptTo.x, ptTo.y, fSide ) == -1 ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//向右
					ptTo.x = ptFrom.x + 1 ;
					if(( ptTo.x <= 5 ) && ( ! HaveFriend( ptTo, fSide ) )
						&& ( IsKingFaceToFace( ptTo.x, ptTo.y, fSide ) == -1 ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					break;


//==========生成黑将的着法
				case BLACK_K:

					// 将帅碰面
					i = IsKingFaceToFace( ptFrom.x, ptFrom.y, fSide );
					if( i != -1 )
						AddMoveToQueue( ptFrom, ptFrom.x, i, nDepth );
					
					//纵向
					ptTo.x = ptFrom.x ;

					//向前
					ptTo.y = ptFrom.y - 1 ;
					if(( ptTo.y >= 7 ) && ( ! HaveFriend( ptTo, fSide ) ))
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//向后
					ptTo.y = ptFrom.y + 1 ;
					if(( ptTo.y <= 9 ) && ( ! HaveFriend( ptTo, fSide ) ))
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//横向
					ptTo.y = ptFrom.y ;

					//向左
					ptTo.x = ptFrom.x + 1 ;
					if(( ptTo.x <= 5 ) && ( ! HaveFriend( ptTo, fSide ) )
						&& ( IsKingFaceToFace( ptTo.x, ptTo.y, fSide ) == -1 ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					//向右
					ptTo.x = ptFrom.x - 1 ;
					if(( ptTo.x >= 3 ) && ( ! HaveFriend( ptTo, fSide ) )
						&& ( IsKingFaceToFace( ptTo.x, ptTo.y, fSide ) == -1 ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					break;


//==========生成红车的着法
				case RED_J:	
					
					//纵向
					ptTo.x = ptFrom.x ;

					//向前
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

					//向后
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

					//横向
					ptTo.y = ptFrom.y ;

					//向左
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

					//向右
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


//==========生成黑车的着法
				case BLACK_J:
					
					//纵向
					ptTo.x = ptFrom.x ;

					//向前
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

					//向后
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


					//横向
					ptTo.y = ptFrom.y ;

					//向左
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

					//向右
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


//==========生成红马的着法
				case RED_M:
					
					//ptHalf用来存储马腿的位置，以判断该位置是否有子憋马腿

					ptHalf.x = ptFrom.x ;
					ptHalf.y = ptFrom.y + 1 ;
					if( ptHalf.y <= 8 && ! HaveMan( ptHalf ) )
					{
						//11点方向
						ptTo.x = ptFrom.x - 1 ;
						ptTo.y = ptFrom.y + 2 ;
						if( ptTo.x >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//1点方向
						ptTo.x = ptFrom.x + 1 ;
						ptTo.y = ptFrom.y + 2 ;
						if( ptTo.x <= 8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x + 1 ;
					ptHalf.y = ptFrom.y ;
					if( ptHalf.x <= 7 && ! HaveMan( ptHalf ) )
					{
						//2点方向
						ptTo.x = ptFrom.x + 2 ;
						ptTo.y = ptFrom.y + 1 ;
						if( ptTo.y <= 9 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//4点方向
						ptTo.x = ptFrom.x + 2 ;
						ptTo.y = ptFrom.y - 1 ;
						if( ptTo.y >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x ;
					ptHalf.y = ptFrom.y - 1 ;
					if( ptHalf.y >= 1 && ! HaveMan( ptHalf ) )
					{
						//5点方向
						ptTo.x = ptFrom.x + 1 ;
						ptTo.y = ptFrom.y - 2 ;
						if( ptTo.x <= 8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//7点方向
						ptTo.x = ptFrom.x - 1 ;
						ptTo.y = ptFrom.y - 2 ;
						if( ptTo.x >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x - 1 ;
					ptHalf.y = ptFrom.y ;
					if( ptHalf.x >= 1 && ! HaveMan( ptHalf ) )
					{
						//8点方向
						ptTo.x = ptFrom.x - 2 ;
						ptTo.y = ptFrom.y - 1 ;
						if( ptTo.y >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//10点方向
						ptTo.x = ptFrom.x - 2 ;
						ptTo.y = ptFrom.y + 1 ;
						if( ptTo.y <= 9 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					break;


//==========生成黑马的着法
				case BLACK_M:
					
					//ptHalf用来存储马腿的位置，以判断该位置是否有子憋马腿

					ptHalf.x = ptFrom.x ;
					ptHalf.y = ptFrom.y + 1 ;
					if( ptHalf.y <= 8 && ! HaveMan( ptHalf ) )
					{
						//5点方向
						ptTo.x = ptFrom.x - 1 ;
						ptTo.y = ptFrom.y + 2 ;
						if( ptTo.x >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//7点方向
						ptTo.x = ptFrom.x + 1 ;
						ptTo.y = ptFrom.y + 2 ;
						if( ptTo.x <= 8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x + 1 ;
					ptHalf.y = ptFrom.y ;
					if( ptHalf.x <= 7 && ! HaveMan( ptHalf ) )
					{
						//8点方向
						ptTo.x = ptFrom.x + 2 ;
						ptTo.y = ptFrom.y + 1 ;
						if( ptTo.y <= 9 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//10点方向
						ptTo.x = ptFrom.x + 2 ;
						ptTo.y = ptFrom.y - 1 ;
						if( ptTo.y >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x ;
					ptHalf.y = ptFrom.y - 1 ;
					if( ptHalf.y >= 1 && ! HaveMan( ptHalf ) )
					{
						//11点方向
						ptTo.x = ptFrom.x + 1 ;
						ptTo.y = ptFrom.y - 2 ;
						if( ptTo.x <= 8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//1点方向
						ptTo.x = ptFrom.x - 1 ;
						ptTo.y = ptFrom.y - 2 ;
						if( ptTo.x >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					ptHalf.x = ptFrom.x - 1 ;
					ptHalf.y = ptFrom.y ;
					if( ptHalf.x >= 1 && ! HaveMan( ptHalf ) )
					{
						//2点方向
						ptTo.x = ptFrom.x - 2 ;
						ptTo.y = ptFrom.y - 1 ;
						if( ptTo.y >= 0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//4点方向
						ptTo.x = ptFrom.x - 2 ;
						ptTo.y = ptFrom.y + 1 ;
						if( ptTo.y <= 9 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					break;


//==========生成红炮的着法
				case RED_P:

					//ptHalf用来存储炮是否有隔子打子的中间子

					//纵向
					ptTo.x = ptFrom.x ;

					//向前
					ptHalf.x = -1;	//标志尚未发现中间子
					for( ptTo.y = ptFrom.y + 1; ptTo.y <= 9; ptTo.y ++ )
					{
						if( ptHalf.x == -1 ) // 无中间子
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
						else // 已有中间子
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//向后
					ptHalf.x = -1;	//标志尚未发现中间子
					for( ptTo.y = ptFrom.y - 1; ptTo.y >= 0; ptTo.y -- )
					{
						if( ptHalf.x == -1 ) // 无中间子
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
						else // 已有中间子
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//横向
					ptTo.y = ptFrom.y ;

					//向左
					ptHalf.x = -1;	//标志尚未发现中间子
					for( ptTo.x = ptFrom.x - 1; ptTo.x >= 0; ptTo.x -- )
					{
						if( ptHalf.x == -1 ) // 无中间子
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
						else // 已有中间子
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//向右
					ptHalf.x = -1;	//标志尚未发现中间子
					for( ptTo.x = ptFrom.x + 1; ptTo.x <= 8; ptTo.x ++ )
					{
						if( ptHalf.x == -1 ) // 无中间子
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
						else // 已有中间子
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


//==========生成黑炮的着法
				case BLACK_P:

					//ptHalf用来存储炮是否有隔子打子的中间子

					//纵向
					ptTo.x = ptFrom.x ;

					//向后
					ptHalf.x = -1;	//标志尚未发现中间子
					for( ptTo.y = ptFrom.y + 1; ptTo.y <= 9; ptTo.y ++ )
					{
						if( ptHalf.x == -1 ) // 无中间子
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
						else // 已有中间子
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//向前
					ptHalf.x = -1;	//标志尚未发现中间子
					for( ptTo.y = ptFrom.y - 1; ptTo.y >= 0; ptTo.y -- )
					{
						if( ptHalf.x == -1 ) // 无中间子
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
						else // 已有中间子
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//横向
					ptTo.y = ptFrom.y ;

					//向右
					ptHalf.x = -1;	//标志尚未发现中间子
					for( ptTo.x = ptFrom.x - 1; ptTo.x >= 0; ptTo.x -- )
					{
						if( ptHalf.x == -1 ) // 无中间子
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
						else // 已有中间子
						{
							if( HaveMan( ptTo ) )
							{
								if( ! HaveFriend( ptTo, fSide ) )
									AddMoveToQueue( ptFrom, ptTo, nDepth );

								break;
							}
						}

					}

					//向左
					ptHalf.x = -1;	//标志尚未发现中间子
					for( ptTo.x = ptFrom.x + 1; ptTo.x <= 8; ptTo.x ++ )
					{
						if( ptHalf.x == -1 ) // 无中间子
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
						else // 已有中间子
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


//==========生成红相的着法
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


//==========生成黑象的着法
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


//==========生成红仕的着法
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


//==========生成黑士的着法
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


//==========生成红兵的着法
				case RED_B:

					//向前
					ptTo.x = ptFrom.x ;
					ptTo.y = ptFrom.y + 1 ;
					if( ptTo.y <=9 && ! HaveFriend( ptTo, fSide ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					if( ptFrom.y >= 5 ) //兵已过河
					{
						ptTo.y = ptFrom.y ;

						//向左
						ptTo.x = ptFrom.x - 1 ;
						if( ptTo.x >=0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//向右
						ptTo.x = ptFrom.x + 1 ;
						if( ptTo.x <=8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					break;


//==========生成黑卒的着法
				case BLACK_B:
					
					//向前
					ptTo.x = ptFrom.x ;
					ptTo.y = ptFrom.y - 1 ;
					if( ptTo.y >=0 && ! HaveFriend( ptTo, fSide ) )
						AddMoveToQueue( ptFrom, ptTo, nDepth );

					if( ptFrom.y <= 4 ) //兵已过河
					{
						ptTo.y = ptFrom.y ;

						//向右
						ptTo.x = ptFrom.x - 1 ;
						if( ptTo.x >=0 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );

						//向左
						ptTo.x = ptFrom.x + 1 ;
						if( ptTo.x <=8 && ! HaveFriend( ptTo, fSide ) )
							AddMoveToQueue( ptFrom, ptTo, nDepth );
					}

					break;

				}	// end switch
			
			}	// end if( CChessBoard[x][y] != 0 )

		}	// end for x 0 to 8, y 0 to 9

	return nMoveCount;	// 返回当前深度的走法总数
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
