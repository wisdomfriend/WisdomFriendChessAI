// CChessEvaluate.h


////////////////////// Type Define /////////////////////////////////////////////

typedef struct _relationtable{

	BYTE nCChessID ;
	int nUAttackCount ;
	int nUGuardCount ;
	BYTE UnderAttack[5];
	BYTE UnderGurad[5];

} RelationTable;



/////////////////// Data Define ////////////////////////////////////////////////

POINT PointList[20];		// 目标点队列
int nPointCount;			// 目标点数目

RelationTable RelationOfMan[9][10];	// 关系表

const int MaxValue = 10000;	// 最大极值（最小极值为最大极值的负值）


//各子的基本价值（子力价值）
//								将， 士， 象， 马， 车， 炮， 卒
const int BasicValues[15] = { 0,0, 250, 250, 300, 500, 300,  80, 
								0, 250, 250, 300, 500, 300,  80 };

//各子的机动性价值（每多一步走法所加的分）
//									将， 士， 象， 马， 车， 炮， 卒
const int MobilityValues[8] = {  0,  0,   1,   1,  12,   6,   6,  15 };


//各子的控制区域价值（所在的位置的价值）
const int PositionValues[8][90] = {
	{
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	}, 
	{ // 帅
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		1, -8, -9,  0,  0,  0,  0,  0,  0,  0,
		5, -8, -9,  0,  0,  0,  0,  0,  0,  0,
		1, -8, -9,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	}, 
	{ // 士
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  3,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	}, 
	{ // 相  
		0,  0, -2,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  3,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0, -2,  0,  0,  0,  0,  0,  0,  0
	}, 
	{ // 马
		 0, -3,  5,  4,  2,  2,  5,  4,  2,  2,
		-3,  2,  4,  6, 10, 12, 20, 10,  8,  2,
		 2,  4,  6, 10, 13, 11, 12, 11, 15,  2,
		 0,  5,  7,  7, 14, 15, 19, 15,  9,  8,
		 2,-10,  4, 10, 15, 16, 12, 11,  6,  2,
		 0,  5,  7,  7, 14, 15, 19, 15,  9,  8,
		 2,  4,  6, 10, 13, 11, 12, 11, 15,  2,
		-3,  2,  4,  6, 10, 12, 20, 10,  8,  2,
		 0, -3,  5,  4,  2,  2,  5,  4,  2,  2
	}, 
	{ // 车
		-6,  5, -2,  4,  8,  8,  6,  6,  6,  6,
		 6,  8,  8,  9, 12, 11, 13,  8, 12,  8,
		 4,  6,  4,  4, 12, 11, 13,  7,  9,  7,
		12, 12, 12, 12, 14, 14, 16, 14, 16, 13,
		 0,  0, 12, 14, 15, 15, 16, 16, 33, 14,
		12, 12, 12, 12, 14, 14, 16, 14, 16, 13,
		 4,  6,  4,  4, 12, 11, 13,  7,  9,  7,
		 6,  8,  8,  9, 12, 11, 13,  8, 12,  8,
		-6,  5, -2,  4,  8,  8,  6,  6,  6,  6
	}, 
	{ // 炮
		0,  0,  1,  0, -1,  0,  0,  1,  2,  4,
		0,  1,  0,  0,  0,  0,  3,  1,  2,  4,
		1,  2,  4,  0,  3,  0,  3,  0,  0,  0,
		3,  2,  3,  0,  0,  0,  2, -5, -4, -5,
		3,  2,  5,  0,  4,  4,  4, -4, -7, -6,
		3,  2,  3,  0,  0,  0,  2, -5, -4, -5,
		1,  2,  4,  0,  3,  0,  3,  0,  0,  0,
		0,  1,  0,  0,  0,  0,  3,  1,  2,  4,
		0,  0,  1,  0, -1,  0,  0,  1,  2,  4
	}, 
	{ // 兵
		0,  0,  0, -2,  3, 10, 20, 20, 20,  0,
		0,  0,  0,  0,  0, 18, 27, 30, 30,  0,
		0,  0,  0, -2,  4, 22, 30, 45, 50,  0,
		0,  0,  0,  0,  0, 35, 40, 55, 65,  2,
		0,  0,  0,  6,  7, 40, 42, 55, 70,  4,
		0,  0,  0,  0,  0, 35, 40, 55, 65,  2,
		0,  0,  0, -2,  4, 22, 30, 45, 50,  0,
		0,  0,  0,  0,  0, 18, 27, 30, 30,  0,
		0,  0,  0, -2,  3, 10, 20, 20, 20,  0
	}
};


/////////////////// Function Prototype /////////////////////////////////////////

// 估值函数，返回对当前局面的估值。fWhoseTurn标志当前轮到哪一方走棋
int Eveluate( int fWhoseTurn );

// 将目标点加入PointList队列
inline void AddPointToQueue( BYTE x, BYTE y );



////////////////// Programmer-Defined Function //////////////////////////////////

int Eveluate( int fWhoseTurn )
{
	int RedValues	= 0;	// 红方总的分值
	int BlackValues	= 0;	// 黑方总的分值

	int nBasicVal[2]	= { 0 , 0 };	// 双方的子力值
	int nMobilityVal[2]	= { 0 , 0 };	// 双方的机动性值
	int nPositionVal[2]	= { 0 , 0 };	// 双方的控制区域值
	int nRelationVal[2]	= { 0 , 0 };	// 双方的关系值（攻击或保护）

	BYTE nCChessID;
	BYTE nTargetType;
	int fSide;
	int nPosition;
	int i;
	bool bHaveHalf;


	//**** Reset RelationTable ****
	memset( RelationOfMan, 0, sizeof(RelationTable)*90 );

	int x, y;
	for( x = 0; x <= 8; x ++ )
		for( y = 0; y <= 9; y ++ )
		{
			if( CChessBoard[x][y] != 0 )
			{
				nCChessID = CChessBoard[x][y];
				fSide = SideOfMan[ nCChessID ];


//++++++++++++++求得棋子的基本价值以及它所占据的位置的价值+++++++++++++++++++++++++++++++++++++++++++++++
				nPosition = x * 10 + y * 9 ;

				if( fSide == RED )
				{
					nBasicVal[fSide]	+= BasicValues[nCChessID];
					nPositionVal[fSide]	+= PositionValues[nCChessID][nPosition];
				}
				else
				{
					nBasicVal[fSide]	+= BasicValues[nCChessID];
					nPositionVal[fSide]	+= PositionValues[nCChessID - 7][89 - nPosition];
				}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


				//求得棋子的所有目标位置（移动到的、攻击的、保护的）
				nPointCount = 0;

				switch( nCChessID )
				{

				case RED_K:

					// 将帅碰面
					i = IsKingFaceToFace( x, y, fSide );
					if( i != -1 )
						AddPointToQueue( x, i );

					//向前
					if( y < 2 )
						AddPointToQueue( x, y + 1 );

					//向后
					if( y > 0 )
						AddPointToQueue( x, y - 1 );

					//向左
					if( x > 3 )
						AddPointToQueue( x - 1, y );

					//向右
					if( x < 5 )
						AddPointToQueue( x + 1, y );

					break;


				case BLACK_K:

					// 将帅碰面
					i = IsKingFaceToFace( x, y, fSide );
					if( i != -1 )
						AddPointToQueue( x, i );

					//向前
					if( y > 7 )
						AddPointToQueue( x, y - 1 );

					//向后
					if( y < 9 )
						AddPointToQueue( x, y + 1 );

					//向左
					if( x < 5 )
						AddPointToQueue( x + 1, y );

					//向右
					if( x > 3 )
						AddPointToQueue( x - 1, y );

					break;


				case RED_J:					// fall through
				case BLACK_J:

					//纵向
					for( i = y + 1; i <= 9; i ++ )
					{
						AddPointToQueue( x, i );

						if( HaveMan( x, i ) )
							break;
					}

					for( i = y - 1; i >= 0; i -- )
					{
						AddPointToQueue( x, i );

						if( HaveMan( x, i ) )
							break;
					}

					//横向
					for( i = x - 1; i >= 0; i -- )
					{
						AddPointToQueue( i, y );

						if( HaveMan( i, y ) )
							break;
					}

					for( i = x + 1; i <= 8; i ++ )
					{
						AddPointToQueue( i, y );

						if( HaveMan( i, y ) )
							break;
					}

					break;


				case RED_M:					// fall through
				case BLACK_M:

					if( y <= 7 && ! HaveMan( x, y + 1 ) )
					{
						//11点方向(相对红马)
						if( x > 0 )
							AddPointToQueue( x - 1, y + 2 );

						//1点方向
						if( x < 8 )
							AddPointToQueue( x + 1, y + 2 );
					}

					if( x <= 6 && ! HaveMan( x + 1, y ) )
					{
						//2点方向
						if( y < 9 )
							AddPointToQueue( x + 2, y + 1 );

						//4点方向
						if( y > 0 )
							AddPointToQueue( x + 2, y - 1 );
					}

					if( y >= 2 && ! HaveMan( x, y - 1 ) )
					{		
						//5点方向
						if( x < 8 )
							AddPointToQueue( x + 1, y - 2 );

						//7点方向
						if( x > 0 )
							AddPointToQueue( x - 1, y - 2 );
					}

					if( x >= 2 && ! HaveMan( x - 1, y ) )
					{
						//8点方向
						if( y > 0 )
							AddPointToQueue( x - 2, y - 1 );

						//10点方向
						if( y < 9 )
							AddPointToQueue( x - 2, y + 1 );
					}

					break;


				case RED_P:				// fall through
				case BLACK_P:
					
					//纵向
					bHaveHalf = false;	//标志尚未发现中间子
					for( i = y + 1; i <= 9; i ++ )
					{
						if( ! bHaveHalf ) // 无中间子
						{
							if( ! HaveMan( x, i ) )
							{
								AddPointToQueue( x, i );
							}
							else // if( HaveMan( x, i ) )
							{
								bHaveHalf = true;
							}
						}
						else // 已有中间子
						{
							if( HaveMan( x, i ) )
							{
								AddPointToQueue( x, i );
								break;
							}
						}
					}

					bHaveHalf = false;	//标志尚未发现中间子
					for( i = y - 1; i >= 0; i -- )
					{
						if( ! bHaveHalf ) // 无中间子
						{
							if( ! HaveMan( x, i ) )
							{
								AddPointToQueue( x, i );
							}
							else // if( HaveMan( x, i ) )
							{
								bHaveHalf = true;
							}
						}
						else // 已有中间子
						{
							if( HaveMan( x, i ) )
							{
								AddPointToQueue( x, i );
								break;
							}
						}
					}


					//横向
					bHaveHalf = false;	//标志尚未发现中间子
					for( i = x - 1; i >= 0; i -- )
					{
						if( ! bHaveHalf ) // 无中间子
						{
							if( ! HaveMan( i, y ) )
							{
								AddPointToQueue( i, y );
							}
							else // if( HaveMan( i, y ) )
							{
								bHaveHalf = true;
							}
						}
						else // 已有中间子
						{
							if( HaveMan( i, y ) )
							{
								AddPointToQueue( i, y );
								break;
							}
						}
					}
 
					bHaveHalf = false;	//标志尚未发现中间子
					for( i = x + 1; i <= 8; i ++ )
					{
						if( ! bHaveHalf ) // 无中间子
						{
							if( ! HaveMan( i, y ) )
							{
								AddPointToQueue( i, y );
							}
							else // if( HaveMan( i, y ) )
							{
								bHaveHalf = true;
							}
						}
						else // 已有中间子
						{
							if( HaveMan( i, y ) )
							{
								AddPointToQueue( i, y );
								break;
							}
						}
					}

					break;


				case RED_X:

					if( x == 0 )
					{
						if( ! HaveMan(1, 3) )
							AddPointToQueue( 2, 4 );

						if( ! HaveMan(1, 1) )
							AddPointToQueue( 2, 0 );
					}
					else if( x == 2 )
					{
						if( y == 4 )
						{
							if( ! HaveMan(1, 3) )
								AddPointToQueue( 0, 2 );

							if( ! HaveMan(3, 3) )
								AddPointToQueue( 4, 2 );
						}
						else // y == 0 
						{
							if( ! HaveMan(1, 1) )
								AddPointToQueue( 0, 2 );

							if( ! HaveMan(3, 1) )
								AddPointToQueue( 4, 2 );
						}	
					}
					else if( x == 4 )
					{
						if( ! HaveMan(3, 3) )
							AddPointToQueue( 2, 4 );

						if( ! HaveMan(3, 1) )
							AddPointToQueue( 2, 0 );

						if( ! HaveMan(5, 3) )
							AddPointToQueue( 6, 4 );

						if( ! HaveMan(5, 1) )
							AddPointToQueue( 6, 0 );
					}
					else if( x == 6 )
					{
						if( y == 4 )
						{
							if( ! HaveMan(5, 3) )
								AddPointToQueue( 4, 2 );

							if( ! HaveMan(7, 3) )
								AddPointToQueue( 8, 2 );
						}
						else //  y == 0 
						{
							if( ! HaveMan(5, 1) )
								AddPointToQueue( 4, 2 );

							if( ! HaveMan(7, 1) )
								AddPointToQueue( 8, 2 );
						}	
					}
					else // x == 8
					{
						if( ! HaveMan(7, 3) )
							AddPointToQueue( 6, 4 );

						if( ! HaveMan(7, 1) )
							AddPointToQueue( 6, 0 );
					}

					break;


				case BLACK_X:

					if( x == 0 )
					{
						if( ! HaveMan(1, 6) )
							AddPointToQueue( 2, 5 );

						if( ! HaveMan(1, 8) )
							AddPointToQueue( 2, 9 );
					}
					else if( x == 2 )
					{
						if( y == 5 )
						{
							if( ! HaveMan(1, 6) )
								AddPointToQueue( 0, 7 );

							if( ! HaveMan(3, 6) )
								AddPointToQueue( 4, 7 );
						}
						else // y == 9 
						{
							if( ! HaveMan(1, 8) )
								AddPointToQueue( 0, 7 );

							if( ! HaveMan(3, 8) )
								AddPointToQueue( 4, 7 );
						}	
					}
					else if( x == 4 )
					{
						if( ! HaveMan(3, 6) )
							AddPointToQueue( 2, 5 );

						if( ! HaveMan(3, 8) )
							AddPointToQueue( 2, 9 );

						if( ! HaveMan(5, 6) )
							AddPointToQueue( 6, 5 );

						if( ! HaveMan(5, 8) )
							AddPointToQueue( 6, 9 );
					}
					else if( x == 6 )
					{
						if( y == 5 )
						{
							if( ! HaveMan(5, 6) )
								AddPointToQueue( 4, 7 );

							if( ! HaveMan(7, 6) )
								AddPointToQueue( 8, 7 );
						}
						else // y == 9 
						{
							if( ! HaveMan(5, 8) )
								AddPointToQueue( 4, 7 );

							if( ! HaveMan(7, 8) )
								AddPointToQueue( 8, 7 );
						}	
					}
					else // x == 8
					{
						if( ! HaveMan(7, 6) )
							AddPointToQueue( 6, 5 );

						if( ! HaveMan(7, 8) )
							AddPointToQueue( 6, 9 );
					}

					break;


				case RED_S:

					if( x == 3 )
					{
						AddPointToQueue( 4, 1 );
					}
					else if( x == 4 )
					{
						AddPointToQueue( 3, 2 );

						AddPointToQueue( 3, 0 );

						AddPointToQueue( 5, 2 );

						AddPointToQueue( 5, 0 );
					}
					else //  x == 5
					{
						AddPointToQueue( 4, 1 );
					}

					break;


				case BLACK_S:

					if( x == 3 )
					{
						AddPointToQueue( 4, 8 );
					}
					else if( x == 4 )
					{
						AddPointToQueue( 3, 7 );

						AddPointToQueue( 3, 9 );

						AddPointToQueue( 5, 7 );

						AddPointToQueue( 5, 9 );
					}
					else // x == 5
					{
						AddPointToQueue( 4, 8 );
					}

					break;


				case RED_B:

					//向前
					if( y < 9 )
						AddPointToQueue( x, y + 1 );

					if( y >= 5 ) //兵已过河
					{
						//向左
						if( x > 0 )
							AddPointToQueue( x - 1, y );

						//向右
						if( x < 8 )
							AddPointToQueue( x + 1, y );
					}

					break;


				case BLACK_B:

					//向前
					if( y > 0 )
						AddPointToQueue( x, y - 1 );

					if( y <= 4 ) //兵已过河
					{
						//向右
						if( x > 0 )
							AddPointToQueue( x - 1, y );

						//向左
						if( x < 8 )
							AddPointToQueue( x + 1, y );
					}

					break;

				}	// end switch

			
				for( i = 0; i < nPointCount; i ++ )
				{
					nTargetType = CChessBoard[ PointList[i].x ][ PointList[i].y ]; //保存目标位置的棋子状况

//++++++++++++++求得棋子的机动性价值++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					// 目标位置为空，机动性加分
					if( nTargetType == 0 )
					{
						if( fSide == RED )
							nMobilityVal[fSide] += MobilityValues[nCChessID];
						else
							nMobilityVal[fSide] += MobilityValues[nCChessID - 7];
					}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


					// 目标位置为对方棋子，将信息存入RelationOfMan中的UnderAttack
					else if( SideOfMan[nTargetType] != fSide )
					{
						//对王受攻击的情况作单独处理
						if( nTargetType == RED_K )	
						{
							if( fWhoseTurn == BLACK )	// 红帅即将被将死
							{
								return MaxValue - 10;	// 返回失败极值（已验证应为 MaxValue ）
								// 减去10表示此种情况稍好于王已经被吃的情况
							}
							else						// 仅仅是将军而已，关系值扣一点分
							{
								nRelationVal[RED] -= 20;
								continue;
							}

						}
						if( nTargetType == BLACK_K )	
						{
							if( fWhoseTurn == RED )		// 黑将即将被将死
							{
								return MaxValue - 10;	// 返回失败极值（已验证应为 MaxValue ）
								// 减去10表示此种情况稍好于王已经被吃的情况
							}
							else						// 仅仅是将军而已，关系值扣一点分
							{
								nRelationVal[BLACK] -= 20;
								continue;
							}
						}

						RelationOfMan[ PointList[i].x ][ PointList[i].y ]
						.nCChessID	=	nTargetType ;

						RelationOfMan[ PointList[i].x ][ PointList[i].y ]
						.UnderAttack[RelationOfMan[ PointList[i].x ][ PointList[i].y ].nUAttackCount ++]
							=	nCChessID ;

					}

					// 目标位置为己方棋子，将信息存入RelationOfMan中的UnderGuard
					else // if( SideOfMan[nTargetType] == fSide )
					{
						// 若受保护的是王，则不进行处理。因为王受保护毫无意义
						if( nTargetType == RED_K || nTargetType == BLACK_K )
							continue;

						RelationOfMan[ PointList[i].x ][ PointList[i].y ]
						.nCChessID	=	nTargetType ;

						RelationOfMan[ PointList[i].x ][ PointList[i].y ]
						.UnderGurad[RelationOfMan[ PointList[i].x ][ PointList[i].y ].nUGuardCount ++]
							=	nCChessID ;
					}

				}	// end for( i = 0; i < nPointCount; i ++ )

			}	// end if( CChessBoard[x][y] != 0 )

		}	// end for x 0 to 8, y 0 to 9


//++++++++++++++求得棋子的关系价值（受攻击和受保护）++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for( x = 0; x <= 8; x ++ )
		for( y = 0; y <= 9; y ++ )
		{
			int nAttack	= 0;		//用于记录攻击方总子力
			int nGuard	= 0;		//用于记录保护方总子力
			int nMinAttack	= 777;	//用于记录攻击方最小子力
			int nMaxAttack	= 0;	//用于记录攻击方最大子力
			//int nMinGuard	= 777;	//用于记录保护方最小子力
			int nMaxGuard	= 0;	//用于记录保护方最大子力
			int nflagValue	= 777;	//用于表记是否有攻击方子力低于被攻击者,若有则其值为攻击方中最低子力

			int nUnitValue;// 单位价值

			if( RelationOfMan[x][y].nCChessID != 0 )
			{
				nCChessID = RelationOfMan[x][y].nCChessID;
				fSide = SideOfMan[nCChessID];

				 nUnitValue = BasicValues[nCChessID] >> 3;	// 单位价值取基本价值的1/8


				// 统计攻击方的子力
				for( i = 0; i < RelationOfMan[x][y].nUAttackCount; i ++ )
				{
					// 查看是否有攻击者子力小于被攻击者子力,若有记录其中子力最小的
					if( BasicValues[ RelationOfMan[x][y].UnderAttack[i] ] < BasicValues[nCChessID] 
						&& BasicValues[ RelationOfMan[x][y].UnderAttack[i] ] < nflagValue )
					{
							nflagValue =  BasicValues[ RelationOfMan[x][y].UnderAttack[i] ] ;
					}
					
					if( BasicValues[ RelationOfMan[x][y].UnderAttack[i] ] < nMinAttack )
						nMinAttack = BasicValues[ RelationOfMan[x][y].UnderAttack[i] ];

					if( BasicValues[ RelationOfMan[x][y].UnderAttack[i] ] > nMaxAttack )
						nMaxAttack = BasicValues[ RelationOfMan[x][y].UnderAttack[i] ];

					nAttack += BasicValues[ RelationOfMan[x][y].UnderAttack[i] ];
				}

				// 统计防守方的子力
				for( i = 0; i < RelationOfMan[x][y].nUGuardCount; i ++ )
				{
					//if( BasicValues[ RelationOfMan[x][y].UnderGurad[i] ] < nMinGuard )
					//	nMinGuard = BasicValues[ RelationOfMan[x][y].UnderGurad[i] ];

					if( BasicValues[ RelationOfMan[x][y].UnderGurad[i] ] > nMaxGuard )
						nMaxGuard = BasicValues[ RelationOfMan[x][y].UnderGurad[i] ];

					nGuard += BasicValues[ RelationOfMan[x][y].UnderGurad[i] ];
				}


				if( nAttack == 0 )	// 没受攻击，而是只有保护
				{
					nRelationVal[fSide] += 5 * RelationOfMan[x][y].nUGuardCount ;
				}
				else				// 遭受攻击
				{
					if( nGuard == 0)	// 没有保护
					{
						if( fWhoseTurn != fSide )	// 轮到对方行棋
						{
							nRelationVal[fSide] -= 5 * nUnitValue ;
						}
						else						// 轮到己方行棋
						{
							nRelationVal[fSide] -=  nUnitValue ;
						}
					}
					else				// 有保护
					{
						// 攻击者子力小于被攻击者子力,对方将愿意换子
						if( nflagValue != 777 )	
						{
							if( fWhoseTurn != fSide )	// 轮到对方行棋
							{
								nRelationVal[fSide]		-= 5 * nUnitValue ;
								nRelationVal[1 - fSide]	-= 5 * ( nflagValue >> 3 );
							}
							else						// 轮到己方行棋
							{
								nRelationVal[fSide]		-=  nUnitValue ;
								nRelationVal[1 - fSide]	-=  ( nflagValue >> 3 );
							}
						}
						// 多攻击\单保护的情况并且攻击者最小子力小于被攻击者子力与保护者子力之和
						//,则对方可能以一子换两子
						else if( RelationOfMan[x][y].nUGuardCount == 1 
								&& RelationOfMan[x][y].nUAttackCount > 1 
								&& nMinAttack < BasicValues[nCChessID] + nGuard )
						{
							if( fWhoseTurn != fSide )	// 轮到对方行棋
							{
								nRelationVal[fSide]		-= 5 * nUnitValue ;
								nRelationVal[fSide]		-= 5 * ( nGuard >> 3 );

								nRelationVal[1 - fSide]	-= 5 * ( nMinAttack >> 3 );
							}
							else						// 轮到己方行棋
							{
								nRelationVal[fSide]		-=  nUnitValue ;
								nRelationVal[fSide]		-=  ( nGuard >> 3 );

								nRelationVal[1 - fSide]	-=  ( nMinAttack >> 3 );
							}
						}
						// 三攻击\两保护的情况并且攻击者子力较小的二者之和小于被攻击者子力与保护者子力之和
						//,则对方可能以两子换三子
						else if( RelationOfMan[x][y].nUGuardCount == 2 
								&& RelationOfMan[x][y].nUAttackCount == 3 
								&& ( nAttack - nMaxAttack ) < ( BasicValues[nCChessID] + nGuard ) )
						{
							if( fWhoseTurn != fSide )	// 轮到对方行棋
							{
								nRelationVal[fSide]		-= 5 * nUnitValue ;
								nRelationVal[fSide]		-= 5 * ( nGuard >> 3 );

								nRelationVal[1 - fSide]	-= 5 * ( ( nAttack - nMaxAttack ) >> 3 );
							}
							else						// 轮到己方行棋
							{
								nRelationVal[fSide]		-=  nUnitValue ;
								nRelationVal[fSide]		-=  ( nGuard >> 3 );

								nRelationVal[1 - fSide]	-=  ( ( nAttack - nMaxAttack ) >> 3 );
							}
						}
						// 攻击方与保护方数量相同并且攻击者子力小于被攻击者子力与保护者子力之和
						//再减去保护者中最大子力,则对方可能以n子换n子
						else if( RelationOfMan[x][y].nUAttackCount == RelationOfMan[x][y].nUGuardCount  
								 && nAttack < BasicValues[nCChessID] + nGuard - nMaxGuard )
						{
							if( fWhoseTurn != fSide )	// 轮到对方行棋
							{
								nRelationVal[fSide]		-= 5 * nUnitValue ;
								nRelationVal[fSide]		-= 5 * ( ( nGuard - nMaxGuard ) >> 3 );

								nRelationVal[1 - fSide]	-= 5 * ( nAttack >> 3 );
							}
							else						// 轮到己方行棋
							{
								nRelationVal[fSide]		-=  nUnitValue ;
								nRelationVal[fSide]		-=  ( ( nGuard - nMaxGuard ) >> 3 );

								nRelationVal[1 - fSide]	-=  ( nAttack >> 3 );
							}
						}
						else
						{
							//上述情况已基本涵盖最常见情况,因而其它情况暂时不做考虑
						}

					}	// end 有保护

				}	// end 遭受攻击

			}	// end if( RelationOfMan[x][y].nCChessID != 0 )

		}	// end for x 0 to 8, y 0 to 9
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	// 统计红方总分值
	RedValues	= nBasicVal[RED] + nPositionVal[RED]
					+ nMobilityVal[RED] + nRelationVal[RED] ;

	// 统计黑方总分值
	BlackValues	= nBasicVal[BLACK] + nPositionVal[BLACK] 
					+ nMobilityVal[BLACK] + nRelationVal[BLACK] ;


	if( fWhoseTurn == RED )
		return ( RedValues - BlackValues )  + rand()%3 ;	//此处 +rand()%X 是通过加一个不会对分值
	else													//造成大的影响的随机量以期电脑在应对同
		return ( BlackValues - RedValues )  + rand()%3 ;	//一种下法时不会每次都有相同的回应。
															//这样做以及X取3是否合适还有待实践检验……
}

inline void AddPointToQueue( BYTE x, BYTE y )
{
	PointList[nPointCount].x = x ;
	PointList[nPointCount].y = y ;

	nPointCount ++;
}
