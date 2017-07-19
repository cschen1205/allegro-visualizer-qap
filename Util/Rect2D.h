#ifndef _H_RECT_2D_H
#define _H_RECT_2D_H

#include <cmath>

/// <summary>Class that represent a rectangle on the 2D screen, the class is self explanable</summary>
class Rect2D
{
public:
	Rect2D();
	virtual ~Rect2D();

public:
	float Width() { return abs(right - left); }
	float Height() { return abs(bottom - top); }

public:
	float top;
	float bottom;
	float left;
	float right;
};
#endif