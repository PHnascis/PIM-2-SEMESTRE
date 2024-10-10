int main(){


int mat[3][3];
int i, j, soma;

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
         mat[i][j] = (i *3) + j + 1;

        }
    }

     for(i=0; i<3; i++){
        for(j=0; j<3; j++){
        printf("%3d", mat[i][j]);

        }
        printf("\n");
    }


return 0;
}
