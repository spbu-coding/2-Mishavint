#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>
#include "sort.h"

#define error(...) (fprintf(stderr, __VA_ARGS__))

int work_with_params (long long* restrict from , long long* restrict to , int number_of_params, char* params[] )
{
    if(number_of_params < 2 ) // Если число параметров меньше, чем 2, то это ошибка (-1)
    {
        return -1;
    }
    if(number_of_params > 3 ) // Если число параметров больше, чем 2, то это ошибка (-2)
    {
        return -2;
    }
    if(number_of_params > 2 && ( ((strncmp(params[1] , "--from=" , 7) ==0 )  && (strncmp(params[2] , "--from=" , 7) ==0))
                        || ((strncmp(params[1] , "--to=" , 5) ==0 )  && (strncmp(params[2] , "--to=" , 5) ==0) ) )  )// Если есть два одинаковых параметра, то это ошибка (-3)
    {
        return -3;
    }


    int flag_for_from = 1 , flag_for_to = 1;
    int second_flag_for_from = 1 , second_flag_for_to = 1;
    for (int i = 1 ; i < number_of_params ; ++i)                                        // Прогоняем циклом все параметры, которые получили из консоли
    {
            if( (*(from) == NULL) && (strncmp(params[i]  , "--from=" , 7) == 0))     // Если нашли параметр, где начало строки совпадает с "--from=" то надо вычислить то, что нам надо из этого параметра
        {
            *(from) = strtoll(params[i] +7 , NULL, 10 );  // Вбиваем число в переменную

            flag_for_from *=2;                            // Если пользователь не вводил параметр from, то флаг будет равен 2
            if((strncmp( params[i] +7  , "0" , 1) == 0 ) ) // Если пользователь намеренно ввёл 0, то нам нужно увеличть переменную, чтобы потом нормально с этим работать
            {
                second_flag_for_from *= 2;
            }
        }
        else if( (*(to) == NULL)  && (strncmp( params[i]  , "--to=" , 5) == 0))    // Если нашли параметр, где начало строки совпадает с "--to=" то надо вычислить то, что нам надо из этого параметра
        {
            *(to) = strtoll(params[i] +5 , NULL, 10 );          // Вбиваем число в переменную

            flag_for_to *=2;                                    // Если пользователь не вводил параметр to, то флаг будет равен 2
            if((strncmp( params[i] +5  , "0" , 1) == 0) )       // Если пользователь намеренно ввёл 0, то нам нужно увеличть переменную, чтобы потом нормально с этим работать
            {
                second_flag_for_to *=2;
            }
        }
    }

    if(((second_flag_for_from == 1 ) && (second_flag_for_to) ==1 ) && ((*(from) == NULL) && (*(to) == NULL) )) // Если 2 раза было введено некоректное число, то это ошибка (-4)
    {
        return -4;
    }
    else if(flag_for_from == 1 && ((*(to) != NULL) || (second_flag_for_to == 2)))       // Если пользователь намеренно не ввёл переменную, то нужно присвоить ей минимально возможное значение
    {
        *(from) = LLONG_MIN;
    }
    else if(flag_for_to == 1 && ((*(from) != NULL) || (second_flag_for_from == 2)))     // Если пользователь намеренно не ввёл переменую, то нужно ей присвоить максимально возможное значение
    {
        *(to) = LLONG_MAX;
    }

    return 0;           // Если всё прошло успешно, возвращаем 0
}

void free_array_string(int* array_string[])                 // "очищаяем массив", чтобы можно было опять его заполнить цифрами
{
    for(int i = 0 ; i < strlen(array_string) ; ++i)
    {
        array_string[i] = ' ';
    }
}

int string_to_array(long long* restrict from ,long long* restrict to, long long* restrict array[] , int max_size_of_array)
{
    int elements_in_array = 0;                                                          // Переменная, обозначающа яколичество цифр в массиве
    long long number;                                                                   // Временное число, которые мы проверим на принадлежность к (from , to)
    char check_for_the_last_element;                                                    // Переменная, нужная для понимания, когда будет последнее число в строке

    do {

        if(scanf("%lli%c" , &number , &check_for_the_last_element ) !=2 )               // Если возникла ошибка при считывании числа, нужно завершить выполнение и выдать ошибку
        {
            error("can't read [%d] element" , elements_in_array);
            check_for_the_last_element = '\n';
        }
        if(number < *from )
        {
            printf("%lli " , number);
        }
        if(number > *to)
        {
            error("%lli " , number);
        }
        if((number > *from) && (number < *to))                                          // Если число спокойно прошло через все ошибки, то вбиваем его в массив
        {
            array[elements_in_array] = number;
            elements_in_array+=1;
        }

    } while (check_for_the_last_element != '\n' && elements_in_array < max_size_of_array);  // Делаем столько раз, сколько нам введут чисел

    return elements_in_array;
}

int main(int argc, char** argv) {
    long long int from = NULL, to  = NULL;                                  // Заполняем переменные нулями, пригодится дальшe
    long long int array[100];

    int result_of_work = work_with_params(&from , &to , argc , argv );      // Создал функцию, которая заполняет переменные и возвращает возможные ошибки
    if(result_of_work != 0 )                                                // Если всё-таки что-то пошло не так, корректно вывести ошибку
    {
        return result_of_work;                                              // Возвращаем ошибку и завершаем работу
    }

    int elements_in_array = string_to_array(&from , &to, &array , 100);        // Получаем количество цифр(элементов) в строке, параллельно заполняя массив цифрами

    work_with_array(array , &elements_in_array );

}
