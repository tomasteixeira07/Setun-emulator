#ifndef WORD18_H
#define WORD18_H

#include <iostream>
#include "trit.h"
#include "utils.h"

class Word18{
    public:
        //constructors
        Word18();
        Word18(int decimal);
        Word18(const int array[], unsigned char size);
        Word18(const Trit array[], unsigned char size);
        //transformations
        int tri_to_dec() const;
        Word18 operator+(const Word18 &tri) const;
        Word18 operator-(Word18 tri) const;
        Word18 operator*(Word18 tri) const;
        Word18 operator/(const Word18 &tri) const;
        void print_() const;
        Trit getTri(const unsigned char &localization) const;
        void setTrit(const unsigned char &index, const Trit &tri);
        bool operator==(const Word18 &tri) const;
        Trit& operator[](const unsigned char &index);


    private:
        Trit array[18];
};


#endif