#include "Matrix3f.h"

using namespace cube;

cube::Matrix3f::Matrix3f()
{
	A11 = 0.0;
	A12 = 0.0;
	A13 = 0.0;
	A21 = 0.0;
	A22 = 0.0;
	A23 = 0.0;
	A31 = 0.0;
	A32 = 0.0;
	A33 = 0.0;
}

cube::Matrix3f::Matrix3f(Vector3f Row1, Vector3f Row2, Vector3f Row3)
{  // To allow 3 rows of vectors to be declared as a matrix
	A11 = Row1.x;
	A12 = Row1.y;
	A13 = Row1.z;
	A21 = Row2.x;
	A22 = Row2.y;
	A23 = Row2.z;
	A31 = Row3.x;
	A32 = Row3.y;
	A33 = Row3.z;
}

cube::Matrix3f::Matrix3f(float _A11, float _A12, float _A13, float _A21, float _A22, float _A23, float _A31, float _A32, float _A33)
{// to allow nine float values
	A11 = _A11;
	A12 = _A12;
	A13 = _A13;
	A21 = _A21;
	A22 = _A22;
	A23 = _A23;
	A31 = _A31;
	A32 = _A32;
	A33 = _A33;
}

Matrix3f Matrix3f::Transpose(Matrix3f M1)
{// a method to transpose a given matrix
	return Matrix3f(M1.A11, M1.A21, M1.A31,
		M1.A12, M1.A22, M1.A32,
		M1.A13, M1.A23, M1.A33);
}

Matrix3f Matrix3f::operator+(Matrix3f M)
{// An overloaded operator + to return the  sum of two matrix 
	return { A11 + M.A11, A12 + M.A12, A13 + M.A13,
		A21 + M.A21, A22 + M.A22, A23 + M.A23,
		A31 + M.A31, A32 + M.A32, A33 + M.A33 };
}

Matrix3f Matrix3f::operator-(Matrix3f M)
{// An overloaded operator * to return the  difference of two matrix
	return { A11 - M.A11, A12 - M.A12, A13 - M.A13,
		A21 - M.A21, A22 - M.A22, A23 - M.A23,
		A31 - M.A31, A32 - M.A32, A33 - M.A33 };
}

Matrix3f Matrix3f::operator*(float x)
{// An overloaded operator * to return the  product of the matrix by a scalar
	Matrix3f answer;
	answer.A11 = A11 * x;
	answer.A12 = A12 * x;
	answer.A13 = A13 * x;

	answer.A21 = A21 * x;
	answer.A22 = A22 * x;
	answer.A23 = A23 * x;

	answer.A31 = A31 * x;
	answer.A32 = A32 * x;
	answer.A33 = A33 * x; ;

	return answer;
}

Matrix3f cube::operator*(float x, Matrix3f M1)
{// An overloaded operator * to return the  product of the matrix by a scalar
	return Matrix3f(M1.A11 * x, M1.A12 * x, M1.A13 * x,
		M1.A21 * x, M1.A22 * x, M1.A23 * x,
		M1.A31 * x, M1.A32 * x, M1.A33 * x);
}

Matrix3f Matrix3f::operator*(Matrix3f M)
{// An overloaded operator * to return the  product of two matrix
	Matrix3f answer;

	answer.A11 = Row(0) * M.Column(0);
	answer.A12 = Row(0) * M.Column(1);
	answer.A13 = Row(0) * M.Column(2);

	answer.A21 = Row(1) * M.Column(0);
	answer.A22 = Row(1) * M.Column(1);
	answer.A23 = Row(1) * M.Column(2);

	answer.A31 = Row(2) * M.Column(0);
	answer.A32 = Row(2) * M.Column(1);
	answer.A33 = Row(2) * M.Column(2);


	return answer;
}

Vector3f Matrix3f::operator*(Vector3f V1)
{// An overloaded operator * to return the  product of the matrix by a vector
	return { A11 * V1.x + A12 * V1.y + A13 * V1.z,
			 A21 * V1.x + A22 * V1.y + A23 * V1.z,
			 A31 * V1.x + A32 * V1.y + A33 * V1.z };
}

Vector3f cube::operator*(Vector3f V1, Matrix3f M1)
{// An overloaded operator * to return the  product of the matrix by a vector
	return Vector3f(M1.A11 * V1.x + M1.A21 * V1.y + M1.A31 * V1.z,
		M1.A12 * V1.x + M1.A22 * V1.y + M1.A32 * V1.z,
		M1.A13 * V1.x + M1.A23 * V1.y + M1.A33 * V1.z);
}

float Matrix3f::Determinant(Matrix3f M1)
{// method to return the determinant of a 3x3 matrix
			//                     aei      -     ahf                  + dhc                     - gec                      +    gbh                    -     dbi   
	return M1.A11 * M1.A22 * M1.A33 - M1.A11 * M1.A32 * M1.A23 + M1.A21 * M1.A32 * M1.A13 - M1.A31 * M1.A22 * M1.A13 + M1.A31 * M1.A12 * M1.A23 - M1.A21 * M1.A12 * M1.A33;
}

Vector3f Matrix3f::Row(int i)
{
	// a method to return as Row as Vector3f 0 == first row, default == last row
	switch (i)
	{
	case 0:
		return { A11, A12, A13 };
	case 1:
		return { A21, A22, A23 };
	case 2:
	default:
		return { A31, A32, A33 };
	}
}

Vector3f Matrix3f::Column(int i)
{// a method to return as column as Vector3f 0 == first column, default == last column
	switch (i)
	{
	case 0:
		return { A11, A21, A31 };
	case 1:
		return { A12, A22, A32 };
	case 2:
	default:
		return { A13, A23, A33 };
	}
}

Matrix3f Matrix3f::Inverse(Matrix3f M1)
{
	// method to return the inverse of a matrix if exists else zero vector
	float det = Determinant(M1);
	if (det == 0)
		return Matrix3f();
	else
	{
		float scale = 1 / det;
		Matrix3f answer;
		answer.A11 = scale * (M1.A22 * M1.A33 - M1.A23 * M1.A32); // ei-fh
		answer.A12 = scale * (M1.A13 * M1.A32 - M1.A12 * M1.A33); // ch-bi
		answer.A13 = scale * (M1.A12 * M1.A23 - M1.A13 * M1.A22); // ch-bi

		answer.A21 = scale * (M1.A23 * M1.A31 - M1.A21 * M1.A33); // fg-di
		answer.A22 = scale * (M1.A11 * M1.A33 - M1.A13 * M1.A31); // ai-cg
		answer.A23 = scale * (M1.A13 * M1.A21 - M1.A11 * M1.A23); // cd-af


		answer.A31 = scale * (M1.A21 * M1.A32 - M1.A22 * M1.A31); // dh-eg
		answer.A32 = scale * (M1.A12 * M1.A31 - M1.A11 * M1.A32); // bg-ah
		answer.A33 = scale * (M1.A11 * M1.A22 - M1.A12 * M1.A21); // ae-bd

		return answer;
	}

}

Matrix3f Matrix3f::Rotation(float _angle)
{
	float radians = PI / 180 * _angle;
	Matrix3f answer;
	answer.A11 = cos(radians);
	answer.A12 = sin(radians);
	answer.A13 = 0;
	answer.A21 = -sin(radians);
	answer.A22 = cos(radians);
	answer.A23 = 0;
	answer.A31 = 0;
	answer.A32 = 0;
	answer.A33 = 1;

	return answer;
}

Matrix3f Matrix3f::Translate(float dx, float dy)
{
	Matrix3f answer;
	answer.A11 = 1;
	answer.A12 = 0;
	answer.A13 = dx;
	answer.A21 = 0;
	answer.A22 = 1;
	answer.A23 = dy;
	answer.A31 = 0;
	answer.A32 = 0;
	answer.A33 = 1;

	return answer;
}

Matrix3f Matrix3f::Scale(float dx, float dy)
{
	Matrix3f answer;
	answer.A11 = dx / 100;
	answer.A12 = 0;
	answer.A13 = 0;
	answer.A21 = 0;
	answer.A22 = dy / 100;
	answer.A23 = 0;
	answer.A31 = 0;
	answer.A32 = 0;
	answer.A33 = 1;

	return answer;
}

Matrix3f Matrix3f::operator-()
{
	return this->operator*(-1.0f);
}

Matrix3f Matrix3f::RotationX(float _angle)
{
	float radians = PI / 180 * _angle;
	Matrix3f answer;
	answer.A11 = 1;
	answer.A12 = 0;
	answer.A13 = 0;
	answer.A21 = 0;
	answer.A22 = cos(radians);
	answer.A23 = -sin(radians);
	answer.A31 = 0;
	answer.A32 = sin(radians);
	answer.A33 = cos(radians);

	return answer;
}

Matrix3f Matrix3f::RotationY(float _angle)
{
	float radians = PI / 180 * _angle;
	Matrix3f answer;
	answer.A11 = cos(radians);
	answer.A12 = 0;
	answer.A13 = sin(radians);
	answer.A21 = 0;
	answer.A22 = 1;
	answer.A23 = 0;
	answer.A31 = -sin(radians);
	answer.A32 = 0;
	answer.A33 = cos(radians);

	return answer;
}

Matrix3f Matrix3f::RotationZ(float _angle)
{
	float radians = PI / 180 * _angle;
	Matrix3f answer;
	answer.A11 = cos(radians);
	answer.A12 = -sin(radians);
	answer.A13 = 0;
	answer.A21 = sin(radians);
	answer.A22 = cos(radians);
	answer.A23 = 0;
	answer.A31 = 0;
	answer.A32 = 0;
	answer.A33 = 1;

	return answer;
}

Matrix3f Matrix3f::Scale3D(float dx)
{
	Matrix3f answer;
	answer.A11 = (float)dx / 100;
	answer.A12 = 0;
	answer.A13 = 0;
	answer.A21 = 0;
	answer.A22 = (float)dx / 100;
	answer.A23 = 0;
	answer.A31 = 0;
	answer.A32 = 0;
	answer.A33 = (float)dx / 100;

	return answer;
}
