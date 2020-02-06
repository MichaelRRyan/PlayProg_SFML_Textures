#include "Vector3f.h"

using namespace cube;

cube::Vector3f::Vector3f()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

cube::Vector3f::Vector3f(float x1, float y1, float z1)
{
	// To allow other values for X, Y and Z to be declared
	x = x1;
	y = y1;
	z = z1;
}

//cube::Vector3f(Vector3f &V)
//{
//	// To allow other values for X, Y and Z to be declared
//	x = V.x;
//	y = V.y;
//	z = V.z;
//}

float Vector3f::Length()
{  // A method to return the length of the vector
	return sqrtf((x * x) + (y * y) + (z * z));
}

float Vector3f::LengthSquared()
{  // A method to return the length squared of the vector
	return (x * x + y * y + z * z);
}

void Vector3f::Normalise()
{
	// A method to reduce the length of the vector to 1.0 
		  // keeping the direction the same
	if (Length() > 0.0)
	{  // Check for divide by zero
		float magnit = Length();
		x /= magnit;
		y /= magnit;
		z /= magnit;
	}

}

Vector3f Vector3f::operator+(Vector3f V)
{  // An overloaded operator + to return the sum of 2 vectors
	return { x + V.x, y + V.y, z + V.z };
}

Vector3f Vector3f::operator-(Vector3f V)
{ // An overloaded operator - to return the difference of 2 vectors
	return { x - V.x, y - V.y, z - V.z };
}

Vector3f Vector3f::operator-()
{
	return { -x, -y, -z };
}

float Vector3f::operator*(Vector3f V)
{// An overloaded operator * to return the scalar product of 2 vectors
	return (x * V.x + y * V.y + z * V.z);
}

Vector3f Vector3f::operator*(double k)
{// An overloaded operator * to return the product of a scalar by a vector
	return { x * static_cast<float>(k), y * static_cast<float>(k), z * static_cast<float>(k) };
}

Vector3f Vector3f::operator*(float k)
{// An overloaded operator * to return the product of a scalar by a vector
	return { x * k, y * k, z * k };
}

Vector3f Vector3f::operator*(int k)
{// An overloaded operator * to return the product of a scalar by a vector
	return { x * static_cast<float>(k), y * static_cast<float>(k), z * static_cast<float>(k) };
}

Vector3f Vector3f::operator^(Vector3f V2)
{// An overloaded operator ^ to return the vector product of 2 vectors
	return { y * V2.z - z * V2.y, z * V2.x - x * V2.z, x * V2.y - y * V2.x };
}

bool cube::Vector3f::operator==(Vector3f V)
{
	return (x == V.x && y == V.y && z == V.z);
}

std::string Vector3f::toString()
{
	return "{ " + std::to_string(x) + "f, " + std::to_string(y) + "f, " + std::to_string(z) + "f }";
}

std::ostream& cube::operator<<(std::ostream& t_ostream, Vector3f t_vector)
{
	t_ostream << "{ " + std::to_string(t_vector.x) + "f, " + std::to_string(t_vector.y) + "f, " + std::to_string(t_vector.z) + "f }";
	return t_ostream;
}
