/*
 * SETUN Emulator - Convention
 * 
 * All ternary values are written LEFT-TO-RIGHT
 * - Array indexing: [0] is LSB (least significant), [N] is MSB (most significant)
 * - Print output: left-to-right (LSB first)
 * - Input (main.cpp): trits written left-to-right (LSB first)
 * 
 * Example: {1,1,0,0,0} is written left-to-right
 *          = 1×3^0 + 1×3^1 + 0×3^2 + 0×3^3 + 0×3^4
 *          = 1 + 3 + 0 + 0 + 0
 *          = decimal 4
 */

#ifndef CPU_H
#define CPU_H



#include "word18.h"
#include "utils.h"


class CPU{
    public:
        CPU();
        void fetch();
        void decode();
        void execute();
        void run();
        Word18 return_S_register() const;
        Word18 return_F_register() const;
        Word18 return_R_register() const;
        void print_registers(const char &reg) const;
        void load_instructions(const Trit addrs[][5], const Trit opcodes[][3], const Trit modifiers[], const unsigned char &size);
        void load_instructions2(const Trit addrs[][5], const std::string opcodes[], const Trit modifiers[], const unsigned char &size);
        void load_program(const Word18 program[], const unsigned char &size);
        void update_sign();
        void update_pc();
        int trit_to_int_operand();
        Word18 make_instr(const Trit addr[5], const Trit opcode[3], const Trit &modifier = 0);
        Word18 get_operand();
        void set_memory(const unsigned char &addr, const Word18 &value);
        Word18 return_memory(const unsigned char &addr);

    private:
        Word18 current_instruction;
        unsigned short program_size;

        bool run_ = true;
        Trit opcode[3];
        Trit operand_address[5]; 
        Trit address_modifier;
        Word18 register_S; //acumulador
        Word18 register_R; //multiplicador
        Trit register_F[5]; //indice(enderaçamento)
        Trit register_C[5]; //PC
        Trit omega; //sinal
        
        Word18 memory[162];

};


#endif