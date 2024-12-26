#include <stdio.h>
#include <stdbool.h>

typedef struct NET{
    int start, end;
} NET;

typedef struct {
    int data[1001];
    int size;
} IntSet;

void initializeSet(IntSet *set) {
    set->size = 0;
}

void insertElement(IntSet *set, int element) {
    if (set->size < 1001) {
        set->data[set->size] = element;
        set->size++;
        printf("Inserted element: %d\n", element);
    } else {
        printf("Set is full. Cannot insert element: %d\n", element);
    }
}

void searchAndDeleteElement(IntSet *set, int element) {
    for (int i = 0; i < set->size; i++) {
        if (set->data[i] == element) {
            for (int j = i; j < set->size - 1; j++) {
                set->data[j] = set->data[j + 1];
            }
            set->size--;
            printf("Deleted element: %d\n", element);
            return;
        }
    }
    printf("Element %d not found in the set.\n", element);
}

bool isEmpty(IntSet *set) {
    return set->size == 0;
}

int main(int argc, char **argv){
    if (argc < 2) {
        printf("Usage: %s <argument>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int net_num;
    int pin_num;
    fscanf(file, "%d", &pin_num);
    fscanf(file, "%d", &net_num);
    int temp = 0;
    int X = 1, Y = 1;
    NET I[1001];

    for (int i = 0; i < 1001; i++)
    {
        I[i].start = -1;
        I[i].end = -1;
    }
     IntSet U;
    initializeSet(&U);

    while (fscanf(file, "%d", &temp) == 1) {
        
        if (I[temp].start == -1){
            I[temp].start = X;
        }
        if (I[temp].end < X){
            I[temp].end = X;
        }
        X++;

        fscanf(file, "%d", &temp);
        if (I[temp].start == -1){
            I[temp].start = Y;
        }
        if (I[temp].end < Y){
            I[temp].end = Y;
        }
        Y++;
    }

    for (int i = 1; i <= net_num; i++)
    {
        insertElement(&U, i);
    }
    int t = 0;

    while (!isEmpty(&U)){
        t++;
        int watermark = 0;

    }


    fclose(file);

    return 0;
}