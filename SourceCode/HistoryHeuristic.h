// HistoryHeuristic.h


#include <memory.h>		// For  void *memset( void *dest, int c, size_t count );



/////////////////// Data Define ////////////////////////////////////////////////

int HistoryTable[90][90];			//历史记录表



/////////////////// Function Prototype /////////////////////////////////////////

// 清空历史记录表（全置0）
inline void ResetHistoryTable();

// 取给定走法（move）的历史得分，返回该得分
inline int GetHistoryScore( CCHESSMOVE *move );

// 为一最佳走法（move）增添历史记录得分，nDepth标志该走法所属的搜索层数
inline void EnterHistoryScore( CCHESSMOVE *move, int nDepth );



////////////////// Programmer-Defined Function //////////////////////////////////

inline void ResetHistoryTable()
{
	memset( HistoryTable, 0, sizeof(int)*8100 );
}

inline int GetHistoryScore( CCHESSMOVE *move )
{
	int nFrom, nTo ;

	// 将位置坐标转换为数组下标
	nFrom	= move->ptFrom.x * 9 + move->ptFrom.y;
	nTo		= move->ptTo.x   * 9 + move->ptTo.y;

	return HistoryTable[nFrom][nTo];	// 返回历史纪录表中的分数
}

inline void EnterHistoryScore( CCHESSMOVE *move, int nDepth )
{
	int nFrom, nTo;

	// 将位置坐标转换为数组下标
	nFrom	= move->ptFrom.x * 9 + move->ptFrom.y;
	nTo		= move->ptTo.x   * 9 + move->ptTo.y;

	HistoryTable[nFrom][nTo] += 2 << nDepth;	// 增量为2的nDepth次方
}
