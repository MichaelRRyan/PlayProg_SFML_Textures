#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <string>

#include <ostream>

namespace cube
{
	class Vector3f
	{
	public:
		// The class has three variables x, y and z 
		float x;
		float y;
		float z;

		// Constructor 1
		Vector3f();

		// Constructor 2
		Vector3f(float x1, float y1, float z1);

		float Length();
		float LengthSquared();
		void Normalise();
		
		Vector3f operator +(Vector3f V);
		Vector3f operator -(Vector3f V);
		Vector3f operator -(); // An overloaded operator - to return the negation of a single vector
		float operator *(Vector3f V);
		Vector3f operator *(double k);
		Vector3f operator *(float k);
		Vector3f operator *(int k);
		Vector3f operator ^(Vector3f V);
		bool operator ==(Vector3f V);

		std::string toString();
		friend std::ostream& operator <<(std::ostream& t_ostream, Vector3f t_vector); // Overloaded << operator to print vector as a string
	};
}

#endif // !VECTOR3F_H