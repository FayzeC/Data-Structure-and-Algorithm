#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Global array for memory
#define max_N 100
int M[max_N];

int top_down_dp(int n)
{
    // Check if F(n) has already been computed and stored in the memory array
    if (M[n] != -1) return M[n]; // return value if it has been calculated

    // Store and return values for F(0), F(1), F(2)
    if(n == 0){
        M[0] = 0;
        return 0;
    }

    if(n == 1){
        M[1] = 1;
        return 1;
    }

    if(n == 2){
        M[2] = 2;
        return 2;
    }

    // Compute F(n) recursively and store in memory array
    M[n] = top_down_dp(n-1) + 2 * top_down_dp(n-2) - 3 * top_down_dp(n-3);
    return M[n];
}

int main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);

    // Initialise M[n] to -1
    for(i = 0; i <= n; i++){
        M[i] = -1;
    }

    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));

}
