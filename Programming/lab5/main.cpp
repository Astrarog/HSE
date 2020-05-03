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
        if(count>10 && count_was<=10){
            auto new_impl = new ral::setOnTrees<T>;
            while (this->count()>0) {
                auto elem = this->impl->getFirstElement();
                new_impl->insert(elem);
                this->erase(elem);
            }
            delete this->impl;
            this->impl = new_impl;
        }
        else if (count<=10 && count_was>10)
        {
            auto new_impl = new ral::setOnHashes<T>;
            while (this->count()>0) {
                auto elem = this->impl->getFirstElement();
                new_impl->insert(elem);
                this->erase(elem);
            }
            delete (this->impl);
            this->impl = new_impl;
        }
        count_was = count;
    }
public:
    set() { this->impl = new ral::setOnHashes<T>; count_was = 0; }

};


int main()
{
//    ral::setOnHashes<int> s;
        set<int> s;
        for(int i=0; i<8; ++i)
        {
            s.insert(i);
        }
        s.PrintSet();
        std::cout << std::endl << "set.find(11)==" << s.find(11)<< std::endl;
        for(int i=8; i<16; ++i)
        {
            s.insert(i);
        }
        s.erase(0);
        s.PrintSet();
        std::cout << std::endl << "set.find(11)==" << s.find(11) << std::endl;
        for(int i=0; i<8; ++i)
        {
            s.erase(i);
        }
        s.PrintSet();
        std::cout << std::endl;

    return 0;
}
