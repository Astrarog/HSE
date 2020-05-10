#include <iostream>
#include <vector>
#include "stack.hpp"


int main()
{

    ral::stack<int> st;

    for(int i=0; i<10; ++i)
    {
        st.push(i*i);
    }
    st.PrintStack();
    std::cout << std::endl;


    st.pop();
    for(int i=0; i<10; ++i)
    {
        st.pop();
    }
    st.PrintStack();
    std::cout << std::endl;

    return 0;
}
