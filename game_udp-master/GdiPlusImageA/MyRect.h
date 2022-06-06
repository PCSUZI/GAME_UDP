#pragma once

class MyRect
{
public:
	static bool Collision(int x, int y, int rect_X, int rect_Y, int rect_width, int rect_height)
	{
		if ((rect_X) <= x &&
			(rect_X + rect_width) > x &&
			(rect_Y) <= y &&
			(rect_Y + rect_height) > y) return true;

		else return false;
	}
};