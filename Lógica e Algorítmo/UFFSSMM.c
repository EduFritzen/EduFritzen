#include <stdio.h>
#include <stdlib.h>

int main(){
    char mat1[4][4] ={'U', 0, 0, 0, 0, 'F', 0, 0, 0, 0, 'S', 0, 0, 0, 0, 'M'};
    for(int i=0;i<4;i++){
        if(mat1[i][i]==mat1[0][0]){
        printf("%c", mat1[i][i]);
        }
        else{
        printf("%c%c", mat1[i][i], mat1[i][i]);
        }
    }
    return 0;
}




















