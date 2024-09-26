#pragma once
#include <mutex>
#include <atomic>
/*
 msvc에 표준된경우 int64_t ,long long을 사용한다. __의 경우 mvsc 컴파일러의 비표준 확장
 다른 컴파일러와 호환이중요할경우 c++표준을 사용
*/
using BYTE = unsigned char;
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

template<typename T>
using Atomic = std::atomic<T>;
using Mutex = std::mutex;
using CondVar = std::condition_variable;
using UnqueLock = std::unique_lock<std::mutex>;
using LockGuard = std::lock_guard<std::mutex>;