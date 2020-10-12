#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>
#include "sort.h"

#define stderr_printf(...) fprintf(stderr, __VA_ARGS__)
#define MAX_INPUT_STRING_LENGTH 8191 // Нашёл в интернете, что нельзя ввести больше 8191 символов в командную строку

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

int string_to_array (long long* restrict from , long long* restrict to , long long* restrict array[] , char* restrict input_string)
{
    int flag = 0;                                                               // Переменная, чтобы знать какой длины нужно создавать вторую строку
    int second_flag=0;                                                          // Переменная, чтобы знать номер элемента, чтобы начать вносить цифри во вторую строку
    int elements_in_array =0;                                                   // Количество цифр
    long long int temp_int;

    for(int i = 0 ; i < strlen(input_string) ; ++i)                                 // Пробегаем цикл от 0 элемента до последнего
    {
        if((input_string[i+1] == ' ') || (input_string[i+1] == '\0'))               // Если следуюзий символ пробел или конец строки, то значит мы на последней цифре числа, и можно его обрабатывать
        {
            char string_with_number [flag+1];                                       // Создаем вторую строку, куда запишем цифры в виде строки
            for(int j = 0 ; j <= flag ; ++j)
            {
                string_with_number[j] = input_string[second_flag + j];              // Заполним вторую строку цифрами в виде символов
            }

            temp_int =strtoll(string_with_number , NULL, 10 );      // Теперь, после проверки вносим только что добавленное число в массив цифр

            if(temp_int > *from && temp_int < *to)
            {
                array[elements_in_array] = temp_int;
                elements_in_array +=1;
            }
            else if(temp_int > to)
            {
                stderr_printf("%lli ", temp_int);
            }
            else if(temp_int < from)
            {
                printf("%lli ", temp_int);
            }

            free_array_string(string_with_number);                                  // "Очищяем" вторую строку, чтобы не было проблем
            second_flag += (flag + 2);                                              // Переносим флаг на начало следующего числа
            flag = -1;
        }
        else
        {
            flag+=1;
        }
    }
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

    char input_string[MAX_INPUT_STRING_LENGTH];                             // Создали массив из символов длинной максимально возможного ввода в консоль
    gets(input_string);                                                     // Считали входхную строку

    int elements_in_array = string_to_array(&from , &to, &array , &input_string);        // Получаем количество цифр(элементов) в строке, параллельно заполняя массив цифрами
    work_with_array(array , &elements_in_array );

}
