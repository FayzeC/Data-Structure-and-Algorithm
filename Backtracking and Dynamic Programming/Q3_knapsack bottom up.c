#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Global matrix for memoization
int **matrix;

int bottom_up_dp(int n, int *s, int *v, int C)
{
    int i, j;

    // Initialise first row of the matrix
    for(j=1 ; j<=C; j++){
        if(s[1] <= j){ // if size of first item fits in current capacity
            matrix[1][j] = v[1]; // set value of matrix to value of first item
        }else{
            matrix[1][j] = 0; // else first item not included
        }
    }

    // Calculate maximum value for each slot starting with item 2
    for(i=2; i<=n; i++){
        for(j=1; j<=C; j++){
            if(j >= s[i]){ // if including the current item doesn't exceed the capacity
                // choose maximum value between including and excluding the item
                matrix[i][j] = (matrix[i-1][j] > matrix[i-1][j-s[i]] + v[i]) ? matrix[i-1][j] : matrix[i-1][j-s[i]] + v[i];
            }else{
                matrix[i][j] = matrix[i-1][j]; // carry forward value from previous row
            }
        }
    }

    return matrix[n][C];
}

int main ()
{
    int n,C; // n = num of items, C = capacity
    int function;
    int *s; // size
    int *v; // value
    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));

    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);

    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);

    // Allocate memory for matrix
    matrix = (int **)malloc((n+1) * sizeof(int *));
    for(i=0; i<=n; i++){
        matrix[i] = (int *)malloc((C+1) * sizeof(int));
    }

    // Initialise matrix with zeros
    for(i=0; i<=n; i++){
        for(j=0; j<=C; j++){
            matrix[i][j] = 0;
        }
    }

    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));

    // Free allocated memory for matrix
    for(i=0; i<=n; i++){
        free(matrix[i]);
    }
    free(matrix);
}
