#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dword 4294967296

struct LongNumber
{
    unsigned int size;
    unsigned int* digit;
};

struct LongNumber Sum(struct LongNumber a, struct LongNumber b);
struct LongNumber Subtracting(struct LongNumber a, struct LongNumber b);
struct LongNumber Multiplication(struct LongNumber a, struct LongNumber b);
struct LongNumber Division(struct LongNumber a, struct LongNumber b, int sumbols);
struct LongNumber Degree(struct LongNumber a, struct LongNumber b, struct LongNumber c);
struct LongNumber InputBinFile(const char* file);
void OutputBinFile(const char* file, struct LongNumber number);
struct LongNumber InputTextFile(const char* file);
void OutputTextFile(const char* file, struct LongNumber number);
struct LongNumber InputNumber(unsigned long long int value);
struct LongNumber InputString(const char* num);
char* OutputNumber(struct LongNumber number);
int Compare(struct LongNumber a, struct LongNumber b);
struct LongNumber Copy(struct LongNumber from);
struct LongNumber ToNorm(struct LongNumber a);
struct LongNumber Shift(struct LongNumber a, unsigned int s);
struct LongNumber MultiplicationSmall(struct LongNumber a, unsigned long long int b);
struct LongNumber DivisionSmall(struct LongNumber a, unsigned long long int b);
