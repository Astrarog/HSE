#include "countOnes.hpp"
#include <config-files/config.hpp>

namespace work {


int countOnes(myLL x){

#ifdef HAVE_POPCOUNTLL
    return __builtin_popcountll(x);



#else
    int count=0;
    while(x)
    {
        if(x & 1) ++count;
        x>>=1;
    }
    return count;
#endif

}

}
