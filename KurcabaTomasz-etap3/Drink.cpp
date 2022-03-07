//
// Created by tomasz on 18.11.2020.
//

#include "Drink.h"

Drink::Drink(float price, const char *name, int ID) : price(price), name(name), ID(ID) {}


std::ostream &operator<<(std::ostream &output,
                         const Drink &Drink) { // a reference as a return value to print e.g. std :: cout << "Hello here:" << Drink;
    output << Drink.ID + 1 << ". " << Drink.name << " Price: " << Drink.price << " PLN.";
    return output;
}



