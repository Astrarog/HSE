//Variant 1.
#include <iostream>
#include <random>
#include "roof.hpp"


template<typename T, std::size_t lSize, std::size_t  hSize>
bool check_cells(fld::field<T,lSize,hSize>& field,std::size_t size, bool direct, std::size_t x, std::size_t y){
    if(direct){  //вправо
        for(std::size_t i=1;i<=3;++i){
            for(std::size_t j=1;j<=size+2;++j){
                if((field[x+i-2][y+j-2]==1)|| (x+size>hSize)) return false;
            }
        }
    }
    else{        //вниз
        for(std::size_t i=1;i<=3;++i){
            for(std::size_t j=1;j<=size+2;++j){
                if((field[x+j-2][y+i-2]==1) || (x+size>lSize))  return false;
            }
        }
    }
    return true;
}

template<typename T, std::size_t lSize, std::size_t  hSize>
void put_ship(fld::field<T,lSize,hSize>& field,std::size_t size, std::size_t count,
              std::mt19937& prng, std::uniform_int_distribution<>& direct, std::uniform_int_distribution<>& posX, std::uniform_int_distribution<>& posY ){
    for(;count>0;--count){

        bool direction = direct(prng);
        std::size_t x = posX(prng);
        std::size_t y = posY(prng);

        while(!check_cells(field, size, direction, x, y)){
            direction = direct(prng);
            x = posX(prng);
            y = posY(prng);
        }

            if(direction){
                for(int i=0; i<int(size); ++i) field[x][y+i]=1;
            }else{
                for(int i=0; i<int(size); ++i) field[x+i][y]=1;
        }

    }
}

int main()
{   
    fld::field<int, 10, 10> battleShip(2);

    std::mt19937 prng{std::random_device{}()};
    std::uniform_int_distribution direction{0,1};   // 1 - вправо; 0 - вниз
    std::uniform_int_distribution positionX{0, 9};
    std::uniform_int_distribution positionY{0, 9};


    for(std::size_t i=1; i<=4; ++i){
       put_ship(battleShip, 4+1-i, i, prng, direction, positionX, positionY);
    }

    std::cout<<'\n';
    for (std::size_t i=0; i<=10; ++i){
        for (std::size_t j=0; j<=10; ++j){
            std::cout<< battleShip[i][j] << ' ';

        }
        std::cout<<'\n';
    }

    return 0;
}
