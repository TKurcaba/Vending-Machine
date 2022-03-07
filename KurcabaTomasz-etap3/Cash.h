//
// Created by tomasz on 13.12.2020.
//

#ifndef KURCABATOMASZ_ETAP3_CASH_H
#define KURCABATOMASZ_ETAP3_CASH_H

#include "Payment.h"
#include "Errors.h"

//class CashErrors;
class Cash : public Payment {
private:
    void ResetPaid() { paid = 0; }

    float paid = 0;

    void Instruction();

    void CheckCorrectOfCoins(int coin);

public:
    Cash() {
        name = "Cash";
    }

    bool Pay(float price, std::ifstream *input) override;  // virtual function for handling paymentsę
    float ReturnPaid() const { return paid; }

    void InsertCoin(int coin, float price);

    bool CheckingIfPaid(float price);

    void InterruptPaying() { ResetPaid(); }
    //friend class CashErrors;
};


#endif //KURCABATOMASZ_ETAP3_CASH_H
