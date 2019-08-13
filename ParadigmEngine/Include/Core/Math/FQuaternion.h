#ifndef _FQUATERNION_H_
#define _FQUATERNION_H_

#include <Core/Math/FVector3.h>
#include <Core/Math/UQuaternion.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			struct FQuaternion
			{
				public:
					////////////////////////////////////////////////
					// STATIC DATA
					//____________________________________			
					/** A Quaternion identity(1,0,0,0). */
					static const UQuaternion Identity;


				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________	
					FQuaternion(UQuaternion&& _quat);
					FQuaternion(const UQuaternion& _quat);
					FQuaternion(float _w = 1, float _x = 0, float _y = 0, float _z = 0);
					FQuaternion(float _w, FVector3);
					~FQuaternion() = default;


				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//____________________________________	
					/** Returns the corresponding Matrix*/
					FMatrix4 ToMatrix4() const;
					/** Returns the corresponding transposed Matrix*/
					FMatrix4 ToTransposedMatrix4() const;

					/** Compute and Returns the Conjugate of the quaternion */
					FQuaternion Conjugate() const;

					FQuaternion Combine(FQuaternion&) const;

					/** Compute and Returns the dot product between tow quaternions*/
					float DotProduct(const FQuaternion& _qua) const;

					/** Scale the quaternion's length to 1*/
					void Normalize();

					//Getters
					/** Returns the correspondings angles of rotation following the 3 axes in a Vector 3*/
					FVector3 ToEulerAngles() const;

					/** Compute and Returns the Yaw value in Radian*/
					float Yaw() const;

					/** Compute and Returns the Pitch value in Radian*/
					float Pitch() const;

					/** Compute and Returns the Roll value in Radian*/
					float Roll() const;

					/** Returns */
					FQuaternion GetInvert() const;

					/** Retrurns the quaternion normalized*/
					FQuaternion GetNormalized() const;

					/** Returns the imagilary part of the quaternion in a Vector3*/
					FVector3 GetImaginary() const;

					/** Returns the Real part of the quaternion in a float*/
					float GetReal() const;

					/** Returns the norm of the quaternion*/
					float GetLength() const;

					/** Returns the square of the norm of the quaternion*/
					float GetsqLength() const;

					/** Returns a direction representing the rotation*/
					FVector3 ToDirection() const;

					//Statics
					/** Returns a quaternion representing the I axe */
					static const FQuaternion I(float _rot = 0);
					/** Returns a quaternion representing the J axe */
					static const FQuaternion J(float _rot = 0);
					/** Returns a quaternion representing the K axe */
					static const FQuaternion K(float _rot = 0);

					/**Return angle in degree between two rotations*/
					static float Angle(const FQuaternion& _q1, const FQuaternion& _q2);

					/**	Create a quaternion from a theta angle (interpretated (theta/2)) and a vectorial part*/
					static FQuaternion FromAngleAxis(float _thetaAngle, const FVector3& _vec);

					/**	Create a quaternion from Euler angles in radiants*/
					static FQuaternion FromEulerAngles(const float _pitch, const float _yaw, const float _roll);
					inline static FQuaternion FromEulerAngles(const FVector3& _angles) { return FromEulerAngles(_angles.x, _angles.y, _angles.z); };

					/** Retruns a quaternions lineary interpolated beteween "_first" and "_second" */
					static FQuaternion Lerp(const FQuaternion& _first, const FQuaternion& _second, float _ratio);

					/** Returns a direction representing a specified rotation*/
					inline static FVector3 ToDirection(const FQuaternion& _quat) { return _quat.ToDirection(); };

					/** Returns a quaternion representing a rotation to specified direction*/
					static FQuaternion FromDirection_IOpt(const FVector3& _direction);

					/** Returns a quaternion representing a rotation to specified direction and stabilize with up*/
					static FQuaternion FromDirection(const FVector3& _direction, const FVector3& _up = FVector3::Up);


				public:
					////////////////////////////////////////////////
					// OPERATORS
					//____________________________________	

					operator UQuaternion();

					void operator=(const UQuaternion& _val);

					void operator*=(const FQuaternion& _quat);
					void operator+=(const FQuaternion& _quat);
					void operator-=(const FQuaternion& _quat);
					bool operator==(const FQuaternion& _quat) const;
					bool operator!=(const FQuaternion& _quat) const;
					FQuaternion operator+(const FQuaternion& b) const;
					FQuaternion operator-(const FQuaternion& b) const;
					FQuaternion operator*(const FQuaternion& b) const;
					FQuaternion operator/(const FQuaternion& b) const;
					inline FQuaternion Mult(const FQuaternion& b) const { return *this * b; };
					FVector3 operator*(const FVector3& b) const;
					FQuaternion operator*(float _value) const;
					FQuaternion operator/(float _value);
					FQuaternion operator-() const;


					public:
						////////////////////////////////////////////////
						// DATA
						//____________________________________

						float w, x, y, z;
			};

			////////////////////////////////////////////////
			// IOSTREAM UTILITY
			//____________________________________
			std::ostream& operator<<(std::ostream& stream, const FQuaternion&);
		}
	}
}
typedef ParadigmEngine::Core::Math::FQuaternion FQuaternion;

////////////////////////////////////////////////
// FSTRING UTILITY
//____________________________________
FString operator+(const FString& _str, const FQuaternion& _vec);
FString operator+(const FQuaternion& _vec, FString& _str);
FString operator+(const char* _str, const FQuaternion& _vec);
FString operator+(const FQuaternion& _vec, const char* _str);
void operator+=(FString& _str, const FQuaternion& _vec);
void operator+=(const FQuaternion& _vec, FString& _str);


#pragma region UnitTests

UNIT_TEST_CLASS(Core::Maths::FQuaternion, 5.67f, 1.23f, 2.34f, 3.45f)
UNIT_TEST_COMPARE_scalarS(DotProduct, { 4, 3.9f, -1.f, 3.f }) UNIT_TEST_EXPECTEDRESULT(35.387f)
UNIT_TEST_COMPARE(ToMatrix4) UNIT_TEST_EXPECTEDRESULT(Core::Maths::FMatrix4{ { -33.75620f,-33.36660f,35.02260f,0.00000f, 44.87940f,-25.83080f,2.19780f,0.00000f, -18.04860f,30.09420f,-12.97700f,0.00000f, 0.00000f,0.00000f,0.00000f,1.00000f } })
UNIT_TEST_COMPARE(Conjugate) UNIT_TEST_EXPECTEDRESULT(Core::Maths::FQuaternion{ 5.67f, -1.23f, -2.34f, -3.45f })
//UNIT_TEST_COMPARE(ToEulerAngles) UNIT_TEST_EXPECTEDRESULT(Core::Maths::FVector3{ -0.0592298f, 0.7562257f, 1.1167754f })
UNIT_TEST_COMPARE(GetInvert) UNIT_TEST_EXPECTEDRESULT(Core::Maths::FQuaternion{ 0.11109f, -0.0240988f, -0.0458465f, -0.0675942f, })
UNIT_TEST_COMPARE(GetNormalized) UNIT_TEST_EXPECTEDRESULT(Core::Maths::FQuaternion{ 5.67f, 1.23f, 2.34f, 3.45f } / 7.14422f)
UNIT_TEST_COMPARE(Mult, { 4, 3.9f, -1.f, 3.f }) UNIT_TEST_EXPECTEDRESULT(Core::Maths::FQuaternion{ 9.873f, 37.503f, 13.455f, 20.454f })
UNIT_TEST_COMPARE_scalarS(GetLength) UNIT_TEST_EXPECTEDRESULT(7.14422f)
UNIT_TEST_END_CLASS

//UNIT_TEST_COMPARE(Core::Maths::FQuaternion::CreateFromEulerAngles, 45.444f, 30.333f, 75.555f) UNIT_TEST_EXPECTEDRESULT(Core::Maths::FQuaternion{ 0.6630749f, 0.5402128f, -0.4273784f, -0.2930009f })
UNIT_TEST_COMPARE(Core::Maths::FQuaternion::FromAngleAxis, 60.f, { 1.f,1.f,1.f }) UNIT_TEST_EXPECTEDRESULT(Core::Maths::FQuaternion{ 0.9f, 0.3f, 0.3f, 0.3f })


#pragma endregion
#endif // !_FQUATERNION_H_