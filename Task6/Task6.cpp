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
int scale(Coin* leftPan, Coin* rightPan,int numCoins) {
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
bool fakeCoin(Coin* coins,  int numCoins) {
    //for dividing the array of coins into smaller arrays
    if (numCoins == 3) {
        Coin* fake = findFakeInGroupOfThree(coins);
        if (fake == NULL) {
            return false;
        }
        else {
            return true;

        }
    }
    else if (numCoins > 3) {
        int numofGroups = (numCoins % 3 == 0)? numCoins/3 : numCoins/3 + 1;
        int n = 0;

        Coin*** group = new Coin** [numofGroups];

        for (int i = 0; i < numofGroups; i++) {
            group[i] = new Coin*[3] {};
        }
        for (int i = 0; i < numCoins; i++) {
            group[i / 3][i % 3] = &coins[i];
        }

        for (int i = 0; i < numofGroups; i++) {
            if (i == numofGroups - 1 && numCoins % 3 == 1) {
                if (scale(group[i - 1][0], group[i][0], 1) == 0) {
                    group[i][0]->gen = Genuine;
                    return false;
                }
                else if (scale(group[i - 1][0], group[i][0], 1) == -1) {
                    group[i][0]->gen = CounterfeitLight;
                    return true;
                }
                else {
                    group[i][0]->gen = CounterfeitHeavy;
                    return true;
                }
            }
            else if (i == numofGroups - 1 && numCoins % 3 == 2) {
                group[i][2] = group[i - 1][0];
                Coin* fake = findFakeInGroupOfThree(*group[i]);
                if (fake == NULL) {
                    return false;
                }
                else {
                    return true;
                }
            }
            Coin* fake = findFakeInGroupOfThree(*group[i]);
            if (fake != NULL) {
                return true;
            }
        }
    }
}

int main(){
    Coin coin1 = {1.0};
    Coin coin2 = { 1.0 };
    Coin coin3 = { 1.0 };
    Coin coin4 = { 1.0 };
    Coin coin5 = { 1.0 };
    Coin coin6 = { 1.0 };
    Coin coin7 = { 1.0 };
    Coin coin8 = { 1.0 };
    Coin coin9 = { 1.0 };
    Coin coin10 = { 1.0 };
    Coin coin11 = { 1.0 };
    Coin coin12 = { 1.1 };
    Coin test[]{coin1,
        coin2,
        coin3,
        coin4,
        coin5,
        coin6,
        coin7,
        coin8,
        coin9,
        coin10,
        coin11,
        coin12};
    if (sizeof(test) / sizeof(Coin) < 3) {
        std::cout << "invalid number of coins"<<std::endl;
    }
    else {
        bool result = fakeCoin(test, 12);
        for (int i = 0; i < 12; i++) {
            std::cout << "Coin " << i << " : " << test[i].gen << std::endl;
        }
    }
}

