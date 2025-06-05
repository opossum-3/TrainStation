#pragma once
#include <stdexcept>
#include <iostream>
#include <fstream>

template <typename T>
class BasicVector
{
public:
	BasicVector();
	BasicVector(size_t size);
	BasicVector(const BasicVector& other);
	BasicVector& operator= (const BasicVector& other);
	~BasicVector();
	void push_back(const T& item);
	T pop_back();
	void removeAt(size_t index);

	void serialize(std::ofstream& ofstr) const;
	void deserialize(std::ifstream& ifstr);

	T& operator[] (size_t index);
	const T& operator[] (size_t index) const;
	size_t getSize() const;
	size_t getCapacity() const;
private:
	T* items;
	size_t size;
	size_t capacity;
	void copy(const BasicVector& other);
	void free();
	void resize();
};

template<typename T>
BasicVector<T>::BasicVector() : size(0), capacity(1)
{
	items = new T[capacity];
}

template<typename T>
BasicVector<T>::BasicVector(size_t size)
{
	capacity = 1;
	while (capacity < size)
	{
		capacity *= 2;
	}
	items = new T[capacity];
	this->size = size;
}

template<typename T>
BasicVector<T>::BasicVector(const BasicVector<T>& other)
{
	copy(other);
}

template<typename T>
BasicVector<T>& BasicVector<T>::operator=(const BasicVector<T>& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template<typename T>
inline BasicVector<T>::~BasicVector()
{
	free();
}

template<typename T>
void BasicVector<T>::push_back(const T& item)
{
	if (size >= capacity)
	{
		resize();
	}
	items[size] = item;
	size++;
}

template<typename T>
T BasicVector<T>::pop_back()
{
	if (size <= 0)
	{
		throw std::exception("No elements to pop");
	}
	size--;
	return items[size];
}

template<typename T>
void BasicVector<T>::removeAt(size_t index)
{
	if (index < 0 || index >= size)
	{
		throw std::exception("Invalid index!");
	}
	for (size_t i = index; i < size - 1; i++)
	{
		items[i] = items[i + 1];
	}
	size--;
}

template<>
void BasicVector<int>::serialize(std::ofstream& ofstr) const
{
	if (!ofstr.is_open())
	{
		throw std::exception("File error!");
	}
	ofstr.write(reinterpret_cast<const char*>(&size), sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		ofstr.write(reinterpret_cast<const char*>(&items[i]), sizeof(int));
	}
}

template<typename T>
void BasicVector<T>::serialize(std::ofstream& ofstr) const
{
	if (!ofstr.is_open())
	{
		throw std::exception("File error!");
	}
	ofstr.write(reinterpret_cast<const char*>(&size), sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		items[i].serialize(ofstr);
	}
}

template<>
void BasicVector<int>::deserialize(std::ifstream& ifstr)
{
	if (!ifstr.is_open())
	{
		throw std::exception("File error!");
	}
	size_t newSize = 0;
	ifstr.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
	for (size_t i = 0; i < newSize; i++)
	{
		int current = 0;
		ifstr.read(reinterpret_cast<char*>(&current), sizeof(int));
		push_back(current);
	}
}

template<typename T>
void BasicVector<T>::deserialize(std::ifstream& ifstr)
{
	if (!ifstr.is_open())
	{
		throw std::exception("File error!");
	}
	size_t newSize = 0;
	ifstr.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
	for (size_t i = 0; i < newSize; i++)
	{
		T current;
		current.deserialize(ifstr);
		push_back(current);
	}
}

template<typename T>
T& BasicVector<T>::operator[](size_t index)
{
	if (index > size)
	{
		throw std::out_of_range("Invalid index");
	}
	return items[index];
}

template<typename T>
const T& BasicVector<T>::operator[](size_t index) const
{
	if (index > size)
	{
		throw std::out_of_range("Invalid index");
	}
	return items[index];
}

template<typename T>
size_t BasicVector<T>::getSize() const
{
	return size;
}

template<typename T>
size_t BasicVector<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
void BasicVector<T>::copy(const BasicVector<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	items = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		items[i] = other.items[i];
	}
}

template<typename T>
void BasicVector<T>::free()
{
	delete[] items;
	size = 0;
	capacity = 0;
}

template<typename T>
void BasicVector<T>::resize()
{
	capacity *= 2;
	T* temp = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = items[i];
	}
	delete[] items;
	items = temp;
}
