#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100

struct ThreadArgs {
    int *arr;
    int start;
    int end;
};


void merge(int arr[], int left[], int right[], int left_size, int right_size) {
    int i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < left_size) {
        arr[k++] = left[i++];
    }
    while (j < right_size) {
        arr[k++] = right[j++];
    }
}


void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        int left_size = mid - left + 1;
        int right_size = right - mid;

        int left_half[left_size], right_half[right_size];
        for (int i = 0; i < left_size; ++i) {
            left_half[i] = arr[left + i];
        }
        for (int j = 0; j < right_size; ++j) {
            right_half[j] = arr[mid + 1 + j];
        }

        merge(arr + left, left_half, right_half, left_size, right_size);
    }
}

void *sort_half(void *args) {
    struct ThreadArgs *th_args = (struct ThreadArgs *)args;
    merge_sort(th_args->arr, th_args->start, th_args->end);
    return NULL;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid input size.\n");
        return 1;
    }

    int arr[MAX_SIZE];
    printf("Enter the numbers:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    int mid = n / 2;

    pthread_t tid[2];
    struct ThreadArgs args[2];

    
    args[0].arr = arr;
    args[0].start = 0;
    args[0].end = mid;
    pthread_create(&tid[0], NULL, sort_half, &args[0]);

    args[1].arr = arr;
    
    args[1].start = mid;
    args[1].end = n-1;
    pthread_create(&tid[1], NULL, sort_half, &args[1]);

    
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    
    int first_half[mid], second_half[n - mid];
    for (int i = 0; i < mid; ++i) {
        first_half[i] = arr[i];
    }
    for (int i = mid; i < n; ++i) {
        second_half[i - mid] = arr[i];
    }

    merge(arr, first_half, second_half, mid, n - mid);

    printf("Sorted array: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
