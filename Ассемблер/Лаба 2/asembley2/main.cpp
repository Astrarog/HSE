#include <iostream>

using namespace std;

short evaluate_task(char x, short y, char z)
{
    short v;
    __asm__ ( ".intel_syntax noprefix\n\t"
     "MOV  al, %1            \n\t"              // помещаем x в байтовый регистр AL=x
     "CBW                    \n\t"              // превращаем x в слово: AX=x
     "SUB  ax, 2             \n\t"              // вычитаем из х двойку: AX=x-2
     "MOV  bx, 7             \n\t"              // переносим в bx 7-ку: BX=7, AX=x-2
     "IMUL bx                \n\t"              // умножаем AX на BX. Результат будет в DX:AX = 7*(x-2), BX=7
     "MOV  bx, ax            \n\t"              // AX в BX для упрощения дальнейших операция, DX:BX = 7*(x-2),
     "MOV  ax, %2            \n\t"              // помещаем y в словестный регист AX, DX:BX = 7*(x-2), AX=y
     "ADD  bx, ax            \n\t"              // сформируем двойное слово из y (будем считать, что старшая часть равна 0)
     "ADC  dx, 0             \n\t"              // и произведеём его сложение с DX:BX. DX:BX = 7*(x-2)+y
     "mov  al, %3            \n\t"              // помещаем z в байтовый регистр AL= z, DX:BX = 7*(x-2)+y
     "cbw                    \n\t"              // превращаем z в слово: AX = z, DX:BX = 7*(x-2)+y
     "add  ax, 0x4           \n\t"              // прибавим 4ку к z: AX = z+4, DX:BX = 7*(x-2)+y
     "xchg ax, bx            \n\t"              // меняем местами AX и BX, чтобы произвести дальнейшее деление. DX:AX=7*(x-2)+y, BX=z+4
     "idiv bx                \n\t"              // Производим деление DX:AX на BX. AX=7*(x-2)+y/(z+4)
     "dec ax                 \n\t"              // вычитаем 1 из результата деления. AX=7*(x-2)+y/(z+4) - 1
     "mov  %0, ax            \n\t"              // заносим результат в v
     : "=r"(v) /* выходные операнды */
     : "r"(x), "r"(y), "r"(z)  /* входные операнды */
     : "%ax", "%bx", "%al", "%dx", "%cx" /* разрушаемые регистры */
    );
    return v;
}

int main()
{
    char x1=-0x1, z1=-0x2;
    short y1=0x13, v1=evaluate_task(x1,y1,z1);
    cout << '-' << hex << -v1 << 'h' << endl;

    char x2=-0x7e, z2=0x7f;
    short y2=0x4fba, v2=evaluate_task(x2,y2,z2);
    cout << hex << v2 << 'h' << endl;

    return 0;
}
