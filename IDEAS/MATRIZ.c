#include <stdio.h>

int main(){


int mat[10][10];
int i, j, soma;

    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
         mat[i][j] = (i *10) + j + 1;

        }
    }

     for(i=0; i<10; i++){
        for(j=0; j<10; j++){
        printf("%5d", mat[i][j]);

        }
        printf("\n");
    }


return 0;
}
