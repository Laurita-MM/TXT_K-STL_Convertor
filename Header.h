#pragma once
struct Coord
{
	double x, y, z;

	Coord() {
		x = y = z = 0;
	}

	Coord(double _x, double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}


};