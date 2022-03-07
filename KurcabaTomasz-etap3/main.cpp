#include "Drink.h"
#include "machine.h"
#include "menu.h"
#include <fstream>


int main(int argc, char *argv[]) {
    try {
        std::ifstream *input; //input
        if (argc > 1)
            input = new std::ifstream(argv[1]); // file name specified, open
        else
            input = (std::ifstream *) &std::cin; // input set to standard input when no file is present



        machine *Machine = machine::InitMachine(true, true, true);
        int choice;

        while ((choice = Displaying(Machine, input))) {
            Drink *chosen_drink = DrinkChoice(machine::CallMachine(),
                                              choice); // another way to operate on an object that is a Singleton
            if (!NoDrink(Machine, *chosen_drink, input))
                continue;// the drink is over but user wants to continue shopping
            MakePayment(Machine, *chosen_drink, input);

        }
    }
    catch (std::bad_alloc &) {
        std::cout << "Out of memory, close unnecessary programs and try a second time."<< std::endl;
        return 1;
    }
    catch (Errors &b) {
        b.Error(); // for any errors not caught by the previous catch
    }

    machine::DeleteMachine();// clean up and free memory
    return 0;
}

