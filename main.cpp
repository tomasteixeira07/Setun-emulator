#include "trit.h"
#include "word18.h"
#include "cpu.h"


/*int main() {
    CPU cpu;
    
    std::cout << "Iniciando teste..." << std::endl;
    
    //addrs and oppodes are written left to write
    Trit addrs[][5] = {{1,1,0,0,0}, {0,0,1,0,0}, {0,0,0,0,0}};
    Trit opcodes[][3] = {{0,0,1}, {1,0,1}, {-1,-1,1}};  // 9, 10, 5 (HALT)
    Trit mods[] = {0, 0, 0};
    
    cpu.set_memory(9, Word18(2));
    cpu.set_memory(4, Word18(3));

    
    std::cout << "Carregando programa..." << std::endl;
    cpu.load_instructions(addrs, opcodes, mods, 3);

    cpu.run();
    
    std::cout << "Resultado S: ";
    cpu.print_registers('S');

    
    return 0;
}
*/


