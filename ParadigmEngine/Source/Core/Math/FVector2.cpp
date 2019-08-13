#include <ParadigmMath.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			const FVector2 FVector2::Zero{ 0.0, 0.0 };
			const FVector2 FVector2::Up{ 0.0, 1.0 };
			const FVector2 FVector2::Down{ 0.0, -1.0 };
			const FVector2 FVector2::Left{ -1.0, 0.0 };
			const FVector2 FVector2::Right{ 1.0, 0.0 };

			////////////////////////////////////////////////
			// OPERATOR
			//____________________________________
			UVector2::operator FVector2()
			{
				return { x, y };
			}
			UVector2::operator FVector3()
			{
				return { x, y };
			}
			UVector2::operator FVector4()
			{
				return { x, y };
			}
			UVector2::operator float*()
			{
				return &x;
			}

			void UVector2::operator=(const FVector2& _val)
			{
				x = _val.x;
				y = _val.y;
			}


			FVector2::operator UVector2()
			{
				return { x, y };
			}
			FVector2::operator FVector3()
			{
				return { x, y };
			}
			FVector2::operator FVector4()
			{
				return { x, y };
			}

			////////////////////////////////////////////////
			// CONSTRUCTOR - DESTRUCTOR
			//____________________________________	

			FVector2::FVector2(UVector2&& _vec)
				: x{ std::move(_vec.x) }, y{ std::move(_vec.y) }
			{}

			FVector2::FVector2(const UVector2& _vec2) 
				: x{ _vec2.x }, y{ _vec2.y }
			{}

			FVector2::FVector2(float new_x, float new_y) 
				: x{ new_x }, y{ new_y }
			{}


			////////////////////////////////////////////////
			// FUNCTIONALITY
			//____________________________________	
			float FVector2::DotProduct(const FVector2& vect2) const
			{
				return ((x*vect2.x) + (y*vect2.y));
			}

			float FVector2::Magnitude_IOpt() // as getMagnitude...
			{
				float sqrNorm = (x*x) + (y*y);
				float diff = (Norm*Norm) - sqrNorm;
				if (!((diff < 0.1f) && (-diff < 0.1f)))
					Norm = sqrtf(sqrNorm);
				return Norm;
			}

			float FVector2::Magnitude() const// as getMagnitude...
			{
				return sqrtf((x*x) + (y*y));
			}

			float FVector2::SqrMagnitude() const
			{
				return (x*x) + (y*y);
			}

			void FVector2::Normalize()
			{
				Magnitude_IOpt();
				if (Norm > 0)
				{
					x /= Norm;
					y /= Norm;
				}
			}

			FVector2 FVector2::Normalized()
			{
				FVector2 new_vector(0, 0);
				Magnitude_IOpt();
				if (Norm > 0)
				{
					new_vector.x = x / Norm;
					new_vector.y = y / Norm;
				}
				return new_vector;
			}

			////////////////////////////////////////////////
			// OPERATORS
			//____________________________________				
			FVector2 FVector2::operator+(const FVector2& vector) const
			{
				return FVector2(x + vector.x, y + vector.y);
			}

			void FVector2::operator+=(const FVector2& vector)
			{
				x += vector.x;
				y += vector.y;
			}

			FVector2 FVector2::operator-(const FVector2& vector) const
			{
				return FVector2(x - vector.x, y - vector.y);
			}

			void FVector2::operator-=(const FVector2& vector)
			{
				x -= vector.x;
				y -= vector.y;
			}

			FVector2 FVector2::operator*(float _val)
			{
				return FVector2(x * _val, y * _val);
			}

			void FVector2::operator*=(float _val)
			{
				x *= _val;
				y *= _val;
			}

			FVector2 FVector2::operator/(float _val)
			{				
				try
				{
					if (!_val)
						THROW_PARADIGM_EXCEPTION_DOMAIN("null value pass as argument");

					return FVector2(x / _val, y / _val);
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
					return FVector2();
				}
			}

			void FVector2::operator/=(float _val)
			{
				try
				{
					if (!_val)
						THROW_PARADIGM_EXCEPTION_DOMAIN("null value pass as argument");

					x /= _val;
					y /= _val;
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
				}
			}

			FVector2 FVector2::operator-() const
			{
				return FVector2(-x, -y);
			}
			
			void FVector2::operator=(const UVector2& _vec)
			{
				x = _vec.x;
				y = _vec.y;
			}

			void FVector2::operator=(const FVector3& _vec)
			{
				x = _vec.x;
				y = _vec.y;
			}

			void FVector2::operator=(const FVector4& _vec)
			{
				x = _vec.x;
				y = _vec.y;
			}

			bool FVector2::operator==(const FVector2& other_vector) const
			{
				return Equalf(x, other_vector.x) && Equalf(y, other_vector.y);
			}

			bool FVector2::operator==(const FVector3& other_vector) const
			{
				return Equalf(x, other_vector.x) && Equalf(y, other_vector.y);
			}

			bool FVector2::operator==(const FVector4& other_vector) const
			{
				return Equalf(x, other_vector.x) && Equalf(y, other_vector.y);
			}

			bool FVector2::operator!=(const FVector2& other_vector) const
			{
				return !Equalf(x, other_vector.x) && Equalf(y, other_vector.y);
			}

			bool FVector2::operator!=(const FVector3& other_vector) const
			{
				return !Equalf(x, other_vector.x) && Equalf(y, other_vector.y);
			}

			bool FVector2::operator!=(const FVector4& other_vector) const
			{
				return !Equalf(x, other_vector.x) && Equalf(y, other_vector.y);
			}

			bool FVector2::operator<(const FVector2& other_vector) const
			{
				return SqrMagnitude() < other_vector.SqrMagnitude();
			}

			bool FVector2::operator>(const FVector2& other_vector)  const
			{
				return SqrMagnitude() > other_vector.SqrMagnitude();
			}

			bool FVector2::operator<=(const FVector2& other_vector) const
			{
				return SqrMagnitude() <= other_vector.SqrMagnitude();
			}

			bool FVector2::operator>=(const FVector2& other_vector) const
			{
				return SqrMagnitude() >= other_vector.SqrMagnitude();
			}

			float FVector2::operator,(const FVector2& other_vector) const
			{
				return DotProduct(other_vector);
			}
			
			FVector2 operator*(float f, const FVector2& vector)
			{
				return FVector2(vector.x*f, vector.y*f);
			}

			FVector2 operator/(float _val, const FVector2& _vector)
			{
				try
				{
					if (!(_vector.x * _vector.y))
						THROW_PARADIGM_EXCEPTION_DOMAIN("Divide up vector with null value.");

					return FVector2(_val / _vector.x, _val / _vector.y);
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
					return FVector2();
				}
			}

			////////////////////////////////////////////////
			// FSTRING UTILITY
			//____________________________________
			FString operator+(const FString& _str, const FVector2& _vector)
			{
				return { _str + "Vector2 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ")" };
			}

			FString operator+(const FVector2& _vector, const FString& _str)
			{
				return { "Vector2 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ")" + _str };
			}

			FString operator+(const char* _str, const FVector2& _vector)
			{
				return _str + FString("Vector2 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ")");
			}

			FString operator+(const FVector2& _vector, const char*  _str)
			{
				return FString("Vector2 (x: " + FString::ToString<float>(_vector.x) + ", y: " + FString::ToString<float>(_vector.y) + ")" + _str);
			}

			void operator+=(FString& _str, const FVector2& vector)
			{
					_str += "Vector2 (x: " + FString::ToString<float>(vector.x) + ", y: " + FString::ToString<float>(vector.y) + ")";
			}

			void operator+=(const FVector2& vector, FString& _str)
			{
				_str.Insert(0, "Vector2 (x: " + FString::ToString<float>(vector.x) + ", y: " +FString::ToString<float>(vector.y) + ")");
			}


			////////////////////////////////////////////////
			// IOSTREAM UTILITY
			//____________________________________
			std::ostream& operator<<(std::ostream& stream, const FVector2& vect)
			{
				return stream << "Vector2 (x: " << vect.x << ", y: " << vect.y << ")";
			}
		}
	}
}




//std::istream& operator>>(std::istream& stream, FVector2& vect)
//{
//	stream >> vect.x >> vect.C(); //>> vect.y;
//
//	if (vect.C() == ',')
//		stream >> vect.y;
//	else if (vect.C() == 'f')
//	{
//		stream >> vect.C();
//		if (vect.C() == ',')
//			stream >> vect.y;
//	}
//	else
//		vect.x = vect.y = 0.0;
//
//	return stream;
//}