typedef struct
{
    char name[5];
    int value;
    int num_of_args;
}opcode;

typedef struct
{
    char name[3];
    int value;
    int value_1; // store the symbol of the operation code, for example, reg 0, restore 0 to value_1
    int value_2; // store the value of the operation code, for example, mov reg 0 val 1, we store 1 to the value of reg 0, so 1 is the value of value_2
    int num_of_corresponding_bit;
}operation;

typedef struct
{
    char name[10];
    char* function[200];
}FUNCTION;

