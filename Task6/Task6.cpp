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
int scale(Coin* leftPan, Coin* rightPan, int numCoins) {
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



/*
1: there exits one fake

0 : impossible

-1 : all are genuine
*/
int fakeCoin(Coin* coins, int numCoins, Coin* fake) {

    if (numCoins == 1 || numCoins == 2) {
        return 0;
    }else if (numCoins == 3) {
        Coin* pt = findFakeInGroupOfThree(coins);
        

        if (pt) {
            fake->gen = pt->gen;
            fake->id = pt->id;
            return 1;
        }else{
            fake->gen = Genuine;
            return -1;
        }

    }else{
        int numofGroups = (numCoins % 3 == 0) ? numCoins / 3 : numCoins / 3 + 1;
        
         Coin** group = new Coin* [numofGroups];
        
        for (int i = 0; i < numofGroups; i++) {
            group[i] = new Coin[3];
        }

        int count = numCoins;
        
            for (int i = 0,z = 0; i < numofGroups; i++) {
                for (int j = 0; j < 3; j++,z++) {
                    if (count == 2) {
                        group[i][j] = coins[z];
                        group[i][++j] = coins[++z];
                        break;
                    }else if (count == 1){
                        group[i][j] = coins[z];
                        break;
                    }
                    group[i][j] = coins[z];
                }
                
                if (count >= 3){
                    count -= 3;
                }
                
            }
            int results = 0;

            int i;

            for ( i = 0; i < numofGroups - 1; i++){
                results = fakeCoin(group[i], 3, fake);
                
                if (results == 1){
                    return results;
                }

            }
            
            if(count == 2){
                group[i][2] = group[i - 1][2];
            }else if (count == 1){
                group[i][1] = group[i - 1][1];
                group[i][2] = group[i - 1][2];
            }
            
        
            results = fakeCoin(group[i], 3, fake);


            // To delete arrays
            for (int i = 0; i < numofGroups; i++) {
                delete[] group[i];
            }
            delete[] group;

            return results;

    }


}

int main(){
    Coin*  a ;
    Coin  b;
    int size;
    int choice;

    std::cout << "Enter Number of Coins: \n";
    std::cin >> size;

    a = new Coin[size];

    for (int i = 0; i < size; i++){
        a[i].id = i;
        a[i].weight = 2;
    }

    std::cout << "Enter Coin Detection Option   : \n";
    std::cout << "1-All Genuine\n";
    std::cout << "2-One Fake\n";
    std::cin >> choice;

    srand(time(0));

    int randIndex = rand() % size;
    int pls = rand() % size;


    if (choice == 1) {
        fakeCoin(a, 4, &b);
    }else{

    }




    fakeCoin(a, 4, &b);

}

