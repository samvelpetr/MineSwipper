#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int difficulty(){
    int num =0;
    printf("******  HELLO  ******\nEnter the difficulty from 1 to 3\n");
    scanf("%d",&num);

    if(num > 3 || num <1){
        printf("WRONG NUMBER\n");
        exit(1);
    }
    return num;
}

void createMatrix(int level, char***arr1,char***arr2,int *sizeOfMatrix, int *mineCount){
    if(level == 1 ){
        *sizeOfMatrix = 6;
        *mineCount= 6;
    }else if (level== 2){
        *sizeOfMatrix = 9; 
        *mineCount =11;
    }
    else{
        *mineCount= 15;
        *sizeOfMatrix = 12;
    }

    *arr1= (char**)calloc(sizeof(char*),*sizeOfMatrix);
    *arr2= (char**)calloc(sizeof(char*),*sizeOfMatrix);
    for(int i = 0;i<*sizeOfMatrix;++i){
        (*arr1)[i]=(char*) calloc(sizeof(char),*sizeOfMatrix);
        (*arr2)[i]=(char*) calloc(sizeof(char),*sizeOfMatrix);
    }
    for(int i = 0;i<*sizeOfMatrix;++i){
        for(int j = 0;j< *sizeOfMatrix;j++){
            (*arr2)[i][j] = '0';
            (*arr1)[i][j] = '_';
        }
    }
}


void clearMatrix(char***arr1,char***arr2,int sizeOfMatix){
    for (int i = 0; i < sizeOfMatix; i++)
    {
        free((*arr1)[i]);
        free((*arr2)[i]);
    }
    free(*arr1);
    free(*arr2);
    
}
int generateNumber(int sizeOfMatrix){

    srand(time(NULL));
    return rand() % sizeOfMatrix;
 
}
void generateMines(int sizeOfMatrix,char **arr2,int mineCounts){
    for(int i = 0;i<mineCounts;i++){
        int y= generateNumber(sizeOfMatrix);
        int x= generateNumber(sizeOfMatrix);
        if(arr2[y][x]=='X'){
            mineCounts++;
            continue;
        }
        arr2[y][x]='X';
        if(y > 0 && arr2[y-1][x] != 'X'){
            arr2[y-1][x]++;
            if(x > 0 && arr2[y-1][x-1] !='X'){
                arr2[y-1][x-1]++;
            }
            if(x < sizeOfMatrix-1 && arr2[y-1][x+1] !='X'){
                arr2[y-1][x+1]++;
            }  
        }
        
             
        if(x > 0  && arr2[y][x-1] !='X' ){
            arr2[y][x-1]++;
        }
        if(x < sizeOfMatrix-1 && arr2[y][x+1] != 'X'){
            arr2[y][x+1]++;
        }
        if(y< sizeOfMatrix-1 && arr2[y+1][x] != 'X'){
            arr2[y+1][x]++;
            if( x > 0 && arr2[y+1][x-1] !='X'){
                arr2[y+1][x-1]++;
            }
            if( x < sizeOfMatrix-1 && arr2[y+1][x+1] !='X'){
                arr2[y+1][x+1]++;
            }
        }
       
        
    }   
}
void printMatrix(int sizeOfMatrix,char**arr){
    for (size_t i = 0; i < sizeOfMatrix; i++)
    {
        for (size_t j = 0; j < sizeOfMatrix; j++)
        {
            printf("%c   ",arr[i][j]);
        }
        printf("\n\n");   
    }
    
}
void openZero(int sizeOfMatrix,char**arr1,char**arr2,int y,int x){
    arr1[y][x]='0';
    if(arr2[y-1][x-1] == '0' &&  arr1[y-1][x-1] != '0' && y > 0 && x >  0){
        openZero(sizeOfMatrix,arr1,arr2,y-1,x-1);
    }if(arr2[y-1][x]=='0' &&  arr1[y-1][x]!='0' && y > 0 ){
        openZero(sizeOfMatrix,arr1,arr2,y-1,x);
    }
    if(arr2[y-1][x+1]=='0' &&  arr1[y-1][x+1]!='0' && y > 0 && x < sizeOfMatrix-1 ){
        openZero(sizeOfMatrix,arr1,arr2,y-1,x+1);
    }
    if(arr2[y][x+1]=='0' &&  arr1[y][x+1]!='0' && x < sizeOfMatrix-1 ){
        openZero(sizeOfMatrix,arr1,arr2,y,x+1);
    }
    if(arr2[y][x-1]=='0' &&  arr1[y][x-1]!='0' && x > 0 ){
        openZero(sizeOfMatrix,arr1,arr2,y,x-1);
    }
    if(arr2[y+1][x-1]=='0' &&  arr1[y+1][x-1]!='0' && x > 0 && y < sizeOfMatrix-1  ){
        openZero(sizeOfMatrix,arr1,arr2,y+1,x-1);
    }
    if(arr2[y+1][x]=='0' &&  arr1[y+1][x]!='0' && y < sizeOfMatrix-1  ){
        openZero(sizeOfMatrix,arr1,arr2,y+1,x);
    }
    if(arr2[y+1][x+1]=='0' &&  arr1[y+1][x+1]!='0' && y < sizeOfMatrix-1  && x< sizeOfMatrix-1 ){
        openZero(sizeOfMatrix,arr1,arr2,y+1,x+1);
    }
}
void enterPosition(int sizeOfMatrix,char**arr1,char**arr2){
    int count =0;


    int y,x;
    while(1){
        count++;
        printf("Enter Y cordinate\n");
        scanf(" %d",&y);
        printf("Enter X cordinate\n");
        scanf(" %d",&x);
        if(x>= sizeOfMatrix || x<0 || y >= sizeOfMatrix || y < 0){
            printf("Non Valid  cordinates\n");
            fflush(stdout);
            fflush(stdin);
            continue;
        }

        if(arr2[y][x]=='X'){
            printf("*****LOSE*****\n");
            printMatrix(sizeOfMatrix,arr2);
            break;
        }
        else if(arr2[y][x] != '0'){
            arr1[y][x]=arr2[y][x];
            printMatrix(sizeOfMatrix,arr1);
        }
        else if(arr2[y][x] == '0'){
            openZero(sizeOfMatrix,arr1,arr2,y,x);
            printMatrix(sizeOfMatrix,arr1);

        }
        
    }
}
int main(){
    int sizeOfMatrix=0; 
    char **arr1;
    char **arr2;
    int mineCount=0;
    int level = difficulty();

    createMatrix(level,&arr1,&arr2,&sizeOfMatrix,&mineCount);
    generateMines(sizeOfMatrix,arr2,mineCount);
    printMatrix(sizeOfMatrix,arr1);
    enterPosition(sizeOfMatrix,arr1,arr2);

    clearMatrix(&arr1,&arr2,sizeOfMatrix);
}