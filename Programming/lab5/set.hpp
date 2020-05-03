#ifndef SET_HPP
#define SET_HPP
#include <set>
#include <unordered_set>
#include <iterator>
#include <iostream>

namespace ral {

    template<typename T>
    class setImplementation_base
    {
    public:
        virtual bool find(const T&) const = 0;
        virtual void erase(const T& Key) = 0;
        virtual void insert(const T& value) = 0;
        virtual size_t count() const = 0;
        virtual T getFirstElement() const = 0;
        virtual void PrintSet() const = 0;
    };

    //set on trees
    template<typename T>
    class setOnTrees : public setImplementation_base<T>
    {
        std::set<T> data;
    public:
        setOnTrees(){}
        bool find(const T& Key) const override  { return data.count(Key);}
        void erase(const T& Key) override { data.erase(Key); }
        void insert(const T& Key) override { data.insert(Key); }
        size_t count() const override { return data.size();}
        T getFirstElement() const override
        {
            return *(data.begin());
        }
        void PrintSet() const override
        {
                std::cout << "set on trees {";
                bool first = true;
                for (auto& elem: data)
                {
                    if(!first)
                    {
                        std::cout << ",";
                    }
                    first = false;
                    std::cout << elem;
                }
                std::cout << '}';
        }
    };


    //set on hash tables
    template<typename T>
    class setOnHashes : public setImplementation_base<T>
    {
         std::unordered_set<T> data;
    public:
        setOnHashes(){}
        bool find(const T& Key) const override { return data.count(Key);}
        void erase(const T& Key) override { data.erase(Key); }
        void insert(const T& Key) override { data.insert(Key); }
        size_t count() const override { return data.size();}
        virtual T getFirstElement() const override
        {
            return *(data.begin());
        }
        void PrintSet() const override
        {
                std::cout << "set on hash tables {";
                bool first = true;
                for (auto& elem: data)
                {
                    if(!first)
                    {
                        std::cout << ",";
                    }
                    first = false;
                    std::cout << elem;
                }
                std::cout << '}';
        }
    };


    template<typename T>
    class set_base
    {
    public:
        virtual bool find(const T& Key) const {
            auto ret = impl->find(Key);
            return ret;
        };
        virtual void erase(const T& Key){
            impl->erase(Key);
            check_capasity();
        }
        virtual void insert(const T& Key){
            impl->insert(Key);
            check_capasity();
        }
        virtual size_t count() const{
            auto ret = impl->count();
            return ret;
        }
        virtual void PrintSet() const
        {
            impl->PrintSet();
        }
    protected:
        setImplementation_base<T>* impl;
        virtual void check_capasity()=0;

    };


}

#endif // SET_HPP
