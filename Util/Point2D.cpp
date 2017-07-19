#include "Point2D.h"
#include <cassert>
#include <cmath>

Point2D::Point2D()
{
	m_x=0;
	m_y=0;
}

Point2D::Point2D(const Point2D& rhs)
{
	m_x=rhs.m_x;
	m_y=rhs.m_y;
}

Point2D::Point2D(float x, float y)
{
	m_x=x;
	m_y=y;
}

Point2D::~Point2D()
{

}

Point2D& Point2D::operator=(const Point2D& rhs)
{
	m_x=rhs.m_x;
	m_y=rhs.m_y;

	return *this;
}

Point2D& Point2D::operator+=(const Point2D& rhs)
{
	m_x+=rhs.m_x;
	m_y+=rhs.m_y;

	return *this;
}

Point2D& Point2D::operator-=(const Point2D& rhs)
{
	m_x-=rhs.m_x;
	m_y-=rhs.m_y;

	return *this;
}

Point2D& Point2D::operator*=(const float& val)
{
	m_x*=val;
	m_y*=val;

	return *this;
}

Point2D& Point2D::operator/=(const float& val)
{
	assert(val!=0.0f);

	m_x/=val;
	m_y/=val;

	return *this;
}

bool Point2D::operator==(const Point2D& rhs)
{
	if(m_x!=rhs.m_x)
	{
		return false;
	}

	if(m_y!=rhs.m_y)
	{
		return false;
	}

	return true;
}

Point2D Point2D::Normalize()
{
	float d=Length();
	assert(d!=0.0f);

	float x=m_x / d;
	float y=m_y / d;

	return Point2D(x, y);
}

float Point2D::Length()
{
	return sqrt(m_x * m_x + m_y * m_y);
}

Point2D operator+(const Point2D& p1, const Point2D& p2)
{
	Point2D p=p1;
	p+=p2;

	return p;
}

Point2D operator-(const Point2D& p1, const Point2D& p2)
{
	Point2D p=p1;
	p-=p2;

	return p;
}

Point2D operator*(const Point2D& p1, const float & val)
{
	Point2D p=p1;
	p*=val;

	return p;
}

Point2D operator*(const float& val, const Point2D& p2)
{
	Point2D p=p2;
	p*=2;

	return p;
}

Point2D operator/(const Point2D& p1, const float & val)
{
	Point2D p=p1;
	p/=val;

	return p;
}

float Point2D::GetX()
{
	return m_x;
}

float Point2D::GetY()
{
	return m_y;
}

void Point2D::SetX(float x)
{
	m_x=x;
}

void Point2D::SetY(float y)
{
	m_y=y;
}
