#include <stdio.h>
#include <stdbool.h>

#define GAME_SIZE 9

void scanGame(int grid[][GAME_SIZE]);
void printGame(int grid[][GAME_SIZE]);
bool solveGame(int grid[][GAME_SIZE]);
bool findBlankSpace(int grid[][GAME_SIZE], int* row, int* col);
bool usedInRow(int grid[][GAME_SIZE], int row, int num);
bool usedInCol(int grid[][GAME_SIZE], int col, int num);
bool usedInBox(int grid[][GAME_SIZE], int row, int col, int num);

void scanGame(int grid[][GAME_SIZE]){
    for(int i = 0; i < GAME_SIZE; ++i){
        for(int j = 0; j < GAME_SIZE; ++j){
            scanf("%d", &grid[i][j]);
        }
    }
}

bool solveGame(int grid[][GAME_SIZE]){
    int row, col;

    if(!findBlankSpace(grid,&row,&col))
        return true;
    else{
        for(int num = 1; num <= 9; ++num){
            if(!usedInBox(grid,row,col,num) && !usedInCol(grid,col,num) && !usedInRow(grid,row,num)){
                grid[row][col] = num;
                if(solveGame(grid))
                    return true;
            }
            grid[row][col] = 0;
        }
    }
    return false;
}

bool findBlankSpace(int grid[][GAME_SIZE], int* row, int* col){
    for(*row = 0; *row < GAME_SIZE; ++*row){
        for(*col = 0; *col < GAME_SIZE; ++*col){
            if(grid[*row][*col] == 0)
                return true;
        }
    }
    return false;
}

bool usedInRow(int grid[][GAME_SIZE], int row, int num){
    for(int col = 0; col < GAME_SIZE; ++col)
        if(grid[row][col] == num){
            return true;
        }
    return false;
}

bool usedInCol(int grid[][GAME_SIZE], int col, int num){
    for(int row = 0; row < GAME_SIZE; ++row)
        if(grid[row][col] == num){
            return true;
        }
    return false;
}

bool usedInBox(int grid[][GAME_SIZE], int row, int col, int num){
    int boxStartRow = row - (row % 3);
    int boxStartCol = col - (col % 3);

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(grid[boxStartRow+i][boxStartCol+j] == num){
                return true;
            }
        }
    }
    return false;
}

void printGame(int grid[][GAME_SIZE]){
    printf("-------------------------\n");
    for(int i = 0; i < GAME_SIZE; ++i){
        printf("|");
        for(int j = 0; j < GAME_SIZE; ++j){
            printf(" %d",grid[i][j]);
            if((j+1) % 3 == 0)
                printf(" |");
        }
        if((i+1) % 3 == 0)
            printf("\n-------------------------");
        printf("\n");
    }
}

int main(){
    int grid[GAME_SIZE][GAME_SIZE];

    scanGame(grid);
    solveGame(grid);
    printGame(grid);
}
