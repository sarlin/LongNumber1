#include "ClassLong.h"

ClassLong::ClassLong()
{
	this->number.size = 1;
	this->number.digit = (unsigned int*)malloc(sizeof(unsigned int));
	this->number.digit[0];
}

ClassLong::ClassLong(const LongNumber &right)
{
	number = Copy(right);
}

ClassLong::ClassLong(const ClassLong &right)
{
	this->number = Copy(right.number);
}

ClassLong::ClassLong(const char* str)
{
	this->number = InputString(str);
}

ClassLong::ClassLong(const unsigned long long int value)
{
	this->number = InputNumber(value);
}

ClassLong::~ClassLong()
{
	if (this->number.size != 0)
	{
		free(number.digit);
	}
}

char* ClassLong::Print()
{
	return OutputNumber(this->number);
}

ClassLong ClassLong::operator=(const ClassLong &right)
{
	this->number = Copy(right.number);
	return *this;
}

ClassLong ClassLong::operator+(const ClassLong &right) 
{
	return Sum(this->number, right.number);
}

ClassLong ClassLong::operator-(const ClassLong &right) 
{
	return Subtracting(this->number, right.number);
}

ClassLong ClassLong::operator*(const ClassLong &right) 
{
	return Multiplication(this->number, right.number);
}

ClassLong ClassLong::operator/(const ClassLong &right) 
{
	return Division(this->number, right.number, 1);
}

ClassLong ClassLong::operator%(const ClassLong &right) 
{
	return Division(this->number, right.number, 2);
}

ClassLong ClassLong::operator+(unsigned long long int value) 
{
	return Sum(this->number, InputNumber(value));
}

ClassLong ClassLong::operator-(unsigned long long int value) 
{
	return Subtracting(this->number, InputNumber(value));
}

ClassLong ClassLong::operator*(unsigned long long int value) 
{
	return Multiplication(this->number, InputNumber(value));
}

ClassLong ClassLong::operator/(unsigned long long int value) 
{
	return Division(this->number, InputNumber(value), 1);
}

ClassLong ClassLong::operator%(unsigned long long int value) 
{
	return Division(this->number, InputNumber(value), 2);
}

void ClassLong::ReadText(const char* filename)
{
	*this = InputTextFile(filename);
}

void ClassLong::ReadBin(const char* filename)
{
	*this = InputBinFile(filename);
}

void ClassLong::WriteText(const char* filename)
{
	ClassLong replica = Copy(this->number);
	OutputTextFile(filename, replica.number);
}

void ClassLong::WriteBin(const char* filename)
{
	ClassLong replica = Copy(this->number);
	OutputBinFile(filename, replica.number);
}

ClassLong Deg(ClassLong &osn, ClassLong &exp, ClassLong &mod)
{
	return Degree(osn.number, exp.number, mod.number);
}

ClassLong Deg(ClassLong &osn, ClassLong &exp, unsigned long long int mod)
{
	return Degree(osn.number, exp.number, InputNumber(mod));
}

ClassLong Deg(ClassLong &osn, unsigned long long int exp, ClassLong &mod)
{
	return Degree(osn.number, InputNumber(exp), mod.number);
}

ClassLong Deg(unsigned long long int osn, ClassLong &exp, ClassLong &mod)
{
	return Degree(InputNumber(osn), exp.number, mod.number);
}

ClassLong Deg(ClassLong &osn, unsigned long long int exp, unsigned long long int mod)
{
	return Degree(osn.number, InputNumber(exp), InputNumber(mod));
}

ClassLong Deg(unsigned long long int osn, ClassLong &exp, unsigned long long int mod)
{
	return Degree(InputNumber(osn), exp.number, InputNumber(mod));
}

ClassLong Deg(unsigned long long int osn, unsigned long long int exp, ClassLong &mod)
{
	return Degree(InputNumber(osn), InputNumber(exp), mod.number);
}
