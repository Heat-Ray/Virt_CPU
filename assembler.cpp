#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

#define FILE_PATH_CODE "assembly.txt"
#define FILE_PATH_OPCODE_TABLE "opcode.txt"
#define MEM_SIZE 256

using namespace std;

class Assembler{
    public:
    char memory[256];
    private:
    char *file_name;
    map<string, int> opcode_table = {{
            {"MOV", 1},
            {"ADD", 2},
            {"SUB", 3},
            {"INC", 4},
            {"DEC", 5},
            {"DMP", 6},
            {"CMP", 7},
            {"JU", 8},
            {"JNU", 9},
            {"JO", 16},
            {"JNO", 17},
            {"MVI", 18},
            {"A", 0x30},
            {"B", 0x31},
            {"C", 0x32},
            {"D", 0x33},
            {"E", 0x34},
            {"H", 0x35},
            {"L", 0x36}
        }};

    public:
    int memory_pointer = 0;

    vector<string> get_token_vector(string line){
        vector<string> token;
        istringstream ss(line);
        while(getline(ss, line, ' ')){
            token.push_back(line);
        }
        return token;
    }

    //Redundant
    void read_opcodes(){
        cout<<"Reading opcodes..\n";
        ifstream file(FILE_PATH_OPCODE_TABLE);
        while(!file.eof()){
            string line;
            getline(file, line);
            vector<string> token = get_token_vector(line);
            try{
                opcode_table.insert({token.at(0), stoi(token.at(1))});
            }
            catch(exception &e){
                cout<<e.what()<<"\n";
            }
        }
        file.close();
        cout<<"Done!\n";
    }
    
    void view_opcode_table(){
        cout<<"Viewing opcode table..\n";
        map<string, int>::iterator itr;
        for(itr=opcode_table.begin(); itr!=opcode_table.end(); ++itr){
            cout<<itr->first<<" : "<<itr->second<<"\n";
        }
        cout<<"Done!\n";
    }

    int query_opcode(string query){
        if(opcode_table.find(query) != opcode_table.end()){
            return opcode_table[query];
        }
        else{
            return -1;
        }
    }

    void insert_in_memory(int opcode){
        memory[memory_pointer] = opcode;
        ++memory_pointer;
    }

    private:
    vector<vector<string> > code_by_line;

    public:
    Assembler(char *file){
        file_name = file;
        read_code();
        //view_code_by_line();
        init_memory();
        convert_to_opcode();
        
        //read_opcodes();
        //view_opcode_table();
        //cout<<query_opcode("MOV")<<"\n";
    }

    void read_code(){
        cout<<"Reading code..\n";
        string line;
        ifstream file(file_name);
        while(!file.eof()){
            getline(file, line);
            try{
                code_by_line.push_back(get_token_vector(line));
            }
            catch(exception &e){
                cout<<e.what()<<"\n";
            }
        }
        file.close();
        cout<<"Done!\n";
    }

    vector<vector<string> > get_code_by_line_copy(){
        return code_by_line;
    }

    void view_code_by_line(){
        cout<<"Viewing code..\n";
        int rows = code_by_line.size();
        
        for(int row=0; row<rows; ++row){
            int cols = code_by_line.at(row).size();

            for(string col_value: code_by_line.at(row)){
                cout<<col_value<<" ";
            }
            cout<<"\n";
        }
        cout<<"Done!\n";
    }

    void init_memory(){
        fill(memory, memory+MEM_SIZE, 0);
    }

    void convert_to_opcode(){
        int rows = code_by_line.size();
        for(int row=0; row<rows; ++row){
            int cols = code_by_line.at(row).size();

            for(string col_value: code_by_line.at(row)){
                int converted_val = query_opcode(col_value);
                if(converted_val > -1){
                    insert_in_memory(converted_val);
                }
                else{
                    insert_in_memory(stoi(col_value));
                }
            }
            //cout<<"\n";
        }
    }
};
