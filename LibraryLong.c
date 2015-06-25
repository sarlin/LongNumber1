#include "LibraryLong.h"

struct LongNumber Sum(struct LongNumber a, struct LongNumber b)
{
	unsigned long long int temporary;
	unsigned int carry = 0, i;
	struct LongNumber result;

	if (a.size < b.size)
	{
		return Sum(b, a);
	}

	result.size = a.size + 1;
	result.digit = (unsigned int*)malloc(sizeof(unsigned int)*(result.size));
	memset(result.digit, 0, result.size * sizeof(unsigned int));

	struct LongNumber b1;
	b1.size = a.size + 1;
	b1.digit = (unsigned int*)malloc(sizeof(unsigned int)*(b1.size));
	memset(b1.digit, 0, b1.size * sizeof(unsigned int));
	for (i = 0; i < b.size; i++)
	{
		b1.digit[i] = b.digit[i];
	}

	for (i = 0; i<a.size; i++)
	{
		temporary = (unsigned long long int) a.digit[i] + (unsigned long long int) b1.digit[i] + (unsigned long long int) carry;
		if (temporary >= dword)
		{
			result.digit[i] = temporary - dword;
			carry = 1;
		}
		else
		{
			result.digit[i] = temporary;
			carry = 0;
		}
	}

	if (carry == 1)
	{
		result.digit[i] = carry;
		result.size = a.size + 1;
	}
	else
		result.size = a.size;

	return result;
}

struct LongNumber Subtracting(struct LongNumber a, struct LongNumber b)
{
	long long int temporary;
	unsigned int carry = 0, i;
	struct LongNumber result;

	if (Compare(a, b) < 0)
	{
		result = Subtracting(b, a);
		return result;
	}

	result.size = a.size;
	result.digit = (unsigned int*)malloc(sizeof(unsigned int)*(result.size));
	memset(result.digit, 0, result.size * sizeof(unsigned int));

	struct LongNumber b1;
	b1.size = a.size;
	b1.digit = (unsigned int*)malloc(sizeof(unsigned int)*(b1.size));
	memset(b1.digit, 0, b1.size * sizeof(unsigned int));
	for (i = 0; i < b.size; i++)
	{
		b1.digit[i] = b.digit[i];
	}

	for (i = 0; i<a.size; i++)
	{
		temporary = (long long int)a.digit[i] - (long long int) b1.digit[i] - (long long int) carry;

		if (temporary < 0)
		{
			result.digit[i] = temporary + dword;
			carry = 1;
		}
		else
		{
			result.digit[i] = temporary;
			carry = 0;
		}
	}
	result = ToNorm(result);
	return result;
}

struct LongNumber Multiplication(struct LongNumber a, struct LongNumber b)
{
	unsigned long long int temporary;
	unsigned int carry, i, j;

	struct LongNumber result;

	result.size = a.size + b.size;
	result.digit = (unsigned int*)malloc(sizeof(unsigned int)*(result.size));
	memset(result.digit, 0, result.size * sizeof(unsigned int));

	for (i = 0; i < b.size; i++)
	{
		carry = 0;

		for (j = 0; j < a.size; j++)
		{
			temporary = (unsigned long long int) b.digit[i] * (unsigned long long int) a.digit[j] + carry + result.digit[i + j];
			carry = temporary / dword;
			result.digit[i + j] = temporary % dword;
		}
		result.digit[i + a.size] = carry;
	}

	result = ToNorm(result);

	return result;
}

struct LongNumber Division(struct LongNumber a, struct LongNumber b, int choice)
{
	struct LongNumber module, result;

	if (Compare(a, b) < 0)
	{
		result.size = 1;
		result.digit = (unsigned int*)malloc(sizeof(unsigned int)*(result.size));
		result.digit[0] = 0;

		if (choice == 1)
			return result;
		else
			return a;
	}

	if (b.size == 1)
	{
		if (b.digit[0] == 0)
		{
			module.size = 0;
			module.digit = NULL;

			return module;
		}

		result = DivisionSmall(a, b.digit[0]);

		module = Subtracting(a, MultiplicationSmall(result, b.digit[0]));

		if (choice == 1)
			return result;
		else
			return module;
	}

	module = Copy(a);

	result.size = a.size - b.size + 1;
	result.digit = (unsigned int*)malloc(sizeof(unsigned int)*(result.size));
	memset(result.digit, 0, result.size * sizeof(unsigned int));

	unsigned int i;

	for (i = a.size - b.size + 1; i != 0; i--)
	{
		unsigned long long int right = dword, left = 0, middle;

		while (right - left > 1)
		{
			middle = (right + left) / 2;

			struct LongNumber temporary = MultiplicationSmall(b, middle);
			temporary = Shift(temporary, i - 1);
			if (Compare(temporary, module) > 0)
				right = middle;
			else
				left = middle;

			free(temporary.digit);
		}

		struct LongNumber temporary = MultiplicationSmall(b, left);
		temporary = Shift(temporary, i - 1);

		module = Subtracting(module, temporary);

		free(temporary.digit);

		result.digit[i - 1] = left;
	}

	module = ToNorm(module);

	result = ToNorm(result);

	if (choice == 1)
		return result;
	else
		return module;
}

struct LongNumber Degree(struct LongNumber a, struct LongNumber b, struct LongNumber c)
{
	struct LongNumber result;
	if (a.size < c.size)
		result.size = c.size + c.size;
	else
		result.size = a.size + a.size;
	result.digit = (unsigned int*)malloc(sizeof(unsigned int)*(result.size));
	memset(result.digit, 0, result.size * sizeof(unsigned int));
	result.digit[0] = 1;
	struct LongNumber com;
	com.size = 1;
	com.digit = (unsigned int*)malloc(sizeof(unsigned int)*(com.size));
	com.digit[0] = 0;
	struct LongNumber value;
	value.size = result.size;
	value.digit = (unsigned int*)malloc(sizeof(unsigned int)*(value.size));
	memset(result.digit, 0, result.size * sizeof(unsigned int));
	memcpy(value.digit, a.digit, a.size * sizeof(unsigned int));
	struct LongNumber pow = Copy(b);
	while ((Compare(pow, com)) > 0)
	{
		if ((pow.digit[0] & 1) == 1)
		{
			result = Multiplication(result, value);
			result = Division(result, c, 2);
		}
		value = Multiplication(value, value);
		value = Division(value, c, 2);
		pow = DivisionSmall(pow, 2);
	}
	free(com.digit);
	free(pow.digit);
	free(value.digit);
	return result;
}

struct LongNumber InputBinFile(const char* file)
{
	unsigned int i;
	struct LongNumber number;
	number.size = 0;
	FILE* check = fopen(file, "r");
    if (!check) 
	{
        printf("Error: Unable to open file: %s \n", file);
		number.size = 1;
		number.digit = (unsigned int*)malloc(sizeof(unsigned int)*(number.size));
		memset(number.digit, 0, number.size * sizeof(unsigned int));
		fclose(check);
        return number;
    }
	fclose(check);
	FILE* in = fopen(file, "rb");
	fseek(in, 0, SEEK_END);
	unsigned int lenght, lmore, size = ftell(in);
	lenght = size / sizeof(unsigned int);
	lmore = size % sizeof(unsigned int);
	if (lmore == 0)
	{
		number.size = lenght;
		number.digit = (unsigned int*)malloc(sizeof(unsigned int)*(number.size));
	}
	else
	{
		number.size = lenght + 1;
		number.digit = (unsigned int*)malloc(sizeof(unsigned int)*(number.size));
	}
	fseek(in, SEEK_SET, 0);  
	for (i = 0; i < lenght; i++)
	{
		fread(&number.digit[i], sizeof(unsigned int), 1, in);
	}
	if (lmore != 0)
	{
		unsigned char ch;
		number.digit[lenght] = 0;

		for(i = 0; i < lmore; i++)
		{
			fread(&ch, sizeof(unsigned char), 1, in);
			number.digit[lenght] |= (ch << i*8);
		}
	}
	fclose(in);		
	return number;
}

void OutputBinFile(const char* file, struct LongNumber number)
{
	int i;
	FILE* out = fopen(file, "wb");
	for (i = 0; i < number.size; i++)
	{
		fwrite(&number.digit[i], sizeof(unsigned int), 1, out);
	}
	fclose(out);
}

struct LongNumber InputTextFile(const char* file)
{
	unsigned int carry, temporary, current = 1, j = 0, k = 0;
	struct LongNumber bin, number;
	number.size = 0;
	char ch;
	FILE* check = fopen(file, "r");
    if (!check) 
	{
        printf("Error: Unable to open file: %s \n", file);
		struct LongNumber number;
		number.size = 1;
		number.digit = (unsigned int*)malloc(sizeof(unsigned int)*(1));
		number.digit[0] = 0;
		fclose(check);
        return number;
    }
	fclose(check);
	FILE *input = fopen(file, "r");
	fseek(input, 0, SEEK_END);
	number.size = ftell(input);
	number.digit = (unsigned int*)malloc(sizeof(unsigned int)*(number.size));
	memset(number.digit, 0, number.size * sizeof(unsigned int));
	bin.size = number.size / 9 + 1;
	bin.digit = (unsigned int*)malloc(sizeof(unsigned int)*(bin.size));
	memset(bin.digit, 0, bin.size * sizeof(unsigned int));
	fseek(input, SEEK_SET, 0);
	long long int i = number.size-1;
	while ((ch = getc(input)) != EOF)
	{
		number.digit[i--] = ch - '0';
	}
	fclose(input);
	while ((number.size != 1) || (number.digit[0]!=0))
	{
		carry = 0;

		for (i = number.size - 1; i >= 0; i--)
		{
			temporary = carry * 10 + number.digit[i];
			number.digit[i] = temporary / 2;
			carry = temporary - number.digit[i] * 2;
		}

		number = ToNorm(number);
		bin.digit[j] = ((current << k) * carry) | bin.digit[j];
		k++;

		if(k == 32)
		{
			k = 0;
			j++;
		}
	}
	free(number.digit);
	bin = ToNorm(bin);
	return bin;
}

void OutputTextFile(const char* file, struct LongNumber number)
{
	struct LongNumber decimal;
	unsigned int a, j = 0;
	long long int temporary, i;
	char carry;
	FILE* out = fopen(file, "w");
	decimal.size = number.size*10;
	decimal.digit = (unsigned int*)malloc(sizeof(unsigned int)*(decimal.size));
	memset(decimal.digit, 0, decimal.size * sizeof(unsigned int));
	while (number.size != 1 || number.digit[0]!=0)
	{
		carry = 0;
		for (i = number.size - 1; i >= 0; i--)
		{
			temporary = carry * dword + number.digit[i];
			number.digit[i] = temporary / 10;
			carry = temporary - (long long int) number.digit[i] * 10;
		}

		carry = carry + '0';

		decimal.digit[j] = carry;
		j++;

		number = ToNorm(number);
	}
	decimal = ToNorm(decimal);
	for (i = decimal.size - 1; i > -1; i--)
	{
		fprintf(out, "%c", decimal.digit[i]);
	}
	fclose(out);
}

struct LongNumber InputNumber(unsigned long long int value)
{
	struct LongNumber number;
	number.size = 0;
	number.digit = (unsigned int*)malloc(sizeof(unsigned int));
	while (value)
	{
		number.size++;
		number.digit[number.size - 1] = value % dword;
		value = value / dword;
	}
	return number;
}

char* OutputNumber(struct LongNumber number)
{
	struct LongNumber decimal;
	unsigned int a, j = 0;
	long long int temporary, i = number.size - 1;
	char carry;
	decimal.size = number.size * 10;
	decimal.digit = (unsigned int*)malloc(sizeof(unsigned int)*(decimal.size));
	memset(decimal.digit, 0, decimal.size * sizeof(unsigned int));
	while ((number.size != 1) || (number.digit[0] != 0))
	{
		carry = 0;
		for (i = number.size - 1; i >= 0; i--)
		{
			temporary = carry * dword + number.digit[i];
			number.digit[i] = temporary / 10;
			carry = temporary - (long long int) number.digit[i] * 10;
		}
		carry += '0';
		decimal.digit[j] = carry;
		j++;
		number = ToNorm(number);
	}
	decimal = ToNorm(decimal);
	char *string = NULL;
	j = 0;
	string = (char*)malloc(sizeof(char)*(1));
	string[0] = '\0';
	for (i = decimal.size - 1; i > -1; i--)
	{
		printf("%c", decimal.digit[i]);
	}
	free(decimal.digit);
	decimal.size = 0;
	return string;
}

struct LongNumber InputString(const char* num)
{
	unsigned int carry, temporary, current = 1, j = 0, k = 0;
	struct LongNumber bin, number;
	char ch;
	long long int i = 0;
	for (; i < strlen(num); i++)
	{
		if (num[i] < '0' || num[i] > '9')
		{
			printf("Error: Wrong string: %s \n", num);
			bin.digit = (unsigned int*)malloc(sizeof(unsigned int)*(1));
			bin.digit[0] = 0;
			bin.size = 1;
			return bin;
		}
	}
	number.size = strlen(num);
	number.digit = (unsigned int*)malloc(sizeof(unsigned int)*(number.size));
	memset(number.digit, 0, number.size * sizeof(unsigned int));
	bin.size = number.size / 9 + 1;
	bin.digit = (unsigned int*)malloc(sizeof(unsigned int)*(bin.size));
	memset(bin.digit, 0, bin.size * sizeof(unsigned int));
	i = number.size - 1;
	for (; i > -1; --i)
	{
		number.digit[i] = num[number.size - i - 1] - '0';
	}
	while (number.size != 1 || number.digit[0] != 0)
	{
		carry = 0;

		for (i = number.size - 1; i >= 0; i--)
		{
			temporary = carry * 10 + number.digit[i];
			number.digit[i] = temporary / 2;
			carry = temporary - number.digit[i] * 2;
		}

		number = ToNorm(number);

		bin.digit[j] = ((current << k) * carry) | bin.digit[j];

		k++;

		if (k == 32)
		{
			k = 0;
			j++;
		}
	}
	free(number.digit);
	bin = ToNorm(bin);
	return bin;
}

struct LongNumber Copy(struct LongNumber from)
{
    struct LongNumber replica;
    replica.size = from.size;
	replica.digit = (unsigned int*)malloc(sizeof(unsigned int)*(replica.size));
	memcpy(replica.digit, from.digit, replica.size * sizeof(unsigned int));
    return replica;
}

int Compare(struct LongNumber a, struct LongNumber b)
{
	if (a.size > b.size)
		return 1;
	if (a.size < b.size)
		return -1;
	int i = a.size - 1;
	while (i > 0)
	{
		i--;
		if (a.digit[i] > b.digit[i])
			return 1;
		if (a.digit[i] < b.digit[i])
			return -1;
	}
	return 0;
}

struct LongNumber ToNorm(struct LongNumber a)
{
	unsigned int i = a.size - 1;

	while ((i > 0) && (a.digit[i] == 0))
	{
		i--;
	}
	a.size = i + 1;

	return a;
}

struct LongNumber Shift(struct LongNumber a, unsigned int s) 
{
    struct LongNumber current;
	current.size = a.size + s;
	current.digit = (unsigned int*)malloc(sizeof(unsigned int)*(current.size));
	memset(current.digit, 0, current.size * sizeof(unsigned int));
	int i;
	for (i = s; i < a.size + s; i++)
	{
		current.digit[i] = a.digit[i - s];
	}
    return current;
}

struct LongNumber MultiplicationSmall(struct LongNumber a, unsigned long long int b)
{
	unsigned long long int temporary, carry = 0;
	unsigned int i, j;
	struct LongNumber result;
	result.size = a.size + 1;
	result.digit = (unsigned int*)malloc(sizeof(unsigned int)*(result.size));
	memset(result.digit, 0, result.size * sizeof(unsigned int));
	carry = 0;
	for (j = 0; j < a.size; j++)
	{
		temporary = b * (unsigned long long int) a.digit[j] + carry + result.digit[j];
		carry = temporary / dword;
		result.digit[j] = temporary % dword;
	}
	result.digit[a.size] = carry;
	result = ToNorm(result);
	i = result.size - 1;
	while ((i > 0) && (result.digit[i] == 0))
	{
		i--;
	}
	result.size = i + 1;
	return result;
}

struct LongNumber DivisionSmall(struct LongNumber a, unsigned long long int b)
{
	unsigned long long int temporary;
	unsigned int carry = 0;
	int i;

	struct LongNumber result;
	result.size = a.size;
	result = Copy(a);
	for (i = a.size - 1; i > -1; i--)
	{
		temporary = (unsigned long long int) carry * dword + a.digit[i];
		result.digit[i] = temporary / b;
		carry = temporary - (unsigned long long int) result.digit[i] * (unsigned long long int) b;
	}

	result = ToNorm(result);

	return result;
}
