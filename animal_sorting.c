#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define INPUT_FILE "scores.txt"
#define NUM_TRAITS 7
#define TOTAL_IDX 6
#define MAX_LEN 13
#define BASE_CASE_SIZE 30


typedef struct Cat_s {
    char *name;             // Cat's name (unique)
    int scores[NUM_TRAITS];
} Cat;

// Global Variable
const char TRAITS[NUM_TRAITS][MAX_LEN] = {
    "Cuteness", "Fluffiness", "Agility", "Friendliness",
    "Intelligence", "Laziness", "Total"
};

// Function Prototypes
void myMain(FILE *ifile);
int compareTo(Cat *ptrC1, Cat *ptrC2, int key);
void mergeSort(Cat **list, int n, int key);
void mergeSortRec(Cat **list, int low, int high, int key);
void quickSort(Cat **list, int n, int key);
void quickSortRec(Cat **list, int low, int high, int key);

// You may add more functions if necessary
void insertionSort(Cat **list, int low, int high, int key);
void merge(Cat **list, int low, int mid, int high, int key);
int partition(Cat **list, int low, int high, int key);
void swapCats(Cat **a, Cat **b);

// BEGIN: DO NOT MODIFY THE MAIN FUNCTION
#ifndef MAIN_FUNCTION
int main(void) {
    // Open the input file for reading.
    // This is the only part of the entire code where the file
    // is going to be opened. You should not have any
    // fopen() function call in your functions. Simply
    // pass this existing FILE pointer when necessary.
    FILE *ifile = fopen(INPUT_FILE, "r");

    if( ifile == NULL ) {
        printf("File Does Not Exist!\n");
        return 1;
    }

    // Calls your own main function and passes the file stream
    myMain(ifile);

    // Close the file
    fclose(ifile);

    return 0;
}
#endif
// END: DO NOT MODIFY THE MAIN FUNCTION

// Function Definitions
void myMain(FILE *ifile) {
    // TODO: Complete this function
    // TODO 1 BEGIN
    int n, i, j;
    int sortType, key;
    Cat **list;
    static char tempName[MAX_LEN];
    srand(time(0));
    // Read number of cats
    fscanf(ifile, "%d", &n);

    list = (Cat **)malloc(sizeof(Cat *) * n);

    // read each cat
    for(i = 0; i < n; i++) {
        list[i] = (Cat *)malloc(sizeof(Cat));

        fscanf(ifile, "%s", tempName);
        list[i]->name = (char *)malloc(sizeof(char) * (strlen(tempName) + 1));
        strcpy(list[i]->name, tempName);

        list[i]->scores[TOTAL_IDX] = 0;
        for(j = 0; j < TOTAL_IDX; j++) {
            fscanf(ifile, "%d", &list[i]->scores[j]);
            list[i]->scores[TOTAL_IDX] += list[i]->scores[j];
        }
    }
    // Read the sorting type
    fscanf(ifile, "%d %d", &sortType, &key);

    if(sortType == 1) {
        mergeSort(list, n, key);
    }
    else {
        quickSort(list, n, key);
    }

    printf("%s Rank List\n", TRAITS[key]);
    // Print sorted list
    for(i = 0; i < n; i++) {
        printf("%d. %-15s %d\n", i + 1, list[i]->name, list[i]->scores[key]);
    }

    for(i = 0; i < n; i++) {
        free(list[i]->name);
        free(list[i]);
    }
    free(list);
    // TODO 1 END
}
int compareTo(Cat *ptrC1, Cat *ptrC2, int key) {
    // TODO: Complete this function
    // TODO 2 BEGIN
    // Compare score
    if(ptrC1->scores[key] > ptrC2->scores[key]) {
        return -1;
    }
    else if(ptrC1->scores[key] < ptrC2->scores[key]) {
        return 1;
    }
    else {
        return strcmp(ptrC1->name, ptrC2->name);
    }
    // TODO 2 END
}
void mergeSort(Cat **list, int n, int key) {
    // TODO: Complete this function
    // TODO 3 BEGIN
    if(n <= 1) {
        return;
    }
    mergeSortRec(list, 0, n - 1, key);
    // TODO 3 END
}
void mergeSortRec(Cat **list, int low, int high, int key) {
    // TODO: Complete this function
    // TODO 4 BEGIN
    int mid;

    if(low >= high) {
        return;
    }

    if(high - low + 1 <= BASE_CASE_SIZE) {
        insertionSort(list, low, high, key);
        return;
    }

    mid = (low + high) / 2;

    mergeSortRec(list, low, mid, key);
    mergeSortRec(list, mid + 1, high, key);
    merge(list, low, mid, high, key);
    // TODO 4 END
}
void quickSort(Cat **list, int n, int key) {
    // TODO: Complete this function
    // TODO 5 BEGIN
    if(n <= 1) {
        return;
    }
    quickSortRec(list, 0, n - 1, key);
    // TODO 5 END
}
void quickSortRec(Cat **list, int low, int high, int key) {
    // TODO: Complete this function
    // TODO 6 BEGIN
    int pivotIndex;

    if(low >= high) {
        return;
    }

    if(high - low + 1 <= BASE_CASE_SIZE) {
        insertionSort(list, low, high, key);
        return;
    }

    pivotIndex = partition(list, low, high, key);

    quickSortRec(list, low, pivotIndex - 1, key);
    quickSortRec(list, pivotIndex + 1, high, key);
    // TODO 6 END
}
void insertionSort(Cat **list, int low, int high, int key) {
    int i, j;
    Cat *temp;

    for(i = low + 1; i <= high; i++) {
        temp = list[i];
        j = i - 1;
        // shift the elements
        while(j >= low && compareTo(temp, list[j], key) < 0) {
            list[j + 1] = list[j];
            j--;
        }

        list[j + 1] = temp;
    }
}
void merge(Cat **list, int low, int mid, int high, int key) {
    int i = low, j = mid + 1, k = 0;
    int size = high - low + 1;
    // Temp usef to merge the arrays
    Cat **temp = (Cat **)malloc(sizeof(Cat *) * size);

    while(i <= mid && j <= high) {
        if(compareTo(list[i], list[j], key) <= 0) {
            temp[k++] = list[i++];
        }
        else {
            temp[k++] = list[j++];
        }
    }
    // copy the remaining elements
    while(i <= mid) {
        temp[k++] = list[i++];
    }
    while(j <= high) {
        temp[k++] = list[j++];
    }
    for(i = 0; i < size; i++) {
        list[low + i] = temp[i];
    }

    free(temp);
}

int partition(Cat **list, int low, int high, int key) {
    // select random pivot
    int pivotPos = low + rand() % (high - low + 1);
    Cat *pivot;
    int i, j;

    swapCats(&list[pivotPos], &list[high]);
    pivot = list[high];

    i = low - 1;
    for(j = low; j < high; j++) {
        if(compareTo(list[j], pivot, key) <= 0) {
            i++;
            swapCats(&list[i], &list[j]);
        }
    }
    // Place in right position
    swapCats(&list[i + 1], &list[high]);
    return i + 1;
}

void swapCats(Cat **a, Cat **b) {
    Cat *temp = *a;
    *a = *b;
    *b = temp;
}