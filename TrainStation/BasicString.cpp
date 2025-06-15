#include "BasicString.h"
#include <stdexcept>

BasicString::BasicString(const char* str)
{
	if (!str)
	{
		throw std::exception("String cannot be null!");
		return;
	}
	length = strlen(str);
	this->str = new char[length + 1];
	strcpy_s(this->str, length + 1, str);
}

BasicString::BasicString()
{
	length = 0;
	str = new char[1];
	str[0] = '\0';
}

BasicString::BasicString(const BasicString& other)
{
	copy(other);
}

const BasicString& BasicString::operator= (const BasicString& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

BasicString::~BasicString()
{
	free();
}

BasicString BasicString::repeat(char symbol, size_t times)
{
	char* data = new char[times + 1];
	for (size_t i = 0; i < times; i++)
	{
		data[i] = symbol;
	}
	data[times] = '\0';
	BasicString result(data);
	delete[] data;
	return result;
}

size_t BasicString::getNumLength(size_t num)
{
	if (num < 10)
	{
		return 1;
	}
	return getNumLength(num / 10) + 1;
}

void BasicString::copy(const BasicString& other)
{
	length = other.length;
	str = new char[length + 1];
	strcpy_s(str, length + 1, other.str);
}

void BasicString::free()
{
	delete[] str;
	str = nullptr;
	length = -1;
}

size_t BasicString::getLength() const
{
	return length;
}

char* BasicString::getStr() const
{
	return str;
}

char& BasicString::operator[](size_t index)
{
	if (index < 0 || index >= length)
	{
		throw std::out_of_range("Invalid index!");
	}
	return str[index];
}

char BasicString::operator[](size_t index) const
{
	if (index < 0 || index >= length)
	{
		throw std::out_of_range("Invalid index!");
	}
	return str[index];
}

std::ostream& operator<< (std::ostream& ostr, const BasicString& myStr)
{
	ostr << myStr.str;
	return ostr;
}

std::istream& operator>> (std::istream& istr, BasicString& myStr)
{
	myStr.free();
	myStr.str = new char[BasicString::BUFFER_SIZE];
	istr.getline(myStr.str, BasicString::BUFFER_SIZE);
	myStr.length = strlen(myStr.str);
	return istr;
}

BasicString operator+ (BasicString& lstr, BasicString& rstr)
{
	size_t length = lstr.length + rstr.length;
	char* content = new char[length + 1] {};
	strcpy_s(content, length, lstr.str);
	strcpy_s(content + lstr.length, length, rstr.str);
	content[length] = '\0';
	return BasicString(content);
}

bool operator== (const BasicString& lstr, const BasicString& rstr)
{
	return !strcmp(lstr.str, rstr.str);
}

bool operator!= (const BasicString& lstr, const BasicString& rstr)
{
	return !(lstr == rstr);
}

bool BasicString::operator< (BasicString& other)
{
	return (strcmp(this->str, other.str) < 0);
}

bool BasicString::operator> (BasicString& other)
{
	return other < *this;
}

bool BasicString::operator<= (BasicString& other)
{
	return !(*this > other);
}

bool BasicString::operator>= (BasicString& other)
{
	return !(*this < other);
}

BasicString& BasicString::operator+= (BasicString& other)
{
	BasicString copy = *this + other;
	free();
	length = copy.length;
	str = new char[length + 1];
	strcpy_s(str, length + 1, copy.str);
	return *this;
}

bool BasicString::startsWith(const char* prefix) const
{
	if (!prefix)
	{
		return false;
	}
	size_t prefixLength = strlen(prefix);
	if (prefixLength > length)
	{
		return false;
	}
	for (size_t i = 0; i < prefixLength; i++)
	{
		if (prefix[i] != str[i])
		{
			return false;
		}
	}
	return true;
}

bool BasicString::equals(const char* otherStr) const
{
	if (!otherStr) return false;
	return (strcmp(str, otherStr) == 0);
}

void BasicString::serialize(std::ofstream& ofstr) const
{
	if (!ofstr.is_open())
	{
		throw std::exception("File error!");
	}
	ofstr.write(reinterpret_cast<const char*>(&length), sizeof(length));
	ofstr.write(str, length + 1);
}

void BasicString::deserialize(std::ifstream& ifstr)
{
	if (!ifstr.is_open())
	{
		throw std::exception("File error!");
	}
	size_t newLength = 0;
	ifstr.read(reinterpret_cast<char*>(&newLength), sizeof(newLength));
	char* data = new char[newLength + 1];
	ifstr.read(data, newLength + 1);
	BasicString strFromFile(data);
	free();
	copy(strFromFile);
	delete[] data;
}
