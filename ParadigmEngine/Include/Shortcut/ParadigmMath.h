#ifndef _PARADIGMMATH_H_
#define _PARADIGMMATH_H_

#include <Core/Math/FVector2.h>
#include <Core/Math/FVector3.h>
#include <Core/Math/FVector4.h>
#include <Core/Math/FMatrix4.h>
#include <Core/Math/FQuaternion.h>
#include <cmath>
#include <iomanip>

UNIT_TEST_ISTRUE ( Equalf,0.00001f,0.00001f,0.00001f)
UNIT_TEST_ISFALSE (Equalf, 0.00001f, 0.000015f, 0.000005f);
UNIT_TEST_ISTRUE (Equalfu, 0.000015682f, 0.000015689f, 4)
UNIT_TEST_ISFALSE (Equalfu, 0.00001f, 0.000015f, 4);
UNIT_TEST_ISTRUE (Equalfu, 0.f, 0.000015f, 4);

#define PI				3.14159265358979323846f // pi
#define RAD90			1.57079633
/** Multiply degree value by this to convert it to radiant value*/
#define DEG_TO_RAD		0.01745329251994329576f //<=> PI / 180.0f				
/** Multiply radiant value by this to convert it to degree value*/
#define RAD_TO_DEG      57.2957795130823208767f //<=> 180.f / PI				

/** Convert degrees value to radiant value*/
#define TO_RADIAN(X)	X * DEG_TO_RAD

/** Convert radiant value to degrees value*/
#define TO_DEGREE(X)	X * RAD_TO_DEG

inline bool Equalf(float a, float b, float tolerance = 0.00001f)
{
	return std::abs(a-b) < tolerance;
}
template<typename T>
constexpr inline T Pow(T _a, T _b)
{
	if (_b == 0)
		return 1;
	return _a * (_b > 1 ? Pow(_a, _b - 1) : 1);
}

inline bool Equalfu(float a, float b, unsigned int mantiseSise = 4)
{
	std::stringstream sa, sb;
	if (Equalf(a, 0.f) && Equalf(b, 0.f)) { return true; }
	sa << std::setprecision(mantiseSise) << a;
	sb << std::setprecision(mantiseSise) <<  b;
	//if (a == 0.f && b == 0.f) return true;
	//int pow = 1;
	//for (unsigned int i = 1; i < mantiseSise; ++i) { pow * 10; }
	//while (a < pow && b < pow) { a * 10; b * 10; }
	return sa.str() == sb.str();
}

static float Abs(float _value)
{
	return fabs(_value);
}
static FVector2 Abs(const FVector2& _value)
{
	return { fabs(_value.x),fabs(_value.y)};
}
static FVector3 Abs(const FVector3& _value)
{
	return { fabs(_value.x),fabs(_value.y), fabs(_value.z) };
}
static FVector4 Abs(const FVector4& _value)
{
	return { fabs(_value.x),fabs(_value.y), fabs(_value.z), fabs(_value.w) };

}

#endif // _MATH_H_