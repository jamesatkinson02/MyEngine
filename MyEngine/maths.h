#pragma once
#include <iostream>

using namespace std;

namespace maths
{
	class vector3f
	{
	private:
		float m_x, m_y, m_z;
	public:
		vector3f(float x, float y, float z);
		vector3f(float scalar);
		vector3f& operator=(vector3f& r);
		vector3f operator+(vector3f& r);
		vector3f operator-(vector3f& r);
		vector3f& operator+=(vector3f& r);
		vector3f& operator-=(vector3f& r);
		vector3f& operator/=(vector3f& r);
		vector3f& operator/=(float scalar);
		vector3f operator/(vector3f& r);
		float length();
		void normalize();
		float dot(vector3f& r);
		vector3f cross(vector3f& r);
		float getX();
		float getY();
		float getZ();
		void setX(float x);
		void setY(float y);
		void setZ(float z);
		float& operator[](int index);
	};

	class matrix4f
	{
	public:
		float m_mat4D[4][4];
		matrix4f();
		void translate(vector3f& pos);
		void scale(float scale, vector3f& axis);
		void rotate(float angle, vector3f& axis);
	};

	vector3f mult(matrix4f& m, vector3f& r);
}

