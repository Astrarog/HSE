#ifndef SET_HPP
#define SET_HPP
#include <list>
#include <string>
#include <stdexcept>


namespace ral {

    class ListException: public std::exception
    {
    private:
        std::string m_error;

    public:
        ListException():m_error("Can't pop empty array"){}
        ListException(const std::string& error): m_error(error){}

        const char* what() const noexcept { return m_error.c_str(); }
    };

    template <typename T>
    class stack_base
    {
    public:
        virtual void pop() = 0;
        virtual void push(const T&) = 0;
    };


    template <typename T>
    class stack : stack_base<T>
    {
        std::list<T> data;
    public:
        stack(){}
        T pop() override
        {
            if(data.size())
            {
                throw ListException();
            }
            else
            {
                auto ret = *(data.begin());
                data.pop_front();
                return ret;
            }
        }
        void push(const T& val) override
        {
            data.push_front(val);
        }
    };

}

#endif // SET_HPP
