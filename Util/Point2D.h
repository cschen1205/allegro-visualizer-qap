#ifndef _H_POINT_2D_H
#define _H_POINT_2D_H

/// <summary>Class that represent a point on the 2D screen, the class is self explanable</summary>
class Point2D
{
public:
	Point2D();
	Point2D(float x, float y);
	virtual ~Point2D();
	Point2D(const Point2D& rhs);
	Point2D& operator=(const Point2D& rhs);

public:
	Point2D& operator+=(const Point2D& rhs);
	Point2D& operator-=(const Point2D& rhs);
	Point2D& operator*=(const float& val);
	Point2D& operator/=(const float& val);
	bool operator==(const Point2D& rhs);

	Point2D Normalize();
	float Length();

public:
	float GetX();
	float GetY();
	void SetX(float x);
	void SetY(float y);

private:
	float m_x;
	float m_y;
};

Point2D operator+(const Point2D& p1, const Point2D& p2);
Point2D operator-(const Point2D& p1, const Point2D& p2);
Point2D operator/(const Point2D& p1, const float& val);
Point2D operator*(const Point2D& p1, const float& val);
Point2D operator*(const float& val, const Point2D & p2);

#define Size2D Point2D
#endif