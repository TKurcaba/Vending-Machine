//
// Created by tomasz on 04.01.2021.
//

#include "Errors.h"

void DisplayErrors::Error() {
    if (message.empty())
        std::cout << "\033[31m" << "Our machine only supports numbers!" << "\033[0m"
                  << std::endl;
    else if (message == "Range")
        std::cout << "\033[31m" << "You entered a number out of range!" << "\033[0m"
                  << std::endl;
    else
        std::cout << "\033[31m" << "Our machine does not support\"" << message << "\". You must enter a number: "
                  << "\033[0m"
                  << std::endl;
}


void PaymentErrors::Error() {
    if (message == "Blik")
        std::cout << "It looks like you don't have an account with Blik. We have to stop the payment." << std::endl;
    else {
        if (message == "Cart") {
            std::cout
                    << "You made a mistake in entering your PIN too many times, the card payment option will be blocked unless you have a second one. If yes, enter 1, if not, enter 2!"
                    << std::endl;
        } else
            std::cout << "The money has been returned to you!" << std::endl;
    }
}


void CashErrors::Error() {
    if (message == "Unknown denomination")
        std::cout << "You must enter a denomination acceptable to the machine." << std::endl;
    else
        std::cout << "You must enter denominations less than the amount remaining to be paid." << std::endl;
}


void ContainerErrors::Error() {
    std::cout << "\033[31m" << "Container Range Exceeded!" << "\033[0m" << std::endl;

}
