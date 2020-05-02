#include <iostream>
#include <vector>
#include "set.hpp"

template<typename T>
class set : public ral::set_base<T>
{
    size_t count_was;
    virtual void check_capasity()
    {
        size_t count = this->count();
        if(count>10'000 && count_was<=10'000){
            auto new_impl = new ral::setOnTrees<T>;
            while (this->count()>0) {
                new_impl->insert(this->impl->getFirstElement());
            }
            delete this->impl;
            this->impl = new_impl;
        }
        else if (count<=10'000 && count_was>10'000)
        {
            auto new_impl = new ral::setOnHashes<T>;
            while (this->count()>0) {
                new_impl->insert(this->impl->getFirstElement());
            }
            delete (this->impl);
            this->impl = new_impl;
        }
    }
public:
    set() { this->impl = new ral::setOnHashes<T>; count_was = 0; }

};


int main()
{
//    ral::setOnHashes<int> s;
        set<int> s;
        s.insert(1);
        s.insert(2);
        s.insert(1);
        s.insert(4);
        s.PrintSet();
    return 0;
}
