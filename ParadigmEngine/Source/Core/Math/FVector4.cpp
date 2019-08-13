#include <ParadigmMath.h>
#include <ParadigmDebug.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			////////////////////////////////////////////////
			// STATIC DATA
			//____________________________________			
			const FVector4 FVector4::Zero{ 0.f, 0.f , 0.f , 1.f };
			const FVector4 FVector4::Up{ 0.f, 1.f , 0.f, 1.f };
			const FVector4 FVector4::Down{ 0.f, -1.f , 0.f, 1.f };
			const FVector4 FVector4::Left{ -1.f, 0.f , 0.f, 1.f };
			const FVector4 FVector4::Right{ 1.f, 0.f , 0.f, 1.f };
			const FVector4 FVector4::Forward{ 0.f, 0.f , 1.f, 1.f };
			const FVector4 FVector4::Backward{ 0.f, 0.f , -1.f, 1.f };

			////////////////////////////////////////////////
			// OPERATOR
			//____________________________________
			UVector4::operator FVector2()
			{
				return { x, y };
			}
			UVector4::operator FVector3()
			{
				return { x, y, z };
			}
			UVector4::operator FVector4()
			{
				return { x, y, z, w };
			}

			UVector4::operator float*()
			{
				return &x;
			}

			void UVector4::operator=(const FVector4& _val)
			{
				x = _val.x;
				y = _val.y;
				z = _val.z;
				w = _val.w;
			}


			FVector4::operator FVector2()
			{
				return { x, y };
			}
			FVector4::operator FVector3()
			{
				return { x, y, z };
			}
			FVector4::operator UVector4()
			{
				return { x, y, z , w };
			}

#pragma region Constructors
			////////////////////////////////////////////////
			// CONSTRUCTOR - DESTRUCTOR
			//____________________________________	
			FVector4::FVector4(UVector4&& _vec)
				: x{ std::move(_vec.x) }, y{ std::move(_vec.y) }, z{ std::move(_vec.z) }, w{ std::move(_vec.w) }, Norm{ 0.0 }
			{}

			FVector4::FVector4(const UVector4& _vec)
				: x{ _vec.x }, y{ _vec.y }, z{ _vec.z }, w{ _vec.w }, Norm{ 0.0 }
			{}

			FVector4::FVector4(const FVector2& _vec, float _z, float _w)
				: x{ _vec.x }, y{ _vec.y }, z{ _z }, w{ _w }, Norm{ _vec.Norm }
			{}

			FVector4::FVector4(const FVector3& _vec, float _w) 
				: x{ _vec.x }, y{ _vec.y }, z{ _vec.z }, w{ _w }, Norm{ _vec.Norm }
			{}

			FVector4::FVector4(float new_x, float new_y, float new_z, float new_w) 
				: x{ new_x }, y{ new_y }, z{ new_z }, w{ new_w }, Norm{ 0.0 }
			{}

#pragma endregion Constructors

#pragma region Methods
			////////////////////////////////////////////////
			// FUNCTIONALITY
			//____________________________________	
			void FVector4::Homogenize()
			{
				x /= w;
				y /= w;
				z /= w;
			}

			bool FVector4::Equal(const FVector4& other_vec, float tolerance) const
			{
				return Equalf(x, other_vec.x, tolerance) && Equalf(y, other_vec.y, tolerance) && Equalf(z, other_vec.z, tolerance) && Equalf(w, other_vec.w, tolerance);
			}

			float FVector4::DotProduct(const FVector3& vect) const
			{
				return (x*vect.x) + (y*vect.y) + (z*vect.z);
			}

			float FVector4::DotProduct(const FVector4& v4) const
			{
				return DotProduct(FVector3(v4));
			}

			FVector4 FVector4::CrossProduct(const FVector3& vect) const
			{
				float a = y * vect.z - z * vect.y;
				float b = z * vect.x - x * vect.z;
				float c = x * vect.y - y * vect.x;
				FVector3 product(a, b, c);
				return product;
			}

			FVector4 FVector4::CrossProduct(const FVector4& v4) const
			{
				return CrossProduct(FVector3(v4));
			}

			float FVector4::Magnitude_IOpt() // as getMagnitude...
			{
				float sqrNorm = (x*x) + (y*y) + (z*z);
				float diff = (Norm*Norm) - sqrNorm;
				if (!((diff < 0.1f) && (-diff < 0.1f)))
					Norm = sqrtf(sqrNorm);
				return Norm;
			}

			float FVector4::Magnitude() const// as getMagnitude...
			{
				return sqrtf((x*x) + (y*y) + (z*z));
			}

			float FVector4::SqrMagnitude() const// as getMagnitude...
			{
				return (x*x) + (y*y) + (z*z);
			}

			void FVector4::Normalize()
			{
				Magnitude_IOpt();
				if (Norm != 0)
				{
					x /= Norm;
					y /= Norm;
					z /= Norm;
				}
			}

			FVector4 FVector4::Normalized() const
			{
				float norm = Magnitude();
				return norm > 0.f ? FVector3(x / norm, y / norm, z / norm) : FVector4::Zero;
			}

			void FVector4::Rotate(const float _pitch, const float _yaw, const float _roll)
			{
				*this = FMatrix4::CreateRotationMatrix(_pitch, _yaw, _roll) * *this;
			}

			FVector4 FVector4::Rotated(const float _pitch, const float _yaw, const float _roll)
			{
				return FMatrix4::CreateRotationMatrix(_pitch, _yaw, _roll) * *this;
			}


			float FVector4::Distance(FVector4* v, FVector4* u)
			{
				return sqrtf((u->x - v->x)*(u->x - v->x) + (u->y - v->y)*(u->y - v->y) + (u->z - v->z)*(u->z - v->z));
			}

			float FVector4::SqrDistance(FVector4* v, FVector4* u)
			{
				return (u->x - v->x)*(u->x - v->x) + (u->y - v->y)*(u->y - v->y) + (u->z - v->z)*(u->z - v->z);
			}

			//FVector3 FVector3::RotationToDir(FVector3& _angles)
			//{
			//	FVector4 retour = FMatrix4::CreateRotationMatrix2(-_angles) * FVector4(forward);
			//	return retour;
			//}

			FVector3 FVector4::DirToRotation(FVector4& _vec)
			{
				FVector3 retour = _vec.Normalized();
				return{ atan2f(retour.z, retour.y) * RAD_TO_DEG, atan2f(retour.x, retour.z) * RAD_TO_DEG, atan2f(retour.y, retour.x) * RAD_TO_DEG };
			}

			FVector4 FVector4::Lerp(FVector4& _from, FVector4& _to, float _speed)
			{
				FVector3 temp = _to - _from;
				_speed = sqrtf(_speed*_speed / temp.SqrMagnitude());
				return _from + (temp * _speed);
			}

			FVector4 FVector4::LookDir(FVector4& _pos, FVector4& _target)
			{
				FVector3 temp = _target - _pos;
				return temp.Normalized();
			}

			FVector3 FVector4::LookRotation(FVector4& _pos, FVector4& _target)
			{
				return DirToRotation(LookDir(_pos, _target));
			}
#pragma endregion Methods

#pragma region Operators
			/*		Operator		*/

			void FVector4::operator*=(float _val)
			{
				x *= _val;
				y *= _val;
				z *= _val;
			}

			FVector4 FVector4::operator*(float _val)
			{
				return FVector4(x * _val, y * _val, z * _val);
			}

			void FVector4::operator/=(float _val)
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

			FVector4 FVector4::operator/(float _val)
			{
				try
				{
					if (!_val)
						THROW_PARADIGM_EXCEPTION_DOMAIN("null value pass as argument");
					
					return FVector4(x / _val, y / _val, z / _val);				
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
					return FVector4();
				}
			}

			FVector4 FVector4::operator+(const FVector3& _vector) const
			{
				return FVector4(x + _vector.x, y + _vector.y, z + _vector.z);
			}

			FVector4 FVector4::operator+(const FVector4& _vector) const
			{
				return FVector4(x + _vector.x, y + _vector.y, z + _vector.z);
			}

			void FVector4::operator+=(const FVector2& _vector)
			{
				x += _vector.x;
				y += _vector.y;
			}

			void FVector4::operator+=(const FVector3& _vector)
			{
				x += _vector.x;
				y += _vector.y;
				z += _vector.z;
			}

			void FVector4::operator+=(const FVector4& _vector)
			{
				x += _vector.x;
				y += _vector.y;
				z += _vector.z;
			}

			FVector4 FVector4::operator-(const FVector3& _vector) const
			{
				return FVector3(x - _vector.x, y - _vector.y, z - _vector.z);
			}

			FVector4 FVector4::operator-(const FVector4& _vector) const
			{
				return FVector4(x - _vector.x, y - _vector.y, z - _vector.z);
			}

			void FVector4::operator-=(const FVector2& _vector)
			{
				x -= _vector.x;
				y -= _vector.y;
			}

			void FVector4::operator-=(const FVector3& _vector)
			{
				x -= _vector.x;
				y -= _vector.y;
				z -= _vector.z;
			}

			void FVector4::operator-=(const FVector4& _vector)
			{
				x -= _vector.x;
				y -= _vector.y;
				z -= _vector.z;
			}

			FVector4 FVector4::operator-() const
			{
				return FVector4(-x, -y, -z);
			}

			float FVector4::operator,(const FVector3& other_vector) const
			{
				return DotProduct(other_vector);
			}

			float FVector4::operator,(const FVector4& other_vector) const
			{
				return DotProduct(other_vector);
			}

			void FVector4::operator=(const FVector2& other_vector)
			{
				x = other_vector.x;
				y = other_vector.y;
			}

			void FVector4::operator=(const FVector3& other_vector)
			{
				x = other_vector.x;
				y = other_vector.y;
				z = other_vector.z;
			}

			void FVector4::operator=(const UVector4& other_vector)
			{
				x = other_vector.x;
				y = other_vector.y;
				z = other_vector.z;
				w = other_vector.w;
			}

			bool FVector4::operator==(const FVector2& other_vector) const
			{
				return (Equalf(x, other_vector.x) && Equalf(y, other_vector.y));
			}

			bool FVector4::operator==(const FVector3& other_vector) const
			{
				return (Equalf(x, other_vector.x) && Equalf(y, other_vector.y) && Equalf(z, other_vector.z));
			}

			bool FVector4::operator==(const FVector4& other_vector) const
			{
				return (Equalf(x, other_vector.x) && Equalf(y, other_vector.y) && Equalf(z, other_vector.z) && Equalf(w, other_vector.w));
			}

			bool FVector4::operator!=(const FVector2& other_vector) const
			{
				return (!Equalf(x, other_vector.x) || !Equalf(y, other_vector.y));
			}

			bool FVector4::operator!=(const FVector3& other_vector) const
			{
				return (!Equalf(x, other_vector.x) || !Equalf(y, other_vector.y) || !Equalf(z, other_vector.z));
			}

			bool FVector4::operator!=(const FVector4& other_vector) const
			{
				return (!Equalf(x, other_vector.x) || !Equalf(y, other_vector.y) || !Equalf(z, other_vector.z) || !Equalf(w, other_vector.w));
			}

			bool FVector4::operator<(const FVector3& other_vector) const
			{
				return SqrMagnitude() < other_vector.SqrMagnitude();
			}

			bool FVector4::operator<(const FVector4& other_vector) const
			{
				return SqrMagnitude() < other_vector.SqrMagnitude();
			}

			bool FVector4::operator>(const FVector3& other_vector)  const
			{
				return SqrMagnitude() > other_vector.SqrMagnitude();
			}

			bool FVector4::operator>(const FVector4& other_vector)  const
			{
				return SqrMagnitude() > other_vector.SqrMagnitude();
			}

			bool FVector4::operator>=(const FVector3& other_vector) const
			{
				return SqrMagnitude() >= other_vector.SqrMagnitude();
			}

			bool FVector4::operator>=(const FVector4& other_vector) const
			{
				return SqrMagnitude() >= other_vector.SqrMagnitude();
			}

			bool FVector4::operator<=(const FVector3& other_vector) const
			{
				return SqrMagnitude() <= other_vector.SqrMagnitude();
			}

			bool FVector4::operator<=(const FVector4& other_vector) const
			{
				return SqrMagnitude() <= other_vector.SqrMagnitude();
			}

			FVector4 operator*(float _val, const FVector4& vector)
			{
				return FVector4(vector.x*_val, vector.y*_val, vector.z*_val);
			}

			FVector4 operator/(float _val, const FVector4& _vector)
			{
				try
				{
					if (!_val)
						THROW_PARADIGM_EXCEPTION_DOMAIN("null value pass as argument");
					return FVector4(_val / _vector.x, _val / _vector.y, _val / _vector.z);
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
					return FVector4();
				}
			}

			////////////////////////////////////////////////
			// FSTRING UTILITY
			//____________________________________
			FString operator+(const FString& _str, const FVector4& _vector)
			{
				return { _str + "Vector4 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ", w: " + FString::ToString<float>(_vector.w) + ")" };
			}

			FString operator+(const FVector4& _vector, const FString& _str)
			{
				return { "Vector4 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ", w: " + FString::ToString<float>(_vector.w) + ")" + _str };
			}

			FString operator+(const char* _str, const FVector4& _vector)
			{
				return _str + FString("Vector4 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ", w: " + FString::ToString<float>(_vector.w) + ")");
			}

			FString operator+(const FVector4& _vector, const char*  _str)
			{
				return FString("Vector4 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ", w: " + FString::ToString<float>(_vector.w) + ")" + _str);
			}

			void operator+=(FString& _str, const FVector4& _vector)
			{
				_str += "Vector4 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ", w: " + FString::ToString<float>(_vector.w) + ")";
			}

			void operator+=(const FVector4& _vector, FString& _str)
			{
				_str.Insert(0, "Vector4 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ", z: " + FString::ToString<float>(_vector.z) + ", w: " + FString::ToString<float>(_vector.w) + ")");
			}


			////////////////////////////////////////////////
			// IOSTREAM UTILITY
			//____________________________________
			std::ostream& operator<<(std::ostream& stream, const FVector4& vect)
			{
				return stream << "Vector4 (x: " << vect.x << ", y: " << vect.y << ", z: " << vect.z << ", w: " << vect.w << ")";
			}

			std::istream& operator>>(std::istream& stream, FVector4& vect)
			{
				char c;
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
						else
							vect.x = vect.y = vect.z = 0.0;
					}
				}
				else
					vect.x = vect.y = vect.z = 0.0;

				return stream;
			}			
#pragma endregion Operators

		}
	}
}