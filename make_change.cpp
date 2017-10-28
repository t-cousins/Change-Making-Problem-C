#include <iostream>
using namespace std;

void make_change(const int coins[], const int numcoins, const int total){
    
    //m[i][j] = min no of coins required to make j pence by using coins attributed to rows <=
    //row i. Allocating memory...
    
    int **m;
    m = new int*[numcoins+1];
    for (int i=0; i<=numcoins; i++){
        m[i] = new int [total];
    };
    
    //q[i][j] = coins required to minimally make j pence using coins attributed to rows <= row i
    
    int **q;
    q = new int*[numcoins+1];
    for (int i=0; i<=numcoins; i++){
          q[i] = new int [total];
    };

    //first row is attributed to 1p by default. min no of 1p coins to make x pence is x

    for(int i=0;i<total;i++){
        m[0][i] = i+1;
        q[0][i] = 1;
    };

    for(int i=0; i<numcoins; i++){       //for each coin

        for(int j=1; j<=total; j++){       //for each value up until the total
//
            if(coins[i]==j){   //if current coin is equal to the total, then total can be made with one coin
                m[i+1][j-1] = 1;
                q[i+1][j-1] = coins[i];
            }
            else if(coins[i]>j){    //if current coin > total, then total use solution for previous coins
                m[i+1][j-1] = m[i][j-1];
                q[i+1][j-1] = q[i][j-1];
            }

            else {       //if we can use current coin, then optimal solution is the minimum of:
             //previous solution & 1 + no. of coins required to make (current total - current coin)
                if(m[i][j-1] > 1 + m[i+1][j-1 - coins[i]]){

                    m[i+1][j-1] = 1 + m[i+1][j-1 - coins[i]];
                    q[i+1][j-1] = q[i+1][j-1-coins[i]];
                }
                else {
                    m[i+1][j-1] = m[i][j-1];
                    q[i+1][j-1] = q[i][j-1];
                }
                
            }

        }
        
    }
    
    printf("The minimum number of coins is %d\n", m[numcoins][total-1]);
    printf("Obtained using the coins:\n");
    
    //go along last row in q and backtrack
    int i = total-1;
    while(i>0){
        printf("%d\n", q[numcoins][i]);
        i -= q[numcoins][i];
    }
    
};

int main(int argc, char **argv)
{
    const int coins[] = {2, 5, 10, 25, 21, 112};
    const int total = 103;
    const int numcoins = sizeof(coins)/sizeof(*coins);
    
    make_change(coins, numcoins, total);
    
    return 0;
};

