#include "bigint.hpp"

bigint::bigint(): _nbr("0") {}

bigint::bigint(std::string nbrs): _nbr(nbrs) {}

bigint::bigint(unsigned long long nbrs): _nbr(std::to_string(nbrs)) {}

bigint::bigint(const bigint& other)
{
	*this = other;
}

bigint::~bigint() {}

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
		this->_nbr = other._nbr;
	return *this;
}

std::string bigint::getNbrs() const
{
	return _nbr;
}

bool bigint::operator< (const bigint& other) const
{
	if (this->_nbr < other._nbr)
		return true;
	return false;
}

bool bigint::operator> (const bigint& other) const
{
	if (this->_nbr > other._nbr)
		return true;
	return false;
}

bool bigint::operator<= (const bigint& other) const
{
	if (this->_nbr <= other._nbr)
		return true;
	return false;
}

bool bigint::operator>= (const bigint& other) const
{
	if (this->_nbr >= other._nbr)
		return true;
	return false;
}

bool bigint::operator== (const bigint& other) const
{
	if (this->_nbr == other._nbr)
		return true;
	return false;
}

bool bigint::operator!= (const bigint& other) const
{
	if (this->_nbr != other._nbr)
		return true;
	return false;
}

bigint& bigint::operator++ ()
{
	*this = *this + bigint(1);
	return *this;
}

bigint bigint::operator++ (int)
{
	bigint tmp = *this;
	*this = *this + bigint(1);
	return tmp;
}

bigint bigint::operator+ (const bigint& other) const
{
	std::string res;
	int carry = 0;
	int i = this->_nbr.size() - 1;
	int j = other.getNbrs().size() - 1;

	while (i >= 0 || j>= 0 || carry != 0)
	{
		int sum = carry;
		if (i >= 0)
			sum += this->_nbr[i--] - '0';
		if (j >= 0)
			sum += other._nbr[j--] - '0';
		res.push_back((sum % 10) + '0');
		carry = sum / 10;
	}
	std::reverse(res.begin(), res.end());
	return bigint(res);
}

bigint& bigint::operator+= (const bigint& other)
{
	*this = *this + other;
	return *this;
}

bigint bigint::operator<< (const bigint& src) const
{
	std::string res = this->getNbrs();
	res.append(toInt(src), '0');
	return bigint(res);
}

bigint bigint::operator>> (const bigint& src) const
{
	std::string res = this->_nbr.substr(0, (this->_nbr.size() - toInt(src)));
	return bigint(res);
}

bigint& bigint::operator<<= (const bigint& src)
{
	*this = *this << toInt(src);
	return *this;
}

bigint& bigint::operator>>= (const bigint& src)
{
	*this = *this >> toInt(src);
	return *this;
}

bigint bigint::operator<< (unsigned int n) const
{
	if (this->_nbr == "0")
		return *this;
	std::string res = this->_nbr;
	res.append(n, '0');
	return bigint(res);
}

bigint bigint::operator>> (unsigned int n) const
{
	if (this->_nbr.size() <= n)
		return bigint(0);
	std::string res = this->_nbr.substr(0, (this->_nbr.size() - n));
	return bigint(res);
}

bigint& bigint::operator<<= (unsigned int n)
{
	*this = *this << n;
	return *this;
}

bigint& bigint::operator>>= (unsigned int n)
{
	*this = *this >> n;
	return *this;
}

std::ostream& operator<< (std::ostream& output, const bigint& src)
{
	output << src.getNbrs();
	return output;
}

int toInt(const bigint& src)
{
	if (src.getNbrs().size() > 9)
		return INT_MAX;
	int res = std::stoi(src.getNbrs());
	return res;
}
