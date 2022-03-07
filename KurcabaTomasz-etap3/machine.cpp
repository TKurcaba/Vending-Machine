//
// Created by tomasz on 18.11.2020.
//

#include <iostream>
#include "machine.h"
#include <string>

machine *machine::Machine = nullptr;   // static variable so we need to initialize it

machine::machine(bool G, bool B, bool K)  {

    // three logical variables on the basis of which the payment methods are added to the machine
    if (G) {
        auto cash = new Cart;
        Container_payment.Add(cash);
    }
    if (B) {
        auto blik = new Blik;
        Container_payment.Add(blik);

    }
    if (K) {
        auto cart = new Cart;
        Container_payment.Add(cart);

    }
    FillMachine(5); // fill machine with Drink
    tab_quantity = new int[Container_drinks.Size()];
    for (int i = 0; i < Container_drinks.Size(); i++)
        tab_quantity[i] = initial_quantity;

}

void machine::DisplayDrinks() const {  // print the contents of the machine
    for (int i = 0; i < Container_drinks.Size(); i++)
        Display(*Container_drinks[i]);
}


Drink *machine::SelectDrink(int choice) const {
    return Container_drinks[choice - 1]; // returns the selected Drink (actually a pointer to it)
}


void machine::Display(Drink &Drink) const {
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    std::cout << Drink << " amount: " << tab_quantity[Drink.ID] << std::endl;
}


bool machine::IsAnyDrinks(const Drink &Drink) const {  // checking if the Drink is not over (i.e. if the corresponding position in tab_number is a number other than 0)
    if (tab_quantity[Drink.ID])
        return true;
    return false;
}


machine::~machine() {
    delete[] tab_quantity;
}


machine *machine::InitMachine(bool g, bool b, bool k) {
    if (Machine == nullptr) { // if the machine does not exist, its constructor is called (once for the entire duration of the program)

        Machine = new machine(g, b, k);
        return Machine;
    }
    std::cerr << "Machine already exists" << std::endl;
    return nullptr;
}


bool machine::Payments(int choice, const Drink &Drink, std::ifstream *input) {
    bool t = Container_payment[choice - 1]->Pay(Drink.price, input);  // call the function Pay for the appropriate (selected) payment method
    if (t) {
        tab_quantity[Drink.ID]--;
    }
    return t;
}


void machine::DisplayPaymentMethods() const {
    int j = 1;
   for(int i =0; i < Container_payment.Size(); i++)
       std::cout << j++ << ". " << Container_payment[i]->Name() << std::endl;
}

machine *machine::CallMachine() {
    if(Machine == nullptr){
        std::cerr << "THE MACHINE DOES NOT EXIST";
    }
    return Machine;
}

void machine::DeleteMachine() {
    delete Machine;
}
// The machine object exists for the entire time the program is running and finally, to free allocated memory, I will call this function
// it will call the machine class destructor and deallocate the memory from the vending machine



void machine::FillMachine(int size) {

    auto Napoj1 = new Drink(2, "Cola", 0);
    auto Napoj2 = new Drink(3.70, "Pepsi", 1);
    auto Napoj3 = new Drink(6.10, "Napoj aloesowy", 2);
    auto Napoj4 = new Drink(10, "Cisowianka", 3);
    auto Napoj5 = new Drink(5.20, "Muszynianka", 4);

    Drink *Napoj_tab[] = {Napoj1, Napoj2, Napoj3, Napoj4, Napoj5};
    Container_drinks.Add(Napoj_tab, size);
}

void machine::DeleteCart(int choice ) {

    Container_payment.Delete(choice - 1);
}























// std :: cout << j ++ << "." << ((std :: string) typeid (* i) .name ()). erase (0,1) << std :: endl; // I did this because it was saying 7 Cash, for example. It will work until the Payment derivative class is not
// more than 9 characters long (then I would just create a function that removes all the numbers at the beginning, but at the moment I think the above version is sufficient

