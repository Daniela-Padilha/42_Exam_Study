#ifndef BIGINT_HPP
#define BIGINT_HPP

# include <iostream>
# include <climits>
# include <algorithm>
# include <string>

class bigint {
	private:
		std::string _nbr;
	public:
		bigint();
		bigint(std::string nbrs);
		bigint(unsigned long long nbrs);
		bigint(const bigint& other);
		~bigint();
		bigint& operator=(const bigint& other);

		std::string getNbrs() const;

		bool operator< (const bigint& other) const;
		bool operator> (const bigint& other) const;
		bool operator<= (const bigint& other) const;
		bool operator>= (const bigint& other) const;
		bool operator== (const bigint& other) const;
		bool operator!= (const bigint& other) const;

		bigint& operator++ ();
		bigint operator++ (int);

		bigint operator+ (const bigint& other) const;
		bigint& operator+= (const bigint& other);

		bigint operator<< (const bigint& src) const;
		bigint operator>> (const bigint& src) const;
		bigint& operator<<= (const bigint& src);
		bigint& operator>>= (const bigint& src);
		
		bigint operator<< (unsigned int) const;
		bigint operator>> (unsigned int) const;
		bigint& operator<<= (unsigned int);
		bigint& operator>>= (unsigned int);
};

std::ostream& operator<< (std::ostream& output, const bigint& src);
int toInt(const bigint& src);

#endif