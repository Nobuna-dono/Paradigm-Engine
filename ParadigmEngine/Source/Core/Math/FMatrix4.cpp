#include <Include/Shortcut/ParadigmMath.h>

using namespace Core::Debug;

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			const FMatrix4 FMatrix4::identity{};
			//	Constructors			
			FMatrix4::FMatrix4(const UMatrix4& _mat)
			{
				memcpy(Matrix, _mat.Matrix, sizeof(float) * 16);
			}

			FMatrix4::FMatrix4()
			{
				memset(Matrix, 0, sizeof(float) * 16);
				Matrix[0] = Matrix[5] = Matrix[10] = Matrix[15] = 1;
			}

			FMatrix4::FMatrix4(const FMatrix4& _mat)
			{
				memcpy(Matrix, _mat.Matrix, sizeof(float) * 16);
			}

			FMatrix4::FMatrix4(const float(&_mat)[16])
			{
				memcpy(Matrix, _mat, sizeof(float) * 16);
			}

			//	Methods
			FMatrix4 FMatrix4::CreateTransformMatrix(const FVector3& position, const FVector3& rotation, const FVector3& scale, bool reverse)
			{
				FMatrix4 matBuffer;
				FMatrix4 Buffer[3];
				if (!reverse)
				{
					Buffer[0] = CreateTranslationMatrix(position);
					Buffer[1] = CreateRotationMatrix(rotation.x, rotation.y, rotation.z);
					Buffer[2] = CreateScaleMatrix(scale);

					matBuffer = Buffer[0] * Buffer[1] * Buffer[2];
				}
				else
				{
					Buffer[0] = CreateTranslationMatrix(position);
					Buffer[1] = CreateRotationMatrix(-rotation.x, -rotation.y, -rotation.z);
					Buffer[2] = CreateScaleMatrix(-scale);

					matBuffer = Buffer[2] * Buffer[1] * Buffer[0];
				}

				return matBuffer;
			}

			FMatrix4 FMatrix4::CreateTranslationMatrix(const FVector3& vec)
			{
				FMatrix4 matBuffer;
				matBuffer[3] = vec.x;
				matBuffer[7] = vec.y;
				matBuffer[11] = vec.z;

				return matBuffer;
			}

			FMatrix4 FMatrix4::CreateScaleMatrix(const FVector3& vec)
			{
				FMatrix4 matBuffer;
				matBuffer[0] = vec.x;
				matBuffer[5] = vec.y;
				matBuffer[10] = vec.z;

				return matBuffer;
			}

			FMatrix4 FMatrix4::CreateRotationMatrix(const float _pitch, const float _yaw, const float _roll)
			{
				return FQuaternion::FromEulerAngles(_pitch, _yaw, _roll).ToMatrix4();
			}

			FMatrix4 FMatrix4::CreateOrthoMatrix(unsigned int width, unsigned int height, int near, int far)
			{
				FMatrix4 ortho = FMatrix4::CreateScaleMatrix({ 2.f / -(int)width, 2.f / -(int)height, -2.f / (far - near) });
				ortho *= FMatrix4::CreateTranslationMatrix({ 1.f,1.f,1.f });
				return ortho;
			}

			FMatrix4 FMatrix4::CreateOrthoMatrix(FVector3 Min, FVector3 Max)
			{
				FMatrix4 ortho;
				ortho = FMatrix4::CreateScaleMatrix({ 2.f / (Max.x - Min.x),
													2.f / (Max.y - Min.y),
													-2.f / (Max.z - Min.z) });

				ortho *= FMatrix4::CreateTranslationMatrix({ -(Max.x + Min.x) / (Max.x - Min.x),
															-(Max.y + Min.y) / (Max.y - Min.y),
															-(Max.z + Min.z) / (Max.z - Min.z) });
				return ortho;
			}

			FMatrix4 FMatrix4::CreateProjMatrix(unsigned int width, unsigned int height,  float near, float far, unsigned int FOV)
			{
				const float ar = (float)width / (float)height;
				const float range = far - near;
				const float tanHalfFOV = tanf(TO_RADIAN(FOV / 2.f));
				FMatrix4 proj{ {
						1.f / (ar * tanHalfFOV), 0.f, 0.f, 0.f,
						0.f, 1.f / tanHalfFOV, 0.f, 0.f,
						0.f, 0.f, -(far + near) / range, (2.f * far*near) / range, // -2 for standard OpenGL RH
						0.f, 0.f, 1.f, 0.f	// -1 for standard OpenGL RH 
					} };

				return proj;
			}

			//Methods Mk2
			void FMatrix4::SetPosition(const FVector3& v)
			{
				Matrix[3] = v.x;
				Matrix[7] = v.y;
				Matrix[11] = v.z;
			}

			FVector3 FMatrix4::GetPosition() const
			{
				return { Matrix[3], Matrix[7], Matrix[11] };
			}

			void FMatrix4::Scale(const UVector3& _scl)
			{
				Matrix[0] *= _scl.x;	Matrix[1] *= _scl.y;	Matrix[2] *= _scl.z;
				Matrix[4] *= _scl.x;	Matrix[5] *= _scl.y;	Matrix[6] *= _scl.z;
				Matrix[8] *= _scl.x;	Matrix[9] *= _scl.y;	Matrix[10] *= _scl.z;
			}

			FMatrix4 FMatrix4::Inverse() const
			{
				FMatrix4 MatOut;
				MatOut[0] = Matrix[6] * Matrix[11] * Matrix[13] - Matrix[7] * Matrix[10] * Matrix[13] + Matrix[7] * Matrix[9] * Matrix[14] - Matrix[5] * Matrix[11] * Matrix[14] - Matrix[6] * Matrix[9] * Matrix[15] + Matrix[5] * Matrix[10] * Matrix[15];
				MatOut[1] = Matrix[3] * Matrix[10] * Matrix[13] - Matrix[2] * Matrix[11] * Matrix[13] - Matrix[3] * Matrix[9] * Matrix[14] + Matrix[1] * Matrix[11] * Matrix[14] + Matrix[2] * Matrix[9] * Matrix[15] - Matrix[1] * Matrix[10] * Matrix[15];
				MatOut[2] = Matrix[2] * Matrix[7] * Matrix[13] - Matrix[3] * Matrix[6] * Matrix[13] + Matrix[3] * Matrix[5] * Matrix[14] - Matrix[1] * Matrix[7] * Matrix[14] - Matrix[2] * Matrix[5] * Matrix[15] + Matrix[1] * Matrix[6] * Matrix[15];
				MatOut[3] = Matrix[3] * Matrix[6] * Matrix[9] - Matrix[2] * Matrix[7] * Matrix[9] - Matrix[3] * Matrix[5] * Matrix[10] + Matrix[1] * Matrix[7] * Matrix[10] + Matrix[2] * Matrix[5] * Matrix[11] - Matrix[1] * Matrix[6] * Matrix[11];
				MatOut[4] = Matrix[7] * Matrix[10] * Matrix[12] - Matrix[6] * Matrix[11] * Matrix[12] - Matrix[7] * Matrix[8] * Matrix[14] + Matrix[4] * Matrix[11] * Matrix[14] + Matrix[6] * Matrix[8] * Matrix[15] - Matrix[4] * Matrix[10] * Matrix[15];
				MatOut[5] = Matrix[2] * Matrix[11] * Matrix[12] - Matrix[3] * Matrix[10] * Matrix[12] + Matrix[3] * Matrix[8] * Matrix[14] - Matrix[0] * Matrix[11] * Matrix[14] - Matrix[2] * Matrix[8] * Matrix[15] + Matrix[0] * Matrix[10] * Matrix[15];
				MatOut[6] = Matrix[3] * Matrix[6] * Matrix[12] - Matrix[2] * Matrix[7] * Matrix[12] - Matrix[3] * Matrix[4] * Matrix[14] + Matrix[0] * Matrix[7] * Matrix[14] + Matrix[2] * Matrix[4] * Matrix[15] - Matrix[0] * Matrix[6] * Matrix[15];
				MatOut[7] = Matrix[2] * Matrix[7] * Matrix[8] - Matrix[3] * Matrix[6] * Matrix[8] + Matrix[3] * Matrix[4] * Matrix[10] - Matrix[0] * Matrix[7] * Matrix[10] - Matrix[2] * Matrix[4] * Matrix[11] + Matrix[0] * Matrix[6] * Matrix[11];
				MatOut[8] = Matrix[5] * Matrix[11] * Matrix[12] - Matrix[7] * Matrix[9] * Matrix[12] + Matrix[7] * Matrix[8] * Matrix[13] - Matrix[4] * Matrix[11] * Matrix[13] - Matrix[5] * Matrix[8] * Matrix[15] + Matrix[4] * Matrix[9] * Matrix[15];
				MatOut[9] = Matrix[3] * Matrix[9] * Matrix[12] - Matrix[1] * Matrix[11] * Matrix[12] - Matrix[3] * Matrix[8] * Matrix[13] + Matrix[0] * Matrix[11] * Matrix[13] + Matrix[1] * Matrix[8] * Matrix[15] - Matrix[0] * Matrix[9] * Matrix[15];
				MatOut[10] = Matrix[1] * Matrix[7] * Matrix[12] - Matrix[3] * Matrix[5] * Matrix[12] + Matrix[3] * Matrix[4] * Matrix[13] - Matrix[0] * Matrix[7] * Matrix[13] - Matrix[1] * Matrix[4] * Matrix[15] + Matrix[0] * Matrix[5] * Matrix[15];
				MatOut[11] = Matrix[3] * Matrix[5] * Matrix[8] - Matrix[1] * Matrix[7] * Matrix[8] - Matrix[3] * Matrix[4] * Matrix[9] + Matrix[0] * Matrix[7] * Matrix[9] + Matrix[1] * Matrix[4] * Matrix[11] - Matrix[0] * Matrix[5] * Matrix[11];
				MatOut[12] = Matrix[6] * Matrix[9] * Matrix[12] - Matrix[5] * Matrix[10] * Matrix[12] - Matrix[6] * Matrix[8] * Matrix[13] + Matrix[4] * Matrix[10] * Matrix[13] + Matrix[5] * Matrix[8] * Matrix[14] - Matrix[4] * Matrix[9] * Matrix[14];
				MatOut[13] = Matrix[1] * Matrix[10] * Matrix[12] - Matrix[2] * Matrix[9] * Matrix[12] + Matrix[2] * Matrix[8] * Matrix[13] - Matrix[0] * Matrix[10] * Matrix[13] - Matrix[1] * Matrix[8] * Matrix[14] + Matrix[0] * Matrix[9] * Matrix[14];
				MatOut[14] = Matrix[2] * Matrix[5] * Matrix[12] - Matrix[1] * Matrix[6] * Matrix[12] - Matrix[2] * Matrix[4] * Matrix[13] + Matrix[0] * Matrix[6] * Matrix[13] + Matrix[1] * Matrix[4] * Matrix[14] - Matrix[0] * Matrix[5] * Matrix[14];
				MatOut[15] = Matrix[1] * Matrix[6] * Matrix[8] - Matrix[2] * Matrix[5] * Matrix[8] + Matrix[2] * Matrix[4] * Matrix[9] - Matrix[0] * Matrix[6] * Matrix[9] - Matrix[1] * Matrix[4] * Matrix[10] + Matrix[0] * Matrix[5] * Matrix[10];
				MatOut = MatOut * (1 / Determinant());
				return MatOut;
			}

			float FMatrix4::Determinant() const
			{
				float value;
				value =
					Matrix[3] * Matrix[6] * Matrix[9] * Matrix[12] - Matrix[2] * Matrix[7] * Matrix[9] * Matrix[12] - Matrix[3] * Matrix[5] * Matrix[10] * Matrix[12] + Matrix[1] * Matrix[7] * Matrix[10] * Matrix[12] +
					Matrix[2] * Matrix[5] * Matrix[11] * Matrix[12] - Matrix[1] * Matrix[6] * Matrix[11] * Matrix[12] - Matrix[3] * Matrix[6] * Matrix[8] * Matrix[13] + Matrix[2] * Matrix[7] * Matrix[8] * Matrix[13] +
					Matrix[3] * Matrix[4] * Matrix[10] * Matrix[13] - Matrix[0] * Matrix[7] * Matrix[10] * Matrix[13] - Matrix[2] * Matrix[4] * Matrix[11] * Matrix[13] + Matrix[0] * Matrix[6] * Matrix[11] * Matrix[13] +
					Matrix[3] * Matrix[5] * Matrix[8] * Matrix[14] - Matrix[1] * Matrix[7] * Matrix[8] * Matrix[14] - Matrix[3] * Matrix[4] * Matrix[9] * Matrix[14] + Matrix[0] * Matrix[7] * Matrix[9] * Matrix[14] +
					Matrix[1] * Matrix[4] * Matrix[11] * Matrix[14] - Matrix[0] * Matrix[5] * Matrix[11] * Matrix[14] - Matrix[2] * Matrix[5] * Matrix[8] * Matrix[15] + Matrix[1] * Matrix[6] * Matrix[8] * Matrix[15] +
					Matrix[2] * Matrix[4] * Matrix[9] * Matrix[15] - Matrix[0] * Matrix[6] * Matrix[9] * Matrix[15] - Matrix[1] * Matrix[4] * Matrix[10] * Matrix[15] + Matrix[0] * Matrix[5] * Matrix[10] * Matrix[15];
				return value;
			}

			FMatrix4 FMatrix4::Transposed() const
			{
				FMatrix4 MatOut;
				for (int i = 0, j = 0; i < 16; ++i, j += 4)
				{
					if (j >= 16)
						j -= 15;

					MatOut[i] = Matrix[j];
				}
				return MatOut;
			}

			void FMatrix4::TransformVectorCoordSystem(const FVector3& _vec, FVector3& out_Vec, const FMatrix4& _coordSystem)
			{
				float x, y, z, w;
				x = _vec.x*_coordSystem[0] + _vec.y*_coordSystem[1] + _vec.z*_coordSystem[2] + _coordSystem[3];
				y = _vec.x*_coordSystem[4] + _vec.y*_coordSystem[5] + _vec.z*_coordSystem[6] + _coordSystem[7];
				z = _vec.x*_coordSystem[8] + _vec.y*_coordSystem[9] + _vec.z*_coordSystem[10] + _coordSystem[11];
				w = _vec.x*_coordSystem[12] + _vec.y*_coordSystem[13] + _vec.z*_coordSystem[14] + _coordSystem[15];

				out_Vec.x = x / w;
				out_Vec.y = y / w;
				out_Vec.z = z / w;
			}

			UMatrix4 FMatrix4::CreateLookAtLH(EMatrixType _type, const FVector3& _position, const FVector3& _target, const FVector3& _up)
			{
				FVector3 xaxis = FVector3(0), yaxis = FVector3(0), zaxis = FVector3(0);
				zaxis = (_position - _target).Normalized();
				xaxis = (zaxis.CrossProduct(_up)).Normalized();
				yaxis = xaxis.CrossProduct(zaxis);

				if (_type == EMatrixType::Row_Major)
					return UMatrix4({
					xaxis.x ,          yaxis.x ,          zaxis.x,          0,
					xaxis.y ,          yaxis.y ,          zaxis.y,          0,
					xaxis.z ,          yaxis.z ,          zaxis.z,          0,
					-xaxis.DotProduct(_position), -yaxis.DotProduct(_position), -zaxis.DotProduct(_position), 1
				});
				else
					return UMatrix4({
					xaxis.x ,			xaxis.y ,			xaxis.z,        -xaxis.DotProduct(_position),
					yaxis.x ,			yaxis.y ,			yaxis.z,        -yaxis.DotProduct(_position),
					zaxis.x ,			zaxis.y ,			zaxis.z,        -zaxis.DotProduct(_position),
					0,					0,					0,				1
				});
			}


			//	Operators
			FMatrix4 FMatrix4::operator*(const FMatrix4& mat2) const
			{
				FMatrix4 matBuffer;
				float buffer = 0;

				for (int i = 0; i < 4; i++)
				{

					for (int j = 0; j < 4; j++)
					{
						buffer = 0;
						for (int k = 0; k < 4; k++)
							buffer += Matrix[(i * 4) + k] * mat2[(k * 4) + j];
						matBuffer[(i * 4) + j] = buffer;
					}

				}
				return matBuffer;
			}

			FMatrix4& FMatrix4::operator*=(const FMatrix4& mat2)
			{
				FMatrix4 matBuffer;
				float buffer = 0;

				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						buffer = 0;
						for (int k = 0; k < 4; k++)
							buffer += Matrix[(i * 4) + k] * mat2[(k * 4) + j];
						matBuffer[(i * 4) + j] = buffer;
					}
				}

				*this = matBuffer;
				return *this;
			}

			FMatrix4 FMatrix4::operator+(const FMatrix4& mat2) const
			{
				FMatrix4 matBuffer;
				float buffer = 0;

				for (int i = 0; i < 16; i++)
				{
					matBuffer[i] = Matrix[i] + mat2[i];
				}
				return matBuffer;
			}

			FVector4 FMatrix4::operator*(const FVector4& vec) const
			{
				FVector4 vecBuffer;
				float buffer = 0;

				for (int i = 0; i < 4; i++)
				{
					buffer = 0;
					for (int j = 0; j < 4; j++)
					{
						buffer += Matrix[(i * 4) + j] * vec.x;
						j++;
						buffer += Matrix[(i * 4) + j] * vec.y;
						j++;
						buffer += Matrix[(i * 4) + j] * vec.z;
						j++;
						buffer += Matrix[(i * 4) + j] * vec.w;
						j++;
					}

					if (i == 0)
						vecBuffer.x = buffer;
					else if (i == 1)
						vecBuffer.y = buffer;
					else if (i == 2)
						vecBuffer.z = buffer;
					else if (i == 3)
						vecBuffer.w = buffer;
				}
				return vecBuffer;
			}

			FVector3 Core::Math::operator*(const FVector3& vec, const FMatrix4& mat)
			{
				return mat * vec;
			}

			FMatrix4 FMatrix4::operator*(const float& f) const
			{
				FMatrix4 matBuffer;
				float buffer = 0;

				for (int i = 0; i < 16; i++)
					matBuffer[i] = Matrix[i] * f;

				return matBuffer;
			}

			bool FMatrix4::operator==(const FMatrix4& mat) const
			{
				for (int i = 0; i < 16; i++)
				{
					if (!Equalf(Matrix[i], mat[i]))
						return false;
				}
				return true;
			}

			bool FMatrix4::operator!=(const FMatrix4& mat) const
			{
				for (int i = 0; i < 16; i++)
				{
					if (!Equalf(Matrix[i], mat[i]))
						return true;
				}
				return false;
			}

			std::ostream& Core::Math::operator<<(std::ostream& stream, const FMatrix4& mat)
			{
				std::string str;
				for (int row = 0; row < 4; row++)
				{
					for (int column = 0; column < 4; column++)
					{
						str += std::to_string(mat[(row * 4) + column]);
						str += "\t";
					}
					str += "\n";
				}
				return stream << "Mat:\n{\n" << str << "}\n";
			}
		}
	}
}