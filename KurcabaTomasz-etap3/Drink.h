//
// Created by tomasz on 18.11.2020.
//

#ifndef KURCABATOMASZ_ETAP3_DRINK_H
#define KURCABATOMASZ_ETAP3_DRINK_H

#include <iostream>


class Drink {
public:
    Drink(float price, const char *name, int ID);

private:
    const int ID;
    const char *name;
    const float price;
    friend std::ostream &operator<<(std::ostream &output, const Drink &Drink);
    friend class machine;

};


#endif //KURCABATOMASZ_ETAP3_DRINK_H
