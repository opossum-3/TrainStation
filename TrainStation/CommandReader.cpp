#include "CommandReader.h"
#include "BasicString.h"
#include <stdexcept>

unsigned CommandReader::readUnsigned(const BasicString& str, int& readIndex)
{
	size_t length = str.getLength();
	if (readIndex < 0 || readIndex >= length || !isDigit(str[readIndex]))
	{
		throw std::exception("Invalid string format.");
	}
	unsigned result = 0;
	for (size_t i = readIndex; i < length; i++)
	{
		if (str[i] == ' ')
		{
			return result;
		}
		else if (isDigit(str[i]))
		{
			result *= 10;
			result += str[i] - TO_DIGIT;
			readIndex++;
		}
		else
		{
			throw std::exception("Invalid string format.");
		}
	}
	return result;
}

double CommandReader::readDouble(const BasicString& str, int& readIndex)
{
	size_t length = str.getLength();
	if (readIndex < 0 || readIndex >= length || !isDigit(str[readIndex]))
	{
		throw std::exception("Invalid string format.");
	}
	double result = 0;
	int denominator = -1;
	for (size_t i = readIndex; i < length; i++)
	{
		if (str[i] == ' ')
		{
			break;
		}
		else if (isDigit(str[i]))
		{
			result *= 10;
			result += str[i] - TO_DIGIT;
			if (denominator != -1)
			{
				denominator *= 10;
			}
			readIndex++;
		}
		else if (str[i] == '.')
		{
			if (denominator != -1)
			{
				throw std::exception("Invalid string format.");
			}
			denominator = 1;
			readIndex++;
		}
		else
		{
			throw std::exception("Invalid string format.");
		}
	}
	return (denominator != -1) ? (result / denominator) : result;
}

BasicString CommandReader::readName(const BasicString& str, int& readIndex)
{
	size_t length = str.getLength();
	if (readIndex < 0 || readIndex >= length || !isCapitalLetter(str[readIndex]))
	{
		throw std::exception("Invalid name format!");
	}
	size_t endIndex = 0;
	for (size_t i = readIndex; i < length; i++)
	{
		if (str[i] == ' ')
		{
			break;
		}
		endIndex = i + 1;
		if (i > readIndex && !(isLetter(str[i]) || str[i] == '_'))
		{
			throw std::exception("Invalid name format!");
		}
	}
	char* result = new char[endIndex - readIndex + 1];
	for (size_t i = readIndex; i < endIndex; i++)
	{
		result[i - readIndex] = str[i];
	}
	result[endIndex - readIndex] = '\0';
	readIndex += (endIndex - readIndex);
	return BasicString(result);
}

BasicString CommandReader::readPassword(const BasicString& str, int& readIndex)
{
	size_t length = str.getLength();
	if (readIndex < 0 || readIndex >= length || !isValidPassSymbol(str[readIndex]))
	{
		throw std::exception("Invalid password format!");
	}
	size_t endIndex = 0;
	for (size_t i = readIndex; i < length; i++)
	{
		if (str[i] == ' ')
		{
			break;
		}
		endIndex = i + 1;
		if (!isValidPassSymbol(str[i]))
		{
			throw std::exception("Invalid password format!");
		}
	}
	char* result = new char[endIndex - readIndex + 1];
	for (size_t i = readIndex; i < endIndex; i++)
	{
		result[i - readIndex] = str[i];
	}
	result[endIndex - readIndex] = '\0';
	readIndex += (endIndex - readIndex);
	return BasicString(result);
}

bool CommandReader::readBool(const BasicString& str, int& readIndex)
{
	size_t length = str.getLength();
	if (readIndex < 0 || readIndex >= length)
	{
		throw std::exception("Invalid index!");
	}
	BasicString word = CommandReader::readWord(str, readIndex);
	if (word.equals("true"))
	{
		return true;
	}
	if (word.equals("false"))
	{
		return false;
	}
	throw std::exception("Invalid string!");
}

BasicString CommandReader::readWord(const BasicString& str, int& readIndex)
{
	size_t length = str.getLength();
	if (readIndex < 0 || readIndex >= length)
	{
		throw std::exception("Invalid index!");
	}
	size_t endIndex = 0;
	for (size_t i = readIndex; i < length; i++)
	{
		if (str[i] == ' ')
		{
			break;
		}
		endIndex = i + 1;
	}
	char* result = new char[endIndex - readIndex + 1];
	for (size_t i = readIndex; i < endIndex; i++)
	{
		result[i - readIndex] = str[i];
	}
	result[endIndex - readIndex] = '\0';
	readIndex += (endIndex - readIndex);
	return BasicString(result);
}

BasicString CommandReader::readToEnd(const BasicString& str, int& readIndex)
{
	size_t length = str.getLength();
	if (readIndex < 0 || readIndex >= length)
	{
		throw std::exception("Invalid string format!");
	}
	size_t resultLength = length - readIndex;
	char* result = new char[resultLength + 1];
	for (size_t i = readIndex; i < length; i++)
	{
		result[i - readIndex] = str[i];
	}
	result[resultLength] = '\0';
	readIndex = length;
	return BasicString(result);
}

time_t CommandReader::readDateTime(const BasicString& str, int& readIndex)
{
	size_t length = str.getLength();
	if (readIndex < 0 || readIndex >= length)
	{
		throw std::exception("Invalid string format!");
	}
	checkDateTimeFormat(str, readIndex);
	int i = readIndex;
	int day = (str[i] - TO_DIGIT) * 10 + (str[i + 1] - TO_DIGIT);
	int month = (str[i + 3] - TO_DIGIT) * 10 + (str[i + 4] - TO_DIGIT);
	int year = (str[i + 6] - TO_DIGIT) * 1000;
	year += (str[i + 7] - TO_DIGIT) * 100;
	year += (str[i + 8] - TO_DIGIT) * 10;
	year += str[i + 9] - TO_DIGIT;
	int hours = (str[i + 11] - TO_DIGIT) * 10 + (str[i + 12] - TO_DIGIT);
	int minutes = (str[i + 14] - TO_DIGIT) * 10 + (str[i + 15] - TO_DIGIT);
	moveIndexByLength("01/01/2000 01:00", readIndex);

	tm tm{};
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hours;
	tm.tm_min = minutes;
	time_t result = std::mktime(&tm);
	return result;
}

void CommandReader::moveIndexByLength(const char* str, int& readIndex)
{
	if (!str)
	{
		return;
	}
	readIndex += strlen(str);
}

bool CommandReader::isCompleted(const BasicString& str, int& readIndex)
{
	return str.getLength() == readIndex;
}

bool CommandReader::isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool CommandReader::isCapitalLetter(char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool CommandReader::isSmallLetter(char c)
{
	return (c >= 'a' && c <= 'z');
}

bool CommandReader::isLetter(char c)
{
	return isCapitalLetter(c) || isSmallLetter(c);
}

bool CommandReader::isValidPassSymbol(char c)
{
	return isDigit(c) || isLetter(c) || c == '_' || c == '.';
}

void CommandReader::checkDateTimeFormat(const BasicString& str, int& readIndex)
{
	size_t length = str.getLength();
	BasicString format("01/01/2000 01:00");
	size_t formatLength = format.getLength();
	if (length - readIndex < formatLength)
	{
		throw std::exception("Invalid string format!");
	}
	for (size_t i = 0; i < formatLength; i++)
	{
		if (isDigit(str[readIndex + i]))
		{
			if (!isDigit(format[i]))
			{
				throw std::exception("Invalid string format!");
			}
		}
		else if (str[readIndex + i] != format[i])
		{
			throw std::exception("Invalid string format!");
		}
	}
}
