// SortMove.h


/////////////////// Data Define ////////////////////////////////////////////////

CCHESSMOVE cmTargetBuffer[80];		//�����õĻ������



/////////////////// Function Prototype /////////////////////////////////////////

// �Գ���ΪnCount���ŷ�����cmSource���й鲢����
void MergeSort( CCHESSMOVE *cmSource, int nCount );		

// ΪMergeSort���������ã��鲢������β��ӵ��������飬
void MergePass( CCHESSMOVE *cmSource, CCHESSMOVE *cmTarget, int nLength, int nCount  ); 

// ΪMergePass���������ã��鲢������β��ӵ��������飨�����������ѷֱ��ź��򣩣����������� ������
// ��������ΪcmSource[beginOne]--cmSource[endOne]; cmSource[beginTwo]--cmSource[endTwo]. ����beginTwo = endOne + 1
inline void Merge_Desc( CCHESSMOVE *cmSource, CCHESSMOVE *cmTarget, int beginOne ,int endOne, int endTwo );



////////////////// Programmer-Defined Function //////////////////////////////////

void MergeSort( CCHESSMOVE *cmSource, int nCount )
{
	int nLength = 1;

	// ����cmTargetBuffer��cmSource���й鲢����
	while( nLength < nCount )
	{
		MergePass( cmSource , cmTargetBuffer , nLength , nCount );
		nLength += nLength ;
		MergePass( cmTargetBuffer , cmSource , nLength , nCount );
		nLength += nLength ;
	}
}

void MergePass( CCHESSMOVE *cmSource, CCHESSMOVE *cmTarget, int nLength, int nCount  )
{
	int i = 0;	// ��Ǵ�����ĵ�һ����������

	while( i + 2 * nLength <= nCount ) // ʣ���Ԫ�ظ������ڵ�������nLength����
	{
		// �鲢���򳤶�Ϊ nLength ����β��ӵ���������
		Merge_Desc( cmSource, cmTarget, i, i + nLength - 1, i + 2 * nLength - 1 );

		i += 2 * nLength ;
	}

	if( i + nLength < nCount )	// ʣ���Ԫ�ظ���С������nLength���ȵ�����һ��nLength����
	{
		// �鲢���򳤶�Ϊ nLength �������������ӵ�ʣ�µ�����Ԫ����ɵ�����
		Merge_Desc( cmSource, cmTarget, i, i + nLength - 1, nCount - 1 );
	}
	else						// ʣ���Ԫ�ظ���С�ڵ���һ��nLength����
	{
		int j;
		// ����ʣ�µ��Ѿ�����õ�����
		for ( j = i ; j < nCount ; j ++ )
			cmTarget[j] = cmSource[j];
	}

}

inline void Merge_Desc( CCHESSMOVE *cmSource, CCHESSMOVE *cmTarget, int beginOne ,int endOne, int endTwo )
{
	int i = beginOne ,
		j = endOne + 1,// j = beginTwo
		k = beginOne ;

	while( i <= endOne  &&  j <= endTwo )	// ȡ����������ֵ���һ������cmTarget������
	{
		if( cmSource[i].nScore>= cmSource[j].nScore )
			cmTarget[k++] = cmSource[i++];
		else
			cmTarget[k++] = cmSource[j++];
	}

	if( i <= endOne )	// ��һ��������δ�꣬����ϵ�һ�������ʣ�ಿ��
	{
		int q;
		for( q = i; q <= endOne; q ++ )
			cmTarget[k++] = cmSource[q];
	}
	else // j <= endTwo		�ڶ���������δ�꣬����ϵڶ��������ʣ�ಿ��
	{
		int q;
		for( q = j; q <= endTwo; q ++ )
			cmTarget[k++] = cmSource[q];
	}

}
