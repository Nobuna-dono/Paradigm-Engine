#ifndef _FVECTOR4_H_
#define _FVECTOR4_H_

#include <ParadigmDebug.h>
#include <Core/Math/UVector4.h>

using namespace std;
namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			struct FVector4
			{
				public:
					////////////////////////////////////////////////
					// STATIC DATA
					//____________________________________			
					/** A Vector3(0,0,0). */
					static const FVector4 Zero;
					/** A Vector3(0,0,0). */
					static const FVector4 One;
					/** A Vector3(0,1,0). */
					static const FVector4 Up;
					/** A Vector3(0,-1,0). */
					static const FVector4 Down;
					/** A Vector3(1,0,0). */
					static const FVector4 Right;
					/** A Vector3(-1,0,0). */
					static const FVector4 Left;
					/** A Vector3(0,0,1). */
					static const FVector4 Forward;
					/** A Vector3(0,0,-1). */
					static const FVector4 Backward;

				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________	
					FVector4(UVector4&& _vec);
					FVector4(const UVector4& _vec);
					FVector4(const FVector2& _vec, float _z = 0.f, float _w = 1.f);
					FVector4(const FVector3& _vec, float _w = 1.f);
					FVector4(float x = 0, float y = 0, float z = 0, float w = 1);
					~FVector4() = default;

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//____________________________________	
					/** Divide x,y and z by w */
					void Homogenize();

					/**Return true if each members of the two vectors are almost equal ( +|-  tolerance)*/
					inline bool Equal(const FVector4& other_vec, float tolerance = 0.0001f) const;

					/**Compute the dot product between this vector and the one  given*/
					float DotProduct(const FVector3&) const;

					/**Compute the dot product between this vector and the one  given*/
					inline float DotProduct(const FVector4& v4) const;

					/**Compute the Cross product between this vector and the one  given*/
					FVector4 CrossProduct(const FVector3& vect) const;
					/**Compute the Cross product between this vector and the one  given*/
					FVector4 CrossProduct(const FVector4& v4) const;

					/**Return the length of the vector and store it for future usages
					(optimised if used frequently (>10 times per seconds) else use Magnitude instead)*/
					float Magnitude_IOpt();

					/**Return the length of the vector*/
					inline float Magnitude() const;

					/**Return the square of the length of the vector*/
					inline float SqrMagnitude() const;

					/**Normalize the vector*/
					void Normalize();

					/**Return the vector normalized*/
					FVector4 Normalized() const;

					/**Rotate the vector by euler angles*/
					void Rotate(const float _pitch, const float _yaw, const float _roll);

					/**Rotate the vector by euler angles*/
					FVector4 Rotated(const float _pitch, const float _yaw, const float _roll);

					/**Return the distance between two points*/
					inline static float Distance(FVector4*, FVector4*);

					/**Return the square of distance between two points*/
					inline static float SqrDistance(FVector4*, FVector4*);

					/**Return direction vector from euler angles in degree*/
					//static FVector4 RotationToDir(FVector3& dir);

					/**Return euler angles in degree from direction vector*/
					static FVector3 DirToRotation(FVector4& rot);

					/**Return interpolated point between "from" and "to"*/
					static FVector4 Lerp(FVector4& from, FVector4& to, float speed);

					/**Return direction vector from two points*/
					static FVector4 LookDir(FVector4& pos, FVector4& target);

					/**Return euler angles in degree from two points*/
					static FVector3 LookRotation(FVector4& pos, FVector4& target);

				public:
					////////////////////////////////////////////////
					// OPERATORS
					//____________________________________	

					inline operator FVector2();
					inline operator FVector3();
					inline operator UVector4();

					void operator*=(float _val);
					void operator/=(float _val);
					void operator+=(const FVector2& _val);
					void operator+=(const FVector3& _val);
					void operator+=(const FVector4& _val);
					void operator-=(const FVector2& _val);
					void operator-=(const FVector3& _val);
					void operator-=(const FVector4& _val);
					FVector4 operator*(float _val);
					FVector4 operator/(float _val);
					FVector4 operator+(const FVector3& _val) const;
					FVector4 operator+(const FVector4& _val) const;
					FVector4 operator-(const FVector3& _val) const;
					FVector4 operator-(const FVector4& _val) const;
					FVector4 operator-() const;
					float operator,(const FVector3& _val) const;
					float operator,(const FVector4& _val) const;

					void operator=(const FVector2& _val);
					void operator=(const FVector3& _val);
					void operator=(const UVector4& _val);

					bool operator==(const FVector2& _val) const;
					bool operator==(const FVector3& _val) const;
					bool operator==(const FVector4& _val) const;

					bool operator!=(const FVector2& _val) const;
					bool operator!=(const FVector3& _val) const;
					bool operator!=(const FVector4& _val) const;

					bool operator<(const FVector3& _val) const;
					bool operator<(const FVector4& _val) const;
					bool operator>(const FVector3& _val) const;
					bool operator>(const FVector4& _val) const;
					bool operator>=(const FVector3& _val) const;
					bool operator>=(const FVector4& _val) const;
					bool operator<=(const FVector3& _val) const;
					bool operator<=(const FVector4& _val) const;

				public:
					////////////////////////////////////////////////
					// DATA
					//____________________________________								
					float x{ 0 };
					float y{ 0 };
					float z{ 0 };
					float w{ 1 };
					float Norm{ 0 };
			};

			FVector4 operator*(float _val, const FVector4& _vec);
			FVector4 operator/(float _val, const FVector4& _vec);

			////////////////////////////////////////////////
			// FSTRING UTILITY
			//____________________________________
			FString operator+(const FString& _str, const FVector4& _vec);
			FString operator+(const FVector4& _vec, FString& _str);
			FString operator+(const char* _str, const FVector4& _vec);
			FString operator+(const FVector4& _vec, const char* _str);
			void operator+=(FString& _str, const FVector4& _vec);
			void operator+=(const FVector4& _vec, FString& _str);

			////////////////////////////////////////////////
			// IOSTREAM UTILITY
			//____________________________________
			std::ostream& operator<<(std::ostream& _os, const FVector4& _val);
			std::istream& operator>>(std::istream& _is, FVector4& _val);
		}
	}
}
//#include <Core/Math/FVector4.inl>
typedef ParadigmEngine::Core::Math::FVector4 FVector4;

#pragma region UnitTests
#include <ParadigmDebug.h>

UNIT_TEST_CLASS(Core::Math::FVector4, Core::Math::FVector4::zero)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector4::zero) UNIT_TEST_EXPECTEDRESULT(0.f)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector4{ 62.5767f,17.6012f,-3.53374f, 1.f }) UNIT_TEST_EXPECTEDRESULT(0.f)
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector4::zero) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4::zero)
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector4{ 62.5767f,17.6012f,-3.53374f, 1.f }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4::zero)
UNIT_TEST_COMPARE_scalarS(Magnitude) UNIT_TEST_EXPECTEDRESULT(0.f)
UNIT_TEST_COMPARE(Normalized) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4::zero)

UNIT_TEST_CLASS(Core::Math::FVector4, 62.5767f, 17.6012f, -3.53374f, 1.f)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector4{ -29.5828f,80.1104f,65.411f, 1.f }) UNIT_TEST_EXPECTEDRESULT(-672.30029542f)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector4{ -99.7485f,13.2945f,-61.1411f, 1.f }) UNIT_TEST_EXPECTEDRESULT(-5791.876055836f)
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector4{ -29.5828f,80.1104f,65.411f, 1.f }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4{ 1434.4f, -3988.67f, 5533.74f, 1.f })
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector4{ -99.7485f,13.2945f,-61.1411f, 1.f }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4{ -1029.18f, 4178.49f, 2587.62f, 1.f })
UNIT_TEST_COMPARE_scalarS(Magnitude) UNIT_TEST_EXPECTEDRESULT(65.1009f)
UNIT_TEST_COMPARE(Normalized) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4{ 0.961226f, 0.270368f, -0.0542809f, 1.f })

UNIT_TEST_CLASS(Core::Math::FVector4, -29.5828f, 80.1104f, 65.411f, 1.f)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector4{ -29.5828f, 80.1104f, 65.411f, 1.f }) UNIT_TEST_EXPECTEDRESULT(11571.417165f)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector4{ -99.7485f,13.2945f,-61.1411f, 1.f }) UNIT_TEST_EXPECTEDRESULT(16.5671465f)
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector4{ -29.5828f, 80.1104f, 65.411f, 1.f }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4::zero)
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector4{ -99.7485f,13.2945f,-61.1411f, 1.f }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4{ -5767.64f, -8333.37f, 7597.6f, 1.f })
UNIT_TEST_COMPARE_scalarS(Magnitude) UNIT_TEST_EXPECTEDRESULT(107.571f)
UNIT_TEST_COMPARE(Normalized) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4{ -0.275008f, 0.744724f, 0.608076f, 1.f })

UNIT_TEST_CLASS(Core::Math::FVector4, 1000.f, 0.f, 0.f, 1.f)
UNIT_TEST_COMPARE(Rotated, PI / 2, 0.f, 0.f) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4{ 1000.f, 0.f, 0.f, 1.f })
UNIT_TEST_COMPARE(Rotated, 0.f, PI / 2, 0.f) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4{ 0.f, 0.f, -1000.f, 1.f })
UNIT_TEST_COMPARE(Rotated, 0.f, 0.f, PI / 2) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4{ 0.f, 1000.f, 0.f, 1.f })
UNIT_TEST_COMPARE(Rotated, PI / 2, PI / 2, PI / 2) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4{ 1000.f, 0.f, 0.f, 1.f })

UNIT_TEST_CLASS(Core::Math::FVector4,  0.f, 1000.f, 0.f, 1.f)
UNIT_TEST_COMPARE(Rotated, PI / 2, 0.f, 0.f) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector4{ 0.f, 0.f, 1000.f, 1.f })

#pragma endregion
#endif