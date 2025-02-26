#include "MemoryPool.h"

/*------------------------------------
			  MemoryPool
-------------------------------------*/

MemoryPool::MemoryPool(int32 allocSize) : _allocsize(allocSize)
{
}

MemoryPool::~MemoryPool()
{
	while (_queue.empty() == false)
	{
		MemoryHeader* header = _queue.front();
		_queue.pop();
		free(header);

	}
}

void MemoryPool::Push(MemoryHeader* ptr)
{
	lock_guard<mutex> lock(mtx);
	ptr->allocSize = 0;
	//pool에 메모리 반납
	_queue.push(ptr);
	_allocCount.fetch_sub(1);

}

MemoryHeader* MemoryPool::Pop()
{
	MemoryHeader* header = nullptr;

	{
		lock_guard<mutex> lock(mtx);
		//Pool 의 여분데이터 확인
		if (_queue.empty() == false)
		{
			//있으면 하나 꺼내온다.
			header = _queue.front();
			_queue.pop();
		}
	}

	if (header == nullptr)
	{
		header = reinterpret_cast<MemoryHeader*>(malloc(_allocsize));
	}
	else
	{
		ASSERT_CRASH(header->allocSize == 0);
	}

	_allocCount.fetch_add(1);

	return header;
}
