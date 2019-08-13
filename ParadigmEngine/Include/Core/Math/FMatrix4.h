#ifndef _FMATRIX4_H_
#define _FMATRIX4_H_

#include <Core/Math/FVector3.h>
#include <Core/Math/UMatrix4.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			struct FVector3;
			struct FVector4;
			
			enum EMatrixType
			{
				Row_Major,
				Coloum_Major
			};
			
			/** basic Matrix 4x4 in raw Major */
			class FMatrix4
			{
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR 
					//____________________________________
					~FMatrix4() = default;
					FMatrix4(const UMatrix4& _mat);
					FMatrix4(const FMatrix4& _mat);
					FMatrix4(const float(&_mat)[16]);

					FMatrix4();


				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY 
					//____________________________________
					/** Return a transform matrix by passing 3 vectors: position, rotation angles in degrees and scale*/
					static FMatrix4 CreateTransformMatrix(const FVector3& position = FVector3(0, 0, 0), const FVector3& rotation = FVector3(0, 0, 0), const FVector3& scale = FVector3(1, 1, 1), bool = true);

					/** Return a translation matrix made from a vector*/
					static FMatrix4 CreateTranslationMatrix(const FVector3& translation);

					/** Return a scale matrix made from a vector*/
					static FMatrix4 CreateScaleMatrix(const FVector3& scale);

					/** Returns a rotation matrix made from euler angles in radiants*/
					static FMatrix4 CreateRotationMatrix(const float _pitch, const float _yaw, const float _roll);

					/** Return an ortographic projection matrix */
					static FMatrix4 CreateOrthoMatrix(unsigned int width, unsigned int height, int near, int far);

					/** Return an ortographic projection matrix */
					static FMatrix4 CreateOrthoMatrix(FVector3 Min, FVector3 Max);

					/** Return an perspective projection matrix */
					static FMatrix4 CreateProjMatrix(unsigned int width, unsigned int height, float _near, float _far, unsigned int FOV);

					/** Change the value of the position in a transform matrix */
					void SetPosition(const FVector3&);

					/** Return the value of the position of a transform matrix*/
					FVector3 GetPosition() const;

					/** Multiply the by a scale Matrix*/
					void Scale(const UVector3&);

					/** Returns reference to a element of the matrix parameters must be between 0 and 3*/
					float& Get(unsigned int _column, unsigned int _raw) { return Matrix[(4 * _raw) + _column]; }

					/** Return the Inverse of the matrix */
					FMatrix4 Inverse() const;

					/** Return the determinant of the matrix */
					float Determinant() const;

					/** Return the transposed of the matrix */
					FMatrix4 Transposed() const;

					/** Return the matrix in an float array */
					inline float* ToFloatArray() const { return (float*)Matrix; };

					/** Transforms the lookAt and up vectors using the rotation matrix so that they are turned correctly */
					static void TransformVectorCoordSystem(const FVector3& _vec, FVector3& out_Vec, const FMatrix4& _coordSystem);

					static UMatrix4 CreateLookAtLH(EMatrixType _type, const FVector3& _position, const FVector3& _target, const FVector3& _up);


				public:
					////////////////////////////////////////////////
					// OPERATORS 
					//____________________________________
					float& operator[](const int& i) { return Matrix[i]; };
					float operator[](const int& i) const { return Matrix[i]; };

					bool operator!=(const FMatrix4&) const;
					bool operator==(const FMatrix4&) const;
					FMatrix4 operator*(const FMatrix4&) const;
					FMatrix4& operator*=(const FMatrix4&);
					FMatrix4 operator+(const FMatrix4&) const;
					FMatrix4 operator*(const float&) const;
					FVector4 operator*(const FVector4&) const;
					inline FVector3 operator*(const FVector3& _vec) const { return { *this * FVector4{ _vec, 1.f } }; };
					inline FMatrix4 Mult(const FMatrix4& _mat) const { return *this * _mat; };

					static const FMatrix4 identity;


				private:
					/* Indexes:				Transposed:
					|---------------|		|---------------|
					| 0	 1	 2	 3	|		| 0	 4	 8	 12	|
					| 4	 5	 6	 7	|		| 1	 5	 9	 13	|
					| 8	 9	 10	 11	|		| 2	 6	 10	 14	|
					| 12 13  14	 15	|		| 3  7   11	 15	|
					|---------------|		|---------------|
					*/
					float Matrix[16];
			};

			////////////////////////////////////////////////
			// OPERATORS 
			//____________________________________
			FVector3 operator*(const FVector3&, const FMatrix4&);
			std::ostream& operator<<(std::ostream& stream, const FMatrix4&);
		}
	}
}
typedef ParadigmEngine::Core::Math::FMatrix4 FMatrix4;
typedef ParadigmEngine::Core::Math::UMatrix4 UMatrix4;

#pragma region UnitTests

UNIT_TEST_CLASS(Core::Math::FMatrix4)
UNIT_TEST_COMPARE(Inverse) UNIT_TEST_EXPECTEDRESULT(Core::Math::FMatrix4::identity)
UNIT_TEST_COMPARE(Determinant) UNIT_TEST_EXPECTEDRESULT(1.f)
UNIT_TEST_COMPARE(Transposed) UNIT_TEST_EXPECTEDRESULT(Core::Math::FMatrix4::identity)

UNIT_TEST_CLASS(Core::Math::FMatrix4, { 1.f,0.f,2.f,4.f, 0.f,1.f,3.f,2.f, 2.f,-1.f,0.f,3.f, 4.f,-1.f,3.f,9.f })
UNIT_TEST_COMPARE(Inverse) UNIT_TEST_EXPECTEDRESULT(Core::Math::FMatrix4{ {-3.f,0.f,-2.f,2.f, -6.f,-3.f,-11.f,7.f, 2.f,2.f,5.f,-3.f, 0.f,-1.f,-2.f,1.f} })
UNIT_TEST_COMPARE(Determinant) UNIT_TEST_EXPECTEDRESULT(-1.f)
UNIT_TEST_COMPARE(Transposed) UNIT_TEST_EXPECTEDRESULT(Core::Math::FMatrix4{ {1.f,0.f,2.f,4.f, 0.f,1.f,-1.f,-1.f, 2.f,3.f,0.f,3.f, 4.f,2.f,3.f,9.f} })
UNIT_TEST_COMPARE(Mult, { {1.f,2.f,3.f,4.f, 5.f,6.f,7.f,8.f, 9.f,10.f,11.f,12.f, 13.f,14.f,15.f,16.f} }) UNIT_TEST_EXPECTEDRESULT(Core::Math::FMatrix4{ {71.f,78.f,85.f,92.f, 58.f,64.f,70.f,76.f, 36.f,40.f,44.f,48.f, 143.f,158.f,173.f,188.f } })
UNIT_TEST_END_CLASS

UNIT_TEST_COMPARE(Core::Math::FMatrix4::CreateRotationMatrix, -PI / 2.f, PI / 2.f, PI) UNIT_TEST_EXPECTEDRESULT(Core::Math::FMatrix4{ { 0.f,1.f,0.f,0.f, 0.f,0.f,-1.f,0.f, -1.f,0.f,0.f,0.0f, 0.f,0.f,0.0f,1.f } })

#pragma endregion

#endif