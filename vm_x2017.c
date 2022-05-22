#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

#define POINTER 32
#define REGISTER 8
#define STACK 256

int myown_atoi(const char s[]);
bool isNumber(char* s);
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
    char sym_; //store the symbol of PTR or STK
    int num_of_corresponding_bit;
}operation;

typedef struct 
{
    char label;
    char instruction_arr[100][20];
    struct function* next;
}function;

typedef struct
{
    char name[3];
    char symbol;
    int value;
}local_var;


int main(int argc, char* argv[])
{

    unsigned char each_line;
    FILE *ptr;    
	// char *buffer
    if (argc != 2)
    {
        printf("Not enough arguments! Exit!\n");
        exit(1);
    }
    ptr = fopen(argv[1],"rb");  // r for read, b for binary

    fseek(ptr, 0, SEEK_END);
    int size = ftell(ptr);
    int size_of_arr = size*8;
    char* arr = malloc((size_of_arr + 1) * sizeof(char));
    fseek(ptr, 0, SEEK_SET);
    
    int count = 0;
    while(fread(&each_line, sizeof(each_line),1,ptr) != 0)
    {
        char eight_bits[8];
        int count_byte = 8;
        for (int i = 0; i < 8; i++)
        {
            eight_bits[i] = (each_line >> i) & 1;
            //place the binary symbol upside-down, and also for each line, we need to check the order for the bit to store,
            // which is convenient for us to work on it afterwards
            arr[size_of_arr - count*8 - count_byte] = eight_bits[i];            
            count_byte -= 1;
        }
        count += 1;
    }


    
    //store the value in an struct array called opcode_arr
    opcode opcode_arr[8];
    //implement the details of each opcode
    strcpy(opcode_arr[0].name, "MOV");
    opcode_arr[0].value = 0;
    opcode_arr[0].num_of_args = 2;

    strcpy(opcode_arr[1].name, "CAL");
    opcode_arr[1].value = 1;
    opcode_arr[1].num_of_args = 1;

    strcpy(opcode_arr[2].name, "RET");
    opcode_arr[2].value = 2;
    opcode_arr[2].num_of_args = 0;

    strcpy(opcode_arr[3].name, "REF");
    opcode_arr[3].value = 3;
    opcode_arr[3].num_of_args = 2;

    strcpy(opcode_arr[4].name, "ADD");
    opcode_arr[4].value = 4;
    opcode_arr[4].num_of_args = 2;

    strcpy(opcode_arr[5].name, "PRINT");
    opcode_arr[5].value = 5;
    opcode_arr[5].num_of_args = 1;

    strcpy(opcode_arr[6].name, "NOT");
    opcode_arr[6].value = 6;
    opcode_arr[6].num_of_args = 1;

    strcpy(opcode_arr[7].name, "EQU");
    opcode_arr[7].value = 7;
    opcode_arr[7].num_of_args = 1;


    operation operation_arr[4];
    strcpy(operation_arr[0].name, "VAL");
    operation_arr[0].value = 0;
    operation_arr[0].num_of_corresponding_bit = 8;

    strcpy(operation_arr[1].name, "REG");
    operation_arr[1].value = 1;
    operation_arr[1].num_of_corresponding_bit = 3;

    strcpy(operation_arr[2].name, "STK");
    operation_arr[2].value = 2;
    operation_arr[2].num_of_corresponding_bit = 5;

    strcpy(operation_arr[3].name, "PTR");
    operation_arr[3].value = 3;
    operation_arr[3].num_of_corresponding_bit = 5;



    function function_array[8];
    int num_max = 0;

    int place = 0;
    int num_of_instructions = 0;
    for (int i = 0; i < 5; i++)
    {
        int result = pow(2,i);
        num_of_instructions += arr[i] * result;
        place += 1;
    }
    
    
    int count_function_real = 0;
    int cntt[8];
    char **result_arr = NULL;
    char symbol_store[32] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f'};


        result_arr = (char**)malloc((num_of_instructions + 1) * sizeof(char*));

        int res = 0;
        
        int place_2 = place;

        for (int i = place_2; i < place_2 + 3; i++)
        {
            int bit_place = pow(2, i - place_2);
            res += bit_place * arr[i];
            place += 1;
        }
    //judge whether the last operation in the function is "RET"(return) or not
        if (res != 2)
            {
                printf("There is no return function in it\n");
                exit(1);
            }

        result_arr[num_of_instructions] = (char*)(malloc(sizeof(char) * (5+1)));
        // // orderedIds[num_of_instructions] = malloc((3+1) * sizeof(char));
        strcpy(result_arr[num_of_instructions],"RET");
        //update the place
            
        int count_instruction = 0;
        while (count_instruction < num_of_instructions - 1)
        {
            char str_5[20] = {0};
            int res_5 = 0;
            place_2 = place;
            for (int i = place_2; i < place_2 + 3; i++)
            {
                int bit_place = pow(2, i - place_2);
                res_5 += bit_place * arr[i];
                place += 1;
            }

            int each_instruction_counter = 0;
            for (int j = 0; j < 8; j++)
            {
                if (opcode_arr[j].value == res_5)
                {
                    strcat(str_5, opcode_arr[j].name);
                    strcat(str_5, " ");
                    each_instruction_counter = opcode_arr[j].num_of_args; //2
                }
                
            }
            res_5 = 0;
            int count_operation = 0;
            while (count_operation < each_instruction_counter)
            {

                place_2 = place;
                for (int i = place_2; i < place_2 + 2; i++)
                {
                    int bit_place = pow(2, i - place_2);
                    res_5 += bit_place * arr[i];
                    place += 1;
                }

                int bit_num = 0;
                char* bit_name = NULL;
                for (int j = 0; j < 4; j++)
                {
                    if (operation_arr[j].value == res_5)
                    {
                        strcat(str_5, operation_arr[j].name);
                        strcat(str_5, " ");
                        bit_num = operation_arr[j].num_of_corresponding_bit;
                        bit_name = operation_arr[j].name;
                    }
                }
                res_5 = 0;
                place_2 = place;
                for (int i = place_2; i < place_2 + bit_num; i++)
                {
                    int bit_place = pow(2, i - place_2);
                    res_5 += bit_place * arr[i];
                    place += 1;
                }
                if (bit_num == 5 && (strcmp(bit_name, "STK") == 0 || strcmp(bit_name, "PTR") == 0 ))
                {                                        
                    char res_5_ch = res_5 + '0' + 17;
                    strncat(str_5, &res_5_ch , 1);
                    if (count_operation < each_instruction_counter - 1)
                    {
                        strcat(str_5, " ");
                    }                  
                }
                
                else
                {
                    char str[10];
                    sprintf(str, "%d", res_5);
                    strcat(str_5, str);
                    if (count_operation < each_instruction_counter - 1)
                    {
                        strcat(str_5, " ");
                    }
                }
                res_5 = 0;
                count_operation += 1;
            }

            result_arr[num_of_instructions - count_instruction - 1] = (char*)(malloc(sizeof(char) * (200)));
            strcpy(result_arr[num_of_instructions - count_instruction - 1], str_5);
            count_instruction += 1;
        }

        char first_element_str[100] = {0};
        int value_of_function = 0;
        place_2 = place;
        for (int i = place_2; i < place_2 + 3; i++)
        {
            int bit_place = pow(2, i - place_2);
            value_of_function += bit_place * arr[i];
            place += 1;
        }
        char first_element = value_of_function + '0';
        function_array[count_function_real].label = first_element - '0';
        strcat(first_element_str, "FUNC LABEL ");
        strncat(first_element_str, &first_element, 1);
        result_arr[0] = (char*)(malloc(sizeof(char) * (20+1)));
        strcpy(result_arr[0],first_element_str);

        for (int cnt = 0; cnt < num_of_instructions + 1; cnt++)
        {
            strcpy(function_array[count_function_real].instruction_arr[cnt], result_arr[cnt]);
            //store how many lines needs to be printed in function 0 to an int array
            cntt[count_function_real] = cnt;
        }
        
        

        int number_of_function_copy = num_of_instructions;
        num_max = num_of_instructions;

        num_of_instructions = 0;
        place_2 = place;
        int ans = size_of_arr - place_2;

       

        if (ans >= 5)
        {            
            for (int i = place_2; i < place_2 + 5; i++)
            {
                int result = pow(2,i - place_2);
                num_of_instructions += arr[i] * result;
                place += 1;
            }


            if (count_function_real > 8)
            {
                printf("Stack overflow!\n");
                exit(1);
            }
            while (num_of_instructions != 0)
            {
                count_function_real += 1;                
                result_arr = realloc(result_arr, (num_of_instructions + 100) * sizeof(char*));
                res = 0;
                place_2 = place;

                for (int i = place_2; i < place_2 + 3; i++)
                {
                    int bit_place = pow(2, i - place_2);
                    res += bit_place * arr[i];
                    place += 1;
                }

            //judge whether the last operation in the function is "RET"(return) or not

                if (res != 2)
                    {
                        printf("There is no return function in it\n");
                        exit(1);
                    }               

                if (num_of_instructions > num_max)
                {                   
                    result_arr[num_of_instructions] = (char*)(malloc(sizeof(char) * (5+1)));                    
                }
                else
                {
                    result_arr[num_of_instructions] = realloc(result_arr[num_of_instructions], sizeof(char) * (5+1));
                }                
                strcpy(result_arr[num_of_instructions],"RET");

                int count_instruction = 0;
                while (count_instruction < num_of_instructions - 1)
                {
                    char str_5[20] = {0};
                    int res_5 = 0;
                    place_2 = place;
                    for (int i = place_2; i < place_2 + 3; i++)
                    {
                        int bit_place = pow(2, i - place_2);
                        res_5 += bit_place * arr[i];
                        place += 1;
                    }

                    int each_instruction_counter = 0;
                    for (int j = 0; j < 8; j++)
                    {
                        if (opcode_arr[j].value == res_5)
                        {
                            strcat(str_5, opcode_arr[j].name);
                            strcat(str_5, " ");
                            each_instruction_counter = opcode_arr[j].num_of_args; //2
                        }
                        
                    }
                    res_5 = 0;
                    int count_operation = 0;
                    while (count_operation < each_instruction_counter)
                    {

                        place_2 = place;
                        for (int i = place_2; i < place_2 + 2; i++)
                        {
                            int bit_place = pow(2, i - place_2);
                            res_5 += bit_place * arr[i];
                            place += 1;
                        }
                        char* bit_name = NULL;
                        int bit_num = 0;
                        for (int j = 0; j < 4; j++)
                        {
                            if (operation_arr[j].value == res_5)
                            {
                                strcat(str_5, operation_arr[j].name);
                                strcat(str_5, " ");
                                bit_num = operation_arr[j].num_of_corresponding_bit;
                                bit_name = operation_arr[j].name;
                            }
                        }
                        res_5 = 0;
                        place_2 = place;
                        for (int i = place_2; i < place_2 + bit_num; i++)
                        {
                            int bit_place = pow(2, i - place_2);
                            res_5 += bit_place * arr[i];
                            place += 1;
                        }
                        if (bit_num == 5 && (strcmp(bit_name, "STK") == 0 || strcmp(bit_name, "PTR") == 0))
                        {
                            char res_5_ch = res_5 + '0' + 17;
                            strncat(str_5, &res_5_ch , 1);
                            if (count_operation < each_instruction_counter - 1)
                            {
                                strcat(str_5, " ");
                            }
                        }
                        
                        else
                        {
                            char str[10];
                            sprintf(str, "%d", res_5);
                            strcat(str_5, str);
                            if (count_operation < each_instruction_counter - 1)
                            {
                                strcat(str_5, " ");
                            }                          
                        }
                        res_5 = 0;
                        count_operation += 1;
                    }

                    if(num_of_instructions - count_instruction - 1 > num_max)
                    {
                        result_arr[num_of_instructions - count_instruction - 1] = (char*)(malloc(sizeof(char) * (200)));
                    }
                    else if (num_of_instructions - count_instruction - 1 > 0)
                    {
                        
                        result_arr[num_of_instructions - count_instruction - 1] = (realloc(result_arr[num_of_instructions - count_instruction - 1], sizeof(char) * (200)));
                    }
                    
                    strcpy(result_arr[num_of_instructions - count_instruction - 1], str_5);
                    count_instruction += 1;
                }

                char first_element_str[100] = {0};
                int value_of_function = 0;
                place_2 = place;
                for (int i = place_2; i < place_2 + 3; i++)
                {
                    int bit_place = pow(2, i - place_2);
                    value_of_function += bit_place * arr[i];
                    place += 1;
                }

                char first_element = value_of_function + '0';
                function_array[count_function_real].label = first_element - '0';
                strcat(first_element_str, "FUNC LABEL ");
                strncat(first_element_str, &first_element, 1);

                result_arr[0] = (realloc(result_arr[0], sizeof(char) * (20+1)));

                strcpy(result_arr[0],first_element_str);
                for (int cnt = 0; cnt < num_of_instructions + 1; cnt++)
                {
                    strcpy(function_array[count_function_real].instruction_arr[cnt], result_arr[cnt]);
                    cntt[count_function_real] = cnt;
                }
                for (int i = 0; i < 8; i++)
                {
                    if (cntt[i] >= num_max)
                    {
                        num_max = cntt[i];
                    }
                }
                number_of_function_copy = num_of_instructions;
                num_of_instructions = 0;
                place_2 = place;
                int diff = size_of_arr - place;

                if (diff >= 5)
                {
                    int ww = 0;
                    for (int i = place_2; i < place_2 + 5;  i++)
                    {
                        int result = pow(2,i - place_2);
                        num_of_instructions += arr[i] * result;
                        place += 1;
                        ww += 1;
                    }
                }
            }
        }

    for (int i = count_function_real; i >= 0; i--)
    {
        char char_sym[32] = {0};
        for (int j = 0; j <= cntt[i]; j++)
        {
            if (j == 0)
            {
                // printf("%s\n", function_array[i].instruction_arr[j]);
            }
            else
            {
                if (strcmp(function_array[i].instruction_arr[j], "RET ") == 0)
                {

                    function_array[i].instruction_arr[j][strlen(function_array[i].instruction_arr[j]) - 1] = '\0';
                    
                }
                for (int w = 0; w < strlen(function_array[i].instruction_arr[j]); w++)
                {
                    if ((function_array[i].instruction_arr[j][w] == 'S' && function_array[i].instruction_arr[j][w + 1] == 'T' && function_array[i].instruction_arr[j][w + 2] == 'K') || (function_array[i].instruction_arr[j][w] == 'P' && function_array[i].instruction_arr[j][w + 1] == 'T' && function_array[i].instruction_arr[j][w + 2] == 'R'))
                    {
                        bool has_same = false;
                        int countt = 0;
                        for (int m = 0; char_sym[m] != '\0'; m++)
                        {
                            if (char_sym[m] == function_array[i].instruction_arr[j][w + 4])
                            {
                                function_array[i].instruction_arr[j][w + 4] = symbol_store[m];
                                has_same = true;
                            }
                            countt += 1;
                        }
                        if (has_same == false)
                        {
                            
                            char_sym[countt] = function_array[i].instruction_arr[j][w + 4];
                            function_array[i].instruction_arr[j][w + 4] = symbol_store[countt];
                            
                        }
                    }
                }
                // printf("    %s\n", function_array[i].instruction_arr[j]);
            }
            
        }
        
    }
    if (count_function_real > 8)
    {
        exit(1);
    }

    local_var stack[STACK];
    int num_ = 0;
    for (int i = count_function_real; i >= 0; i--)
    {
        int count_diff_instructions = 0;
        bool can_change = false;

        for (int j = 0; j <= cntt[i]; j++)
        {
            if (j == 0)
            {
                if (strcmp(function_array[i].instruction_arr[j], "RET ") == 0)
                {
                    function_array[i].instruction_arr[j][strlen(function_array[i].instruction_arr[j]) - 1] = '\0';
                }
                // printf("%s\n",function_array[i].instruction_arr[j]);
            }
            
            else
            {
                
                if (strcmp(function_array[i].instruction_arr[j], "RET ") == 0)
                {

                    function_array[i].instruction_arr[j][strlen(function_array[i].instruction_arr[j]) - 1] = '\0';
                    
                }

                for (int w = 0; w < strlen(function_array[i].instruction_arr[j]); w++)
                {
                    if (function_array[i].instruction_arr[j][w] == 'S' && function_array[i].instruction_arr[j][w + 1] == 'T' && function_array[i].instruction_arr[j][w + 2] == 'K')
                    {
                        num_ += 1;
                        if (num_ > 256)
                        {
                            exit(1);
                        }
                    }
                    if (function_array[i].instruction_arr[j][w] == 'R' && function_array[i].instruction_arr[j][w + 1] == 'E' && function_array[i].instruction_arr[j][w + 2] == 'F')
                    {
                        char operation_code_2[4] = {0};
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 10], 1);
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 11], 1);
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 12], 1);
                                                // char str_of_int[4] = {0};
                        // local_var_arr[count_diff_instructions].symbol = function_array[i].instruction_arr[j][w + 14];
                        // printf("%c\n", local_var_arr[count_diff_instructions].symbol);
                        // strcpy(local_var_arr[count_diff_instructions].name, operation_code_2);
                        // printf("%s\n", local_var_arr[count_diff_instructions].name);

                        char operation_code_1[4] = {0};
                        
                        strncat(operation_code_1, &function_array[i].instruction_arr[j][w + 4], 1);
                        strncat(operation_code_1, &function_array[i].instruction_arr[j][w + 5], 1);
                        strncat(operation_code_1, &function_array[i].instruction_arr[j][w + 6], 1);
                        bool already_have = false;
                        for (int mm = 0; mm <= count_diff_instructions; mm++)
                        {
                            if (stack[mm].name[0] ==  operation_code_1[0] &&  stack[mm].name[1] ==  operation_code_1[1] && stack[mm].name[2] ==  operation_code_1[2] && function_array[i].instruction_arr[j][w + 8] == stack[mm].symbol)
                            {
                                already_have = true;
                            }
                        }
                        if (already_have == false)
                        {
                            
                            // printf("现在在这里%i\n",count_diff_instructions);
                            strcpy(stack[count_diff_instructions].name, operation_code_1);
                            stack[count_diff_instructions].symbol = function_array[i].instruction_arr[j][w + 8];

                            // printf("count diff instructions: %i\n", count_diff_instructions);
                            for (int mm = 0; mm < count_diff_instructions; mm++)
                            {
                                if (stack[mm].name[0] ==  operation_code_2[0] &&  stack[mm].name[1] ==  operation_code_2[1] && stack[mm].name[2] ==  operation_code_2[2] && function_array[i].instruction_arr[j][w + 14] == stack[mm].symbol)
                                {
                                    stack[count_diff_instructions].value = stack[count_diff_instructions - 1].value;
                                }
                            }
                            count_diff_instructions += 1;

                        }


                    }
                    
                    if (function_array[i].instruction_arr[j][w] == 'C' && function_array[i].instruction_arr[j][w + 1] == 'A' && function_array[i].instruction_arr[j][w + 2] == 'L')
                    {
                        
                        
                        can_change = true;
                        // printf("hhhh\n");
                    }
                    if (function_array[i].instruction_arr[j][w] == 'N' && function_array[i].instruction_arr[j][w + 1] == 'O' && function_array[i].instruction_arr[j][w + 2] == 'T')
                    {
                        char operation_code_2[4] = {0};
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 4], 1);
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 5], 1);
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 6], 1);
                        for (int mm = 0; mm < 8; mm++)
                        {
                            if (stack[mm].name[0] == operation_code_2[0] && stack[mm].name[1] == operation_code_2[1] && stack[mm].name[2] == operation_code_2[2] && stack[mm].symbol == function_array[i].instruction_arr[j][w + 8])
                            {
                                stack[mm].value = 255 - stack[mm].value;
                            }
                        }
                    }
                    if (function_array[i].instruction_arr[j][w] == 'A' && function_array[i].instruction_arr[j][w + 1] == 'D' && function_array[i].instruction_arr[j][w + 2] == 'D')
                    {
                        char operation_code_2[4] = {0};
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 4], 1);
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 5], 1);
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 6], 1);


                        char operation_code_1[4] = {0};
                        strncat(operation_code_1, &function_array[i].instruction_arr[j][w + 10], 1);
                        strncat(operation_code_1, &function_array[i].instruction_arr[j][w + 11], 1);
                        strncat(operation_code_1, &function_array[i].instruction_arr[j][w + 12], 1);
                        
                        int value = 0;
                        for (int mm = 0; mm < 8; mm++)
                        {
                            if (stack[mm].name[0] == operation_code_2[0] && stack[mm].name[1] == operation_code_2[1] && stack[mm].name[2] == operation_code_2[2] && stack[mm].symbol == function_array[i].instruction_arr[j][w + 14])
                            {
                                value = stack[mm].value;
                            }
                        }
                        for (int mm = 0; mm < 8; mm++)
                        {
                            if (stack[mm].name[0] == operation_code_1[0] && stack[mm].name[1] == operation_code_1[1] && stack[mm].name[2] == operation_code_1[2] && stack[mm].symbol == function_array[i].instruction_arr[j][w + 8])
                            {
                                stack[mm].value = stack[mm].value + value;
                                if (stack[mm].value > 255)
                                {
                                    stack[mm].value = 0;
                                }
                            }
                        }

                    }



                    if (function_array[i].instruction_arr[j][w] == 'M' && function_array[i].instruction_arr[j][w + 1] == 'O' && function_array[i].instruction_arr[j][w + 2] == 'V')
                    {
                        char operation_code_2[4] = {0};
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 10], 1);
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 11], 1);
                        strncat(operation_code_2, &function_array[i].instruction_arr[j][w + 12], 1);                                               
                        
                        // strcpy(local_var_arr[count_diff_instructions].name, operation_code_2);                          
                        char str_of_int[4] = {0};
                        int value = 0;
                        if (strcmp(operation_code_2, "VAL") == 0)
                        { 
                            
                            for (int m = 14; function_array[i].instruction_arr[j][w + m] != '\0'; m++)
                            {
                                strncat(str_of_int, &function_array[i].instruction_arr[j][w + m], 1);
                            }
                            value = myown_atoi(str_of_int);
                        }
                        else
                        {
                            for (int mm = 0; mm < 8; mm++)
                            {
                                if (stack[mm].name[0] == operation_code_2[0] &&  stack[mm].name[1] == operation_code_2[1] && stack[mm].name[2] == operation_code_2[2] && stack[mm].symbol == function_array[i].instruction_arr[j][w + 14])
                                {
                                    value = stack[mm].value;
                                }
                            }
                            
                        }

                                                

                        /////////////////////////////////////////////////////

                        char operation_code_1[4] = {0};
                        
                        strncat(operation_code_1, &function_array[i].instruction_arr[j][w + 4], 1);
                        strncat(operation_code_1, &function_array[i].instruction_arr[j][w + 5], 1);
                        strncat(operation_code_1, &function_array[i].instruction_arr[j][w + 6], 1);

                               
                        // printf("%s\n",local_var_arr[1].name);
                        strcpy(stack[count_diff_instructions].name, operation_code_1);

                        
                        stack[count_diff_instructions].symbol = function_array[i].instruction_arr[j][w + 8];
                        

                        stack[count_diff_instructions].value = value;                        
                        count_diff_instructions += 1;                                
                                                
                    }

                    if (function_array[i].instruction_arr[j][w] == 'P' && function_array[i].instruction_arr[j][w + 1] == 'R' && function_array[i].instruction_arr[j][w + 2] == 'I' && function_array[i].instruction_arr[j][w + 3] == 'N' && function_array[i].instruction_arr[j][w + 4] == 'T')
                    {
                        if (function_array[i].instruction_arr[j][w + 6] == 'V' && function_array[i].instruction_arr[j][w + 7] == 'A' && function_array[i].instruction_arr[j][w + 8] == 'L')
                        {
                            printf("%c\n",function_array[i].instruction_arr[j][w + 10]);
                        }
                        else
                        {
                            char resu[5] = {0};
                            for (int m = 6; function_array[i].instruction_arr[j][m] != ' '; m++)
                            {
                                strncat(resu, &function_array[i].instruction_arr[j][m], 1);
                            }
                            // printf("%c\n", function_array[i].instruction_arr[j][w + 10]);
                            strncat(resu, &function_array[i].instruction_arr[j][10], 1);
                            
                            // printf("number %i\n", count_diff_instructions);
                            for (int m = 0; m < count_diff_instructions; m++)
                            {
                                if (resu[0] == 'P' && resu[1] == 'T' && resu[2] == 'R')
                                {
                                    resu[0] = 'S';
                                    resu[1] = 'T';
                                    resu[2] = 'K';
                                }
                                // printf("hsdkjfhaksj%c\n", resu[3]);
                                // printf("local_var_arr[m].name: %s\n", local_var_arr[m].name);
                                if (resu[0] == stack[m].name[0] && resu[1] == stack[m].name[1] && resu[2] == stack[m].name[2] && stack[m].symbol == resu[3])
                                {
                                    if (can_change == true)
                                    {
                                        printf("%i\n", stack[m].value + 2);
                                        // printf("hhhhhhhkdfjkal\n");
                                    }
                            
                                    // printf("djfhlajkhfladjkhfkladf;adhs;   %c\n", local_var_arr[m].symbol);
                                    else
                                    {
                                        printf("%i\n", stack[m].value);  
                                    }
                                    
                                    // printf("%s\n", local_var_arr[m].name);  
                                    
                                }
                            }
                        }
                    }
                    
                }
                // printf("    %s\n",function_array[i].instruction_arr[j]);
            }
        }
    }
    // for (int i = 0; i < 8; i++)
    // {
    //     printf("%s: %i\n", stack[i].name,stack[i].value);
    // }
    
   
   
    
    free(arr);
    int max = 0;
    for (int i = 0; i < 8; i++)
    {
        if (cntt[i] >= max)
        {
            max = cntt[i];
        }
    }
    // printf("cntt max: %i\n", max);
    if (number_of_function_copy > max)
    {
        for (int w = 0; w < number_of_function_copy + 1; w++)
        {
            free(result_arr[w]);
            
        }
    }
    else
    {
        for (int w = 0; w < max + 1; w++)
        {
            free(result_arr[w]);
            
        }
    }   
    
    free(result_arr);   
    
    return 0;
}


int myown_atoi(const char s[])
{
    int number = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        number = number * 10 + s[i] - '0';
    }
    return number;
}

bool isNumber(char* s)
{
    for (int i = 0; i < strlen(s); i++)
        if (isdigit(s[i]) == false)
            return false;
 
    return true;
}
