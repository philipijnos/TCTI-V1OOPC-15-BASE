#ifndef VECTOR_HPP
#define VECTOR_HPP

/// @file

/// vector ADT
//
/// This is an ADT that iplements vector manipulations.
/// Both x and y-values are stored in an integer.
/// The appropriate constructors are also added.
class vector{
private:
	int x;
	int y;
	
public:
	/// constructor for explicit values
	//
	/// This constructor initializes a vector for two given values x and y.
	/// If no value is given, it assumes that value is zero.
	vector(int x = 0, int y = 0):
		x(x), y(y)
	{}
	
	/// operator+ one vector
	//
	/// This operator+ returns the vector if there is just one vector given, because +v is always the same as v.
	vector operator+() const{
		return vector(x, y);
	}
	
	/// operator+= two vectors
	//
	/// This operator+= returns the head-tail sum of two vectors.
	vector & operator+=(const vector & rhs){
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	
	/// operator+ two vectors
	//
	/// This operator+ returns the head-tail sum of two vectors.
	vector operator+(const vector & rhs) const{
		vector temp = *this;
		temp += rhs;
		return temp;
	}
	
	/// operator- one vector
	//
	/// This operator- turns the vector around, by making its x- and y-values negative.
	vector operator-() const{
		return vector(-x, -y);
	}
	
	/// operator-= two vectors
	//
	/// This operator-= substracts one vector from another.
	vector & operator-=(const vector & rhs){
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	
	/// operator- two vectors
	//
	/// This operator- substracts one vector from another.
	vector operator-(const vector & rhs) const{
		vector temp = *this;
		temp -= rhs;
		return temp;
	}
	
	/// operator*= vector integer
	//
	/// This operator*= multiplies a vector by a natural number.
	vector & operator*=(const int & rhs){
		x *= rhs;
		y *= rhs;
		return *this;
	}
	
	/// operator* vector integer
	//
	/// This operator* multiplies a vector by a natural number.
	vector operator*(const int & rhs) const{
		vector temp = *this;
		temp *= rhs;
		return temp;
	}
	
	/// operator* integer vector
	//
	/// This operator* multiplies a natural number by a vector.
	vector operator*(const vector & rhs) const{
		vector temp = rhs;
		temp *= *this;
		return temp;
	}
	
	/// operator/= vector integer
	//
	/// This operator/= divides a vector by a natural number.
	vector & operator/=(const int & rhs){
		x /= rhs;
		y /= rhs;
		return *this;
	}
	
	/// operator/ vector integer
	//
	/// This operator/ divides a vector by a natural number.
	vector operator/(const int & rhs) const{
		vector temp = *this;
		temp /= rhs;
		return temp;
	}
	
	/// operator<< vector
	//
	/// This operator<< prints a vector in horizontal coördinates.
	std::ostream & operator<<( std::ostream & lhs, vector rhs ){
		return lhs << "(" << rhs.x << "," << rhs.y << ")";
	}
}

#endif // VECTOR_HPP
