#pragma once
#include <iostream>
#include <fstream>
#include <cstring>

class BasicString
{
public:
	static constexpr int BUFFER_SIZE = 100;
	BasicString(const char* str);
	BasicString();
	BasicString(const BasicString& other);
	const BasicString& operator= (const BasicString& other);
	~BasicString();
	static BasicString repeat(char symbol, size_t times);
	static size_t getNumLength(size_t num);
	char& operator[] (size_t index);
	char operator[] (size_t index) const;
	size_t getLength() const;
	char* getStr() const;
	friend std::ostream& operator<< (std::ostream& ostr, const BasicString& myStr);
	friend std::istream& operator>> (std::istream& istr, BasicString& myStr);
	friend bool operator != (const BasicString& lstr, const BasicString& rstr);
	friend bool operator == (const BasicString& lstr, const BasicString& rstr);
	bool operator< (BasicString& other);
	bool operator> (BasicString& other);
	bool operator<= (BasicString& other);
	bool operator>= (BasicString& other);
	BasicString& operator+= (BasicString& other);
	bool startsWith(const char* prefix) const;
	bool equals(const char* otherStr) const;
	void serialize(std::ofstream& ofstr) const;
	void deserialize(std::ifstream& ifstr);
	friend BasicString operator+(BasicString& lstr, BasicString& rstr);
private:
	char* str;
	size_t length;
	void free();
	void copy(const BasicString& other);
};