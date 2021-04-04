//Shubhayu Shrestha 1001724804
//Coding Assignment 4: Part 2 of Building a Coke Machine
/*Create a class called CokeMachine and a Code3_xxxxxxxxxx.cpp 
    program to instantiate your own CokeMachine and exercise its functionality */
#include "CokeMachine.h"
#include "CokeLib.h"

using namespace std;

//function that prints out menu and takes in user choice
void printMenu(int &menuChoice)
{
    //asking user for input
    cout << "\nPlease choose from the following options\n" << endl;

    //Printing out options to user
    cout << "0. Walk Away" << endl;
    cout << "1. Buy a Coke" << endl;
    cout << "2. Restock Machine" << endl;
    cout << "3. Add change" << endl;
    cout << "4. Display Machine Info" << endl;
    cout << "5. Set Machine Name" << endl; 
    cout << "6. Set Coke Price\n" << endl; 

    cout << "Choice: ";

    //utilizing if statement utilizing ors and fail flags for error handling user input
    cin >> menuChoice;

    //checking if input is a letter, and if it is, ask user to reenter
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "\ninput must be numeric, please reenter ";
        cin >> menuChoice;
    }
}

void getMachineChoice(int &machineChoice, vector<CokeMachine> SetOfCokeMachines)
{
    cout << "Pick a Coke Machine\n" << endl; 
    cout << "0. Exit" << endl; 
    //for loop that prints out machine options
    for(int i = 1; i <= SetOfCokeMachines.size(); i++)
    {
        cout << i << ". " << SetOfCokeMachines.at(i-1).getMachineName() << endl;  
    }
    cout << SetOfCokeMachines.size()+1 << ". Add New Machine\n" << endl; 

    cout << "Enter Machine Choice: ";
    cin >> machineChoice; 

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "\ninput must be numeric, please reenter ";
        cin >> machineChoice;
    }
   
    while(machineChoice > SetOfCokeMachines.size()+1 || machineChoice < 0)
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "\ninput must be in range, please reenter ";
        cin >> machineChoice;
    }
    
    if ((machineChoice > 0 && machineChoice < SetOfCokeMachines.size()+1))
    {
        cout << "You chose machine " << SetOfCokeMachines[machineChoice-1].getMachineName() << endl; 
    }
 }

//create coke output line

int main(int argc, char *argv[])
{
    //declaring variables
    int menuChoice{};
    bool runSwitch = true;
    int inventory;
    int payment;
    string change;
    int action;
    int inputStock;
    bool inputStockBool;
    int inputChange;
    bool inputChangeBool;
    bool ableToBuy;
    int newCokePrice; 
    string newMachineName; 

    CokeMachine MyCokeMachine{};

    vector<CokeMachine> SetOfCokeMachines{};
    string CokeMachineLine; 
    vector<string> ConstructorValues(4);  
    string InputFileName; 
    string OutputFileName; 
    CokeMachine tempCokeMachine; 

    int LineCounter = 0; 

    try
    {
        get_command_line_params(argc, argv, InputFileName, OutputFileName);
    }
    catch(const invalid_argument& ex)
    {
        cerr << ex.what() << endl;
    }

    cout << InputFileName << endl; 
    cout << OutputFileName << endl; 

    ifstream CokeInputFile{InputFileName};
    ofstream CokeOutputFile{OutputFileName};

    if (CokeInputFile.is_open()) 
    {
        while(getline(CokeInputFile, CokeMachineLine))
        {
            if (ParseCokeLine(CokeMachineLine, ConstructorValues))
            {
                CokeMachine tempCokeMachine{ConstructorValues[0], stoi(ConstructorValues[1]), stoi(ConstructorValues[2]), stoi(ConstructorValues[3])}; 
                SetOfCokeMachines.push_back(tempCokeMachine); 
            }
        }
    }
    else
    {
        cout << "The file did not open "<< endl; 
        exit(1); 
    }

    
    int machineChoice = 1; 
    bool machinePickExit = false; 
    CokeMachine newMachine{}; 
    string outputLine{}; 
    //print coke machine menu
    do
    {
        machineChoice = 1; 
        getMachineChoice(machineChoice, SetOfCokeMachines);

        runSwitch = true;
        if(machineChoice==0)
        {
            machinePickExit = true;
            //write to output file
            if (CokeOutputFile.is_open())
            {
                for (int i = 0; i < SetOfCokeMachines.size(); i++)
                {
                    CreateCokeOutputLine(CokeOutputFile, SetOfCokeMachines.at(i)); 
                }
            }
            else
            {
                cout << "\nThe file did not open\n" << endl; 
            }
            
        }
        else if (machineChoice == SetOfCokeMachines.size() + 1)
        {
            SetOfCokeMachines.push_back(newMachine); 
            cout << "\nNew Machine Added\n" << endl; 
        }
        else
        {
            do
            {
                //printing menu
                printMenu(menuChoice);
                //creating switch statement to follow allong with menu choice
                //switch statement with user menu choice
                switch (menuChoice)
                {
                case 0: // walk away
                {
                    //cout << "Thank you. Have a good day!" << endl;
                    runSwitch = false;

                    //write state to new file

                    break;
                }
                case 1: //purchase coke
                {
                    cout << "Insert payment for 1 coke (in cents): ";
                    cin >> payment;

                    while (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(100, '\n');
                        cout << "\ninput must be numeric, please reenter ";
                        cin >> payment;
                    }

                    ableToBuy = SetOfCokeMachines[machineChoice - 1].buyACoke(payment, change, action);

                    if (ableToBuy)
                    {
                        if (action == ACTION::EXACTCHANGE)
                        {
                            cout << "\nThank you for providing the exact change!\n" << endl;
                            cout << "Here is your coke!\n\n\n" << endl;
                        }
                        else if (action == ACTION::OK)
                        {
                            cout << "\nHere is your Coke and your change of " << change << endl;
                        }
                        else
                        {
                            cout << "\nunknown error occured" << endl; 
                        }
                    }
                    else
                    {
                        if (action == ACTION::NOCHANGE)
                        {
                            cout << "\nUnable to give change at this time... returning your payment\n" << endl;
                        }
                        else if (action == ACTION::NOINVENTORY)
                        {
                            cout << "\nThis machine is now out of product...\n" << endl;
                        }
                        else if (action == ACTION::INSUFFICIENTFUNDS)
                        {
                            cout << "\nInsufficiant payment... returning your payment\n" << endl;
                        }
                        else if (action == ACTION::BOXFULL)
                        {
                            cout << "\nChange box is full - call 1800IMFULL to get change removed... \n" << endl;
                        }
                        else
                        {
                            cout << "\nunknown error occured\n" << endl;
                        }
                    }

                    break;
                }
                case 2: //restock inventory
                {
                    cout << "Enter how much product you are adding to the machine: ";
                    cin >> inputStock;

                    while (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(100, '\n');
                        cout << "\ninput must be numeric, please reenter ";
                        cin >> inputStock;
                    }

                    inputStockBool = SetOfCokeMachines[machineChoice - 1].incrementInventory(inputStock);

                    if (inputStockBool == true)
                    {
                        cout << "\n\nYour machine has been restocked.\n"
                             << endl;

                        cout << "\nYour inventory level is now " << SetOfCokeMachines[machineChoice - 1].getInventoryLevel() << endl;
                    }
                    else
                    {
                        cout << "\n\nYou have exceeded your machine's max capacity\n" << endl;

                        cout << "\nYour inventory level is now " << SetOfCokeMachines[machineChoice - 1].getInventoryLevel() << endl;
                    }

                    break;
                }
                case 3: //add change
                {
                    cout << "Enter how much change you are adding to the machine: ";
                    cin >> inputChange;

                    while (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(100, '\n');
                        cout << "\ninput must be numeric, please reenter ";
                        cin >> inputChange;
                    }

                    inputChangeBool = SetOfCokeMachines[machineChoice - 1].incrementChangeLevel(inputChange);

                    if (inputChangeBool == true)
                    {
                        cout << "\n\nYour change has been refilled.\n" << endl;

                        cout << "\nYour change level is now " << SetOfCokeMachines[machineChoice - 1].getChangeLevel() << endl;
                    }
                    else
                    {
                        cout << "\n\nYou have exceeded your machine's max change capacity\n" << endl;

                        cout << "\nYour change level is now " << SetOfCokeMachines[machineChoice - 1].getChangeLevel() << endl;
                    }

                    break;
                }
                case 4: //display machine info
                {
                    cout << SetOfCokeMachines.at(machineChoice - 1);
                    break;
                }
                case 5: //Set machine name
                {
                    cout << "\n\nNew Machine Name: " << endl;
                    cin.ignore(); 
                    getline(cin, newMachineName);
                    SetOfCokeMachines[machineChoice - 1].setMachineName(newMachineName);
                    break;
                }
                case 6: //set coke price
                {
                    cout << "\n\nNew Coke Price: " << endl;
                    cin >> newCokePrice;
                    SetOfCokeMachines.at(machineChoice - 1).setCokePrice(newCokePrice);
                    break;
                }
                default:
                    cout << "\nInvalid menu choice. Please choose again." << endl;
                }
            } 
            while (runSwitch == true);
        }
    } 
    while (machinePickExit == false);
    
    cout << "\n\nThank you! Have a nice day!\n" << endl; 

    CokeInputFile.close();
    CokeOutputFile.close();
    return 0;
}
