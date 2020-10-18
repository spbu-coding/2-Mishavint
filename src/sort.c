void work_with_array(long long* restrict array[] , int* number_of_elements)
{
    for(int i = 0 ; i < *(number_of_elements)-1 ; ++i)
    {
        for(int j = 0 ; j < *(number_of_elements) - i - 1 ; ++j)
        {
            if(array[j] > array[j+1])
            {
                long long int temp = *array[j];
                array[j] = array[j+1];
                *array[j+1] = temp;
            }
        }
    }
}