#include "maths.h"
#include <cassert>

using namespace maths;

vector3f::vector3f(float x, float y, float z) : m_x{ x }, m_y{ y }, m_z{ z }
{

}

vector3f::vector3f(float scalar) : m_x{ scalar }, m_y{ scalar }, m_z{ scalar }
{
}

vector3f& vector3f::operator=(vector3f& r)
{
	m_x = r.getX();
	m_y = r.getY();
	m_z = r.getZ();
	return *this;
}

vector3f vector3f::operator+(vector3f& r)
{
	return vector3f(m_x + r.getX(), m_y + r.getY(), m_z + r.getZ());
}

vector3f vector3f::operator-(vector3f& r)
{
	return vector3f(m_x - r.getX(), m_y - r.getY(), m_z - r.getZ());
}

vector3f& vector3f::operator+=(vector3f& r)
{
	m_x += r.getX();
	m_y += r.getY();
	m_z += r.getZ();
	return *this;
}
vector3f& vector3f::operator-=(vector3f& r)
{
	m_x -= r.getX();
	m_y -= r.getY();
	m_z -= r.getZ();
	return *this;
}

vector3f vector3f::operator/(vector3f& r)
{
	return vector3f(m_x / r.getX(), m_y / r.getY(), m_z / r.getZ());
}

vector3f& vector3f::operator/=(vector3f& r)
{
	m_x /= r.getX();
	m_y /= r.getY();
	m_z /= r.getZ();
	return *this;
}
vector3f& vector3f::operator/=(float scalar)
{
	m_x /= scalar;
	m_y /= scalar;
	m_z /= scalar;
	return *this;
}

float vector3f::length()
{
	return sqrtf((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
}

void vector3f::normalize()
{
	m_x /= length();
	m_y /= length();
	m_z /= length();
}

float vector3f::dot(vector3f& r)
{
	return m_x * r.getX() + m_y * r.getY() + m_z * r.getZ();
}

vector3f vector3f::cross(vector3f& r)
{
	float cx = m_y * r.getZ() - m_z * r.getY();
	float cy = m_z * r.getX() - m_x * r.getZ();
	float cz = m_x * r.getY() - m_y * r.getX();

	return vector3f(cx, cy, cz);
}

float& vector3f::operator[](int index)
{
	assert(index < 3 && "Index out of bounds!\n");
	switch (index)
	{
	case 0:
		return m_x;
		break;
	case 1:
		return m_y;
		break;
	case 2:
		return m_z;
		break;
	default:
		break;
	}
}

float vector3f::getX()
{
	return m_x;
}

float vector3f::getY()
{
	return m_y;
}

float vector3f::getZ()
{
	return m_z;
}

void vector3f::setX(float x)
{
	m_x = x;
}

void vector3f::setY(float y)
{
	m_y = y;
}

void vector3f::setZ(float z)
{
	m_z = z;
}

matrix4f::matrix4f()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == i)
				m_mat4D[i][j] = 1.0f;
			else
				m_mat4D[i][j] = 0.0f;
		}
	}
}

void matrix4f::translate(vector3f& pos)
{
	for (int i = 0; i < 3; i++)
	{
		m_mat4D[i][3] = pos[i];
	}
}

void matrix4f::scale(float scale, vector3f& axis)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == i)
			{
				m_mat4D[i][j] = scale * axis[i];
			}
		}
	}
}

void matrix4f::rotate(float angle, vector3f& axis)
{
	//TODO: Learn rotation matrices lol
}

vector3f maths::mult(matrix4f& m, vector3f& r)
{
	vector3f vec(0.0f);
	for (int rows = 0; rows < 3; rows++)
	{
		for (int cols = 0; cols < 4; cols++)
		{
			vec[rows] += r[rows] * m.m_mat4D[rows][cols];
		}
	}

	return vec;
}
