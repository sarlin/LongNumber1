#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LibraryLong.h"

int main(int argc, const char * argv[])
{
	if (argc < 5) 
	{
        printf("Error: Too few arguments. <first_long_number_filename> [ + | - | * | / | % | ^ ] <second_long_number_filename> <result_long_number_filename>\n");
        return 0;
    }
    
    if (argc > 7) 
	{
        printf("Error: Too many arguments. <first_long_number_filename> [ + | - | * | / | % | ^ ] <second_long_number_filename> <result_long_number_filename> <module_long_number_filename> <-b>\n");
        return 0;
    }
    
    FILE* firstLongNumFile = fopen(argv[1], "r");
    if (!firstLongNumFile) 
	{
        printf("Error: Unable to open file: %s \n", argv[1]);
        return 0;
    }
	fclose(firstLongNumFile);

    const char* operation = argv[2];
    if ((strlen(operation) > 1 || operation[0] == '\0') || operation[0] != '+' && operation[0] != '-' && operation[0] != 'u' && operation[0] != '/' && operation[0] != '%' && operation[0] != 'd') 
	{
        printf("Error: Wrong operation: %s \n", operation);
        return 0;
    }
    
    FILE* secondLongNumFile = fopen(argv[3], "r");
    if (!secondLongNumFile) 
	{
        printf("Error: Unable to open file: %s \n", argv[3]);
        return 0;
    }
    fclose(secondLongNumFile);

	FILE* resultLongNumFile = fopen(argv[4], "r");
    if (!resultLongNumFile) 
	{
        printf("Error: Unable to open file: %s \n", argv[4]);
        return 0;
    }
    fclose(resultLongNumFile);

	int bin = 0;

	if (argc == 5)
		if (argv[2][0] == 'd')
		{
			printf("Error: Input module file\n");
			return 0;
		}

    if (argc == 6) 
	{
		if (argv[2][0] == 'd')
		{
			FILE* moduleLongNumFile = fopen(argv[5], "r");
			if (!moduleLongNumFile) 
			{
				printf("Error: Unable to open file: %s \n", argv[5]);
				return 0;
			}
			fclose(moduleLongNumFile);
		}
		else
		{
			if (strcmp(argv[5], "-b")) 
			{
				printf("Error: Invalid flag: %s \n", argv[5]);
				return 0;
			}
			bin = 1;
		}
		
    }

	if (argc == 7) 
	{
		FILE* moduleLongNumFile = fopen(argv[5], "r");
		if (!moduleLongNumFile) 
		{
			printf("Error: Unable to open file: %s \n", argv[5]);
			return 0;
		}
		fclose(moduleLongNumFile);

        if (strcmp(argv[6], "-b")) 
		{
            printf("Error: Invalid flag: %s \n", argv[6]);
            return 0;
        }
		bin = 1;
    }
    
	struct LongNumber a,b;

  if(bin == 1)
		a = InputBinFile(argv[1]);
	else
		a = InputTextFile(argv[1]);
    
  if(bin == 1)
		b = InputBinFile(argv[3]);
	else
		b = InputTextFile(argv[3]);
    
  
    struct LongNumber result;
    
    switch (operation[0]) {
        case '+':
        {
            result = Sum(a, b);
            break;
        }
        case '-':
        {
            result = Subtracting(a, b);
            break;
        }
        case 'u':
        {
            result = Multiplication(a, b);
            break;
        }
        case '/':
        {
            result = Division(a, b, 1);
            break;
        }
        case '%':
        {
            result = Division(a, b, 2);
            break;
        }
        case 'd':
        {
			struct LongNumber c;
            if(bin == 1)
				c = InputBinFile(argv[5]);
			else
				c = InputTextFile(argv[5]);

			result = Degree(a, b, c);
			free(c.digit);
            break;
        }
        default:
            break;
    }
     
    if (bin == 1)
		OutputBinFile(argv[4], result);
	else
		OutputTextFile(argv[4], result);

    free(a.digit);
    free(b.digit);
    free(result.digit);

	return 0;
}
