#ifndef ROOF_HPP
#define ROOF_HPP
#include<array>
#include<cstdint>
#include<iostream>


namespace fld {

template<typename T, std::size_t lSize, std::size_t  hSize>
class field
{
    private:
        T outOfRange;
        std::array<std::array<T, hSize>,lSize> Cells{};

        class proxy_const;
        class proxy_value;
        class proxy_line
        {
           private:
               field* owner;
               std::size_t givenL;
               T OOR;

               proxy_line(field* own, std::size_t l, T& OofR): owner(own), givenL(l), OOR(OofR) {}
               friend class field;

           public:

               proxy_value operator[](std::size_t  givenH) { return proxy_value(owner, givenL, givenH, OOR); }
               const proxy_const operator[](std::size_t  givenH) const { return proxy_const(owner, givenL, givenH, OOR);}
        };

        class proxy_value
        {
          private:
            field* owner;
            std::size_t givenL;
            std::size_t givenH;
            T OOR;

            proxy_value(field* own, std::size_t l, std::size_t h, T& OofR): owner(own), givenL(l), givenH(h), OOR(OofR)  {}
            friend class proxy_line;

          public:

            operator T(){ return (0<=givenL)&&(givenL<=lSize-1)&&(0<=givenH)&&(givenH<=lSize-1)? owner->Cells[givenL][givenH]: OOR; }
            T& operator =(const T& toCell){ return (0<=givenL)&&(givenL<=lSize-1)&&(0<=givenH)&&(givenH<=lSize-1)? owner->Cells[givenL][givenH]=toCell : OOR; }
        };

        class proxy_const{
            private:
              field* owner;
              std::size_t givenL;
              std::size_t givenH;
              T OOR;

              proxy_const(field* own, std::size_t l, std::size_t h, T& OofR): owner(own), givenL(l), givenH(h), OOR(OofR)  {}
              friend class proxy_line;

            public:
              operator T() const { return (0<=givenL)&&(givenL<=lSize-1)&&(0<=givenH)&&(givenH<=lSize-1)? owner->Cells[givenL][givenH]: OOR;}
        };

     public:
        explicit field(T OofR): outOfRange(OofR), Cells{} {}

        proxy_line operator[](std::size_t  index) { return proxy_line(this, index, outOfRange); }
        const proxy_line operator[](std::size_t  index) const { return proxy_line(this, index, outOfRange); }


};



}
#endif // ROOF_HPP
