//
// Created by tomasz on 18.11.2020.
//

#ifndef KURCABATOMASZ_ETAP3_MENU_H
#define KURCABATOMASZ_ETAP3_MENU_H

#include "Drink.h"
#include "machine.h"



int Displaying(machine *Machine, std::ifstream *input);

Drink *DrinkChoice(machine *Machine, int choice);

int NoDrink(machine *Machine, const Drink &chosen_drink, std::ifstream *input);

void MakePayment(machine *Machine, const Drink &drink, std::ifstream *input);

#endif //KURCABATOMASZ_ETAP3_MENU_H
