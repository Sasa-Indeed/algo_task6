// Task6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

enum genuinity  { Genuine, CounterfeitLight, CounterfeitHeavy};



typedef struct {
    int id;
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


//NULL ----> all coins are genuine
Coin* findFakeInGroupOfThree(Coin* groupOfCoins){
    //1:2
    int scaleResult = scale(&groupOfCoins[0], &groupOfCoins[1], 1);

    if (scaleResult == 0) {
        groupOfCoins[0].gen = Genuine;
        groupOfCoins[1].gen = Genuine;
        scaleResult = scale(&groupOfCoins[1], &groupOfCoins[2], 1); // 2 : 3
        // 1 = 2
        if (scaleResult == 0) {
            //All coins are the same weight
            groupOfCoins[2].gen = Genuine;
            return NULL;
        }else {
            /*Here the third coin is either heavier or lighter than the first two*/
            (scaleResult > 0) ? groupOfCoins[2].gen = CounterfeitHeavy : groupOfCoins[2].gen = CounterfeitLight;
            return &groupOfCoins[2];
        }
    }else if(scaleResult == -1) {
        /*1 : 2 and left pan went down*/
        if (scale(&groupOfCoins[0], &groupOfCoins[2], 1) == 0) {
            groupOfCoins[1].gen = CounterfeitLight;
            groupOfCoins[0].gen = Genuine;
            groupOfCoins[2].gen = Genuine;
            return &groupOfCoins[1];
        }
        else {
            groupOfCoins[1].gen = Genuine;
            groupOfCoins[2].gen = Genuine;
            groupOfCoins[0].gen = CounterfeitHeavy;
            return &groupOfCoins[0];
        }
    }else{
        if (scale(&groupOfCoins[0], &groupOfCoins[2], 1) == 0) {
            groupOfCoins[1].gen = CounterfeitHeavy;
            groupOfCoins[2].gen = Genuine;
            groupOfCoins[0].gen = Genuine;
            return &groupOfCoins[1];
        }
        else {
            groupOfCoins[2].gen = Genuine;
            groupOfCoins[1].gen = Genuine;
            groupOfCoins[0].gen = CounterfeitLight;
            return &groupOfCoins[0];
        }
    }
}

/*return false if all coins are geniune*/
bool fakeCoin(Coin* coins,  int numCoins,Coin* fake) {
    //for dividing the array of coins into smaller arrays
    if (numCoins == 1 || numCoins == 2) {
        std::cout << "Impossible to determine whether there is a fake coin or not using a balance scale"<<std::endl;
    }
    else if (numCoins == 3) {
        Coin* fake = findFakeInGroupOfThree(coins);
        if (fake == NULL) {
            std::cout << "All coins are genuine" << std::endl;
        }
        else {
            std::cout << "Coin number: " << fake->id << " is fake" << std::endl;

        }
    }
    else if (numCoins > 3) {
        int numofGroups = (numCoins % 3 == 0)? numCoins/3 : numCoins/3 + 1;
        int n = 0;

        Coin** group = new Coin* [numofGroups];

        for (int i = 0; i < n; i++) {
            group[i] = new Coin[3];
        }

        for (int i = 0; i < numCoins; i++) {
            group[i / 3][i % 3] = coins[i];
        }
        Coin** result = new Coin*[numofGroups];

        for (int i = 0; i < numofGroups; i++) {
            if (i == numofGroups - 1) {
                // implement logic to check if last group has less than 3 elements
                // and act acordingly
            }
            result[i] = findFakeInGroupOfThree(group[i]);
        }
    }
}

int main(){
    int  a [5];

    std::cout << "Hello World!\n";
}

