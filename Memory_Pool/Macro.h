#pragma once
#pragma once

#define OUT
/*--------------------------
			Lock
---------------------------*/
#define USE_MANY_LOCK(count) Lock _locks[count];
#define USE_LOCK			 USE_MANY_LOCK(1);
#define READ_LOCK_IDX(idx)	 ReadLockGuard readLockGuard_##idx(_locks[idx],typeid(this).name());
#define READ_LOCK			 READ_LOCK_IDX(0);
#define WRITE_LOCK_IDX(idx)	 WriteLockGuard writeLockGuard_##idx(_locks[idx],typeid(this).name());
#define WRITE_LOCK			 WRITE_LOCK_IDX(0);

/*--------------------------
			Memory
---------------------------*/
#ifdef _DEBUG
#define Xalloc(size)		 PoolAllocator::Alloc(size) 
#define Xrelease(ptr)		 PoolAllocator::Release(ptr)
#else
#define Xalloc(size)		 BaseAllocator::Alloc(size) 
#define Xrelease(ptr)		 BaseAllocator::Release(ptr)
#endif; // _DEBUG





/*--------------------------
			Crash
---------------------------*/
#define CRASH(cause)					    \
{										    \
	uint32* crash = nullptr;				\
	_Analysis_assume_(crash != nullptr);	\
	*crash = 0xDEADBEEF ;					\
}							

#define ASSERT_CRASH(expr)					\
{											\
	if (!(expr))							\
	{										\
		CRASH("ASSERT_CRASH");				\
		__analysis_assume(expr);			\
	}										\
}