#include "vect2.hpp"

vect2::vect2()
{
	std::cout << "vect2 created\n";
}

vect2::vect2(int nbr1, int nbr2): _x(nbr1), _y(nbr2)
{
	std::cout << "vect2 created with numbers: " << nbr1 << " and " << nbr2 << std::endl;
}

vect2::vect2(const vect2& other): _x(other._x), _y(other._y)
{
	std::cout << "vect2 copy constructor called\n";
}

vect2::~vect2()
{
	std::cout << "vect2 destroyed\n";
}

vect2&	vect2::operator = (const vect2& other)
{
	std::cout << "vect2 assignment operator called\n";
	if (this != &other)
		*this = other;
	return (*this);
}

int		vect2::operator [] (int index)
{
	if (index == 0)
		return (_x);
	else if (index == 1)
		return (_y);
	else
	{
		std::cout << "Invalid\n";
		return (-1);
	}

}

int operator + ()
{

}
std::ostream& operator << (std::ostream& output, const vect2& other);
{
	std::cout << "{" << other[0];
	return (output);
}
 

int main()
{
	vect2 v1; // 0, 0
	vect2 v2(1, 2); // 1, 2
	const vect2 v3(v2); // 1, 2
	vect2 v4 = v2; // 1, 2
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v1: " << "{" << v1[0] << ", " << v1[1] << "}" << std::endl; //should be the same as the line above
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "v3: " << v3 << std::endl;
	std::cout << "v4: " << v4 << std::endl;
	std::cout << v4++ << std::endl; // 2, 3
	std::cout << ++v4 << std::endl; // 3, 4
	std::cout << v4-- << std::endl; // 2, 3
	std::cout << --v4 << std::endl; // 1, 2
	v2 += v3; // 2, 4
	v1 -= v2; // -2, -4
	v2 = v3 + v3 * 2; // 3, 6
	v2 = 3 * v2; // 9, 18
	v2 += v2 += v3; // 20, 40
	v1 *= 42; // -84, -168
	v1 = v1 - v1 + v1;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "-v2: " << -v2 << std::endl;
	std::cout << "v1[1]: " << v1[1] << std::endl;
	v1[1] = 12;
	std::cout << "v1[1]: " << v1[1] << std::endl;
	std::cout << "v3[1]: " << v3[1] << std::endl;
	std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
	std::cout << "v1 == v1: " << (v1 == v1) << std::endl;
	std::cout << "v1 != v3: " << (v1 != v3) << std::endl;
	std::cout << "v1 != v1: " << (v1 != v1) << std::endl;
}