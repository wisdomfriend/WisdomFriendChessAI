// HistoryHeuristic.h


#include <memory.h>		// For  void *memset( void *dest, int c, size_t count );



/////////////////// Data Define ////////////////////////////////////////////////

int HistoryTable[90][90];			//��ʷ��¼��



/////////////////// Function Prototype /////////////////////////////////////////

// �����ʷ��¼��ȫ��0��
inline void ResetHistoryTable();

// ȡ�����߷���move������ʷ�÷֣����ظõ÷�
inline int GetHistoryScore( CCHESSMOVE *move );

// Ϊһ����߷���move��������ʷ��¼�÷֣�nDepth��־���߷���������������
inline void EnterHistoryScore( CCHESSMOVE *move, int nDepth );



////////////////// Programmer-Defined Function //////////////////////////////////

inline void ResetHistoryTable()
{
	memset( HistoryTable, 0, sizeof(int)*8100 );
}

inline int GetHistoryScore( CCHESSMOVE *move )
{
	int nFrom, nTo ;

	// ��λ������ת��Ϊ�����±�
	nFrom	= move->ptFrom.x * 9 + move->ptFrom.y;
	nTo		= move->ptTo.x   * 9 + move->ptTo.y;

	return HistoryTable[nFrom][nTo];	// ������ʷ��¼���еķ���
}

inline void EnterHistoryScore( CCHESSMOVE *move, int nDepth )
{
	int nFrom, nTo;

	// ��λ������ת��Ϊ�����±�
	nFrom	= move->ptFrom.x * 9 + move->ptFrom.y;
	nTo		= move->ptTo.x   * 9 + move->ptTo.y;

	HistoryTable[nFrom][nTo] += 2 << nDepth;	// ����Ϊ2��nDepth�η�
}
