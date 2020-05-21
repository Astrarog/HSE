#ifndef SET_HPP
#define SET_HPP
#include <list>
#include <string>
#include <stdexcept>
#include <iostream>

namespace ral {

    /**
     * @class ListException
     * @brief Класс исключения для стека
     */
    class ListException: public std::exception
    {
    private:
        std::string m_error;

    public:
        ListException():m_error("Can't pop empty array"){}
        ListException(const std::string& error): m_error(error){}

        const char* what() const noexcept { return m_error.c_str(); }
    };


    /**
     * @class stack_base
     * @brief базовый класс для стека
     */
    template <typename T>
    class stack_base
    {
    public:
        virtual void pop() = 0;
        virtual void push(const T&) = 0;
    };


    /**
     * @class stack
     * @brief Реализация стека через std::list
     */
    template <typename T>
    class stack : public std::list<T>, public stack_base<T>
    {
    public:
        stack(){}
        void pop() override
        {
            if(this->size()==0)
            {
                throw ListException();
            }
            else
            {
                this->pop_front();
            }
        }
        void push(const T& val) override
        {
            this->push_front(val);
        }

        void PrintStack() const
        {
            for (auto pos = this->begin(); pos!=this->end(); pos = next(pos))
            {
                std::cout << *pos << ' ';
            }
        }
    };

}

#endif // SET_HPP
