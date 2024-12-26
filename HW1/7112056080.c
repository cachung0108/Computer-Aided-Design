#include <stdio.h>

int xRy[100][100] = {0};
int extra[100][100];

int power(int x, int times) {
    if (times == 0) {
        return 1;
    }
    return x * power(x, times - 1);
}

typedef struct {
    int setY;
    int y_num, cost;
    int Y[100];
} Set;

Set min_cover (int sizeOfX, int sizeOfY, int weightOfY[]) {
    for (int i = 1; i <= sizeOfY; i++) {
        for (int j = 1; j <= sizeOfY; j++) {
            extra[i][j] = 0;
        }
    }
    Set min_set;
    min_set.cost = 10000;
    int min_y_num = 10000;
    for (int i = 0; i < power(2, sizeOfY); i++) {
        Set temp_set;
        temp_set.cost = 0;
        temp_set.setY = i;
        int cur_setY = i;
        int count = 1;
        int coveredX[100] = {0};
        int covered = 1;
        int y_num = 0;
        int Y[100] = {0};
        while ( cur_setY > 0 ){
            if ( cur_setY%2 == 1 ){
                Y[count] += 1;
                y_num += 1;
                temp_set.cost += weightOfY[count];
                //printf("%d ", weightOfY[count]);
                for (int j = 1; j <= sizeOfX; j++){
                    if ( xRy[j][count] == 1){
                        coveredX[j] = 1;
                    }
                }
            }
            cur_setY /= 2;
            count ++;
        }
        
        
        for (int j = 1; j <= sizeOfX; j++) {
            if ( coveredX[j] == 0 ) {
                covered = 0;
            }
        }


        if ( y_num < min_y_num  && covered == 1 ){
            min_set.setY = i;
            min_set.y_num = y_num;
            min_y_num = y_num;
            min_set.cost = temp_set.cost;
            for (int j = 1; j <= sizeOfY; j++){
                min_set.Y[j] = Y[j];
            }
        } else if ( y_num == min_y_num && temp_set.cost < min_set.cost && covered == 1 )
        {
            min_set.setY = i;
            min_set.y_num = y_num;
            min_y_num = y_num;
            min_set.cost = temp_set.cost;
            for (int j = 1; j <= sizeOfY; j++){
                min_set.Y[j] = Y[j];
            }
        }
        //printf("\n");
    }

    for (int i = 0; i < power(2, sizeOfY); i++) {
        Set temp_set;
        temp_set.cost = 0;
        temp_set.setY = i;
        int cur_setY = i;
        int count = 1;
        int coveredX[100] = {0};
        int covered = 1;
        int y_num = 0;
        int Y[100] = {0};
        while ( cur_setY > 0 ){
            if ( cur_setY%2 == 1 ){
                Y[count] += 1;
                y_num += 1;
                temp_set.cost += weightOfY[count];
                for (int j = 1; j <= sizeOfX; j++){
                    if ( xRy[j][count] == 1){
                        coveredX[j] = 1;
                    }
                }
            }
            cur_setY /= 2;
            count ++;
        }

        for (int j = 1; j <= sizeOfX; j++) {
            if ( coveredX[j] == 0 ) {
                covered = 0;
            }
        }
        if ( y_num == min_y_num && temp_set.cost == min_set.cost && covered == 1 ) {
            
            int k = 0;
            while (extra[k][0] != 0){
                k++;
            }
            extra[k][0] = 1;
            for (int j = 1; j <= sizeOfY; j++){
                if (Y[j]) {
                    extra[k][j] = Y[j];
                }
            }
        }
    }

    return min_set;
}

int main (int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s input_filename\n", argv[0]);
        return 1;
    }

    char *input_filename = argv[1];

    FILE *input = fopen(input_filename,"r");
    if(input == NULL) {
        printf("An error occurred while reading the file.");
        return 1;
    }
    FILE *output = fopen("output.txt","w");

    int weightOfY[100] = {0};
    int sizeOfX;
    int sizeOfY;
    int tempX, tempY;
    int i;
    int setY[100] = {0};
    Set min;
    
    fscanf(input, "%d", &sizeOfX);
    fscanf(input, "%d", &sizeOfY);
    
    for (int i = 1; i <= sizeOfY; i++){
        fscanf(input, "%d", &weightOfY[i]);
    }

    while (1) {
        fscanf(input, "%d", &tempX);
        fscanf(input, "%d", &tempY);
        if (xRy[tempX][tempY] == 0) {
            xRy[tempX][tempY] = 1;    
        } else {
            break;
        }
    }

    for (int i = 1; i <= sizeOfX; i++) {
        for (int j = 1; j <= sizeOfY; j++){
            printf("%d ", xRy[i][j]);
        }
        printf("\n");
    }

    min = min_cover (sizeOfX, sizeOfY, weightOfY);

    int k = 0;
    while (extra[k][0] != 0){
        for (int j = 1; j <= sizeOfY; j++){
            if (extra[k][j]) {
                fprintf(output, "%d ", j);
            }
        }
        fprintf(output, "\n");
        k++;
    }    

    fprintf(output, "(%d, %d)", min.y_num, min.cost); 



    fclose(input);
    fclose(output);

    return 0;
}