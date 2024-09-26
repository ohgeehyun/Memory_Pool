#include <iostream>
#include "Container.h"
#include "Memory.h"
#include "Global.h"
#include <thread>
/*
    메모리를 할당과 해제를 하면서 생긴 단편화 및 사용하 였던 메모리의 영역을 바로 할당해제하는 것이 아니라
    나중에 올 데이터를 다시 할당하는 등 메모리를 효율적으로 쓰기 위한 기법
    요새는 내부적으로 메모리를 단편화관련해서는 엄청 잘 지원해준다고한다.
    but 공부하는 입장인데 그런거 신경 쓸 필요있나 배워야지
*/


class Knight
{
public:
    Knight() { cout << "knight()" << endl; };
    ~Knight() { cout << "~Knight" << endl; };
    Knight(int32 hp) : _hp(hp) { cout << "Knight(hp)" << endl; };

    int32_t _hp = 100;
    int32_t _mp = 100;

private:
};


int main()
{
    
    thread t1([]() {Vector<Knight>v(10); });
    thread t2([]() {Vector<Knight>v(10); });
    thread t3([]() {Vector<Knight>v(10); });
    thread t4([]() {Vector<Knight>v(10); });
    thread t5([]() {Vector<Knight>v(10); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
   
}

