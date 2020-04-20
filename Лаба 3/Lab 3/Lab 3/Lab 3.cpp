#include <iostream>
#include <stdexcept>

int main() {
	char string[4];
	bool correct = true;
	std::cout << "Input string: ";
	for (int i = 0; i < 4; ++i)
	{
		std::cin >> string[i];
		correct = correct &&
			('0' <= string[i] && string[i] <= '9');

	}
	if (!correct)
	{
		std::cerr << "String should contain only digits.";
		return 0;
	}

	__asm {
		mov al, string[0]	;  помещаем 1ую цифру в al
		mov ah, string[1]	;  помещаем 2ую цифру в ah
		cmp al, ah			;  сравниваем 1ую и 2ую цифры на равенство
		jne change			;  если не равны, то переходим к блоку "chagne", иначе проверяем дальше
		cmp al, string[3]	;  сравниваем 1ую(а так же 2ую, если они были равны) цифру с 4ой
		jb change			;  если 1ая меньше, то переход к блоку "change", иначе увеличиваем 1ую цифру
		cmp al, '9'			;  сравниваем 1ую цифру с 9 - кой
		je end				;  по условию задачи 9 - ку не изменять, поэтому завершаем программу
		inc string[0]		;  иначе увевличиваем цифру на 1 по условию
		jmp end				;  завершаем программу
		change :			;  в случае не выполнения условия на строку выполняем альтернативу
		mov string[2], '3'	;  изменяем 3ью бувку на 3 - ку
		mov string[3], '3'	;  изменяем 4ью бувку на 3 - ку и завершаем программу
		end :
	}


	std::cout << std::endl << "Output string: ";
	for (int i = 0; i < 4; ++i)
	{
		std::cout << string[i];
	}
	std::cout << std::endl;
	return 0;
}


