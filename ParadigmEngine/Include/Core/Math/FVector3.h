#ifndef _FVECTOR3_H_
#define _FVECTOR3_H_

#include <ParadigmDebug.h>
#include <Core/Math/UVector3.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			/** A vector3 structure with mathematique functionality. */
			struct FVector3
			{
				public:
					////////////////////////////////////////////////
					// STATIC DATA
					//____________________________________			
					/** A Vector3(0,0,0). */
					static const UVector3 Zero;
					/** A Vector3(1,1,1). */
					static const UVector3 One;
					/** A Vector3(0,1,0). */
					static const UVector3 Up;
					/** A Vector3(0,-1,0). */
					static const UVector3 Down;
					/** A Vector3(1,0,0). */
					static const UVector3 Right;
					/** A Vector3(-1,0,0). */
					static const UVector3 Left;
					/** A Vector3(0,0,1). */
					static const UVector3 Forward;
					/** A Vector3(0,0,-1). */
					static const UVector3 Backward;

				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________	

					FVector3(UVector3&& _vec);
					FVector3(const FVector2& _vec, float _z = 0);
					FVector3(const UVector3& _vec);
					FVector3(const FVector4& _vec);
					FVector3(float _x = 0, float _y = 0, float _z = 0);
					~FVector3() = default;


				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//____________________________________	
					/**Compute the dot product between this vector and the one  given*/
					float DotProduct(const FVector3&) const;
					/**Compute the dot product between this vector and the one  given*/
					inline float DotProduct(const FVector4& v4) const { return DotProduct(FVector3(v4)); };

					/**Compute the Cross product between this vector and the one  given*/
					FVector3 CrossProduct(const FVector3& vect) const;
					/**Compute the Cross product between this vector and the one  given*/
					inline FVector3 CrossProduct(const FVector4& v4) const { return CrossProduct(FVector3(v4)); };

					/**Return the length of the vector and store it for future usages
					(optimised if used frequently (>10 times per seconds) else use Magnitude instead)*/
					float Magnitude_IOpt() const;

					/**Return the length of the vector*/
					inline float Magnitude() const; 

					/**Return the square of the length of the vector*/
					inline float SqrMagnitude() const;

					/**Normalize the vector*/
					void Normalize();

					/**Return the vector normalized*/
					FVector3 Normalized() const;

					/**Return true if each members of the two vectors are almost equal ( +|-  tolerance)*/
					inline bool Equal(const FVector3& other_vec, float tolerance = 0.0001f) const;

					/**Return the distance between two points*/
					inline static float Distance(FVector3*, FVector3*);

					/**Return the square of distance between two points*/
					inline static float SqrDistance(FVector3*, FVector3*);

					/**Return direction vector from euler angles in degree*/
					//static FVector3 RotationToDir(FVector3& dir);

					/**Return euler angles in degree from direction vector*/
					static FVector3 DirToRotation(FVector3& rot);

					//void homogenize();	

					/**Return interpolated point between "from" and "to"*/
					static FVector3 Lerp(FVector3& from, FVector3& to, float speed);

					/**Return direction vector from two points*/
					static FVector3 LookDir(FVector3& pos, FVector3& target);

					/**Return euler angles in degree from two points*/
					static FVector3 LookRotation(FVector3& pos, FVector3& target);

					/**Return angle in degree between two vectors*/
					static float Angle(const FVector3& _v1, const FVector3& _v2);


				public:
					////////////////////////////////////////////////
					// OPERATORS
					//____________________________________	

					operator UVector3();
					operator FVector2();
					operator FVector4();
					operator FString();

					void operator*=(float _val);
					void operator/=(float _val);
					void operator+=(const FVector3& _val);
					void operator-=(const FVector3& _val);
					FVector3 operator*(float _val) const;
					FVector3 operator*(const FQuaternion& _val) const;
					FVector3 operator*(const FVector3& _val) const;
					FVector3 operator/(const FVector3& _val) const;
					FVector3 operator/(float _val) const;
					FVector3 operator+(const FVector3& _val) const;
					FVector3 operator-(const FVector3& _val) const;
					FVector3 operator-() const;
					float operator,(const FVector3& _val) const;

					void operator=(const FVector2& _val);
					void operator=(const UVector3& _val);
					void operator=(const FVector4& _val);

					bool operator==(const FVector2& _val) const;
					bool operator==(const FVector3& _val) const;
					bool operator==(const FVector4& _val) const;

					bool operator!=(const FVector2& _val) const;
					bool operator!=(const FVector3& _val) const;
					bool operator!=(const FVector4& _val) const;

					bool operator<(const FVector3& _val) const;
					bool operator>(const FVector3& _val) const;
					bool operator>=(const FVector3& _val) const;
					bool operator<=(const FVector3& _val) const;


				public:
					////////////////////////////////////////////////
					// DATA
					//____________________________________
					
					float x;
					float y;
					float z;
					mutable float Norm{ 0 };
			};

			FVector3 operator*(float _val, const FVector3& _vec);
			FVector3 operator/(float _val, const FVector3& _vec);
			
			////////////////////////////////////////////////
			// IOSTREAM UTILITY
			//____________________________________
			std::ostream& operator<<(std::ostream& _os, const FVector3& _vec);
			std::istream& operator>>(std::istream& _is, FVector3& _vec);
		}
	}
}
typedef ParadigmEngine::Core::Math::UVector3 UVector3;
typedef ParadigmEngine::Core::Math::FVector3 FVector3;

////////////////////////////////////////////////
// FSTRING UTILITY
//____________________________________
FString operator+(const FString& _str, const FVector3& _vec);
FString operator+(const FVector3& _vec, FString& _str);
FString operator+(const char* _str, const FVector3& _vec);
FString operator+(const FVector3& _vec, const char* _str);
void operator+=(FString& _str, const FVector3& _vec);
void operator+=(const FVector3& _vec, FString& _str);

//#include <Core\Math\FVector3.inl>


#pragma region UnitTests

UNIT_TEST_CLASS(Core::Math::FVector3, 0.f)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector3{ 0.f }) UNIT_TEST_EXPECTEDRESULT(0.f)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector3{ 62.5767f,17.6012f,-3.53374f }) UNIT_TEST_EXPECTEDRESULT(0.f)
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector3{ 0.f }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector3{ 0.f })
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector3{ 62.5767f,17.6012f,-3.53374f }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector3{ 0.f })
UNIT_TEST_COMPARE_scalarS(Magnitude) UNIT_TEST_EXPECTEDRESULT(0.f)
UNIT_TEST_COMPARE(Normalized) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector3{ 0.f })

UNIT_TEST_CLASS(Core::Math::FVector3, 62.5767f, 17.6012f, -3.53374f)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector3{ -29.5828f,80.1104f,65.411f }) UNIT_TEST_EXPECTEDRESULT(-672.300f)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector3{ -99.7485f,13.2945f,-61.1411f }) UNIT_TEST_EXPECTEDRESULT(-5791.87f)
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector3{ -29.5828f,80.1104f,65.411f }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector3{ 1434.4f, -3988.67f, 5533.74f })
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector3{ -99.7485f,13.2945f,-61.1411f }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector3{ -1029.18f, 4178.49f, 2587.62f })
UNIT_TEST_COMPARE_scalarS(Magnitude) UNIT_TEST_EXPECTEDRESULT(65.1009f)
UNIT_TEST_COMPARE(Normalized) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector3{ 0.961226f, 0.270368f, -0.0542809f })

UNIT_TEST_CLASS(Core::Math::FVector3, -29.5828f, 80.1104f, 65.411f)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector3{ -29.5828f, 80.1104f, 65.411f }) UNIT_TEST_EXPECTEDRESULT(11571.4f)
UNIT_TEST_COMPARE_scalarS(DotProduct, Core::Math::FVector3{ -99.7485f,13.2945f,-61.1411f }) UNIT_TEST_EXPECTEDRESULT(16.5671f)
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector3{ -29.5828f, 80.1104f, 65.411f }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector3{ 0 })
UNIT_TEST_COMPARE(CrossProduct, Core::Math::FVector3{ -99.7485f,13.2945f,-61.1411f }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector3{ -5767.64f, -8333.37f, 7597.6f })
UNIT_TEST_COMPARE_scalarS(Magnitude) UNIT_TEST_EXPECTEDRESULT(107.571f)
UNIT_TEST_COMPARE(Normalized) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector3{ -0.275008f, 0.744724f, 0.608076f })

#pragma endregion
#endif