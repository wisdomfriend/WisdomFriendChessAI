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

POINT PointList[20];		// Ŀ������
int nPointCount;			// Ŀ�����Ŀ

RelationTable RelationOfMan[9][10];	// ��ϵ��

const int MaxValue = 10000;	// ���ֵ����С��ֵΪ���ֵ�ĸ�ֵ��


//���ӵĻ�����ֵ��������ֵ��
//								���� ʿ�� �� �� ���� �ڣ� ��
const int BasicValues[15] = { 0,0, 250, 250, 300, 500, 300,  80, 
								0, 250, 250, 300, 500, 300,  80 };

//���ӵĻ����Լ�ֵ��ÿ��һ���߷����ӵķ֣�
//									���� ʿ�� �� �� ���� �ڣ� ��
const int MobilityValues[8] = {  0,  0,   1,   1,  12,   6,   6,  15 };


//���ӵĿ��������ֵ�����ڵ�λ�õļ�ֵ��
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
	{ // ˧
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
	{ // ʿ
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
	{ // ��  
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
	{ // ��
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
	{ // ��
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
	{ // ��
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
	{ // ��
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

// ��ֵ���������ضԵ�ǰ����Ĺ�ֵ��fWhoseTurn��־��ǰ�ֵ���һ������
int Eveluate( int fWhoseTurn );

// ��Ŀ������PointList����
inline void AddPointToQueue( BYTE x, BYTE y );



////////////////// Programmer-Defined Function //////////////////////////////////

int Eveluate( int fWhoseTurn )
{
	int RedValues	= 0;	// �췽�ܵķ�ֵ
	int BlackValues	= 0;	// �ڷ��ܵķ�ֵ

	int nBasicVal[2]	= { 0 , 0 };	// ˫��������ֵ
	int nMobilityVal[2]	= { 0 , 0 };	// ˫���Ļ�����ֵ
	int nPositionVal[2]	= { 0 , 0 };	// ˫���Ŀ�������ֵ
	int nRelationVal[2]	= { 0 , 0 };	// ˫���Ĺ�ϵֵ�������򱣻���

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


//++++++++++++++������ӵĻ�����ֵ�Լ�����ռ�ݵ�λ�õļ�ֵ+++++++++++++++++++++++++++++++++++++++++++++++
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


				//������ӵ�����Ŀ��λ�ã��ƶ����ġ������ġ������ģ�
				nPointCount = 0;

				switch( nCChessID )
				{

				case RED_K:

					// ��˧����
					i = IsKingFaceToFace( x, y, fSide );
					if( i != -1 )
						AddPointToQueue( x, i );

					//��ǰ
					if( y < 2 )
						AddPointToQueue( x, y + 1 );

					//���
					if( y > 0 )
						AddPointToQueue( x, y - 1 );

					//����
					if( x > 3 )
						AddPointToQueue( x - 1, y );

					//����
					if( x < 5 )
						AddPointToQueue( x + 1, y );

					break;


				case BLACK_K:

					// ��˧����
					i = IsKingFaceToFace( x, y, fSide );
					if( i != -1 )
						AddPointToQueue( x, i );

					//��ǰ
					if( y > 7 )
						AddPointToQueue( x, y - 1 );

					//���
					if( y < 9 )
						AddPointToQueue( x, y + 1 );

					//����
					if( x < 5 )
						AddPointToQueue( x + 1, y );

					//����
					if( x > 3 )
						AddPointToQueue( x - 1, y );

					break;


				case RED_J:					// fall through
				case BLACK_J:

					//����
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

					//����
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
						//11�㷽��(��Ժ���)
						if( x > 0 )
							AddPointToQueue( x - 1, y + 2 );

						//1�㷽��
						if( x < 8 )
							AddPointToQueue( x + 1, y + 2 );
					}

					if( x <= 6 && ! HaveMan( x + 1, y ) )
					{
						//2�㷽��
						if( y < 9 )
							AddPointToQueue( x + 2, y + 1 );

						//4�㷽��
						if( y > 0 )
							AddPointToQueue( x + 2, y - 1 );
					}

					if( y >= 2 && ! HaveMan( x, y - 1 ) )
					{		
						//5�㷽��
						if( x < 8 )
							AddPointToQueue( x + 1, y - 2 );

						//7�㷽��
						if( x > 0 )
							AddPointToQueue( x - 1, y - 2 );
					}

					if( x >= 2 && ! HaveMan( x - 1, y ) )
					{
						//8�㷽��
						if( y > 0 )
							AddPointToQueue( x - 2, y - 1 );

						//10�㷽��
						if( y < 9 )
							AddPointToQueue( x - 2, y + 1 );
					}

					break;


				case RED_P:				// fall through
				case BLACK_P:
					
					//����
					bHaveHalf = false;	//��־��δ�����м���
					for( i = y + 1; i <= 9; i ++ )
					{
						if( ! bHaveHalf ) // ���м���
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
						else // �����м���
						{
							if( HaveMan( x, i ) )
							{
								AddPointToQueue( x, i );
								break;
							}
						}
					}

					bHaveHalf = false;	//��־��δ�����м���
					for( i = y - 1; i >= 0; i -- )
					{
						if( ! bHaveHalf ) // ���м���
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
						else // �����м���
						{
							if( HaveMan( x, i ) )
							{
								AddPointToQueue( x, i );
								break;
							}
						}
					}


					//����
					bHaveHalf = false;	//��־��δ�����м���
					for( i = x - 1; i >= 0; i -- )
					{
						if( ! bHaveHalf ) // ���м���
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
						else // �����м���
						{
							if( HaveMan( i, y ) )
							{
								AddPointToQueue( i, y );
								break;
							}
						}
					}
 
					bHaveHalf = false;	//��־��δ�����м���
					for( i = x + 1; i <= 8; i ++ )
					{
						if( ! bHaveHalf ) // ���м���
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
						else // �����м���
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

					//��ǰ
					if( y < 9 )
						AddPointToQueue( x, y + 1 );

					if( y >= 5 ) //���ѹ���
					{
						//����
						if( x > 0 )
							AddPointToQueue( x - 1, y );

						//����
						if( x < 8 )
							AddPointToQueue( x + 1, y );
					}

					break;


				case BLACK_B:

					//��ǰ
					if( y > 0 )
						AddPointToQueue( x, y - 1 );

					if( y <= 4 ) //���ѹ���
					{
						//����
						if( x > 0 )
							AddPointToQueue( x - 1, y );

						//����
						if( x < 8 )
							AddPointToQueue( x + 1, y );
					}

					break;

				}	// end switch

			
				for( i = 0; i < nPointCount; i ++ )
				{
					nTargetType = CChessBoard[ PointList[i].x ][ PointList[i].y ]; //����Ŀ��λ�õ�����״��

//++++++++++++++������ӵĻ����Լ�ֵ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					// Ŀ��λ��Ϊ�գ������Լӷ�
					if( nTargetType == 0 )
					{
						if( fSide == RED )
							nMobilityVal[fSide] += MobilityValues[nCChessID];
						else
							nMobilityVal[fSide] += MobilityValues[nCChessID - 7];
					}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


					// Ŀ��λ��Ϊ�Է����ӣ�����Ϣ����RelationOfMan�е�UnderAttack
					else if( SideOfMan[nTargetType] != fSide )
					{
						//�����ܹ������������������
						if( nTargetType == RED_K )	
						{
							if( fWhoseTurn == BLACK )	// ��˧����������
							{
								return MaxValue - 10;	// ����ʧ�ܼ�ֵ������֤ӦΪ MaxValue ��
								// ��ȥ10��ʾ��������Ժ������Ѿ����Ե����
							}
							else						// �����ǽ������ѣ���ϵֵ��һ���
							{
								nRelationVal[RED] -= 20;
								continue;
							}

						}
						if( nTargetType == BLACK_K )	
						{
							if( fWhoseTurn == RED )		// �ڽ�����������
							{
								return MaxValue - 10;	// ����ʧ�ܼ�ֵ������֤ӦΪ MaxValue ��
								// ��ȥ10��ʾ��������Ժ������Ѿ����Ե����
							}
							else						// �����ǽ������ѣ���ϵֵ��һ���
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

					// Ŀ��λ��Ϊ�������ӣ�����Ϣ����RelationOfMan�е�UnderGuard
					else // if( SideOfMan[nTargetType] == fSide )
					{
						// ���ܱ������������򲻽��д�����Ϊ���ܱ�����������
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


//++++++++++++++������ӵĹ�ϵ��ֵ���ܹ������ܱ�����++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for( x = 0; x <= 8; x ++ )
		for( y = 0; y <= 9; y ++ )
		{
			int nAttack	= 0;		//���ڼ�¼������������
			int nGuard	= 0;		//���ڼ�¼������������
			int nMinAttack	= 777;	//���ڼ�¼��������С����
			int nMaxAttack	= 0;	//���ڼ�¼�������������
			//int nMinGuard	= 777;	//���ڼ�¼��������С����
			int nMaxGuard	= 0;	//���ڼ�¼�������������
			int nflagValue	= 777;	//���ڱ���Ƿ��й������������ڱ�������,��������ֵΪ���������������

			int nUnitValue;// ��λ��ֵ

			if( RelationOfMan[x][y].nCChessID != 0 )
			{
				nCChessID = RelationOfMan[x][y].nCChessID;
				fSide = SideOfMan[nCChessID];

				 nUnitValue = BasicValues[nCChessID] >> 3;	// ��λ��ֵȡ������ֵ��1/8


				// ͳ�ƹ�����������
				for( i = 0; i < RelationOfMan[x][y].nUAttackCount; i ++ )
				{
					// �鿴�Ƿ��й���������С�ڱ�����������,���м�¼����������С��
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

				// ͳ�Ʒ��ط�������
				for( i = 0; i < RelationOfMan[x][y].nUGuardCount; i ++ )
				{
					//if( BasicValues[ RelationOfMan[x][y].UnderGurad[i] ] < nMinGuard )
					//	nMinGuard = BasicValues[ RelationOfMan[x][y].UnderGurad[i] ];

					if( BasicValues[ RelationOfMan[x][y].UnderGurad[i] ] > nMaxGuard )
						nMaxGuard = BasicValues[ RelationOfMan[x][y].UnderGurad[i] ];

					nGuard += BasicValues[ RelationOfMan[x][y].UnderGurad[i] ];
				}


				if( nAttack == 0 )	// û�ܹ���������ֻ�б���
				{
					nRelationVal[fSide] += 5 * RelationOfMan[x][y].nUGuardCount ;
				}
				else				// ���ܹ���
				{
					if( nGuard == 0)	// û�б���
					{
						if( fWhoseTurn != fSide )	// �ֵ��Է�����
						{
							nRelationVal[fSide] -= 5 * nUnitValue ;
						}
						else						// �ֵ���������
						{
							nRelationVal[fSide] -=  nUnitValue ;
						}
					}
					else				// �б���
					{
						// ����������С�ڱ�����������,�Է���Ը�⻻��
						if( nflagValue != 777 )	
						{
							if( fWhoseTurn != fSide )	// �ֵ��Է�����
							{
								nRelationVal[fSide]		-= 5 * nUnitValue ;
								nRelationVal[1 - fSide]	-= 5 * ( nflagValue >> 3 );
							}
							else						// �ֵ���������
							{
								nRelationVal[fSide]		-=  nUnitValue ;
								nRelationVal[1 - fSide]	-=  ( nflagValue >> 3 );
							}
						}
						// �๥��\��������������ҹ�������С����С�ڱ������������뱣��������֮��
						//,��Է�������һ�ӻ�����
						else if( RelationOfMan[x][y].nUGuardCount == 1 
								&& RelationOfMan[x][y].nUAttackCount > 1 
								&& nMinAttack < BasicValues[nCChessID] + nGuard )
						{
							if( fWhoseTurn != fSide )	// �ֵ��Է�����
							{
								nRelationVal[fSide]		-= 5 * nUnitValue ;
								nRelationVal[fSide]		-= 5 * ( nGuard >> 3 );

								nRelationVal[1 - fSide]	-= 5 * ( nMinAttack >> 3 );
							}
							else						// �ֵ���������
							{
								nRelationVal[fSide]		-=  nUnitValue ;
								nRelationVal[fSide]		-=  ( nGuard >> 3 );

								nRelationVal[1 - fSide]	-=  ( nMinAttack >> 3 );
							}
						}
						// ������\��������������ҹ�����������С�Ķ���֮��С�ڱ������������뱣��������֮��
						//,��Է����������ӻ�����
						else if( RelationOfMan[x][y].nUGuardCount == 2 
								&& RelationOfMan[x][y].nUAttackCount == 3 
								&& ( nAttack - nMaxAttack ) < ( BasicValues[nCChessID] + nGuard ) )
						{
							if( fWhoseTurn != fSide )	// �ֵ��Է�����
							{
								nRelationVal[fSide]		-= 5 * nUnitValue ;
								nRelationVal[fSide]		-= 5 * ( nGuard >> 3 );

								nRelationVal[1 - fSide]	-= 5 * ( ( nAttack - nMaxAttack ) >> 3 );
							}
							else						// �ֵ���������
							{
								nRelationVal[fSide]		-=  nUnitValue ;
								nRelationVal[fSide]		-=  ( nGuard >> 3 );

								nRelationVal[1 - fSide]	-=  ( ( nAttack - nMaxAttack ) >> 3 );
							}
						}
						// �������뱣����������ͬ���ҹ���������С�ڱ������������뱣��������֮��
						//�ټ�ȥ���������������,��Է�������n�ӻ�n��
						else if( RelationOfMan[x][y].nUAttackCount == RelationOfMan[x][y].nUGuardCount  
								 && nAttack < BasicValues[nCChessID] + nGuard - nMaxGuard )
						{
							if( fWhoseTurn != fSide )	// �ֵ��Է�����
							{
								nRelationVal[fSide]		-= 5 * nUnitValue ;
								nRelationVal[fSide]		-= 5 * ( ( nGuard - nMaxGuard ) >> 3 );

								nRelationVal[1 - fSide]	-= 5 * ( nAttack >> 3 );
							}
							else						// �ֵ���������
							{
								nRelationVal[fSide]		-=  nUnitValue ;
								nRelationVal[fSide]		-=  ( ( nGuard - nMaxGuard ) >> 3 );

								nRelationVal[1 - fSide]	-=  ( nAttack >> 3 );
							}
						}
						else
						{
							//��������ѻ�������������,������������ʱ��������
						}

					}	// end �б���

				}	// end ���ܹ���

			}	// end if( RelationOfMan[x][y].nCChessID != 0 )

		}	// end for x 0 to 8, y 0 to 9
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	// ͳ�ƺ췽�ܷ�ֵ
	RedValues	= nBasicVal[RED] + nPositionVal[RED]
					+ nMobilityVal[RED] + nRelationVal[RED] ;

	// ͳ�ƺڷ��ܷ�ֵ
	BlackValues	= nBasicVal[BLACK] + nPositionVal[BLACK] 
					+ nMobilityVal[BLACK] + nRelationVal[BLACK] ;


	if( fWhoseTurn == RED )
		return ( RedValues - BlackValues )  + rand()%3 ;	//�˴� +rand()%X ��ͨ����һ������Է�ֵ
	else													//��ɴ��Ӱ�����������ڵ�����Ӧ��ͬ
		return ( BlackValues - RedValues )  + rand()%3 ;	//һ���·�ʱ����ÿ�ζ�����ͬ�Ļ�Ӧ��
															//�������Լ�Xȡ3�Ƿ���ʻ��д�ʵ�����顭��
}

inline void AddPointToQueue( BYTE x, BYTE y )
{
	PointList[nPointCount].x = x ;
	PointList[nPointCount].y = y ;

	nPointCount ++;
}
