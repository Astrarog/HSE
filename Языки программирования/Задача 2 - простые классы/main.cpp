//Variant 11.
#include "myclass.hpp"
#include <cassert>
#include <iostream>

int main()
{
    work::registerFib t1(3,3);
    std::cout<<t1;
    bool test1=t1();
    assert(test1==0);
    std::cout<<t1;
    bool test2=t1();
    assert(test2==1);
    std::cout<<t1;
    work::registerFib t2(1,2);
    t2.reset(0b0101,0b10101010000);
    std::cout<<t2;
    work::registerFib t3(4,2);
    bool test3=t3();
    assert(test3==0);
    return 0;
}
