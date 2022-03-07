//
// Created by tomasz on 04.01.2021.
//

#ifndef KURCABATOMASZ_ETAP3_ERRORS_H
#define KURCABATOMASZ_ETAP3_ERRORS_H

#include <iostream>

struct Errors {
    std::string message;
    explicit Errors(std:: string a) : message(std::move(a)){}
    virtual void Error() {
        std::cout << "\033[31m" <<"Unidentified Error"<< "\033[0m"<< std::endl;
    };
};

struct PaymentErrors : Errors {
    explicit PaymentErrors(std::string a) : Errors(std::move(a)) {}
    void Error() override;

};

struct DisplayErrors : Errors {
    explicit DisplayErrors(std::string a="") : Errors(std::move(a)) {
    }
    void Error() override;

};
struct CashErrors : PaymentErrors {
    explicit CashErrors(std::string a=""): PaymentErrors(std::move(a)){}
    void Error() override;
};
struct ContainerErrors : Errors {
    explicit ContainerErrors(std::string a="") : Errors(std::move(a)) {}
    void Error() override;
};
#endif //KURCABATOMASZ_ETAP3_ERRORS_H
