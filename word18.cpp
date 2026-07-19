#include "word18.h"


Word18::Word18(){
    for(unsigned char i = 0; i < 18; i++){array[i]=0;}
}


Word18::Word18(int decimal){
    bool reverse = 0;
    if (decimal < 0){reverse = 1;decimal = - decimal;}
    short resto = 3;
    unsigned char contagem = 0;
    while (decimal != 0){

        resto = decimal % 3;
        decimal = (decimal - resto) / 3;


        if (resto == 1){array[contagem] = 1;}
        else if (resto == 2){array[contagem] = -1; decimal++;}
        contagem++;

    }
        
    if(reverse){
        for (unsigned char i = 0; i < 18; i++){
            array[i] = - array[i];
        }
    }
}


Word18::Word18(const Trit array[], unsigned char size){
    unsigned char count;
    for (unsigned char i = 0; i < size; i++){
        this->array[i] = array[i];
        count = i;
    }
    for (unsigned char i = count; i < 18; i++){
        this->array[i] = 0;
    }
}



int Word18::tri_to_dec() const{
    int soma = 0;
    for(unsigned char i = 0; i < 18; i++){
        soma += potencia(i) * array[i];
    }
    return soma;
}



void Word18::print_() const{
    std::cout << tri_to_dec() << '\n';
}


Word18::Word18(const int array[], unsigned char size){
    for (unsigned char i = 0; i < size; i++){
        this->array[i] = array[i]; 
    }
}


Trit Word18::getTri(const unsigned char &localization) const{
    return array[localization];
}

Word18 Word18::operator+(const Word18 &tri) const{
    int array2 [18];
    Trit carry = 0;
    Trit left, right;
    for (unsigned char i = 0; i < 18; i++){
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
    return Word18(array2, 18);
}


Trit& Word18::operator[](const unsigned char &index){
    return array[index];
}


Word18 Word18::operator-(Word18 tri) const{
    for (unsigned char i = 0; i < 18; i++){
        tri[i] = - tri[i];
    }
    return *this + tri;
}


Word18 Word18::operator*(Word18 tri) const{
    Trit left, right;
    for (unsigned char i = 0; i < 18; i++){
        left = getTri(i);
        right = tri.getTri(i);
        if (left == 0 or right == 0){tri[i] = 0;}
        else if (right == left){}
        else{tri[i] = - tri[i];}
    }
    return tri;
}


Word18 Word18::operator/(const Word18 &tri) const{
    return Word18(this->tri_to_dec() / tri.tri_to_dec());
}


void Word18::setTrit(const unsigned char &index, const Trit &tri){
    array[index] = tri;
}


bool Word18::operator==(const Word18 &tri) const{
    for (unsigned char i = 0; i < 18; i++){
        if (getTri(i) != tri.getTri(i)){return false;}
    }
    return true;
}

