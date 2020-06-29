#pragma once

#include <cstdlib>
#include <stdexcept>
// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size)
    {
        data_begin = new T[size];
        data_end = data_begin + size;
        capasity_end = data_end;
    }
    ~SimpleVector()
    {
        delete [] data_begin;
    }

    T& operator[](size_t index)
    {
        if(index >= this->Size())
        {
            throw std::invalid_argument("Index out of range");
        }
        return data_begin[index];
    };

    T* begin() { return data_begin; }
    T* end() { return data_end; }

    const T* begin() const { return data_begin; }
    const T* end() const { return data_end; }

    size_t Size() const { return capasity_end==nullptr?0:data_end - data_begin;}
    size_t Capacity() const { return capasity_end==nullptr?0:capasity_end - data_begin; }
    void PushBack(const T& value)
    {
        if(Capacity()==0)
        {
            data_begin = new T[1];
            data_end = data_begin;
            capasity_end = data_begin+1;
        }
        if(Capacity() == Size())
        {
            size_t size = Size();
            T* new_data_begin = new T[2*size];
            capasity_end = new_data_begin + 2*size;

            Copy(data_begin, Size(), new_data_begin);

            delete [] data_begin;
            data_begin = new_data_begin;
            data_end = data_begin + size;
        }
        *data_end++ = value;
    }

private:
    void Copy(T* from, size_t count, T* dest)
    {
        for(size_t i=0; i<count; ++i)
        {
            dest[i] = from[i];
        }
    }
    T* data_begin = nullptr;
    T* data_end = nullptr;
    T* capasity_end = nullptr;
};
