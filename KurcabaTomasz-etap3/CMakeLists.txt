cmake_minimum_required(VERSION 3.17)
project(KurcabaTomasz-etap3)

set(CMAKE_CXX_STANDARD 14)

add_executable(KurcabaTomasz-etap3 main.cpp machine.cpp machine.h Drink.cpp Drink.h menu.cpp menu.h Payment.cpp Payment.h Cash.cpp Cash.h Errors.cpp Errors.h Container.cpp Container.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/stdin1.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/stdin2.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})