#include "cpu.h"


void print_reg_size(const Trit array[], const unsigned char &size = 5){
    for (unsigned char i = 0; i < size; i++){
        print_trits(array[i]);
            std::cout << ' ';
    }
    std::cout << '\n';
}


void CPU::print_registers(const char &reg) const{
    if (reg == 'S'){register_S.print_();}
    else if (reg == 'R'){register_R.print_();}
    else if (reg == 'C'){print_reg_size(register_C);}
    else if (reg == 'F'){print_reg_size(register_F);}
    else if (reg == 'W'){print_trits(omega);}
    else if (reg == 'A'){print_reg_size(operand_address, 5);}
    else if (reg == 'O'){print_reg_size(opcode, 3);}
    else if (reg == 'I'){std::cout << program_size;}
    else if (reg == 'M'){
        for (unsigned char i = 0; i < 162; i++){
            std::cout << i << ": ";
            memory[i].print_();
        }
    }   
}


void CPU::load_program(const Word18 program[], const unsigned char &size){
    for (unsigned char i = 0; i < size; i++){
        memory[i] = program[i];
    }
    program_size = size;
}


void CPU::fetch(){
    current_instruction = memory[trit_to_decimal(register_C, 5)];
    tri_plus_one(register_C, 5);
}


void CPU::decode(){
    for (unsigned char i = 0; i < 5; i++){
        operand_address[i] = current_instruction[i];
    }
    opcode[0] = current_instruction[5];
    opcode[1] = current_instruction[6];
    opcode[2] = current_instruction[7];
    address_modifier = current_instruction[8];    
}


void CPU::update_sign(){
    for (char i = 17; i >= 0; i--){
        if(register_S[i] == 1){omega = 1; break;}
        else if (register_S[i] == -1){omega = -1; break;}
    }
}


Word18 CPU::get_operand(){
    Word18 oper = Word18();
    int addr = trit_to_decimal(operand_address, 5) + address_modifier * trit_to_decimal(register_F, 5);
    if (addr >= 0 && addr < 162) {
        oper = memory[addr];
        //std::cout << addr << '\n';
        //oper.print_();
    }
    return oper;
}


void CPU::update_pc(){
    Word18 temp = get_operand();
    for (unsigned char i = 0; i < 5; i++){
        register_C[i] = temp[i];
    }
}


int CPU::trit_to_int_operand(){
    Word18 storage_word = get_operand();
    int storage = 0;
    for (unsigned char i = 0; i < 5; i++){
        storage += storage_word[i] * potencia(i);
    }
    return storage;
}


void CPU::execute(){
    switch (trit_to_decimal(opcode, 3)){
        case 9:{
            register_S = get_operand();
            update_sign();
            break;}

        case 10:{
            register_S = register_S + get_operand();
            update_sign();
            break;}

        case 8:{
            register_S = register_S - get_operand();
            update_sign();
            break;}
        
        case 5:{
            run_ = 0;
            register_R = get_operand();
            break;}
        
        case 0:{
            update_pc();
            break;}

        case 2:{
            if (omega == -1){
                update_pc();
            }
            break;}
        
        case 3:{
            if (omega == 0){
                update_pc();
            }
            break;}

        case 4:{
            if (omega == 1){
                update_pc();
            }
            break;}
        
        case 1:{
            int decimal = trit_to_int_operand();
            memory[decimal] = Word18(register_C, 5); 
            break;
        }
        
        case -1:{
            int decimal = trit_to_int_operand();
            memory[decimal] = Word18(register_F, 5); 
            break;
        }

        case -3:{
            int decimal = trit_to_int_operand();
            for (unsigned char i = 0; i < 5; i++){
                register_F[i] = memory[decimal][i];
            }
            break;
        }

        case -2:{
            Word18 operand = get_operand();
            Word18 oper_C = Word18(register_C, 5);
            operand = operand + oper_C;
            for (unsigned char i = 0; i < 5; i++){
                register_F[i] = operand[i];
            }
            break;
        }

        case 7:{
            register_R = get_operand();
            break;
        }
        
        case 6:{
            Word18 operand = get_operand();
            for (unsigned char i = 0; i < 18; i++){
                Trit left = register_S[i];
                Trit right = operand[i];
                if (left == 0 or right == 0){
                    register_S[i] = 0;
                }
                else if (left != right){
                    register_S[i] = 1;
                }
                else{register_S[i] = -1;}
            }
            break;
        }

        case -5:{
            int decimal = trit_to_int_operand();
            for (unsigned char i = 0; i < 18; i++){
                memory[decimal][i] = register_S[i];
            }
            break;}

        case -4:{
            Word18 operand = get_operand();
            Word18 oper_F = Word18(register_F, 5);
            operand = operand + oper_F;
            for (unsigned char i = 0; i < 5; i++){
                register_F[i] = operand[i];
            }
            break;}

        case 13:{
            Word18 operand = get_operand();
            register_S = register_S + (operand * register_R);
            update_sign();
            break;}
        
        case 11:{
            register_S = get_operand() + (register_R * register_S);
            update_sign();
            break;}
        
        case 12:{
            register_R = register_S;
            register_S = get_operand() * register_R;
            update_sign();
            break;}
        
        case -6:{
            int decimal = trit_to_int_operand();
            while (decimal > 17){decimal -= 18;}
            while (decimal < -17){decimal += 18;}

            if (decimal > 0){
                for (int i = 17; i >= decimal; i--){
                    register_S[i] = register_S[i - decimal];
                }
                for (int i = 0; i < decimal; i++){
                    register_S[i] = 0;
                }
            }
            else if (decimal < 0){
                decimal = -decimal;
                for (int i = 0; i <= (17 - decimal); i++){
                    register_S[i] = register_S[i + decimal];
                }
                for (int i = (17 - decimal); i < 17; i++){
                    register_S[i] = 0;
                }

            }
            update_sign();
            break;}

        default:{break;}
    }
}


void CPU::run(){
    run_ = 1;
    while(run_){
        print_registers('C');
        print_registers('S');
        //memory[4].print_();
        fetch();
        decode();
        execute();

    }
}

CPU::CPU(){}


Word18 CPU::make_instr(const Trit addr[5], const Trit opcode[3], const Trit &modifier){
    Word18 instr;
    for (unsigned char i = 0; i < 5; i++){
        instr[i] = addr[i];
    }
    for (unsigned char i = 5; i < 8; i++){
        instr[i] = opcode[i - 5];
    }
    instr[8] = modifier;
    return instr;
}


void CPU::load_instructions(const Trit addrs[][5], const Trit opcodes[][3], const Trit modifiers[], const unsigned char &size){
    unsigned char count = 0;
    while (count < size){
        memory[count] = make_instr(addrs[count], opcodes[count], modifiers[count]);
        count++;
    }
    program_size = count;
}


void CPU::set_memory(const unsigned char &addr, const Word18 &value){
    memory[addr] = value;
}