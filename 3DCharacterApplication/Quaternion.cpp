#include "quaternion.h"

#include <cmath>

Quaternion::Quaternion(const Vector& n, float a)
{
	// a sẽ là góc tính bằng độ.
	//chúng ta cần chuyển nó sang radian
	// 360 degrees == 2pi radians
	a = a / 360 * (float)M_PI * 2;
	w = cos(a / 2);
	v = n * sin(a / 2);
}
//lấy quaternion nghịch đảo
const Quaternion Quaternion::Inverted() const
{
	Quaternion q;
	q.w = w;
	q.v = -v;
	return q;
}
//nhấn 2 quaternion với nhau dùng cho xoay theo 2 trục cùng 1 lúc
//nó sẽ kết hợp 2 trục và 2 góc xoay lại thành 1 để xoay
//nên nhớ trục nào muốn xoay trước thì nhân sau,nó xoay theo thứ tự từ trục nhân sau cùng
//tới trục nhân đầu tiên
const Quaternion Quaternion::operator*(const Quaternion& q) const
{
	Quaternion r;

	r.w = w*q.w + v.Dot(q.v);
	r.v = v*q.w + q.v*w + v.Cross(q.v);

	return r;
}
//nhấn quaternion với vector để xoay vector đó
const Vector Quaternion::operator*(const Vector& V) const
{
	Quaternion p;
	p.w = 0;
	p.v = V;

	// Could do it this way:
	/*
	const Quaternion& q = (*this);
	return (q * p * q.Inverted()).v;
	*/

	// But let's optimize it a bit instead.
	Vector vcV = v.Cross(V);
	return V + vcV*(2 * w) + v.Cross(vcV) * 2;
}
