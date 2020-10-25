#ifndef MYCLASS_HPP
#define MYCLASS_HPP

#include <cstdint>
#include <iostream>

namespace work {

using myLL=std::uint64_t;

class registerFib
{
    private:
        unsigned int length_;
        myLL mask_;
        myLL currentStatus_;
        friend std::ostream& operator<<(std::ostream& output, const registerFib&);

    public:
        registerFib(myLL m, myLL cS ) { reset(m,cS); }
        void reset(myLL m, myLL cS);
        bool operator()();
};


}


#endif
