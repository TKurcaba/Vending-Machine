//
// Created by tomasz on 09.12.2020.
//

#ifndef KURCABATOMASZ_ETAP3_PAYMENT_H
#define KURCABATOMASZ_ETAP3_PAYMENT_H

#include <iostream>
#include <cmath>

constexpr int when_stop = 4;


std::string ReadString(std::ifstream *input); // function that reads user choices

class Payment {
public:
    virtual bool Pay(float price, std::ifstream *input) = 0; // two virtual functions of which Pay is purely virtual, so the class is abstract (you cannot create an object of this class)
    virtual const char *Name() const { return name; }
    virtual ~Payment() =default;
protected:
    const char *name = "Brak metody platnosci ";

    int char_numbers(const std::string& code) const;

    int nervous_level{0};
};


class Blik : public Payment {
    bool Pay(float price, std::ifstream *input) override;

public:
    Blik() {
        name = "Blik";
    }
};


class Cart : public Payment {
    bool Pay(float price, std::ifstream *input) override;

public:
    Cart() {
        name = "Cart";
    }
};



// I have dedicated a separate module to the Cash class to keep it transparent

#endif //KURCABATOMASZ_ETAP3_PAYMENT_H
