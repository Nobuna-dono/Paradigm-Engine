#ifndef _FVECTOR2_H_
#define _FVECTOR2_H_

#include <ParadigmDebug.h>
#include <Core/Math/UVector2.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			/** A vector2 structure with mathematique functionality. */
			struct FVector2
			{
				public:
					////////////////////////////////////////////////
					// STATIC DATA
					//____________________________________			
					/** A Vector2(0,0). */
					static const FVector2 Zero;
					/** A Vector2(0,1). */
					static const FVector2 Up;
					/** A Vector2(0,-1). */
					static const FVector2 Down;
					/** A Vector2(1,0). */
					static const FVector2 Right;
					/** A Vector2(-1,0). */
					static const FVector2 Left;

				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________	
					FVector2(UVector2&& _vec2);
					FVector2(const UVector2& _vec2);
					FVector2(float x = 0, float y = 0);
					~FVector2() = default;


				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//____________________________________	
					/**Compute the dot product between this vector and the one  given*/
					float DotProduct(const FVector2&) const;

					/**Return the length of the vector and store it for future usages
					(optimised if used frequently (>10 times per seconds) else use Magnitude instead)*/
					float Magnitude_IOpt();

					/**Return the length of the vector*/
					float Magnitude() const;

					/**Return the square of the length of the vector*/
					float SqrMagnitude() const;

					/**Normalize the vector*/
					void Normalize();

					/**Return the vector with normalized*/
					FVector2 Normalized();


				public:
					////////////////////////////////////////////////
					// OPERATORS
					//____________________________________	

					inline operator UVector2();			
					inline operator FVector3();
					inline operator FVector4();

					void operator*=(float _val);
					void operator/=(float _val);
					void operator+=(const FVector2& _val);
					void operator-=(const FVector2& _val);
					FVector2 operator*(float _val);
					FVector2 operator/(float _val);
					FVector2 operator+(const FVector2& _val) const;
					FVector2 operator-(const FVector2& _val) const;
					FVector2 operator-() const;
					float operator,(const FVector2& _val) const;

					void operator=(const UVector2& _val);
					void operator=(const FVector3& _val);
					void operator=(const FVector4& _val);

					bool operator==(const FVector2& _val) const;
					bool operator==(const FVector3& _val) const;
					bool operator==(const FVector4& _val) const;

					bool operator!=(const FVector2& _val) const;
					bool operator!=(const FVector3& _val) const;
					bool operator!=(const FVector4& _val) const;

					bool operator<(const FVector2& _val) const;
					bool operator>(const FVector2& _val) const;
					bool operator>=(const FVector2& _val) const;
					bool operator<=(const FVector2& _val) const;


				public:
					////////////////////////////////////////////////
					// DATA
					//____________________________________						

					float x;
					float y;
					float Norm{ 0 };
			};
			FVector2 operator*(float _val, const FVector2& _vec);
			FVector2 operator/(float _val, const FVector2& _vec);

			////////////////////////////////////////////////
			// FSTRING UTILITY
			//____________________________________
			FString operator+(const FString& _str, const FVector2& _vec);
			FString operator+(const FVector2& _vec, FString& _str);
			FString operator+(const char* _str, const FVector2& _vec);
			FString operator+(const FVector2& _vec, const char* _str);
			void operator+=(FString& _str, const FVector2& _vec);
			void operator+=(const FVector2& _vec, FString& _str);

			////////////////////////////////////////////////
			// IOSTREAM UTILITY
			//____________________________________
			std::ostream& operator<<(std::ostream& _os, const FVector2& _vec);
			//std::istream& operator>>(std::istream& _is, FVector2& _vec);
		}
	}
}
//#include <Core\Math\FVector2.inl>
typedef ParadigmEngine::Core::Math::UVector2 UVector2;
typedef ParadigmEngine::Core::Math::FVector2 FVector2;


#pragma region UnitTests
#include <ParadigmDebug.h>

UNIT_TEST_CLASS(Core::Math::FVector2, 0.f)
UNIT_TEST_COMPARE_scalarS(DotProduct, { 0.f }) UNIT_TEST_EXPECTEDRESULT(0.f)
UNIT_TEST_COMPARE_scalarS(DotProduct, { -99.7485f,13.2945f }) UNIT_TEST_EXPECTEDRESULT(0.f)
UNIT_TEST_COMPARE_scalarS(Magnitude) UNIT_TEST_EXPECTEDRESULT(0.f)
UNIT_TEST_COMPARE(Normalized) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector2{ 0.f })

UNIT_TEST_CLASS(Core::Math::FVector2, -99.7485f, 13.2945f)
UNIT_TEST_COMPARE_scalarS(DotProduct, { -61.1411f,62.5767f }) UNIT_TEST_EXPECTEDRESULT(6930.6589f)
UNIT_TEST_COMPARE_scalarS(DotProduct, { 17.6012f,-3.53374f }) UNIT_TEST_EXPECTEDRESULT(-1802.6726f)
UNIT_TEST_COMPARE_scalarS(Magnitude) UNIT_TEST_EXPECTEDRESULT(100.631f)
UNIT_TEST_COMPARE(Normalized) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector2{ -0.991235f, 0.132112f })

UNIT_TEST_CLASS(Core::Math::FVector2, -61.1411f, 62.5767f)
UNIT_TEST_COMPARE_scalarS(DotProduct, { -61.1411f,62.5767f }) UNIT_TEST_EXPECTEDRESULT(7654.0774f)
UNIT_TEST_COMPARE_scalarS(DotProduct, { 17.6012f,-3.53374f }) UNIT_TEST_EXPECTEDRESULT(-1297.2865f)
UNIT_TEST_COMPARE_scalarS(Magnitude) UNIT_TEST_EXPECTEDRESULT(87.4876f)
UNIT_TEST_COMPARE(Normalized) UNIT_TEST_EXPECTEDRESULT(Core::Math::FVector2{ -0.698855f, 0.715264f })

#pragma endregion
#endif