#include <Physics/FTransform.h>

namespace ParadigmEngine
{
	namespace Physics
	{

			void FTransform::RotateAround(UMetaTransform& _tr, const FVector3& _center, const FQuaternion& _rotation)
			{
				FVector3 temp = _tr.m_Position;
				while (!_tr.m_Position.compare_exchange_strong(temp, _center + (_rotation.GetInvert() * (temp - _center)), std::memory_order_release, std::memory_order_acquire))
				{
					temp = _tr.m_Position;
				}

				Rotate(_tr, _rotation);
			}

			void FTransform::TranslateAround(UMetaTransform& _tr, const FVector3& _center, const FQuaternion& _rotation)
			{
				FVector3 temp = _tr.m_Position;
				while (!_tr.m_Position.compare_exchange_strong(temp, _center + _rotation.GetInvert()*(temp - _center), std::memory_order_release, std::memory_order_acquire))
				{
					temp = _tr.m_Position;
				}
			}

			void FTransform::Translate(UMetaTransform& _tr, const FVector3& _translation)
			{
				//std::atomic_fetch_add_explicit(&_tr.m_Position, _translation, std::memory_order_release);
				FVector3 temp = _tr.m_Position;
				while (!_tr.m_Position.compare_exchange_strong(temp, temp + _translation, std::memory_order_release, std::memory_order_acquire))
				{
					temp = _tr.m_Position;
				}
			}

			void FTransform::RelativeTranslate(UMetaTransform& _tr, const FVector3& _translation)
			{
				FVector3 temp = _tr.m_RelativePosition;
				while (!_tr.m_RelativePosition.compare_exchange_strong(
					temp, temp + _translation,
					std::memory_order_release, std::memory_order_acquire))
				{
					temp = _tr.m_RelativePosition;
				}
				//std::atomic_fetch_add_explicit(&_tr.m_RelativePosition, _translation, std::memory_order_release);
			}

			void FTransform::Rotate(UMetaTransform& _tr, const FQuaternion& _rotation)
			{
				FQuaternion tempr = _tr.m_Rotation;
				while (!_tr.m_Rotation.compare_exchange_strong(tempr, tempr * _rotation, std::memory_order_release, std::memory_order_acquire))
				{
					tempr = _tr.m_Rotation;
				}
			}

			void FTransform::RelativeRotate(UMetaTransform& _tr, const FQuaternion& _rotation)
			{
				FQuaternion tempr = _tr.m_RelativeRotation;
				while (!_tr.m_RelativeRotation.compare_exchange_strong(tempr, tempr * _rotation, std::memory_order_release, std::memory_order_acquire))
				{
					tempr = _tr.m_RelativeRotation;
				}
			}

			void FTransform::ApplyScale(UMetaTransform& _tr, const FVector3& _scaling)
			{
				FVector3 temp = _tr.m_RelativeScale;
				while (!_tr.m_RelativeScale.compare_exchange_strong(
					temp, { temp.x * _scaling.x, temp.y * _scaling.y, temp.z * _scaling.z },
					std::memory_order_release, std::memory_order_acquire))
				{
					temp = _tr.m_RelativeScale;
				}
			}
	}
}