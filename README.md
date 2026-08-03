# SETUN-1958 Emulator

A C++ emulator of the SETUN, the world's first ternary computer, built at Moscow State University in 1958 by Nikolay Brusentsov.

## About SETUN

SETUN was the only mass-produced computer to use **balanced ternary logic** (digits -1, 0, +1) instead of conventional binary. 49 units were built between 1959 and 1965, mainly used in Soviet universities for teaching and research.

## Architecture

- **Long word:** 18 trits (`Word18`) — used by registers S and R
- **Short word:** 9 trits (`Word9`) — instructions: 5 address trits, 3 opcode trits, 1 modifier trit
- **Registers:** S (accumulator), R (multiplier), F (index), C (program counter), ω (sign)
- **Memory:** 162 cells of 9 trits (ferrite-core RAM)
- **24 single-address instructions**

## Project status


This project emulates only the SETUN **CPU** (the arithmetic/control unit and RAM) — not the full historical machine. Peripherals such as the magnetic drum, photoelectric paper-tape reader, and the electromechanical typewriter/printer are not emulated.

**20 of 24 original instructions implemented:**
- Arithmetic: LOAD, ADD, SUB, MUL1, MUL2, MUL3, bitwise MUL
- Control flow: JMP, conditional JMP (ω=-/0/+), HALT
- Register ops: WriteC, WriteF, MoveF, WriteS, MoveR, ADD to F, ADD-C-and-MoveF
- Shift

**Not yet implemented:** magnetic drum read/write, I/O, normalization (depend on peripherals not emulated in this version).

## Conventions

- Exemple of trits representation: +-- = {-1,-1,1} = (1 * 3 ^ 2) - (1 * 3 ^ 1) - (1 * 3 ^ 0)  = 9 - 3 - 1 = case 5 
- `Word<N>` template underlies both `Word9` and `Word18`

## Build and run

```bash
make
./emulator
```

## Tests

Unit test suite covering each implemented instruction, with expected values computed by hand.

## Sources

- Brusentsov, N.P. et al., "Малая автоматическая цифровая машина «Сетунь»" (1962)
- [Materials on ternary computer science, MSU](http://ternarycomp.cs.msu.ru/)
- [Reference C emulator](https://github.com/askfind/Emulator-Setun-1958)

## Acknowledgements

Thanks to [@askfind](https://github.com/askfind) and [@mrkeuz](https://github.com/mrkeuz) for maintaining the reference SETUN-1958 emulator in C since 2018, which helped clarify ambiguous points in the original Russian documentation.