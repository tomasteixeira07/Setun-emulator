#include "tests.h"
//opcodes used:
// +-- = {-1,-1,1} = case 5 
unsigned char test_shift(){
    unsigned char ret = 1;
    std::cout << "Shift Test\n";
    CPU cpu;
    Trit addrs[][5] = {{1,1,0,0,0}, {1,0,0,0,0}, {0,0,0,0,0}};
    std::string opcodes[3] = {"+00","-+0","+--"};
    Trit mods[] = {0, 0, 0};
    

    cpu.set_memory(4, Word18(4));
    cpu.load_instructions2(addrs,opcodes, mods, 3);
    cpu.run();
    
    if (cpu.return_S_register() == Word18(12)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 4    Obtained:";
        cpu.print_registers('S');
        ret = 0;
    }
    return ret;
}


unsigned char test_add_in_S(){
    unsigned char ret = 1;
    std::cout << "ADD in S Test\n";
    CPU cpu;
    Trit addrs[][5] = {{1,1,0,0,0}, {-1,-1,1,0,0}, {0,0,0,0,0}};
    std::string opcodes[3] = {"+00","+0+","+--"};
    Trit mods[] = {0, 0, 0};
    

    cpu.set_memory(4, Word18(4));
    cpu.set_memory(5, Word18(9));

    cpu.load_instructions2(addrs, opcodes, mods, 3);
    cpu.run();
    
    if (cpu.return_S_register() == Word18(13)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 13    Obtained:";
        cpu.print_registers('S');
        ret = 0;
    }
    return ret;
}


unsigned char test_sub_in_S(){
    unsigned char ret = 1;
    std::cout << "SUB in S Test\n";
    CPU cpu;
    Trit addrs[][5] = {{1,1,0,0,0}, {-1,-1,1,0,0}, {0,0,0,0,0}};
    std::string opcodes[3] = {"+00","+0-","+--"};
    Trit mods[] = {0, 0, 0};
    

    cpu.set_memory(4, Word18(4));
    cpu.set_memory(5, Word18(9));

    cpu.load_instructions2(addrs, opcodes, mods, 3);
    cpu.run();
    
    if (cpu.return_S_register() == Word18(-5)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: -5    Obtained:";
        cpu.print_registers('S');
        ret = 0;
    }
    return ret;
}


unsigned char test_add_in_F(){
    unsigned char ret = 1;
    std::cout << "ADD in F Test\n";
    CPU cpu;
    Trit addrs[][5] = {{1,1,0,0,0}, {-1,-1,1,0,0}, {0,0,0,0,0}};
    std::string opcodes[3] = {"0-0","0--","+--"};
    Trit mods[] = {0, 0, 0};
    

    cpu.set_memory(4, Word18(4));
    cpu.set_memory(5, Word18(9));

    cpu.load_instructions2(addrs, opcodes, mods, 3);
    cpu.run();
    
    if (cpu.return_F_register() == Word18(13)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 13    Obtained:";
        cpu.print_registers('F');
        ret = 0;
    }
    return ret;
}


unsigned char mul_1(){
    unsigned char ret = 1;
    std::cout << "Mul 1 Test\n";
    CPU cpu;
    Trit addrs[][5] = {{-1,-1,1,0,0}, {0,-1,1,0,0}, {1,-1,1,0,0}, {0,0,0,0,0}};
    
    std::string opcodes[4] = {"+00","+-+","++-","+--"};
    Trit mods[] = {0, 0, 0,0};
    

    cpu.set_memory(5, Word18(4));  //load to S
    cpu.set_memory(6, Word18(5));  //load to R
    cpu.set_memory(7, Word18(12)); //load to A
    //S = A + S * R  = 32
    cpu.load_instructions2(addrs, opcodes, mods, 4);
    cpu.run();
    
    if (cpu.return_S_register() == Word18(32)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 32    Obtained:";
        cpu.print_registers('S');
        ret = 0;
    }
    return ret;
}


unsigned char mul_3(){
    unsigned char ret = 1;
    std::cout << "Mul 3 Test\n";
    CPU cpu;
    Trit addrs[][5] = {{-1,-1,1,0,0}, {0,-1,1,0,0}, {1,-1,1,0,0}, {0,0,0,0,0}};
    
    std::string opcodes[4] = {"+00","+-+","+++","+--"};
    Trit mods[] = {0, 0, 0,0};
    

    cpu.set_memory(5, Word18(4));  //load to S
    cpu.set_memory(6, Word18(5));  //load to R
    cpu.set_memory(7, Word18(6)); //load to A
    //S +=  A * R  = 4 + 5 * 6
    cpu.load_instructions2(addrs, opcodes, mods, 4);
    cpu.run();
    
    if (cpu.return_S_register() == Word18(34)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 34    Obtained:";
        cpu.print_registers('S');
        ret = 0;
    }
    return ret;
}


unsigned char mul_2(){
    unsigned char ret = 1;
    std::cout << "Mul 3 Test\n";
    CPU cpu;
    Trit addrs[][5] = {{-1,-1,1,0,0}, {0,-1,1,0,0}, {1,-1,1,0,0}, {0,0,0,0,0}};
    std::string opcodes[4] = {"+00","+-+","++0","+--"};
    Trit mods[] = {0, 0, 0,0};
    

    cpu.set_memory(5, Word18(4));  //load to S
    cpu.set_memory(6, Word18(5));  //load to R
    cpu.set_memory(7, Word18(6)); //load to A
    //R = S = 4
    //S =  A * R = A * S =  = 4 * 6 = 24
    cpu.load_instructions2(addrs, opcodes, mods, 4);
    cpu.run();
    
    if (cpu.return_S_register() == Word18(24)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 24 Obtained:";
        cpu.print_registers('S');
        ret = 0;
    }
    return ret;
}


unsigned char jump(){
    unsigned char ret = 1;
    std::cout << "JUMP Test\n";
    CPU cpu;
    Trit addrs[][5] = { {1,1,1,0,0},{0,0,1,0,0} ,{-1,1,1,0,0}, {0,1,1,0,0},{0,0,0,0,0}};
    std::string opcodes[5] = {"+00","000","+00","+00","+--"};
    Trit mods[] = {0, 0, 0,0,0};
    
    cpu.set_memory(9, Word18(4));  //new pc
    cpu.set_memory(10, Word18(5));  //load to S
    cpu.set_memory(11, Word18(6));  //load to S
    cpu.set_memory(12, Word18(7));  //load to S
    cpu.set_memory(13, Word18(8));  //load to S
    cpu.load_instructions2(addrs, opcodes, mods, 5);
    cpu.run();
    
    if (cpu.return_S_register() == Word18(8)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 8 Obtained:";
        cpu.print_registers('S');
        ret = 0;
    }
    return ret;
}


unsigned char jump_w_1(){
    unsigned char ret = 1;
    std::cout << "JUMP if positive Test\n";
    CPU cpu;
    Trit addrs[][5] = { {1,1,1,0,0},{0,0,1,0,0} ,{-1,1,1,0,0}, {0,1,1,0,0},{0,0,0,0,0}};
    std::string opcodes[5] = {"+00","0++","+00","+00","+--"};
    Trit mods[] = {0, 0, 0,0,0};
    
    cpu.set_memory(9, Word18(4));  //new pc
    cpu.set_memory(10, Word18(5));  //load to S
    cpu.set_memory(11, Word18(6));  //load to S
    cpu.set_memory(12, Word18(7));  //load to S
    cpu.set_memory(13, Word18(8));  //load to S

    cpu.load_instructions2(addrs, opcodes, mods, 5);
    cpu.run();
    
    if (cpu.return_S_register() == Word18(8)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 8 Obtained:";
        cpu.print_registers('S');
        ret = 0;
    }
    return ret;
}


unsigned char jump_w_negative(){
    unsigned char ret = 1;
    std::cout << "JUMP if negative Test\n";
    CPU cpu;
    Trit addrs[][5] = { {1,1,1,0,0},{0,0,1,0,0} ,{-1,1,1,0,0}, {0,1,1,0,0},{0,0,0,0,0}};
    std::string opcodes[5] = {"+00","0+-","+00","+00","+--"};
    Trit mods[] = {0, 0, 0,0,0};
    
    cpu.set_memory( 9, Word18(4)); //new pc
    cpu.set_memory(10, Word18(5)); //load to S
    cpu.set_memory(11, Word18(6));  //load to S
    cpu.set_memory(12, Word18(7));  //load to S
    cpu.set_memory(13, Word18(-8));  //load to S

    cpu.load_instructions2(addrs, opcodes, mods, 5);
    cpu.run();
    
    if (cpu.return_S_register() == Word18(-8)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: -8 Obtained:";
        cpu.print_registers('S');
        ret = 0;
    }
    return ret;
}


unsigned char jump_zero(){
    unsigned char ret = 1;
    std::cout << "JUMP if 0 Test\n";
    CPU cpu;
    Trit addrs[][5] = { {1,1,1,0,0},{0,0,1,0,0} ,{-1,1,1,0,0}, {0,1,1,0,0},{0,0,0,0,0}};
    std::string opcodes[5] = {"+00","0+0","+00","+00","+--"};
    Trit mods[] = {0, 0, 0,0,0};
    
    cpu.set_memory( 9, Word18(4)); //new pc
    cpu.set_memory(10, Word18(5)); //load to S
    cpu.set_memory(11, Word18(6));  //load to S
    cpu.set_memory(12, Word18(7));  //load to S
    cpu.set_memory(13, Word18(0));  //load to S

    cpu.load_instructions2(addrs, opcodes, mods, 5);
    cpu.run();
    
    if (cpu.return_S_register() == Word18(0)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 0 Obtained:";
        cpu.print_registers('S');
        ret = 0;
    }
    return ret;
}


unsigned char bitwise_mul(){
    unsigned char ret = 1;
    std::cout << "Bitwise Mull Test\n";
    CPU cpu;
    Trit addrs[][5] = {{1,1,0,0,0}, {-1,-1,1,0,0}, {0,0,0,0,0}};
    std::string opcodes[3] = {"+00","+-0","+--"};
    Trit mods[] = {0, 0, 0};
    
    Trit arr[] = {0,0,0,1,1,1,-1,-1,-1};
    cpu.set_memory(4, Word18(arr, 9) );
    Trit arr2[] = {0,1,-1,0,1,-1,0,1,-1};
    cpu.set_memory(5, Word18(arr2,9)); 
    cpu.load_instructions2(addrs,opcodes, mods, 3);
    cpu.run();
    Trit arr3[] = {0,0,0,0,1,-1,0,-1,1};
    if (cpu.return_S_register() == Word18(arr3,9)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "ERROR";
        ret = 0;
    }
    return ret;
}


unsigned char write_from_S(){
    unsigned char ret = 1;
    std::cout << "Write from S Test\n";
    CPU cpu;
    Trit addrs[][5] = {{1,1,0,0,0}, {-1,-1,1,0,0}, {0,0,0,0,0}};
    std::string opcodes[3] = {"+00","-++","+--"};
    Trit mods[] = {0, 0, 0};
    

    cpu.set_memory(4, Word18(10));
    cpu.load_instructions2(addrs,opcodes, mods, 3);
    cpu.run();
    
    if (cpu.return_memory(5) == Word18(10)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 10    Obtained:";
        cpu.return_memory(5).print_();
        ret = 0;
    }
    return ret;
}


unsigned char write_from_F(){
    unsigned char ret = 1;
    std::cout << "Write from F Test\n";
    CPU cpu;
    Trit addrs[][5] = {{1,1,0,0,0}, {-1,-1,1,0,0}, {0,0,0,0,0}};
    std::string opcodes[3] = {"0-0","00-","+--"};
    Trit mods[] = {0, 0, 0};
    

    cpu.set_memory(4, Word18(10));
    cpu.load_instructions2(addrs,opcodes, mods, 3);
    cpu.run();
    
    if (cpu.return_memory(5) == Word18(10)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 10    Obtained:";
        cpu.return_memory(5).print_();
        ret = 0;
    }
    return ret;
}


unsigned char write_from_C(){
    unsigned char ret = 1;
    std::cout << "Write from C Test\n";
    CPU cpu;
    Trit addrs[][5] = {{1,1,0,0,0}, {-1,-1,1,0,0}, {0,0,0,0,0}};
    std::string opcodes[3] = {"0-0","00+","+--"};
    Trit mods[] = {0, 0, 0};
    
    cpu.load_instructions2(addrs,opcodes, mods, 3);
    cpu.run();

    if (cpu.return_memory(5) == Word18(2)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 2    Obtained:";
        cpu.return_memory(5).print_();
        ret = 0;
    }
    return ret;
}


unsigned char add_and_save_in_F(){
    unsigned char ret = 1;
    std::cout << "ADD in C + Move F Test\n";
    CPU cpu;
    Trit addrs[][5] = {{-1,-1,1,0,0}, {0,0,0,0,0}};
    std::string opcodes[2] = {"0-+","+--"};
    Trit mods[] = {0, 0};
    cpu.set_memory(5, Word18(9));
    
    //F = A + C = 9 + 1 = 10
    cpu.load_instructions2(addrs,opcodes, mods, 2);
    cpu.run();

    if (cpu.return_F_register() == Word18(10)){
        std::cout << "PASS\n";
    }
    else{
        std::cout << "Expected: 10    Obtained:";
        cpu.return_F_register().print_();
        ret = 0;
    }
    return ret;
}


void test_all() {
    unsigned short total;
    total 
        = test_shift()
        + test_add_in_S()
        + test_sub_in_S()
        + test_add_in_F()
        + mul_1()
        + mul_2()
        + mul_3()
        + jump()
        + jump_w_1()
        + jump_w_negative()
        + jump_zero()
        + bitwise_mul()
        + write_from_S()
        + write_from_F()
        + write_from_C()
        + add_and_save_in_F();
    std::cout << "Passed " << total << "/16\n";
}


