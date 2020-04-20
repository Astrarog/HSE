#include <iostream>
#include <iomanip>

int main() {

	char A[16], B[16];
	int C[16], A1[16] = { 0, -1, -3, 5, -6, 3, -4, -5, -2, 6, 6, 2, 3, -1, -2, -6 };
	int count;
	std::cout << "Input array" << std::endl << "A: ";

	for (int i = 0; i < 16; ++i) 
	{
		A[i] = char(A1[i]); B[i] = -4; C[i] = -1; std::cout << std::setw(2) << A1[i] << ' ';
	}
	std::cout << std::endl;
	__asm {

		xor eax, eax;					eax - для цикла и адресации по A
		xor ebx, ebx;					ebx - для адресации по B и по C
		xor edx, edx;					edx - для подсчёта количества интересующих элементов
		mov esi, 0;						esi - для проверки был ли найден первый неотрицательный элемент в A
		mov eax, 16;					Записываем адрес последнего элемента
		dec eax;						Вычитаем 1, чтобы не смотреть за конец массива
	next_step:
		cmp eax, 0;						Проверка на конец прохождения по массиву
		jl done;						Переход в случае конца
		mov cl, byte ptr A[eax];		Записываем элемент из массива A
		cmp cl, 0;						Узнаём знак элемента
		jl negative;					Переходим к блоку работы с отрицательными элементами
		mov esi, 1;						Нашли неотрицалтельный элемент
	skip:	
		cmp cl, -2;						Проверяем условие из задания
		jle not_app;					Пропускаем, если условие не выполнено
		mov byte ptr B[ebx],  cl;		Помещаем это значение в B;
		mov dword ptr C[ebx*4], eax;	Помещаем смещение этого значения в C;
		inc edx;						Увеличиваем число интересующих элементов
		inc ebx;						Увеличиваем счётчик прохода по массивам B и C;
	not_app:
		dec eax;						Уменьшаем счётчик цикла
		jmp next_step;					Переход на следующую итерацию
	negative:
		cmp esi, 0;						Проверяем был ли уже найден первый неотрицательный элемент
		je skip;						Пропускаем блок, если не был
		inc cl;							Увеличиваем отриц.элемент массива
		mov byte ptr A[eax], cl;		Помещаем это значение обратно в A;
		jmp skip;
	done:
		mov count, edx;					Записываем колчиество интересующих элементов
	}


	std::cout << "There are " << count << " interesting values. Output arrays are shown below." << std::endl;
	std::cout << "A: ";
	for (int i = 0; i < 16; ++i)
	{
		std::cout << std::setw(2) <<  int(A[i]) << ' ';
	}
	std::cout << std::endl;

	std::cout << "B: ";
	for (int i = 0; i < 16; ++i)
	{
		if (B[i] != -4) {
			std::cout << std::setw(2) << int(B[i]) << ' ';
		}
	}
	std::cout << std::endl;

	std::cout << "C: ";
	for (int i = 0; i < 16; ++i)
	{
		if (C[i] != -1) {
			std::cout << std::setw(2) << int(C[i]) << ' ';
		}
	}
	std::cout << std::endl;
	return 0;
}