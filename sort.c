# include "include/ft_nm.h"

void  sort(t_row  *array, int low, int high)
{
  if (low >= high || low < 0)
    return;
  int pivot = partition(array, low, high);
  sort(array, low, pivot - 1);
  sort(array, pivot + 1, high);
}

int partition(t_row *array, int low, int high)
{
    int i = low;
    int plus = (array[high].name[0] == '_' ? 1 : 0) + (array[high].name[1] == '_' ? 1 : 0);
    char  *pivot = array[high].name + plus;

    for (int j = low; j < high; j++)
    {
      int plus = (array[j].name[0] == '_' ? 1 : 0) + (array[j].name[1] == '_' ? 1 : 0);
      if (strcasecmp(array[j].name + plus, pivot) < 0)
      { // if less than or equal to pivot, swap array[j] and pivot
        t_row temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
      }
    }
    t_row temp = array[i];
    array[i] = array[high];
    array[high] = temp;

    return (i);
}


