#ifndef WORD_H
#define WORD_H

#include <iostream>
#include "trit.h"
#include "utils.h"


template <unsigned char N>
class Word{
    public:
        //constructors
        Word(){}
        Word(int decimal){
            bool reverse = 0;
            if (decimal < 0){reverse = 1;decimal = - decimal;}
            short resto = 3;
            unsigned char contagem = 0;
            while (decimal != 0 and contagem < N){
        
                resto = decimal % 3;
                decimal = (decimal - resto) / 3;
        
        
                if (resto == 1){array[contagem] = 1;}
                else if (resto == 2){array[contagem] = -1; decimal++;}
                contagem++;
        
            }
                
            if(reverse){
                for (unsigned char i = 0; i < N; i++){
                    array[i] = - array[i];
                }
            }
        }
        Word(const int array[], unsigned char size){
            for (unsigned char i = 0; i < size; i++){
                this->array[i] = array[i]; 
            }
        }
        Word(const Trit array[], unsigned char size){
            for (unsigned char i = 0; i < size; i++){
                this->array[i] = array[i];
            }
        }
        
        //transformations
        int tri_to_dec() const{
            int soma = 0;
            for(unsigned char i = 0; i < N; i++){
                soma += potencia(i) * array[i];
            }
            return soma;
        }
        Word operator+(const Word &tri) const{
            int array2 [N];
            Trit carry = 0;
            Trit left, right;
            for (unsigned char i = 0; i < N; i++){
                array2[i] = carry;
                left = getTri(i);
                right = tri.getTri(i);
                if (left == right){
                    if (left == 0){
                        carry = 0;
                        array2[i] += 0;
                    }
                    else{
                        carry = getTri(i);
                        array2[i] -= array[i];
                    }
                }
                else{
                    carry = 0;
                    if (left == -right){}
                    else if (left > 0 or right >0){array2[i] += 1;}
                    else{array2[i] -= 1;}
                }
            }
            return Word(array2, N);
        }
        Word operator-(Word tri) const{
            for (unsigned char i = 0; i < N; i++){
                tri[i] = - tri[i];
            }
            return *this + tri;
        }
        Word operator*(Word tri) const{
            return Word(tri.tri_to_dec() * tri_to_dec());
        }
        Word operator/(const Word &tri) const{
            return Word(this->tri_to_dec() / tri.tri_to_dec());
        }
        void print_() const{
            std::cout << tri_to_dec() << '\n';
        }
        Trit getTri(const unsigned char &localization) const{
            return array[localization];
        }
        void setTrit(const unsigned char &index, const Trit &tri){
            array[index] = tri;
        }
        bool operator==(const Word &tri) const{
            for (unsigned char i = 0; i < N; i++){
                if (getTri(i) != tri.getTri(i)){return false;}
            }
            return true;
        }
        Trit& operator[](const unsigned char &index){
            return array[index];
        }


    private:
        Trit array[N]{};
};


using Word9 = Word<9>;
using Word18 = Word<18>;

#endif