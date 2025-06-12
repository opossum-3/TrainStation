#include "Admin.h"

Admin::Admin() : username(), password()
{

}

const BasicString& Admin::getName() const
{
	return username;
}

bool Admin::isPasswordCorrect(const BasicString& password) const
{
	return this->password == password;
}

void Admin::serialize(std::ofstream& ofstr) const
{
	if (!ofstr.is_open())
	{
		throw std::exception("File error!");
	}
	ofstr << username << password;
}

void Admin::deserialize(std::ifstream& ifstr)
{
	if (!ifstr.is_open())
	{
		throw std::exception("File error!");
	}
	ifstr >> username >> password;
}