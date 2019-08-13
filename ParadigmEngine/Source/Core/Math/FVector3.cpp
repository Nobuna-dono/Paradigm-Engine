#include <Include/Shortcut/ParadigmMath.h>
#include <iomanip>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			const UVector3 FVector3::Zero{ 0.f, 0.f , 0.f };
			const UVector3 FVector3::One{ 1.f, 1.f , 1.f };
			const UVector3 FVector3::Up{ 0.f, 1.f , 0.f };
			const UVector3 FVector3::Down{ 0.f, -1.f , 0.f };
			const UVector3 FVector3::Left{ -1.f, 0.f , 0.f };
			const UVector3 FVector3::Right{ 1.f, 0.f , 0.f };
			const UVector3 FVector3::Forward{ 0.f, 0.f , 1.f };
			const UVector3 FVector3::Backward{ 0.f, 0.f , -1.f };

			////////////////////////////////////////////////
			// OPERATOR
			//____________________________________
			UVector3::operator FVector2()
			{
				return { x, y };
			}
			UVector3::operator FVector3()
			{
				return { x, y, z };
			}
			UVector3::operator FVector4()
			{
				return { x, y, z };
			}

			UVector3::operator float*()
			{
				return &x;
			}

			void UVector3::operator=(const FVector3& _val)
			{
				x = _val.x;
				y = _val.y;
				z = _val.z;
			}


			FVector3::operator FVector2()
			{
				return { x, y };
			}
			FVector3::operator UVector3()
			{
				return { x, y, z };
			}
			FVector3::operator FVector4()
			{
				return { x, y, z };
			}

#pragma region Constructor
			////////////////////////////////////////////////
			// CONSTRUCTOR - DESTRUCTOR
			//____________________________________

			//UVector3::UVector3(const FVector3& _vec)
			//	: x{ _vec.x }, y{ _vec.y }, z{ _vec.z }
			//{}

			FVector3::FVector3(UVector3&& _vec)
				: x{ std::move(_vec.x) }, y{ std::move(_vec.y) }, z{ std::move(_vec.z) }
			{}

			FVector3::FVector3(const UVector3& _vec)
				: x{ _vec.x }, y{ _vec.y }, z{ _vec.z }
			{}

			FVector3::FVector3(const FVector4& _vec)
				: x{ _vec.x }, y{ _vec.y }, z{ _vec.z }
			{}

			FVector3::FVector3(const FVector2& _vec, float _z)
				: x{ _vec.x }, y{ _vec.y }, z{ _z }
			{}

			FVector3::FVector3(float new_x, float new_y, float new_z)
				: x{ new_x }, y{ new_y }, z{ new_z }
			{}

#pragma endregion Constructor

#pragma region Methods
			/*		Methods			*/
			float FVector3::DotProduct(const FVector3& vect) const
			{
				return (x*vect.x) + (y*vect.y) + (z*vect.z);
			}

			FVector3 FVector3::CrossProduct(const FVector3& vect) const
			{
				float a = y * vect.z - z * vect.y;
				float b = z * vect.x - x * vect.z;
				float c = x * vect.y - y * vect.x;
				FVector3 product(a, b, c);
				return product;
			}

			float FVector3::Magnitude_IOpt() const // as getMagnitude...
			{
				float sqrNorm = (x*x) + (y*y) + (z*z);
				float diff = (Norm*Norm) - sqrNorm;
				if (!((diff < 0.1f) && (-diff < 0.1f)))
					Norm = sqrtf(sqrNorm);
				return Norm;
			}

			float FVector3::Magnitude() const// as getMagnitude...
			{
				return sqrtf((x*x) + (y*y) + (z*z));
			}

			float FVector3::SqrMagnitude() const// as getMagnitude...
			{
				return (x*x) + (y*y) + (z*z);
			}

			void FVector3::Normalize()
			{
				Magnitude_IOpt();
				if (Norm != 0)
				{
					x /= Norm;
					y /= Norm;
					z /= Norm;
					Norm = 1.f;
				}
			}

			FVector3 FVector3::Normalized() const
			{
				Magnitude_IOpt();
				return Norm > 0.f ? FVector3(x / Norm, y / Norm, z / Norm) : FVector3::Zero;
			}

			bool FVector3::Equal(const FVector3& other_vec, float tolerance) const
			{
				return Equalf(x, other_vec.x, tolerance) && Equalf(y, other_vec.y, tolerance) && Equalf(z, other_vec.z, tolerance);
			}


			float FVector3::Distance(FVector3* v, FVector3* u)
			{
				return sqrtf((u->x - v->x)*(u->x - v->x) + (u->y - v->y)*(u->y - v->y) + (u->z - v->z)*(u->z - v->z));
			}

			float FVector3::SqrDistance(FVector3* v, FVector3* u)
			{
				return (u->x - v->x)*(u->x - v->x) + (u->y - v->y)*(u->y - v->y) + (u->z - v->z)*(u->z - v->z);
			}


			//FVector3 FVector3::RotationToDir(FVector3& _angles)
			//{
			//	FVector4 retour = FMatrix4::CreateRotationMatrix2(-_angles) * FVector4(forward);
			//	return retour;
			//}

			FVector3 FVector3::DirToRotation(FVector3& _vec)
			{
				FVector3 retour = _vec.Normalized();
				return{ atan2f(retour.z, retour.y) * RAD_TO_DEG, atan2f(retour.x, retour.z) * RAD_TO_DEG, atan2f(retour.y, retour.x) * RAD_TO_DEG };
			}

			FVector3 FVector3::Lerp(FVector3& _from, FVector3& _to, float _speed)
			{
				FVector3 temp = _to - _from;
				_speed = sqrtf(_speed*_speed / temp.SqrMagnitude());
				return _from + (temp * _speed);
			}

			FVector3 FVector3::LookDir(FVector3& _pos, FVector3& _target)
			{
				FVector3 temp = _target - _pos;
				return temp.Normalized();
			}

			FVector3 FVector3::LookRotation(FVector3& _pos, FVector3& _target)
			{
				return DirToRotation(LookDir(_pos, _target));
			}

			float FVector3::Angle(const FVector3& _v1, const FVector3& _v2)
			{
				return acosf(_v1.DotProduct(_v2) / (_v1.Magnitude() * _v2.Magnitude()));
			}
#pragma endregion Methods

#pragma region Operators
			/*		Operator		*/
			FVector3 FVector3::operator+(const FVector3& vector) const
			{
				return FVector3(x + vector.x, y + vector.y, z + vector.z);
			}

			void FVector3::operator+=(const FVector3& vector)
			{
				x += vector.x;
				y += vector.y;
				z += vector.z;
			}

			FVector3 FVector3::operator-(const FVector3& vector) const
			{
				return FVector3(x - vector.x, y - vector.y, z - vector.z);
			}

			void FVector3::operator-=(const FVector3& vector)
			{
				x -= vector.x;
				y -= vector.y;
				z -= vector.z;
			}

			FVector3 FVector3::operator*(float _val) const
			{
				return FVector3(x * _val, y * _val, z * _val);
			}

			FVector3 FVector3::operator*(const FQuaternion& _q) const
			{
				return _q * *this;
			}

			FVector3 FVector3::operator*(const FVector3& _vec) const
			{
				return {x* _vec.x, y * _vec.y, z * _vec.z};
			}

			FVector3 FVector3::operator/(const FVector3& _vec) const
			{
				return { x / _vec.x, y / _vec.y, z / _vec.z };
			}

			FVector3::operator FString()
			{
				return FString("Vector3 (x: ") + std::to_string(x) + ", y: " + std::to_string(y) + ", z: " + std::to_string(z) + ")";
			}

			void FVector3::operator*=(float _val)
			{
				x *= _val;
				y *= _val;
				z *= _val;
			}

			FVector3 FVector3::operator/(float _val) const
			{
				try
				{
					if (!_val)
						THROW_PARADIGM_EXCEPTION_DOMAIN("null value pass as argument");

					return FVector3(x / _val, y / _val, z / _val);
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
					return FVector3();
				}
			}

			void FVector3::operator/=(float _val)
			{
				try
				{
					if (!_val)
						THROW_PARADIGM_EXCEPTION_DOMAIN("null value pass as argument");

					x /= _val;
					y /= _val;
					z /= _val;
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
				}
			}

			FVector3 FVector3::operator-() const
			{
				return FVector3(-x, -y, -z);
			}
			
			void FVector3::operator=(const FVector2& _vec)
			{
				x = _vec.x;
				y = _vec.y;
				z = 0;
			}
			
			void FVector3::operator=(const UVector3& _vec)
			{
				x = _vec.x;
				y = _vec.y;
				z = _vec.z;
			}

			void FVector3::operator=(const FVector4& _vec)
			{
				x = _vec.x;
				y = _vec.y;
				z = _vec.z;
			}
			
			bool FVector3::operator==(const FVector2& other_vector) const
			{
				return (Equalf(x, other_vector.x) && Equalf(y, other_vector.y));
			}

			bool FVector3::operator==(const FVector3& other_vector) const
			{
				return (Equalf(x, other_vector.x) && Equalf(y, other_vector.y) && Equalf(z, other_vector.z));
			}

			bool FVector3::operator==(const FVector4& other_vector) const
			{
				return (Equalf(x, other_vector.x) && Equalf(y, other_vector.y) && Equalf(z, other_vector.z));
			}

			bool FVector3::operator!=(const FVector2& other_vector) const
			{
				return (!Equalf(x, other_vector.x) || !Equalf(y, other_vector.y) );
			}

			bool FVector3::operator!=(const FVector3& other_vector) const
			{
				return (!Equalf(x, other_vector.x) || !Equalf(y, other_vector.y) || !Equalf(z, other_vector.z));
			}

			bool FVector3::operator!=(const FVector4 & other_vector) const
			{
				return (!Equalf(x, other_vector.x) || !Equalf(y, other_vector.y) || !Equalf(z, other_vector.z));
			}

			bool FVector3::operator<(const FVector3& other_vector) const
			{
				return SqrMagnitude() < other_vector.SqrMagnitude();
			}

			bool FVector3::operator>(const FVector3& other_vector)  const
			{
				return SqrMagnitude() > other_vector.SqrMagnitude();
			}

			bool FVector3::operator<=(const FVector3& other_vector) const
			{
				return SqrMagnitude() <= other_vector.SqrMagnitude();
			}

			bool FVector3::operator>=(const FVector3& other_vector) const
			{
				return SqrMagnitude() >= other_vector.SqrMagnitude();
			}

			float FVector3::operator,(const FVector3& other_vector) const
			{
				return DotProduct(other_vector);
			}									
#pragma endregion Operators
			
			FVector3 operator*(float _val, FVector3&& _vec)
			{
				return FVector3(_vec.x * _val, _vec.y * _val, _vec.z * _val);
			}

			FVector3 operator*(float _val, const FVector3& vector)
			{
				return FVector3(vector.x*_val, vector.y*_val, vector.z*_val);
			}

			FVector3 operator/(float _val, const FVector3& _vector)
			{
				try
				{
					if (!(_vector.x * _vector.y))
						THROW_PARADIGM_EXCEPTION_DOMAIN("Divide up vector with null value.");

					return FVector3(_val / _vector.x, _val / _vector.y);
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
					return FVector3();
				}
			}

			////////////////////////////////////////////////
			// IOSTREAM UTILITY
			//____________________________________
			std::ostream& operator<<(std::ostream& stream, const FVector3& vect)
			{
				return stream << "Vector3 (x: " << vect.x << ", y: " << vect.y << ", z: " << vect.z << ")";
			}

			std::istream& operator >> (std::istream& stream, FVector3& vect)
			{
				char c{ 0 };
				stream >> vect.x >> c;

				if (c == ',')
					stream >> vect.y;
				else if (c == 'f')
				{
					stream >> c;
					if (c == ',')
					{
						stream >> vect.y;
						stream >> c;
						if (c == ',')
							stream >> vect.z;
						else if (c == 'f')
						{
							stream >> c;
							if (c == ',')
							{
								stream >> vect.z;
							}
						}
					}
					else
						vect.x = vect.y = vect.z = 0.0;
				}
				else
					vect.x = vect.y = vect.z = 0.0;

				return stream;
			}
		}
	}
}

////////////////////////////////////////////////
// FSTRING UTILITY
//____________________________________
FString operator+(const FString& _str, const FVector3& _vector)
{
	return { _str + "Vector3 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ")" };
}

FString operator+(const FVector3& _vector, const FString& _str)
{
	return { "Vector3 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ")" + _str };
}

FString operator+(const char* _str, const FVector3& _vector)
{
	return _str + FString("Vector3 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ")");
}

FString operator+(const FVector3& _vector, const char*  _str)
{
	return FString("Vector3 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ")" + _str);
}

void operator+=(FString& _str, const FVector3& _vector)
{
	_str += "Vector3 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ")";
}

void operator+=(const FVector3& _vector, FString& _str)
{
	_str.Insert(0, "Vector3 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ")");
}