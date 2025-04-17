#include <iostream>
#include <conio.h>
#include <windows.h>
#include "../include/number.h"
#include <vector>
#include <cmath>

using namespace std;

Number buyX(Number& resource, Number& gain, Number& cost, double costStep, int amount) {
    Number totalCost = Number();
    for (int i = 0; i < amount; i++) {
        totalCost += cost * pow(costStep, i);
    }

    // Update the cost for the next amount
    cost = cost * pow(costStep, amount - 1);

    //cout << "Cost for " << amount << " items: " << totalCost.printNumber() << endl;
    return totalCost;
}

Number showCostX(Number& resource, Number& gain, Number& cost, Number& costResource, double costStep, int amount) {
    Number totalCost = Number();
    if (amount != 999) {
        for (int i = 0; i < amount; i++) {
            totalCost += cost * pow(costStep, i);
        }
    }
    else {
        int i = 0;
        Number nextTotalCost = Number();
        while (nextTotalCost < costResource) {
            totalCost += cost * pow(costStep, i);
            nextTotalCost = totalCost + cost * pow(costStep, i+1);
            i++;
        }
    }
    //cout << "Cost for " << amount << " items: " << totalCost.printNumber() << endl;
    return totalCost;
}


void handleBuyX(Number& resource, Number& gain, Number& cost, double costStep, vector<int>& buyAmounts, int& currentBuyAmount) {
    int amount = buyAmounts[currentBuyAmount];
    
    if (amount == 999) {
        // MAX: Buy as many as possible with the current balance
        Number totalCost = Number();
        int maxBuy = 0;
        
        while (resource >= totalCost + cost) {
            totalCost += cost;
            maxBuy++;
            cost = cost * costStep;
        }
        
        // Perform the buy
        resource -= totalCost;
        gain += maxBuy;
        cout << "You bought " << maxBuy << " items for " << totalCost.printNumber() << endl;
    } else {
        // Buy the specified amount
        Number totalCost = Number();
        for (int i = 0; i < amount; i++) {
            totalCost += cost * pow(costStep, i);
        }

        if (resource >= totalCost) {
            resource -= totalCost;
            gain += amount;
            cost = cost * pow(costStep, amount - 1);
            cout << "You bought " << amount << " items for " << totalCost.printNumber() << endl;
        } else {
            cout << "Not enough resources to buy " << amount << " items." << endl;
        }
    }
}

int main() {
    // Resources
    Number cash(0, 0);
    Number multi(0, 0);
    Number super(0, 0);
    Number mega(0, 0);

    // Base Gains
    Number baseCashGain(1, 0);
    Number baseMultiGain(1, 0);
    Number baseSuperGain(1, 0);

    // Tick Gains
    Number cashGain(1, 0);
    Number multiGain(1, 0);
    Number superGain(1, 0);
    Number megaGain(0,0);

    // Costs
    Number multiCost(10, 0);
    Number superCost(10, 0);     // Cost in Multiplier
    Number megaCost(10, 0);     // Cost in Super

    // Buy amount options: [1, 5, 10, 25, 999 (MAX)]
    vector<int> buyAmounts = {1, 5, 10, 25, 999};
    int currentBuyAmount = 0; // Default to buying 1 item

    int tickspeed = 250;
    bool gameLoop = true;

    while (gameLoop) {
        // --- Input ---
        if (_kbhit()) {
            char ch = _getch();

            if (ch == '1') { // Buy Multiplier with Cash
                handleBuyX(cash, multi, multiCost, 1.15, buyAmounts, currentBuyAmount);
            } else if (ch == '2') { // Buy Super with Multiplier
                handleBuyX(multi, super, superCost, 1.2, buyAmounts, currentBuyAmount);
            } else if (ch == '3') { // Buy Mega with Super
                handleBuyX(super, mega, megaCost, 1.3, buyAmounts, currentBuyAmount);
            } else if (ch == 'X' || ch == 'x') { // Cycle buy amount
                currentBuyAmount = (currentBuyAmount + 1) % buyAmounts.size();
            } else if (ch == 27) { // ESC key to quit
                gameLoop = false;
            }
        }

        // --- Gains ---
        cashGain = baseCashGain * (multi + 1); // Only cash ticks up
        cash += cashGain;

        // --- Display ---
        system("cls");
        cout << "[1] Buy Multiplier    " << buyAmounts[currentBuyAmount] <<  "x (" << showCostX(multi, multiGain, multiCost, cash, 1.15, buyAmounts[currentBuyAmount]).printNumber() << " Cash)" << endl;
        cout << "[2] Buy Super         " << buyAmounts[currentBuyAmount] <<  "x (" << showCostX(super, superGain, superCost, multi, 1.2, buyAmounts[currentBuyAmount]).printNumber() << " Multi)" << endl;
        cout << "[3] Buy Mega          " << buyAmounts[currentBuyAmount] <<  "x (" << showCostX(mega, megaGain, megaCost, super, 1.3, buyAmounts[currentBuyAmount]).printNumber() << " Super)" << endl;

        cout << "---------------------------------------------" << endl;
        cout << "Cash:       " << cash.printNumber()  << "   (" << cashGain.printNumber()  << " / tick)" << endl;
        cout << "Multiplier: " << multi.printNumber() << endl;
        cout << "Super:      " << super.printNumber() << endl;
        cout << "Mega:       " << mega.printNumber() << endl;
        cout << "---------------------------------------------" << endl;

        cout << "[X] Current Buy Amount: " << buyAmounts[currentBuyAmount] << endl;

        cout << "---------------------------------------------" << endl;
        cout << "[ESC] Quit" << endl;

        Sleep(tickspeed);
    }

    return 0;
}
