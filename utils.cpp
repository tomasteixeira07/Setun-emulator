#include "utils.h"


void print_trits(const Trit &tri){
    char out = '0';
    if (tri == -1){out = '-';}
    else if (tri == 1){out = '+';}
    std::cout << out;
}


int potencia (const int &potenc, const int &num){
    int total = 1;
    for (int i = 0; i < potenc; i++){
        total *= num;
    }
    return total;
} 


int trit_to_decimal(const Trit array[], const unsigned char &size){
    int soma = 0;
    for(unsigned char i = 0; i < size; i++){
        soma += potencia(i) * array[i];
    }
    return soma;
}


void tri_plus_one(Trit array[], const unsigned char &size){
    unsigned char i = 0;
    while(array[i]==1){
        array[i] = -1;
        i++;
        if (i >= size){std::cout << "ERROR"; i--; break;}
    }
    if(array[i] == -1){array[i] = 0;}
    else{array[i] = 1;}    
}
