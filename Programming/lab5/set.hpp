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
        using iterator = T*;
    public:
        virtual iterator find(const T&) = 0;
        virtual void erase(const T& Key) = 0;
        virtual void insert(const T& value) = 0;
        virtual size_t count() = 0;
        virtual T getFirstElement() = 0;
        virtual void PrintSet()=0;
    };

    //set on trees
    template<typename T>
    class setOnTrees : public setImplementation_base<T>
    {
        using iterator = T*;
        std::set<T> data;
    public:
        setOnTrees(){}
        iterator find(const T& Key) override {
            iterator val = const_cast<iterator>(&(*(data.find(Key))));
            return val;}
        void erase(const T& Key) override { data.erase(Key); }
        void insert(const T& Key) override { data.insert(Key); }
        size_t count() override { return data.size();}
        T getFirstElement() override
        {
            return *(data.begin());
        }
        void PrintSet() override
        {
                std::cout << '{';
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
        using iterator = T*;
        std::unordered_set<T> data;
    public:
        setOnHashes(){}
        iterator find(const T& Key) override {
            iterator val = const_cast<iterator>(&(*(data.find(Key))));
            return val;}
        void erase(const T& Key) override { data.erase(Key); }
        void insert(const T& Key) override { data.insert(Key); }
        size_t count() override { return data.size();}
        virtual T getFirstElement() override
        {
            return *(data.begin());
        }
        void PrintSet() override
        {
                std::cout << '{';
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
        using iterator = T*;
        virtual void check_capasity()=0;
    public:
        virtual iterator find(const T& Key){
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
        virtual size_t count(){
            auto ret = impl->count();
            return ret;
        }
        virtual void PrintSet()
        {
            impl->PrintSet();
        }
    protected:
        setImplementation_base<T>* impl;

    };


}

#endif // SET_HPP
