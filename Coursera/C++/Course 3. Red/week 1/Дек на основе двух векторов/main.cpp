#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque
{
private:
    vector<T> back;
    vector<T> front;

public:
    Deque() = default;
    bool Empty() const { return back.empty()&&front.empty(); }
    size_t Size() const { return back.size()+front.size(); }

    T& operator[](size_t idx)
    { return (idx<front.size()?front[front.size() -1 - idx]: back[idx-front.size()]);}
    const T& operator[](size_t idx) const
    { return (idx<front.size()?front[front.size() -1 - idx]: back[idx-front.size()]);}

    T& Front(){return (front.size()>0?front.back():back.front());}
    const T& Front() const {return (front.size()>0?front.back():back.front());}

    T& Back(){return (back.size()>0?back.back():front.front());}
    const T& Back() const {return (back.size()>0?back.back():front.front());}

    void PushBack(const T & elem){ back.push_back(elem);}
    void PushFront (const T & elem){ front.push_back(elem);}
    T& At(size_t index)
    {
        if(index >= back.size()+front.size())
        {
            throw out_of_range("Index out of range");
        }
        return (*this)[index];
    }
    const T& At(size_t index) const
    {
        if(index >= back.size()+front.size())
        {
            throw out_of_range("Index out of range");
        }
        return (*this)[index];
    }
};


int main() {
  return 0;
}
