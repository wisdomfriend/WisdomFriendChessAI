// SortMove.h


/////////////////// Data Define ////////////////////////////////////////////////

CCHESSMOVE cmTargetBuffer[80];		//排序用的缓冲队列



/////////////////// Function Prototype /////////////////////////////////////////

// 对长度为nCount的着法队列cmSource进行归并排序
void MergeSort( CCHESSMOVE *cmSource, int nCount );		

// 为MergeSort函数所调用，归并排序首尾相接的两个数组，
void MergePass( CCHESSMOVE *cmSource, CCHESSMOVE *cmTarget, int nLength, int nCount  ); 

// 为MergePass函数所调用，归并排序首尾相接的两个数组（这两个数组已分别排好序），！！！降序 ！！！
// 两个数组为cmSource[beginOne]--cmSource[endOne]; cmSource[beginTwo]--cmSource[endTwo]. 其中beginTwo = endOne + 1
inline void Merge_Desc( CCHESSMOVE *cmSource, CCHESSMOVE *cmTarget, int beginOne ,int endOne, int endTwo );



////////////////// Programmer-Defined Function //////////////////////////////////

void MergeSort( CCHESSMOVE *cmSource, int nCount )
{
	int nLength = 1;

	// 借助cmTargetBuffer对cmSource进行归并排序
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
	int i = 0;	// 表记待排序的第一个数组的起点

	while( i + 2 * nLength <= nCount ) // 剩余的元素个数大于等于两个nLength长度
	{
		// 归并排序长度为 nLength 的首尾相接的两个数组
		Merge_Desc( cmSource, cmTarget, i, i + nLength - 1, i + 2 * nLength - 1 );

		i += 2 * nLength ;
	}

	if( i + nLength < nCount )	// 剩余的元素个数小于两个nLength长度但大于一个nLength长度
	{
		// 归并排序长度为 nLength 的数组和与其相接的剩下的所有元素组成的数组
		Merge_Desc( cmSource, cmTarget, i, i + nLength - 1, nCount - 1 );
	}
	else						// 剩余的元素个数小于等于一个nLength长度
	{
		int j;
		// 接上剩下的已经排序好的数组
		for ( j = i ; j < nCount ; j ++ )
			cmTarget[j] = cmSource[j];
	}

}

inline void Merge_Desc( CCHESSMOVE *cmSource, CCHESSMOVE *cmTarget, int beginOne ,int endOne, int endTwo )
{
	int i = beginOne ,
		j = endOne + 1,// j = beginTwo
		k = beginOne ;

	while( i <= endOne  &&  j <= endTwo )	// 取两个数组中值大的一个放入cmTarget（降序）
	{
		if( cmSource[i].nScore>= cmSource[j].nScore )
			cmTarget[k++] = cmSource[i++];
		else
			cmTarget[k++] = cmSource[j++];
	}

	if( i <= endOne )	// 第一个数组尚未完，则接上第一个数组的剩余部分
	{
		int q;
		for( q = i; q <= endOne; q ++ )
			cmTarget[k++] = cmSource[q];
	}
	else // j <= endTwo		第二个数组尚未完，则接上第二个数组的剩余部分
	{
		int q;
		for( q = j; q <= endTwo; q ++ )
			cmTarget[k++] = cmSource[q];
	}

}
