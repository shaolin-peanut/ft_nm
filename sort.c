# include "include/ft_nm.h"

void    sort(t_row *array, int low, int high) {
    if (low < high) {
        int pivot = partition(array, low, high);
        sort(array, low, pivot - 1);
        sort(array, pivot + 1, high);
    }
}

int partition(t_row *array, int low, int high) {
    t_row *left_val = 0;
    t_row *right_val = 0;
    char *pivot = array[low].name;
    int left = low + 1;
    int right = high;

    while (left <= right) {
        left_val = array + left;
        right_val = array + right;
        while (left_val->name < pivot)
            left++;
        while (right_val->name > pivot)
            right--;
        if (left <= right) {
            swap_ptr((void *) left_val, (void *) right_val);
            left++; right--;
        }
    }
}