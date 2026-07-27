#ifndef UTILS_H
#define UTILS_H


#include "trit.h"
#include "word18.h"
#include <string>
#include <iostream>



void print_trits(const Trit &tri);
int potencia (const int &potenc, const int &num = 3);
int trit_to_decimal(const Trit array[], const unsigned char &size);
void tri_plus_one(Trit array[], const unsigned char &size);
Trit conver_signal_to_trit(const char &signal);
Trit* make_opcode(const std::string opcode, Trit array[]);


#endif