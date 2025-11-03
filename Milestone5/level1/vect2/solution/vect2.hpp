#ifndef VECT2_HPP
# define VECT2_HPP

# include <iostream>

class vect2 {
	private: 
		int _x;
		int _y;

	public:
		vect2();
		vect2(int x, int y);
		vect2(const vect2& other);
		~vect2();

		vect2&	operator = (const vect2& other);

		int&	operator[](int i);
		int		operator[](int i) const;

		vect2&	operator++();
		vect2	operator++(int);
		vect2&	operator--();
		vect2	operator--(int);

		vect2&	operator+=(const vect2& v);
		vect2&	operator-=(const vect2& v);
		vect2&	operator*=(int s);
		vect2	operator+(const vect2& v) const;
		vect2	operator-(const vect2& v) const;
		vect2	operator*(int s) const;
		friend vect2	operator*(int s, const vect2& v);

		vect2	operator-() const;

		bool	operator==(const vect2& v) const;
		bool	operator!=(const vect2& v) const;

};

std::ostream& operator << (std::ostream& output, const vect2& other);

#endif