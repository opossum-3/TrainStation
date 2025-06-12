#pragma once
#include <iostream>
#include <stdexcept>
#include "BasicString.h"

class CommandReader
{
public:
	static const int TO_DIGIT = '0';
	static unsigned readUnsigned(const BasicString& str, int& readIndex);
	static double readDouble(const BasicString& str, int& readIndex);
	static BasicString readName(const BasicString& str, int& readIndex);
	static BasicString readPassword(const BasicString& str, int& readIndex);
	static BasicString readWord(const BasicString& str, int& readIndex);
	static BasicString readToEnd(const BasicString str, int& readIndex);
	static void moveIndexByLength(const char* str, int& readIndex);
	static bool isCompleted(const BasicString& str, int& readIndex);
	static bool isDigit(char c);
	static bool isCapitalLetter(char c);
	static bool isSmallLetter(char c);
	static bool isLetter(char c);
	static bool isValidPassSymbol(char c);
};