#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_STROK 1000
//Тут был Kozykov2 !!!!!!!!!!!!!!!!!!!!!!
void zamena(char strings[100][MAX_STROK], int min, int max)
{
    char bufer[MAX_STROK];
    strcpy_s(bufer, strings[min]);//копирование минимальной строки в промежуточный массив
    strcpy_s(strings[min], strings[max]);//замена мин строки на макс
    strcpy_s(strings[max], bufer);//копирование мин строки из промежуточного массива на место максимальной
}
int main()
{
    SetConsoleOutputCP(1251);
    int i, n, chislo = 0;
    char stroka[100], slovo[5];
    FILE* inFile, * outFile;
    char strings[100][MAX_STROK];
    char string[MAX_STROK];
    int num = 0, min = 0, max = 0;
    printf("ЧАСТЬ 1 \n");
    printf("Введите строку текста (Для завершения обработки строк наберите quit в конце строки) \n");
    fgets(stroka, sizeof(stroka), stdin);//первоначальное считывание строки в массив stroka
    while (1)
    {
        printf("Числа в строке: ");
        n = strlen(stroka);//определение длины строки
        for (i = 0; i < n; i++)
        {
            if (stroka[i] == '0' && !(stroka[i - 1] >= '0' && stroka[i - 1] <= '9') && !(stroka[i + 1] >= '0' && stroka[i + 1] <= '9'))// вывести "0", если встретится "0", а предыдущий и следующий символ не являются числом
            {
                printf("0 ");
            }
            if (stroka[i] >= '0' && stroka[i] <= '9')
            {
                chislo = chislo * 10 + (stroka[i] - '0');//'0' перевод из символа в число
            }
            else if (chislo != 0)
            {
                printf("%d ", chislo);
                chislo = 0;
            }
        }
        if (chislo != 0)
        {
            printf("%d ", chislo);
        }
        // проверка 4-ех последних символов на quit
        strncpy_s(slovo, stroka + n - 5, 4);//копируем 4 символа из stroka, начиная со смещения n - 5, в slovo
        if (strcmp(slovo, "quit") == 0)// сравниваем slovo c "quit"
            // if (slovo == "quit")
        {
            printf("\n\n");
            printf("Ввод строк завершен \n");
            break;
        }
        printf("\n\n");
        printf("Введите строку текста (Для завершения обработки строк наберите quit в конце строки) \n");
        fgets(stroka, sizeof(stroka), stdin);//продолжаем считывать строки в массив stroka если не было прерывания
    }
    printf(" \n");
    printf("ЧАСТЬ 2 \n");
    // Открытие файла на чтение
    errno_t err = fopen_s(&inFile, "d:\input.txt", "r");
    if (err == 0)
    {
        while (fgets(string, MAX_STROK, inFile))
        {
            strcpy_s(strings[num], string);
            // Поиск номеров самой короткой и самой длинной строки
            if (strlen(string) < strlen(strings[min]))
            {
                min = num;
            }
            if (strlen(string) > strlen(strings[max]))
            {
                max = num;
            }
            num++;
        }
        // Закрытие файла для чтения
        fclose(inFile);
        // Проверка, что в файле должно быть не менее 30 строк
        if (num < 30)
        {
            printf("Ошибка чтения файла. Файл должен содержать как минимум 30 строк.\n");
            return 1;
        }
        // Обмен позициями самой короткой и самой длиной строки
        zamena(strings, min, max);
    }
    else
    {
        printf("Ошибка чтения файла\n");
        return 0;
    }
    // Открытие файла на запись
    errno_t errw = fopen_s(&outFile, "d:\output.txt", "w");
    if (errw == 0)
    {
        for (int i = 0; i < num; i++)
        {
            fputs(strings[i], outFile);
        }
        // Закрытие файла для записи
        fclose(outFile);
        printf("Строки успешно заменены и записаны в файл output.txt.\n");
        return 0;
    }
    else
    {
        printf("Ошибка записи файла\n");
        return 0;
    }
}