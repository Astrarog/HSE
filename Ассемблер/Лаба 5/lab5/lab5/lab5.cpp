#include <iostream>

void printBytes(char x)
{
	for (int j=0; j<8; j++)
	{
		std::cout << int(((x>>1)&(0b01111111))>>6);
		x <<= 1;
	}
	std::cout << 'b';
}

int main()
{
	char A[6] = {'\x5e', 'e', '\x1d', '\xe9' ,'\xaa'  ,'f' };
	int count;
	std::cout << "Input array" << std::endl << "A: ";

	for (int i = 0; i < 6; ++i)
	{
		printBytes(A[i]);
		std::cout << ' ';
	}
	std::cout << std::endl;
	__asm {

			lea esi, A;						esi - указательн на начало массива A
			mov ecx, 0;						ecx - счётчик для прохода по A
	next_step :
			mov al, byte ptr[esi + ecx];	В al записывается элемент массива
			mov ah, al;						В ah копируем это значение
			and al, 00011000b;				Выделяем битовое поле 4:3 из элемента массива
			shr al, 2;						Сдвигаем битовое поле 4:3 до позиции 2:1
			and ah, 00000110b;				Выделяем битовое поле 2:1 из элемента массива
			or  ah, 00000010b;				Производим дизъюнкция битового поля 2:1 с образцом 01
			cmp ah, al;						Проверяем на равенстно по условию задачи
			jne skip;						Пропкускаем установку битов, если не равны
			call paste_bits;				Вызваем функцию устанавки старшего и младшего битов у элемента, если условние выполнено
	skip:
			inc ecx;						Увеличиваем счётчик на 1
			cmp ecx, 6;						Проверка на конец прохождения по массиву
			jne next_step;					Переход на следующую опреацию цикла, если ещё не конец
			jmp end;
	paste_bits:;							функция установки старших и младших битов
			mov al, byte ptr[esi + ecx];	В al записывается элемент массива
			or  al, 10000001b;				Устанавливаем старший и младший биты
			mov byte ptr[esi + ecx], al;	Заносим значение в элемент массива
			ret;							Возвращаемся обратно к выполнению цикла
	end:
	}

	std::cout << std::endl;

	std::cout << "Resulting array.\nA: ";
	for (int i = 0; i < 6; ++i)
	{
		printBytes(A[i]);
		std::cout << ' ';
	}
	std::cout << std::endl;
	return 0;
}