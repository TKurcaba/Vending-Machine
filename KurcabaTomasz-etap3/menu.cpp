//
// Created by tomasz on 18.11.2020.
//

#include "menu.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Errors.h"

#define BELT "***************************************************************************"

int ReadInt(std::ifstream *input);

bool Range(int number, int start, int end);

int Displaying(machine *Machine, std::ifstream *input) {
    std::cout << BELT << std::endl << std::endl;
    std::cout << "Welcome to our slot machine. Here is our offer:" << std::endl;

    Machine->DisplayDrinks();

    std::cout << std::endl
              << "If you are not interested in further purchases, enter 0. This will turn off the machine. However, if you want to choose a drink, enter its number:"
              << std::endl;
    int end;
    do {
        try {
            end = ReadInt(input);
            if (Range(end, 0, Machine->MachineSize()))
                break;
        }
        catch (DisplayErrors &b) {
            b.Error();  // errors like entering or letters are caught here
        }

    } while (true);

    std::cout << std::endl << BELT << std::endl << std::endl;
    return end;
}


Drink *DrinkChoice(machine *Machine, int choice) {
    return Machine->SelectDrink(choice); // the selected Drink is returned
}


int NoDrink(machine *Machine, const Drink &chosen_drink, std::ifstream *input) {
    if (!Machine->IsAnyDrinks(chosen_drink)) {
        std::cout << "The selected drink is over :(, choose another or finish " << std::endl;

        int choice;
        do {
            std::cout << std::endl << "---****** CHOOSE ******---"<< std::endl;
            std::cout << "1: Finish shopping" << std::endl;
            std::cout << "2. Continue shopping"<< std::endl << std::endl;
            try {
                choice = ReadInt(input);
                if (Range(choice, 1, 2)) {
                    if (choice == 2)
                        return 0;
                    else {
                        machine::DeleteMachine();
                        exit(0);
                    }
                }
            }
            catch (DisplayErrors &b) {
                b.Error();
            }

        } while (true);
    }
    return 1;
}

void MakePayment(machine *Machine, const Drink &drink, std::ifstream *input) {
    int choice;
    try {
        std::cout << "Choose the method you want to pay by:" << std::endl;
        Machine->DisplayPaymentMethods();
        std::cout << std::endl << BELT << std::endl << std::endl;

        do {
            try {
                choice = ReadInt(input);
                if (Range(choice, 1, Machine->AmountOfPayments()))
                    break;
            }
            catch (DisplayErrors &b) {
                b.Error();
            }
        } while (true);

        if (Machine->Payments(choice, drink, input))
            std::cout << std::endl << "You paid the whole thing!" << std::endl << std::endl;
    }
    catch (PaymentErrors &b) {
        b.Error();
        if (b.message == "Cart") {
            // if there is an error in card payment, we block the card payment option in order to reflect reality as much as possible
            // which is to symbolize the blocking of the card after a sufficiently large number of mistakes in the PIN, the following while I handle this situation
            // additionally there is a possibility that the user has two cards (or more), therefore he is asked about it

            do {
                try {
                    int choice_2 = ReadInt(input);
                    if (Range(choice_2, 1, 2)) {
                        if (choice_2 == 2) {
                            Machine->DeleteCart(choice);
                            return;
                        } else
                            return;
                    }
                }
                catch (Errors &b) {
                    b.Error();
                }

            } while (true);

        }

    }
}


int ReadInt(std::ifstream *input) {
    std::string line;

    bool sign;
    do {
        std::getline(*input, line);
        if (line.empty()) { // when user types "Enter"
            throw DisplayErrors("Enter");
        }
        sign = false;
        for (char i : line)
            if (!isdigit(i)) {
                sign = true;
                break;
            }

        if (sign)
            throw DisplayErrors();
        else
            break;

    } while (true);

    return atoi(line.c_str());
}


bool Range(int number, int start, int end) { // the Range of the given number was checked many times, therefore this function was created, which additionally throws exceptions in case of exceeding the range
    if (number >= start && number <= end)
        return true;
    throw DisplayErrors("Range");
}
