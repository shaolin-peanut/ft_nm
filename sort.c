# include "include/ft_nm.h"

void  sort(t_row  *array, int low, int high)
{
  if (low >= high || low < 0)
    return;
  int pivot = partition(array, low, high);
  sort(array, low, pivot - 1);
  sort(array, pivot + 1, high);
}

char  *get_name(t_row *array, int index)
{
  int plus = (array[index].name[0] == '_' ? 1 : 0) + (array[index].name[1] == '_' ? 1 : 0);
  return (array[index].name + plus);
}

int partition(t_row *array, int low, int high)
{
    int left = low;
    char *pivot = get_name(array, high);

    for (int right = low; right < high; right++)
    {
      int plus = (array[right].name[0] == '_' ? 1 : 0) + (array[right].name[1] == '_' ? 1 : 0);
      if (strcasecmp(get_name(array, right), pivot) < 0)
      { // if less than or equal to pivot, swap array[j] and pivot
        t_row temp = array[left];
        array[left] = array[right];
        array[right] = temp;
        left++;
      }
    }
    t_row temp = array[left];
    array[left] = array[high];
    array[high] = temp;

    return (left);
}


