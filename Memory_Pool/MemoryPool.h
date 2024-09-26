#pragma once
#include "Types.h"
#include "Macro.h"
#include "Container.h"
#include "mutex"
using namespace std;
//메모리풀을 관리할때 동일한 데이터끼리 관리할 것이냐 유동적인 데이터끼리 할것이냐 를 정해야한다.
//[32] [64] [] [] [] [] []
//[][]:메모리풀

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
	//TODO :필요한 추가 정보
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
	atomic<int32>_allocCount = 0;//메모리의 갯수 Pool의 카운터아님
	mutex mtx;
	queue<MemoryHeader*>_queue;
};

