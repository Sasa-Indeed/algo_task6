// Task6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

enum genuinity  { Genuine, CounterfeitLight, CounterfeitHeavy};



typedef struct {
    double weight;
    genuinity gen;
}Coin;



/*
-1 : left pan is down

0  : pans are equal

1  : left pan is up
*/
int scale(Coin* rightPan, Coin* leftPan,int numCoins) {
    double rweight = 0, lweight = 0;

    for (int i = 0; i < numCoins; i++){
        rweight += rightPan[i].weight;
        lweight += leftPan[i].weight;
    }

    if (lweight > rweight){
        return -1;
    }else if (rweight > lweight) {
        return 1;
    } else{
        return 0;
    }

}

/*return false if all coins are geniune*/
bool fakeCoin(Coin* coins,  int numCoins,Coin* fake) {
    //for dividing the array of coins into smaller arrays
    if (numCoins > 3) {
        int numofGroups = (numCoins % 3 == 0)? numCoins/3 : numCoins/3 + 1;
        int n = 0;

        Coin** group = new Coin* [numofGroups];

        for (int i = 0; i < n; i++) {
            group[i] = new Coin[3];
        }

    }
}

int main(){
    int  a [5];

    std::cout << "Hello World!\n";
}

