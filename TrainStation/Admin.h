#pragma once
#include "BasicString.h"
#include <fstream>

class Admin
{
public:
	Admin();
	const BasicString& getName() const;
	bool isPasswordCorrect(const BasicString& password) const;
	void serialize(std::ofstream& ofstr) const;
	void deserialize(std::ifstream& ifstr);
private:
	BasicString username;
	BasicString password;
};