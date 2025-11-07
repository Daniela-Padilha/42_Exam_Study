#pragma once

#include "given_files/tree_bag.hpp"
#include "given_files/searchable_bag.hpp"

class  searchable_tree_bag: virtual public tree_bag, virtual public searchable_bag {
	public:
		searchable_tree_bag();
		~searchable_tree_bag();
		searchable_tree_bag(const searchable_tree_bag& other);
		searchable_tree_bag& operator = (const searchable_tree_bag& other);
		bool has(int) const;
};