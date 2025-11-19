#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}

vect2::vect2(int x, int y) : x(x), y(y) {}

vect2::vect2(const vect2& copy) : x(copy.x), y(copy.y) {}

vect2&	vect2::operator=(const vect2& copy)
{
	if (this != &copy)
	{
		x = copy.x;
		y = copy.y;
	}
	return (*this);
}

int&	vect2::operator[](int i)
{
	if (i == 0)
		return (x);
	else
		return (y);
}

int		vect2::operator[](int i) const
{
	if (i == 0)
		return (x);
	else
		return (y);
}

vect2&	vect2::operator++()
{
	x++;
	y++;
	return (*this);
}

vect2	vect2::operator++(int)
{
	vect2	tmp = *this;
	x++;
	y++;
	return (tmp);
}

vect2&	vect2::operator--()
{
	x--;
	y--;
	return (*this);
}

vect2	vect2::operator--(int)
{
	vect2	tmp = *this;
	x--;
	y--;
	return (tmp);
}

vect2&	vect2::operator+=(const vect2& v)
{
	x += v.x;
	y += v.y;
	return (*this);
}

vect2&	vect2::operator-=(const vect2& v)
{
	x -= v.x;
	y -= v.y;
	return (*this);
}

vect2&	vect2::operator*=(int s)
{
	x *= s;
	y *= s;
	return (*this);
}

vect2	vect2::operator+(const vect2& v) const
{
	return (vect2(x + v.x, y + v.y));
}

vect2	vect2::operator-(const vect2& v) const
{
	return (vect2(x - v.x, y - v.y));
}

vect2	vect2::operator*(int s) const
{
	return (vect2(x * s, y * s));
}

vect2	vect2::operator-() const
{
	return (vect2(-x, -y));
}

vect2	operator*(int s, const vect2& v)
{
	return (vect2(v.x * s, v.y * s));
}

bool	vect2::operator==(const vect2& v) const
{
	return (x == v.x && y == v.y);
}

bool	vect2::operator!=(const vect2& v) const
{
	return (!(x == v.x && y == v.y));
}

std::ostream& operator<<(std::ostream& os, const vect2& v)
{
	os << "{" << v[0] << ", " << v[1] << "}";	
	return (os);
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
