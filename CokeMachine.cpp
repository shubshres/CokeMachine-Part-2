#include "CokeMachine.h"

void CreateCokeOutputLine(std::ostream& CokeOutputFile, const CokeMachine& MyCokeMachine)
{
    //writing machine name
    CokeOutputFile << MyCokeMachine.machineName << "|"; 

    //writing cost
    CokeOutputFile << MyCokeMachine.CokePrice << "|";

    //writing change level
    CokeOutputFile << MyCokeMachine.changeLevel << "|";

    //writing inventory
    CokeOutputFile << MyCokeMachine.inventoryLevel << "\n";
}

std::ostream& operator<<(std::ostream &output, const CokeMachine &MyCokeMachine)
{
    //Machine Name
    output << "\n\nMachine Name: ";
    output << MyCokeMachine.machineName << std::endl;

    //Checking current Inventory Level
    output << "\nCurrent Inventory Level: ";
    output << MyCokeMachine.inventoryLevel << std::endl;

    //Checking Max Inventory Capacity
    output << "\nMax Inventory Capacity: ";
    output << MyCokeMachine.maxInventoryCapacity << std::endl;

    //Checking Current Change Level
    output << "\n\nCurrent Change Level: ";
    output << MyCokeMachine.getChangeLevel() << std::endl;

    //Checking Max Change Capacity
    output << "\nMax Change Capacity: ";
    output << MyCokeMachine.getMaxChangeCapacity() << std::endl;

    //Checking Current Coke Price
    output << "\n\nCurrent Coke Price: ";
    output << MyCokeMachine.getCokePrice() << "\n\n" << std::endl;

    return output;
}

CokeMachine::CokeMachine(std::string name, int cost, int change, int inventory)
{
    //setting machine name
    machineName = name;

    //setting the price of the coke
    CokePrice = cost;

    //setting teh change level
    changeLevel = change;

    //setting the inventory level of the machine
    inventoryLevel = inventory;
}

CokeMachine::~CokeMachine()
{
    std::cout << "Coke Machine " << machineName << " has been destroyed" << std::endl; 
}

std::string CokeMachine::getMachineName()
{
    return machineName;
}

bool CokeMachine::buyACoke(int payment, std::string &change, int &action)
{
    //initializing local boolean
    bool passFail;
    //checking inventory level
    if (inventoryLevel <= 0)
    {
        passFail = false;
        action = ACTION::NOINVENTORY;
    }
    else
    {
        if (payment == CokePrice) //checking to see if exact change was used
        {
            passFail = true;
            inventoryLevel--;
            changeLevel += CokePrice;
            action = ACTION::EXACTCHANGE;
        }
        else if (payment > CokePrice) //if payment is greater than price
        {
            if (changeLevel >= maxChangeCapacity)
            {
                action = ACTION::BOXFULL;
            }
            else if (changeLevel >= (payment - CokePrice)) // checking if we have enough change to give back
            {
                passFail = true;
                action = ACTION::OK;
                inventoryLevel--;
                changeLevel += CokePrice;
                change = displayMoney(payment - CokePrice);
            }
            else
            {
                action = ACTION::NOCHANGE;
                passFail = false;
            }
        }
        else if (payment < CokePrice) //checking if there is insufficient funds
        {
            action = ACTION::INSUFFICIENTFUNDS;
            passFail = false;
        }
    }

    return passFail;
}

int CokeMachine::getInventoryLevel()
{
    return inventoryLevel;
}

int CokeMachine::getMaxInventoryCapacity()
{
    return maxInventoryCapacity;
}

bool CokeMachine::incrementInventory(int amountToAdd)
{
    int newAmount = inventoryLevel + amountToAdd;
    bool result;

    if (newAmount > maxInventoryCapacity)
    {
        result = false;
    }
    else if (amountToAdd < 0)
    {
        result = false;
    }
    else
    {
        result = true;

        inventoryLevel = newAmount;
    }

    return result;
}

std::string CokeMachine::getChangeLevel() const
{
    return displayMoney(changeLevel);
}

bool CokeMachine::incrementChangeLevel(int amountToAdd)
{
    int newChangelevel = changeLevel + amountToAdd;
    bool result;

    if (newChangelevel > maxChangeCapacity)
    {
        result = false;
    }
    else if (amountToAdd < 0)
    {
        result = false;
    }
    else
    {
        result = true;

        changeLevel = newChangelevel;
    }

    return result;
}

std::string CokeMachine::getMaxChangeCapacity() const
{
    return displayMoney(maxChangeCapacity);
}

std::string CokeMachine::getCokePrice() const
{
    return displayMoney(CokePrice);
}

std::string CokeMachine::displayMoney(int amount) const
{
    std::string dollars{std::to_string(amount / 100)};
    std::string cents{std::to_string(abs(amount % 100))};

    std::string price{"$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents};

    return price;
}

void CokeMachine::setMachineName(std::string newMachineName)
{
    machineName = newMachineName; 
}

void CokeMachine::setCokePrice(int newCokePrice)
{
    CokePrice = newCokePrice; 
}