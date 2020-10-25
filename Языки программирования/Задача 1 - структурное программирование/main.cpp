//Variant №10. ver 13.11.17
#include <iostream>
#include <math.h>

void showMyPoint(float myX, float myY)
{
    std::cout<<"\nYou coordinats is about:\nx="<< static_cast<std::int64_t>(myX) <<"\ny="<<static_cast<std::int64_t>(myY);
}

bool checkEscape(float myX, float myY)
{
    showMyPoint(myX, myY);
    if(abs( myY ) + abs( myX ) > 100)
    {
        return true;
    }
    else if( myX*myX + myY*myY > 10000)
    {
        return true;
    }
    else return false;
}

int main()
{
    const float sqrt2= sqrt(2);
    int moveTo=0;
    float xPoint=0, yPoint=0, distance=0;
    std::cout << "Welcome to Funny Point Game!\n You are a point. And you need to escape.";

    while(!checkEscape(xPoint, yPoint))
    {
        distanceAgain:
        std::cout << "\nInput the distance: ";
        if(!(std::cin >> distance))
        {
            std::cerr << "\nIncorrect input. Try again.";
            return 1;
        }
        if (distance<0)
        {
            std::cout << "\nDistance should be a positive nubmer! Try Again.\n";
            goto distanceAgain;
        }

        moveAgain:
        std::cout << "\nInput the direction:  ";
        if(!(std::cin >> moveTo))
        {
            std::cerr << "\nIncorrect input. Try again.\n";
            return 1;
        }
        switch (moveTo) {
              case 1:
                  xPoint+= -distance*sqrt2/2;
                  yPoint+= -distance*sqrt2/2;
                  break;
              case 2:
                  yPoint+= -distance;
                  break;
              case 3:
                  xPoint+= distance*sqrt2/2;
                  yPoint+= -distance*sqrt2/2;
                  break;
              case 4:
                  xPoint+= -distance;
                  break;
              case 6:
                  xPoint+= distance;
                  break;
              case 7:
                  xPoint+= -distance*sqrt2/2;
                  yPoint+= distance*sqrt2/2;
                  break;
              case 8:
                  yPoint+= distance;
                  break;
              case 9:
                  xPoint+= distance*sqrt2/2;
                  yPoint+= distance*sqrt2/2;
                  break;
              default:
                  std::cout << "\nIncorect direction. Try again.";
                  goto moveAgain;
        }
    }
    std::cout << "\nYupeeee! You won!\n";
    return 0;
}
