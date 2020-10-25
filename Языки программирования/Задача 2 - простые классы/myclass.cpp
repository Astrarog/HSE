#include "myclass.hpp"
#include "countOnes.hpp"
#include <cassert>

namespace work {


       void registerFib::reset(myLL m, myLL cS)
        {
            mask_=m|1;
            currentStatus_=cS;
            unsigned int l=(mask_>currentStatus_?mask_:currentStatus_), count=0;
            while(l) {++count; l>>=1;}
            length_=count;
        }


        bool registerFib::operator()()
        {
            myLL s= currentStatus_ & mask_;
            //assert((countOnes(s)&1)==0);
            //assert((((currentStatus_>>1)<<1) & 1 )==0);
            currentStatus_= (currentStatus_<<1)^(countOnes(s) & 1);
            //assert((currentStatus_&1)==0);
            return currentStatus_ & 1;
        }


        std::ostream& operator<<(std::ostream& output, const registerFib& outingClass)
        {
            myLL currSt=outingClass.currentStatus_;
            myLL msk=outingClass.mask_;
            int len=outingClass.length_;
            output <<'\n';
            for(int i=0;i<len;++i)
               {output << '=';}
            output<<'\n';

            while(len)
            {
                output << (currSt & 1);
                currSt>>=1;
                --len;
            }

            output<<'\n';

            len=outingClass.length_;
            while(len)
            {
                (msk & 1)?(output<<'*'):(output<<' ');
                msk>>=1;
                --len;
            }

            len=outingClass.length_;
            output <<'\n';
            for(int i=0;i<len;++i)
               {output << '=';}
            output<<'\n';

            return output;
        }

}
