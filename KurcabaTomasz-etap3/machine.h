//
// Created by tomasz on 18.11.2020.
//

#ifndef KURCABATOMASZ_ETAP3_MACHINE_H
#define KURCABATOMASZ_ETAP3_MACHINE_H

#include "Drink.h"
#include "Payment.h"
#include "Cash.h"
#include <vector>
#include "Container.h"

class machine {
private:

    machine(bool G, bool B, bool K);

    ~machine();


    const int initial_quantity = 3;  // number of drinks
    int *tab_quantity; // showing how many drinks are left
    void Display(Drink& Drink) const;


    Container<Drink *> Container_drinks;
    Container<Payment *>Container_payment;
    void FillMachine(int size);

public:

    void DeleteCart(int choice );

    static machine *Machine;

    static machine *CallMachine();

    void DisplayPaymentMethods() const;

    int AmountOfPayments() const { return Container_payment.Size(); }

    bool Payments(int choice, const Drink &Drink, std::ifstream *input);

    static machine *InitMachine(bool g = true, bool b = true,
                                bool k = true);  // static function creating a machine (it is a singleton)

    int MachineSize() const { return Container_drinks.Size(); }

    bool IsAnyDrinks(const Drink &Drink) const;

    void DisplayDrinks() const;

    Drink *SelectDrink(int choice) const;

    static void DeleteMachine();

};


#endif //KURCABATOMASZ_ETAP3_MACHINE_H
