//
// Created by tomasz on 13.12.2020.
//

#include "Cash.h"
#include <string>
#include <fstream>
#include "Errors.h"


bool Cash::Pay(float price, std::ifstream *input) {
    nervous_level = 0;
    std::cout << "You have chosen to pay in cash. The price you need to pay is: " << price << " PLN. Reminder: "
              << std::endl;
    Instruction();
    int choice;
    do {
        try {
            if (nervous_level ==
                when_stop) {   // an option that allows you to interrupt the payment after x errors (e.g. it turns out that the user has only coins that do not match the machine)
                std::cout << std::endl
                          << "You made a mistake many times, do you want to stop paying? If so, enter 0 and we will refund your money."
                          << std::endl;
                nervous_level = 0;
                choice = atoi(ReadString(input).c_str());  // 0 the payment is completed
                if (!choice) {
                    InterruptPaying();
                    throw PaymentErrors("Cash"); // throwing an exception related to a payment Error that will be caught in the function where the payment is made
                }
            }
            std::cout << "Enter the denomination you want to use:" << std::endl;
            choice = atoi(ReadString(input).c_str());
            CheckCorrectOfCoins(choice);
            InsertCoin(choice, price);
            if (fabs(price - ReturnPaid()) >
                0.00001f)  // because with more actions, floats for 0.10-0.10 did not give 0
                std::cout << std::endl << "Left to pay: " << price - ReturnPaid() << " PLN" << std::endl;
        }
        catch (CashErrors &b) {
            b.Error(); // catching typing exceptions
            if (++nervous_level != when_stop)
                Instruction();

        }
    } while (!CheckingIfPaid(price));

    return true;
}

void Cash::Instruction() {  // denominations accepted by the machine
    std::cout << "Reminder  :" << std::endl << "Denominations accepted by the machine\n"
                                                  "10gr - type 10\n"
                                                  "20gr - type 20\n"
                                                  "50gr - type 50\n"
                                                  "1PLN  - type 1\n"
                                                  "2PLN  - type 2\n"
                                                  "5PLN  - type 5\n";

}

void Cash::InsertCoin(int coin, float price) {  //accepting the coin and adding it to the price already paid
    float temp;
    if (coin >= 10)
        temp = (float) coin / 100;  // for 10/20/50 to get 0.10 / 0.20 / 0.50
    else
        temp = (float) coin;

    if (fabs(temp - price + paid) < 0.00001f) {
        paid += temp;
        return;
    }
    if (temp > (price - paid)) {
        throw CashErrors();
    }
    paid += temp;

}

bool Cash::CheckingIfPaid(float price) {
    if (fabs(paid - price) < 0.00001f) {
        ResetPaid();  // for later transactions
        return true;
    }
    return false;
}

void Cash::CheckCorrectOfCoins(const int coin) {
    if (coin == 10 || coin == 20 || coin == 50 || coin == 1 || coin == 2 || coin == 5)
        return;

    throw CashErrors("Unknown denomination");
}

