//
// Created by tomasz on 09.12.2020.
//
#include <fstream>
#include "Payment.h"
#include "Errors.h"
// practically redefinition of read_int but I needed a function that returns strings so that the PIN type 0123 was correct
// we could use this function in the menu and do atoi (return value) but left it that way for readability and distinction
// where I return int and where string

std::string ReadString(std::ifstream *input) {
    std::string line;

    bool sign;
    do {
        std::getline(*input, line);
        if (line.empty()) { // when the user types "Enter"
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

    return line;
}


//************************************PAYMENT******************************************************************
int Payment::char_numbers(const std::string& code) const {  // the number of characters in the code to be typed
    return code.length();
}

//****************************************BLIK****************************************************************
bool Blik::Pay(float price, std::ifstream *input) {
    nervous_level = 0;
    std::cout << "You have chosen to pay by blik. The price you have to pay is:" << price
              << " PLN. You must enter the 6-digit BLIK code:" << std::endl;

       std::string code;
       do{
           try {
               code = ReadString(input);
               if(char_numbers(code) == 6 )
                   return true;
               else {


                   if (++nervous_level == when_stop)
                       throw PaymentErrors("Blik");


                   std::cout << "The Blik code consists of 6 digits. Please enter the correct one !!!" << std::endl;
               }

           }
           catch(DisplayErrors& b)
           {
               b.Error();
           }
       } while( true );


   // return true;
}


//*************************************CART*********************************************************************
bool Cart::Pay(float price, std::ifstream *input) {
    nervous_level = 0;
    std::cout << "You have chosen to pay by bank card. The price you need to pay is:" << price
              << "PLN. Insert the card and enter the 4-digit PIN:" << std::endl;
    std::string code;
    do {
        try {
            code = ReadString(input);
            if (char_numbers(code) == 4)
                return true;
            else {

                if (++nervous_level == when_stop)
                    throw PaymentErrors("Cart");

                std::cout << "The PIN code consists of 4 digits. Please enter the correct one !!!" << std::endl;
            }
        }

    catch(DisplayErrors & b)
    {
        b.Error();

    }
}while(true);
}

