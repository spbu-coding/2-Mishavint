#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "sort.h"

struct exist_of_params
{
    int from;
    int to;
};

int work_with_params (long long* restrict from , long long* restrict to ,
                      int number_of_params, char* params[] , struct exist_of_params *existOfParams)
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


    for (int i = 1 ; i < number_of_params ; ++i)                                        // Прогоняем циклом все параметры, которые получили из консоли
    {
            if( (*(from) == 0) && (strncmp(params[i]  , "--from=" , 7) == 0))     // Если нашли параметр, где начало строки совпадает с "--from=" то надо вычислить то, что нам надо из этого параметра
        {
            *(from) = strtoll(params[i] +7 , NULL, 10 );  // Вбиваем число в переменную

            existOfParams -> from = 1;
        }
        else if( (*(to) == 0)  && (strncmp( params[i]  , "--to=" , 5) == 0))    // Если нашли параметр, где начало строки совпадает с "--to=" то надо вычислить то, что нам надо из этого параметра
        {
            *(to) = strtoll(params[i] +5 , NULL, 10 );          // Вбиваем число в переменную

            existOfParams -> to = 1;
        }
    }

    if( (existOfParams -> from == 0) && (existOfParams -> to == 0)  ) // Если 2 раза было введено некоректное число, то это ошибка (-4)
    {
        return -4;
    }

    return 0;           // Если всё прошло успешно, возвращаем 0
}

int string_to_array(long long* restrict from ,long long* restrict to, long long* restrict array ,
                    long long* restrict array2 , int max_size_of_array , struct exist_of_params *existOfParams)
{
    int elements_in_array = 0;                                                          // Переменная, обозначающа яколичество цифр в массиве
    long long number;                                                                   // Временное число, которые мы проверим на принадлежность к (from , to)
    char check_for_the_last_element;                                                    // Переменная, нужная для понимания, когда будет последнее число в строке

    do {

        if(scanf("%lli%c" , &number , &check_for_the_last_element ) !=2 )               // Если возникла ошибка при считывании числа, нужно завершить выполнение и выдать ошибку
        {
            fprintf(stderr , "can't read [%d] element" , elements_in_array);
            return -1;
        }
        if(number <= *from && existOfParams ->from != 0 )
        {
            fprintf(stdout, "%lli " , number);
        }
        if(number >= *to && existOfParams->to != 0)
        {
            fprintf(stderr , "%lli " , number);
        }
        if(((number > *from) || (existOfParams -> from == 0 ))
        && ((number < *to) || existOfParams -> to == 0))                                     // Если число спокойно прошло через все ошибки, то вбиваем его в массив
        {
            array[elements_in_array] = number;
            array2[elements_in_array] = number;
            elements_in_array+=1;
        }

    } while (check_for_the_last_element != '\n' && elements_in_array < max_size_of_array);  // Делаем столько раз, сколько нам введут чисел

    return elements_in_array;
}

int main(int argc, char** argv) {
    long long int from = 0, to  = 0;                                  // Заполняем переменные нулями, пригодится дальшe
    long long int array[100];
    long long int copy_of_first_array [100];
    struct exist_of_params existOfParams = {0 , 0};

    int result_of_work = work_with_params(&from , &to , argc , argv , &existOfParams );      // Создал функцию, которая заполняет переменные и возвращает возможные ошибки
    if(result_of_work != 0 )                                                // Если всё-таки что-то пошло не так, корректно вывести ошибку
    {
        return result_of_work;                                              // Возвращаем ошибку и завершаем работу
    }

    int elements_in_array = string_to_array(&from , &to, array , copy_of_first_array , 100 , &existOfParams);        // Получаем количество цифр(элементов) в строке, параллельно заполняя массив цифрами
    if(elements_in_array < 0 )
    {
        return -5;
    }

    work_with_array(array , &elements_in_array );

    int result_of_return = 0;
    for(int i = 0 ; i < elements_in_array ; ++i)
    {
        if(array[i] != copy_of_first_array[i])
        {
            result_of_return+=1;
        }
    }

    return result_of_return;
}
