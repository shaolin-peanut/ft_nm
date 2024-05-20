# include "include/ft_nm.h"

void swap(t_row *a, t_row *b) {
  t_row temp = *a;
  *a = *b; 
  *b = temp;
}

void sort(t_row *array, int low, int high) {

  if (low < high) {
    int pivot_index = partition(array, low, high);

    sort(array, low, pivot_index - 1); 
    sort(array, pivot_index + 1, high);
  }

}

int partition(t_row *array, int low, int high) {

  t_row pivot = array[low];  

  int i = low - 1; 
  int j = high + 1;

  while (true) {

    do {
      i++; 
    } while (strcmp(array[i].name, pivot.name) < 0);

    do { 
      j--;
    } while (strcmp(array[j].name, pivot.name) > 0);

    if (i >= j)
      return j;

    swap(&array[i], &array[j]);

  }

}
