#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag()
{}
searchable_tree_bag::~searchable_tree_bag()
{}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& other)
{
	*this = other;
}
searchable_tree_bag& searchable_tree_bag::operator = (const searchable_tree_bag& other)
{
	if (this != &other)
		*this = other;
	return (*this);
}

bool searchable_tree_bag::has(int val) const
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