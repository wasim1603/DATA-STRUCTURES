#include <stdio.h>
#define MAX_SIZE 100
void display(int arr[], int size) {
    printf("Array elements: ");
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int insert(int arr[], int size, int pos, int element) {
    if (size >= MAX_SIZE) {
        printf("Array is full. Cannot insert.\n");
        return size;
    }
    if (pos < 0 || pos > size) {
        printf("Invalid position for insertion.\n");
        return size;
    }
    int i;
    for (i = size; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = element;
    return size + 1;
}
int deleteElement(int arr[], int size, int pos) {
    if (size <= 0) {
        printf("Array is empty. Cannot delete.\n");
        return size;
    }
    if (pos < 0 || pos >= size) {
        printf("Invalid position for deletion.\n");
        return size;
    }
    int i;
    for (i = pos; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    return size - 1;
}
int main() {
    int arr[MAX_SIZE];
    int size = 0;
    size = insert(arr, size, 0, 5);
    size = insert(arr, size, 1, 10);
    size = insert(arr, size, 2, 7);
    display(arr, size);
    size = deleteElement(arr, size, 2);
    display(arr, size);
    return 0;
}

