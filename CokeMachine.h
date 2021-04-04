//Shubhayu Shrestha 1001724804
#ifndef COKE_MACHINE_H
#define COKE_MACHINE_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

enum ACTION
{
    OK,
    NOINVENTORY,
    NOCHANGE,
    INSUFFICIENTFUNDS,
    EXACTCHANGE,
    BOXFULL
};

class CokeMachine
{
    friend std::ostream& operator<<(std::ostream& output, const CokeMachine& MyCokeMachine); 
    friend void CreateCokeOutputLine(std::ostream& CokeOutputFile, const CokeMachine& MyCokeMachine); 
    public:
        CokeMachine(std::string name = "New Machine", int cost = 50, int change = 500, int inventory = 100);
        ~CokeMachine(); 
        std::string getMachineName();
        bool buyACoke(int payment, std::string &change, int &action);
        int getInventoryLevel();
        int getMaxInventoryCapacity();
        bool incrementInventory(int amountToAdd);
        std::string getChangeLevel()const;
        bool incrementChangeLevel(int amountToAdd);
        std::string getMaxChangeCapacity() const;
        std::string getCokePrice() const;
        std::string displayMoney(int amount) const;
        //Adding the new member functions 
        void setMachineName(std::string newMachineName); 
        void setCokePrice(int newCokePrice); 

    private:
        std::string machineName;
        int changeLevel;
        int maxChangeCapacity{5000};
        int CokePrice;
        int inventoryLevel;
        int maxInventoryCapacity{100};
};

#endif
