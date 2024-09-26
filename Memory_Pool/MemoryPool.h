#pragma once
#include "Types.h"
#include "Macro.h"
#include "Container.h"
#include "mutex"
using namespace std;
//�޸�Ǯ�� �����Ҷ� ������ �����ͳ��� ������ ���̳� �������� �����ͳ��� �Ұ��̳� �� ���ؾ��Ѵ�.
//[32] [64] [] [] [] [] []
//[][]:�޸�Ǯ

/*------------------------------------
			  MemoryHeader
-------------------------------------*/

struct MemoryHeader
{
	//[MemoryHeader][Data]
	MemoryHeader(int32 size) : allocSize(size) {};

	static void* AttachHeader(MemoryHeader* header, int32 size)
	{
		new(header)MemoryHeader(size); //placement new
		return reinterpret_cast<void*>(++header);
	}

	static MemoryHeader* DetacchHeader(void* ptr)
	{
		MemoryHeader* header = reinterpret_cast<MemoryHeader*>(ptr) - 1;
		return header;
	}

	int32 allocSize;
	//TODO :�ʿ��� �߰� ����
};

/*------------------------------------
			  MemoryPool
-------------------------------------*/
class MemoryPool
{
public:
	MemoryPool(int32 allocSize);
	~MemoryPool();

	void Push(MemoryHeader* ptr);
	MemoryHeader* Pop();

private:
	int32 _allocsize = 0;
	atomic<int32>_allocCount = 0;//�޸��� ���� Pool�� ī���;ƴ�
	mutex mtx;
	queue<MemoryHeader*>_queue;
};

