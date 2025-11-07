#include "set.hpp"

set::set()
{}
set::~set()
{}
set::set(const set& other)
{
	*this = other;
}
set& set::operator = (const set& other)
{
	if (this != &other)
		*this = other;
	return (*this);
}

void set::insert(int)
{

}

void set::insert(int *, int)
{

}

void set::print() const
{

}

void set::clear()
{

}

bool set::has(int val) const
{
	node *n = tree;
	while (n)
	{
		if (val == n->value)
			return true;
		if (val < n->value)
			n = n->l;
		else if (val >= n->value)
			n = n->r;
	}
	return false;
}

const searchable_bag& set::get_bag() const
{

}