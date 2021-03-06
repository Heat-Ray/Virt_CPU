**

## Virt_CPU is a virtual CPU emulator written in C++ which seeks to emulate the behaviour of Intel 8080 and Zilog Z80 series of CPUs.

**
****************************************************************************************************************************


Virt_CPU emulates a 8-bit CPU with 1 Kilobytes of memory.

It has 8 8-bit registers and 12 different instructions that can be implemented on these registers.
>Build using -> g++ z80.cpp -o z80 -std=c++17

>Run using -> ./z80 prog.asm (where prog is name of assembly source file)

The emulator is divided into 2 parts :-

 1. The Assembler
 2. The CPU

**The Assembler**
The assembler takes in the written assembly source file and then converts it into the required opcode which is interpreted by the CPU.
The assembler uses a STL map to determine the hex opcode of registers and instructions.
This ensures that the conversion of source code to hexadecimal opcode happens in constant time.

The syntax for the assmembly source is name of the instruction followed by operands all in caps and seperated by whitespaces.

**The CPU**
The CPU is built up of 8 registers and 1024 bytes of memory. The Instruction Set Architecture of the CPU is similar to that of Intel 8080.
12 instructions are also implemented as of now.

 1. **Registers**
 There are total 8 8-bit wide registers in Virt_CPU.
 A is the accumulator register, whereas B, C, D, E, H, L are 8-bit general purpose registers.
 The last register is the 8-bit wide Program counter which helps in executing the instructions present in memory.
 
 2. **Instructions**
 As of now there are total 12 instruction implemented in Virt_CPU
 > 1. MOV -> moves data from one register to another
 > 2. MVI -> Loads integer data up to 255 into registers
 > 3. ADD -> Adds contents of a register to accumulator A
 > 4. SUB -> Subtracts contents of a register from accumulator A
 > 5. INC -> Increments a register by 1
 > 6. DEC -> Decrements a register by 1
 > 7. DMP -> Dumps the contents of registers and flags onto the terminal (useful in checking the progress of a program)
 > 8. CMP -> Compares a register with accumulator A and sets the flags accordingly
 > 9. JU -> Jump to a memory location if underflow flag is set
 > 10. JNU -> Jump to a memory location if underflow flag is not set
 > 11. JO -> Jump if overflow flag is set
 > 12. JNO -> Jump if overflow flag is not set

The CMP instruction sets the *underflow flag* when both accumulator A and registers have same value.
If A is bigger than value of register *overflow* flag is set.

3. **Flags**
There are 3 flags in our CPU
> 1. The Overflow flag -> Flag is set when result of addition is greater than 255
 >2. The Underflow flag -> Flag is set when result of a subtraction is less than 0
> 3. The Sign bit flag -> Used to represent negative numbers 


Built by :-
> Vaibhav Dwivedi - 9917103100

>Milind Kumar - 9917103089
