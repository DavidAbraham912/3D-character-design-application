#ifndef Quaternion_H
#define Quaternion_H
#include "Point.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include "vector.h"

class Quaternion
{
public:
	Quaternion() {};
	Quaternion(const Vector& n, float a);

public:
	const Quaternion Inverted() const;
	const Quaternion operator*(const Quaternion& q) const;
	const Vector operator*(const Vector& p) const;

public:
	float w;
	Vector v; // x, y, z
};


#endif