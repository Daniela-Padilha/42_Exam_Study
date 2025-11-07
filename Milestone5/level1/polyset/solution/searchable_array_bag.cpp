#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag()
{}
searchable_array_bag::~searchable_array_bag()
{}
searchable_array_bag::searchable_array_bag(const searchable_array_bag& other)
{
	*this = other;
}
searchable_array_bag& searchable_array_bag::operator = (const searchable_array_bag& other)
{
	if (this != &other)
		*this = other;
	return (*this);
}

bool searchable_array_bag::has(int val) const
{
	for (int i = 0; i < size; i++)
	{
		if (data[i] == val)
			return true;
	}
	return false;
}