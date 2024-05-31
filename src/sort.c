# include "../include/ft_nm.h"

char  *strip_prefix(char *name)
{
  int prefix_count = (name[0] == '_' ? 1 : 0) + (name[1] == '_' ? 1 : 0);
  return (name + prefix_count);
}

bool inferior_or_equal(t_row *array, int left, int right)
{
  char  *sleft = strip_prefix(array[left].name);
  char  *sright = strip_prefix(array[right].name);
  int difference = ft_strcasecmp(sleft, sright);
  if (difference == 0)
    return left >= right;
  return (difference < 0);
}

void  swap(t_row *array, int left, int right)
{
  t_row temp = array[left];
  array[left] = array[right];
  array[right] = temp;
}

// quicksort

void  sort(t_row *array, int low, int high)
{
  if (low > high || low < 0)
    return;
  int pivot = partition(array, low, high);
  sort(array, low, pivot - 1);
  sort(array, pivot + 1, high);
}

int partition(t_row *array, int low, int high)
{
  for (int right = low; right < high; right++)
  {
    if (inferior_or_equal(array, right, high))
    {
      swap(array, right, low);
      low++;
    }
  }
  swap(array, low, high);
  return low;
}


