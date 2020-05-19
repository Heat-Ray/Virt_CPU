#include <bits/stdc++.h>
#include "assembler.cpp"

using namespace std;

class CPU
{
    private:
    unordered_map < unsigned char, unsigned char> registers = {{0x30, 0x0}, {0x31,0x0}, {0x32,0x0}, {0x33,0x0}, {0x34,0x0}, {0x35,0x0}, {0x36,0x0}};
    char o_f, u_f, bt_f;
    char memory[256] = {0};
    char * program_counter;

    public:
    CPU(char ins[])
    {
        int i = 0;
        o_f = 0;
        u_f = 0;
        bt_f = 0;
        while(ins[i] != 0x0)
        {
            memory[i] = ins[i];
            ++i;
        }
        program_counter = memory;

        while((*program_counter) != 0)
        {
            run();
        }
        
    }

    private:
    void run()
    {
        switch(*program_counter)
        {
            case 0x1:                           //  MOV
                registers[*(program_counter+1)] = registers[*(program_counter+2)];
                program_counter += 3;
                break;

            case 0x12:                           //  MVI
                registers[*(program_counter+1)] = *(program_counter+2);
                program_counter += 3;
                break;

            case 0x2:                           //  ADD
                if(*(program_counter+1) + registers[0x1] > 255)
                {
                    o_f = 1;
                    registers[0x30] += registers[*(program_counter+1)];
                }
                else
                {
                    registers[0x30] += registers[*(program_counter+1)];
                }
                program_counter += 2;
                break;

            case 0x3:                           //  SUB
                if(*(program_counter+1) + registers[0x1] < 0)
                {
                    u_f = 1;
                    registers[0x30] -= registers[*(program_counter+1)];
                }
                else
                {
                    registers[0x30] -= registers[*(program_counter+1)];
                }
                program_counter += 2;
                break;

            case 0x4:                           //  INC
                ++registers[*(program_counter+1)];
                program_counter += 2;
                break;

            case 0x5:                           //  DEC
                --registers[*(program_counter+1)];
                program_counter += 2;
                break;

            case 0x6:                           //  DMP
                cout << "Register A -> " << (int)registers[0x30] << endl;
                cout << "Register B -> " << (int)registers[0x31] << endl;
                cout << "Register C -> " << (int)registers[0x32] << endl;
                cout << "Register D -> " << (int)registers[0x33] << endl;
                cout << "Register E -> " << (int)registers[0x34] << endl;
                cout << "Register H -> " << (int)registers[0x35] << endl;
                cout << "Register L -> " << (int)registers[0x36] << endl;
                cout << "Underflow Flag -> " << (int)u_f << "   Overflow Flag -> " << (int)o_f << endl;
                program_counter += 1;
                break;

            case 0x7:                           //  CMP
                if( registers[0x30] == registers[*(program_counter+1)])
                {
                    u_f = 1;
                }
                else
                {
                    u_f = 0;
                }

                if( registers[0x30] > registers[*(program_counter+1)])
                {
                    o_f = 1;
                }
                else
                {
                    o_f = 0;
                }
                
                program_counter += 2;
                break;
                
            case 0x8:                           //  JU   (jump if underflow flag is set)
                if(u_f == 1)
                program_counter = &memory[*(program_counter+1)];
                
                break;

            case 0x9:                           //  JNU  (not jump if underflow flag is set)
                if(u_f != 1)
                program_counter = &memory[*(program_counter+1)];
                
                break;

            case 0x10:                           //  JO
                if(o_f == 1)
                program_counter = &memory[*(program_counter+1)];
                
                break;

            case 0x11:                           //  JNO
                if(o_f != 1)
                program_counter = &memory[*(program_counter+1)];
                
                break;

            default:
                cout << "Error in opcode\nAborted\ncore dumped\n";
        }
    }

};

int main(int argc, char *argv[])
{
    cout << argv[1] << endl;
    Assembler assembler(argv[1]);
    /*int i = 0;
    while(assembler.memory[i] != 0x0)
        {
            cout << (int)assembler.memory[i] << endl;
            i++;
        }*/
    CPU z80(assembler.memory);
}