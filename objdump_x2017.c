#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

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
    char label;
    char instruction_arr[100][20];
    struct function* next;
}function;


int main(int argc, char* argv[])
{

    unsigned char each_line;
    FILE *ptr;    
	// char *buffer
    ptr = fopen(argv[1],"rb");  // r for read, b for binary
    // ptr = fopen("test.bin","rb"); 

    fseek(ptr, 0, SEEK_END);
    int size = ftell(ptr);
    // printf("size: %i\n",size);
    int size_of_arr = size*8;
    char* arr = malloc((size_of_arr + 1) * sizeof(char));
    // char* arr = ((char*)malloc(sizeof(char) * (size_of_arr + 9)));
    fseek(ptr, 0, SEEK_SET);
    
    int count = 0;
    while(fread(&each_line, sizeof(each_line),1,ptr) != 0)
    {
        // printf("what?: %u\n", each_line);
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

    
    // printf("the result is %s, %i, %i\n",opcode_arr[0].name,opcode_arr[0].value,opcode_arr[0].num_of_args);


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



    function function_array[10];
  
    int place = 0;
    int num_of_instructions = 0;
    for (int i = 0; i < 5; i++)
    {
        int result = pow(2,i);
        num_of_instructions += arr[i] * result;
        place += 1;
    }
    
    
    // char* result_arr = ((char*)malloc(sizeof(char) * (num_of_instructions+1)));
    int count_function_real = 0;
    //cntt is used to count how many lines needs to print in each function
    int cntt[8];
    
    // char* result_2D_array[200][200] = {{0}};
    char **result_arr = NULL;
    // int num = 0;
    // int num_2 = 0;
    int num_max = 0;
    // char char_sym[32] = {0};
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

        // printf("%i\n",num_of_instructions);
        result_arr[num_of_instructions] = (char*)(malloc(sizeof(char) * (5+1)));
        // // orderedIds[num_of_instructions] = malloc((3+1) * sizeof(char));
        strcpy(result_arr[num_of_instructions],"RET");
        //update the place
            
        // int i = 0;

        int count_instruction = 0;
        while (count_instruction < num_of_instructions - 1)
        {
            // printf("number of count instruction: %i\n", count_instruction);
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
            // printf("each instructuion counter: %i\n",each_instruction_counter);
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

            // printf("%s\n", str_5);
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

     //create a fixed length 2D array
        // char result_1[20][20] = {0};
        // printf("number of instructions: %i\n",num_of_instructions);
        for (int cnt = 0; cnt < num_of_instructions + 1; cnt++)
        {
            // result_2D_array[count_function_real][cnt] = result_arr[cnt];
            strcpy(function_array[count_function_real].instruction_arr[cnt], result_arr[cnt]);
            // printf("%s\n",function_array[count_function_real].instruction_arr[cnt]);
            // strcpy(result_1[cnt], result_arr[cnt]);
            //store how many lines needs to be printed in function 0 to an int array
            cntt[count_function_real] = cnt;
            // printf("cntt: %i\n",  cntt[count_function_real])
        }
        
        

        int number_of_function_copy = num_of_instructions;
        // num = num_of_instructions;
        num_max = num_of_instructions;
        // num_2 = num_of_instructions;
        num_of_instructions = 0;
        place_2 = place;
        int ans = size_of_arr - place_2;

       
        // char result_2[20][20] = {0};

        if (ans >= 5)
        {
            // printf("function_number: %i place: %i\n",count_function_real, place);
            
            for (int i = place_2; i < place_2 + 5; i++)
            {
                int result = pow(2,i - place_2);
                num_of_instructions += arr[i] * result;
                place += 1;
            }
            // printf("function_number: %i place: %i\n",count_function_real, place);
            // printf("Number of functions: %i\n", num_of_instructions);

            while (num_of_instructions != 0)
            {
                // printf("function_number: %i place: %i\n",count_function_real, place);
                // printf("hhhhh\n");
                count_function_real += 1;
                // result_arr = NULL;
                
                result_arr = realloc(result_arr, (num_of_instructions + 100) * sizeof(char*));
                

                res = 0;
                // printf("function_number: %i place_2: %i\n",count_function_real, place_2);
                place_2 = place;
                // printf("function_number: %i place_2: %i\n",count_function_real, place_2);

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
               //// result_arr[num_of_instructions] = NULL;
                // printf("?hhhh\n");
                // printf("number of instructions: %i\n", num_of_instructions);
                // printf("number of num_2: %i\n", num_2);
                // printf("number of num_max: %i\n", num_max);
                
                if (num_of_instructions > num_max)
                {
                    // i += 1;
                    // if (i > 1)
                    // {
                    //     break;
                    // }
                    // else
                    // {
                        result_arr[num_of_instructions] = (char*)(malloc(sizeof(char) * (5+1)));
                    // }
                    
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
                            // each_instruction_counter += 1;
                            each_instruction_counter = opcode_arr[j].num_of_args; //2
                        }
                        
                    }
                    res_5 = 0;
                    int count_operation = 0;

                    // printf("each instructuion counter: %i\n",each_instruction_counter);
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
                    // printf("%s\n",result_arr[num_of_instructions - count_function - 1]);
                    count_instruction += 1;
                }
                // printf("count_function:%i\n",count_function);


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
                // printf("%i\n", function_array[count_function_real].label);

                strcat(first_element_str, "FUNC LABEL ");
                strncat(first_element_str, &first_element, 1);

                result_arr[0] = (realloc(result_arr[0], sizeof(char) * (20+1)));

                strcpy(result_arr[0],first_element_str);
                

                // printf("count function real: %i\n", count_function_real);
                for (int cnt = 0; cnt < num_of_instructions + 1; cnt++)
                {

                    strcpy(function_array[count_function_real].instruction_arr[cnt], result_arr[cnt]);
                    // printf("%s\n",function_array[count_function_real].instruction_arr[cnt]);
                    cntt[count_function_real] = cnt;
                }
                for (int i = 0; i < 8; i++)
                {
                    if (cntt[i] >= num_max)
                    {
                        num_max = cntt[i];
                    }
                }
                
                // num_2 = num_of_instructions;
                number_of_function_copy = num_of_instructions;
                num_of_instructions = 0;
                place_2 = place;
                
                int diff = size_of_arr - place;
                // printf("dhslfhdf%i\n",place);

                if (diff >= 5)
                {
                    int ww = 0;
                    for (int i = place_2; i < place_2 + 5;  i++)
                    {

                        int result = pow(2,i - place_2);
                        // printf("result: %i\n", result);
                        num_of_instructions += arr[i] * result;
                        place += 1;
                        ww += 1;
                        // printf("number of instructions: %i\n", num_of_instructions);
                        // printf("dhslfhdf%i\n",place);
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
                printf("%s\n", function_array[i].instruction_arr[j]);
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
                printf("    %s\n", function_array[i].instruction_arr[j]);
            }
                            

            
        }
        
    }
    
   
   
    
    free(arr);
    // printf("number of instructions: %i\n", number_of_function_copy);
    // printf("number of num_2: %i\n", num_2);
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