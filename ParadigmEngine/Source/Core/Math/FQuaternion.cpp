#include <Include/Shortcut/ParadigmMath.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			const UQuaternion FQuaternion::Identity{ 1.0f, 0.0f, 0.0f, 0.0f };


			UQuaternion::operator FQuaternion()
			{
				return { w, x, y, z };
			}

			void UQuaternion::operator=(const FQuaternion& _val)
			{
				w = _val.w;
				x = _val.x;
				y = _val.y;
				z = _val.z;
			}

#pragma region Constructors
			FQuaternion::FQuaternion(UQuaternion&& _quat) : w{ std::move(_quat.w) }, x{ std::move(_quat.x) }, y{ std::move(_quat.y) }, z{ std::move(_quat.z) }
			{

			}

			FQuaternion::FQuaternion(const UQuaternion& _quat) : w{ _quat.w }, x{ _quat.x }, y{ _quat.y }, z{ _quat.z }
			{

			}

			FQuaternion::FQuaternion(float _a, float _x, float _y, float _z) : w{ _a }, x{ _x }, y{ _y }, z{ _z }
			{
			}

			FQuaternion::FQuaternion(float _w, FVector3 _vec) : FQuaternion::FQuaternion(_w, _vec.x, _vec.y, _vec.z)
			{
			}
#pragma endregion Constructors

#pragma region Methods
			FMatrix4 FQuaternion::ToMatrix4() const
			{
				FMatrix4 mat;
				mat[3] = mat[7] = mat[11] = mat[12] = mat[13] = mat[14] = 0;

				mat[0] = 1 - 2 * (y*y + z*z);
				mat[1] = 2 * x*y - 2 * w*z;
				mat[2] = 2 * w*y + 2 * x*z;
				mat[4] = 2 * w*z + 2 * x*y;
				mat[5] = 1 - 2 * (x*x + z*z);
				mat[6] = 2 * y*z - 2 * w*x;
				mat[8] = 2 * x*z - 2 * w*y;
				mat[9] = 2 * w*x + 2 * y*z;
				mat[10] = 1 - 2 * (x*x + y*y);
				mat[15] = 1;

				return mat;
			}

			FMatrix4 FQuaternion::ToTransposedMatrix4() const
			{
				FMatrix4 mat;
				mat[3] = mat[7] = mat[11] = mat[12] = mat[13] = mat[14] = 0;

				mat[0] = 1 - 2 * (y*y + z*z);
				mat[1] = 2 * w*z + 2 * x*y;
				mat[2] = 2 * x*z - 2 * w*y;
				mat[4] = 2 * x*y - 2 * w*z;
				mat[5] = 1 - 2 * (x*x + z*z);
				mat[6] = 2 * w*x + 2 * y*z;
				mat[8] = 2 * w*y + 2 * x*z;
				mat[9] = 2 * y*z - 2 * w*x;
				mat[10] = 1 - 2 * (x*x + y*y);
				mat[15] = 1;

				return mat;
			}

			FQuaternion FQuaternion::Conjugate() const
			{
				return FQuaternion(w, -x, -y, -z);
			}

			FQuaternion FQuaternion::Combine(FQuaternion& q2) const
			{
				//FQuaternion q1c = q2.Conjugate();
				FQuaternion q1c = Conjugate();
				//FQuaternion qMult = q2 * *this;
				FQuaternion qMult = *this * q2;

				FQuaternion out = q1c * qMult;
				return out;
			}

			float FQuaternion::DotProduct(const FQuaternion& _qua) const
			{
				return (w * _qua.w) + (x * _qua.x) + (y * _qua.y) + (z * _qua.z);
			}

			void FQuaternion::Normalize()
			{
				float norm = GetLength();
				if (norm > 0)
				{
					w /= norm;
					x /= norm;
					y /= norm;
					z /= norm;
				}
			}

			FVector3 FQuaternion::ToEulerAngles() const
			{
				FQuaternion q = GetNormalized();
				return { q.Pitch(), q.Yaw(), q.Roll() };
			};

			float FQuaternion::Yaw() const
			{
				double sinp = +2.0 * (w * y - z * x);
				if (fabs(sinp) >= 1)
					return TO_DEGREE((float)copysign(PI / 2, sinp)); // use 90 degrees if out of range
				return TO_DEGREE((float)asin(sinp));
				return TO_DEGREE(std::asinf(-2 * (x*z - w*y)));
			};

			float FQuaternion::Pitch() const
			{
				double sinr = +2.0 * (w * x + y * z);
				double cosr = +1.0 - 2.0 * (x * x + y * y);
				return TO_DEGREE((float)atan2(sinr, cosr));
				return TO_DEGREE(std::atan2f(2 * (y*z + w*x), w*w - x*x - y*y + z*z));
			};

			float FQuaternion::Roll() const
			{
				double siny = +2.0 * (w * z + x * y);
				double cosy = +1.0 - 2.0 * (y * y + z * z);
				return TO_DEGREE((float)atan2(siny, cosy));
				return TO_DEGREE( std::atan2f(2 * (x*y + w*z), w*w + x*x - y*y - z*z));
			};

			FQuaternion FQuaternion::GetInvert() const
			{
				return Conjugate() / GetsqLength();
			}

			FQuaternion FQuaternion::GetNormalized() const
			{
				FQuaternion q = *this;
				float length = GetLength();

				q.w /= length;
				q.x /= length;
				q.y /= length;
				q.z /= length;

				return q;
			}

			FVector3 FQuaternion::GetImaginary() const
			{
				return FVector3{ x,y,z };
			}

			float FQuaternion::GetReal() const
			{
				return w;
			}

			float FQuaternion::GetLength() const
			{
				return sqrtf(w * w + x * x + y * y + z * z);
			}

			float FQuaternion::GetsqLength() const
			{
				return w * w + x * x + y * y + z * z;
			}

			FVector3 FQuaternion::ToDirection() const
			{
				return (*this) * FVector3::Forward;
			}

#pragma endregion Methods

#pragma region Statics
			const FQuaternion FQuaternion::I(float _rot)
			{
				return FromAngleAxis(_rot, FVector3(1.f, 0.f, 0.f));
			}
			const FQuaternion FQuaternion::J(float _rot)
			{
				return FromAngleAxis(_rot, FVector3(0.f, 1.f, 0.f));
			}
			const FQuaternion FQuaternion::K(float _rot)
			{
				return FromAngleAxis(_rot, FVector3(0.f, 0.f, 1.f));
			}

			float FQuaternion::Angle(const FQuaternion& _q1, const FQuaternion& _q2)
			{
				FQuaternion qd = _q1.GetInvert() * _q2;

				return TO_DEGREE( 2.f * atan2(qd.GetImaginary().Magnitude(), qd.w));
			}

			FQuaternion FQuaternion::FromAngleAxis(float _thetaAngle, const FVector3& _rotateAxes)
			{
				float radAngle = (TO_RADIAN(_thetaAngle)) * 0.5f;
				FVector3 vec = (sin(radAngle)) * _rotateAxes.Normalized();
				return FQuaternion(cos(radAngle), FVector3(vec.x, vec.y, vec.z));
			}

			FQuaternion FQuaternion::FromEulerAngles(const float _pitch, const float _yaw, const float _roll)
			{
				FQuaternion q;
				// Abbreviations for the various angular functions
				float _cy = cosf(TO_RADIAN(_yaw) * 0.5f);
				float _sy = sinf(TO_RADIAN(_yaw) * 0.5f);
				float _cp = cosf(TO_RADIAN(_pitch) * 0.5f);
				float _sp = sinf(TO_RADIAN(_pitch) * 0.5f);
				float _cr = cosf(TO_RADIAN(_roll) * 0.5f);
				float _sr = sinf(TO_RADIAN(_roll) * 0.5f);

				q.w = _cr * _cp * _cy + _sr * _sp * _sy;
				q.x = _cr * _sp * _cy - _sr * _cp * _sy;
				q.y = _cr * _cp * _sy + _sr * _sp * _cy;
				q.z = _sr * _cp * _cy - _cr * _sp * _sy;

				//q.w = _cy * _cr * _cp + _sy * _sr * _sp;
				//q.x = _cy * _sr * _cp - _sy * _cr * _sp;
				//q.y = _cy * _cr * _sp + _sy * _sr * _cp;
				//q.z = _sy * _cr * _cp - _cy * _sr * _sp;
				return q;
			}

			FQuaternion FQuaternion::Lerp(const FQuaternion& _first, const FQuaternion& _second, float _ratio)
			{
				float currentAngle = _first.DotProduct(_second);
				float scale = 1.0f - _ratio;

				if (currentAngle < 0.0f)
				{
					const FQuaternion _negativeFirst = -_first;
					currentAngle *= -1;
					return ((_negativeFirst * scale) + (_second * _ratio));
				}

				return ((_first * scale) + (_second * _ratio));
			}

			FQuaternion FQuaternion::FromDirection_IOpt(const FVector3& _direction)
			{
				FVector3 v = FVector3(FVector3::Forward).CrossProduct(_direction);

				float angle = FVector3::Angle(FVector3::Forward, _direction);
				return FQuaternion::FromAngleAxis(angle, v);
			}

			FQuaternion FQuaternion::FromDirection(const FVector3& _direction, const FVector3& _up)
			{
				FVector3 forward = _direction.Normalized();

				FVector3 right = (_up.CrossProduct(forward)).Normalized();
				FVector3 actualUp = forward.CrossProduct(right);

				float num8 = (right.x + actualUp.y) + forward.z;
				FQuaternion quaternion;
				if (num8 > 0.f)
				{
					float num = sqrtf(num8 + 1.f);
					quaternion.w = num * 0.5f;
					num = 0.5f / num;
					quaternion.x = (actualUp.z - forward.y) * num;
					quaternion.y = (forward.x - right.z) * num;
					quaternion.z = (right.y - actualUp.x) * num;
					return quaternion;
				}
				if ((right.x >= actualUp.y) && (right.x >= forward.z))
				{
					float num7 = sqrtf(((1.f + right.x) - actualUp.y) - forward.z);
					float num4 = 0.5f / num7;
					quaternion.x = 0.5f * num7;
					quaternion.y = (right.y + actualUp.x) * num4;
					quaternion.z = (right.z + forward.x) * num4;
					quaternion.w = (actualUp.z - forward.y) * num4;
					return quaternion;
				}
				if (actualUp.y > forward.z)
				{
					float num6 = sqrtf(((1.f + actualUp.y) - right.x) - forward.z);
					float num3 = 0.5f / num6;
					quaternion.x = (actualUp.x + right.y) * num3;
					quaternion.y = 0.5f * num6;
					quaternion.z = (forward.y + actualUp.z) * num3;
					quaternion.w = (forward.x - right.z) * num3;
					return quaternion;
				}

				float num5 = sqrtf(((1.f + forward.z) - right.x) - actualUp.y);
				float num2 = 0.5f / num5;
				quaternion.x = (forward.x + right.z) * num2;
				quaternion.y = (forward.y + actualUp.z) * num2;
				quaternion.z = 0.5f * num5;
				quaternion.w = (right.y - actualUp.x) * num2;
				return quaternion;
			}
#pragma endregion Statics

#pragma region Operators
			FQuaternion::operator UQuaternion()
			{
				return {w,x,y,z};
			}

			void FQuaternion::operator=(const UQuaternion& _val)
			{
				w = _val.w;
				x = _val.x;
				y = _val.y;
				z = _val.z;
			}

			void FQuaternion::operator*=(const FQuaternion& _qua)
			{
				FQuaternion	q = this->operator*(_qua);

				w = q.w;
				x = q.x;
				y = q.y;
				z = q.z;
			}

			void FQuaternion::operator+=(const FQuaternion& _qua)
			{
				w += _qua.w;
				x += _qua.x;
				y += _qua.y;
				z += _qua.z;
			}

			void FQuaternion::operator-=(const FQuaternion& _qua)
			{
				w -= _qua.w;
				x -= _qua.x;
				y -= _qua.y;
				z -= _qua.z;
			}

			bool FQuaternion::operator==(const FQuaternion& _quat) const
			{
				//return ToEulerAngles() == _quat.ToEulerAngles();
				bool bx = Equalf(x, _quat.x);
				bool by = Equalf(y, _quat.y);
				bool bz = Equalf(z, _quat.z);
				bool bw = Equalf(w, _quat.w);
				return bx && by && bz && bw;
			}

			bool FQuaternion::operator!=(const FQuaternion& _quat) const
			{
				//return ToEulerAngles() != _quat.ToEulerAngles();
				bool bx = Equalf(x, _quat.x);
				bool by = Equalf(y, _quat.y);
				bool bz = Equalf(z, _quat.z);
				bool bw = Equalf(w, _quat.w);
				return !(bx && by && bz && bw);
			}

			FQuaternion FQuaternion::operator+(const FQuaternion& b) const
			{
				FQuaternion temp;

				temp.w = w + b.w;
				temp.x = x + b.x;
				temp.y = y + b.y;
				temp.z = z + b.z;

				return temp;
			}

			FQuaternion FQuaternion::operator-(const FQuaternion& b) const
			{
				FQuaternion temp;

				temp.w = w - b.w;
				temp.x = x - b.x;
				temp.y = y - b.y;
				temp.z = z - b.z;

				return temp;
			}

			FQuaternion FQuaternion::operator*(const FQuaternion& b) const
			{
				FQuaternion temp;

				temp.w = w * b.w - x * b.x - y * b.y - z * b.z;
				temp.x = w * b.x + x * b.w + y * b.z - z * b.y;
				temp.y = w * b.y + y * b.w + z * b.x - x * b.z;
				temp.z = w * b.z + x * b.y - y * b.x + z * b.w;
				/*temp.x = w * b.x + x * b.w - y * b.z + z * b.y;
				temp.y = w * b.y + y * b.w - z * b.x + x * b.z;
				temp.z = w * b.z - x * b.y + y * b.x + z * b.w;*/

				return temp;
			}

			FQuaternion FQuaternion::operator/(const FQuaternion& b) const
			{
				return *this * b.GetInvert();
			}

			FVector3 FQuaternion::operator*(const FVector3& vec) const
			{
				///V1				27		+	16	Multiplications
				//Vec4 tempVec = ToMatrix4() * Vec4(b);
				//return FVector3(tempVec.x, tempVec.y , tempVec.z);

				///V2	21 Multiplications
				//return xyz() * xyz().dotProduct(b) + xyz().cross(b)*(w * 2) + b* (w*w - xyz().dotProduct(xyz()));

				///V3	15 Multiplications
				//FVector3 tmp = 2 * GetInvert().GetImaginary().CrossProduct(vec);
				//return vec + w * tmp + GetImaginary().CrossProduct(tmp);

				///V4 Morg's version
				FQuaternion qt = (*this * FQuaternion(0.f, vec)) * this->GetInvert();
				return FVector3(qt.x, qt.y, qt.z);
			}

			FQuaternion FQuaternion::operator*(float _value) const
			{
				return FQuaternion(w*_value, x*_value, y *_value, z *_value);
			}

			FQuaternion FQuaternion::operator/(float _value)
			{
				try 
				{
					if (!_value)
						THROW_PARADIGM_EXCEPTION_ARGUMENT("Quaternion divide by null value");
					return FQuaternion(w / _value, x / _value, y / _value, z / _value);
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
					return FQuaternion();
				}
			}

			FQuaternion FQuaternion::operator-() const
			{
				return FQuaternion{ -w,-x,-y,-z };
			}

		

			////////////////////////////////////////////////
			// IOSTREAM UTILITY
			//____________________________________
			std::ostream& operator<<(std::ostream& stream, const FQuaternion& qua)
			{
				return stream << "FQuaternion (w: " << qua.w << ", x: " << qua.x << ", y: " << qua.y << ", z: " << qua.z << ")";
			}
#pragma endregion Operators
		}
	}
}

////////////////////////////////////////////////
// FSTRING UTILITY
//____________________________________
FString operator+(const FString& _str, const FQuaternion& _vector)
{
	return { _str + "Quaternion (w: " + FString::ToString<float>(_vector.x) + ", x: " + FString::ToString<float>(_vector.y) + ", y: " + FString::ToString<float>(_vector.z) + ", z: " + FString::ToString<float>(_vector.w) + ")" };
}

FString operator+(const FQuaternion& _vector, const FString& _str)
{
	return { "Quaternion (w: " + FString::ToString<float>(_vector.x) + ", x: " + FString::ToString<float>(_vector.y) + ", y: " + FString::ToString<float>(_vector.z) + ", z: " + FString::ToString<float>(_vector.w) + ")" + _str };
}

FString operator+(const char* _str, const FQuaternion& _vector)
{
	return _str + FString("Quaternion (w: " + FString::ToString<float>(_vector.x) + ", x: " + FString::ToString<float>(_vector.y) + ", y: " + FString::ToString<float>(_vector.z) + ", z: " + FString::ToString<float>(_vector.w) + ")");
}

FString operator+(const FQuaternion& _vector, const char*  _str)
{
	return FString("Quaternion (w: " + FString::ToString<float>(_vector.x) + ", x: " + FString::ToString<float>(_vector.y) + ", y: " + FString::ToString<float>(_vector.z) + ", z: " + FString::ToString<float>(_vector.w) + ")" + _str);
}

void operator+=(FString& _str, const FQuaternion& _vector)
{
	_str += "Quaternion (w: " + FString::ToString<float>(_vector.x) + ", x: " + FString::ToString<float>(_vector.y) + ", y: " + FString::ToString<float>(_vector.z) + ", z: " + FString::ToString<float>(_vector.w) + ")";
}

void operator+=(const FQuaternion& _vector, FString& _str)
{
	_str.Insert(0, "Quaternion (w: " + FString::ToString<float>(_vector.x) + ", x: " + FString::ToString<float>(_vector.y) + ", y: " + FString::ToString<float>(_vector.z) + ", z: " + FString::ToString<float>(_vector.w) + ")");
}