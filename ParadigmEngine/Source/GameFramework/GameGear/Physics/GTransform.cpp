#include <GameFramework\GameGear\Physics\GTransform.h>


namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear
		{
			namespace Physics
			{
				//Methods
				FVector3 GTransform::Forward() const
				{ 
					return m_MetaGear->Forward(); 
				};
				
				FVector3 GTransform::Upward() const
				{ 
					return m_MetaGear->Upward(); 
				};

				FVector3 GTransform::Rightward() const
				{ 
					return m_MetaGear->Rightward(); 
				};

				//Methods 
				void GTransform::RotateAround(const FVector3& _center, const FQuaternion& _rotation)
				{
					FTransform::RotateAround(*m_MetaGear, _center, _rotation);
				}

				void GTransform::RotateAround(const FVector3& _center, const FVector3& _Angles)
				{
					FTransform::RotateAround(*m_MetaGear, _center, _Angles);
				}

				void GTransform::TranslateAround(const FVector3& _center, const FQuaternion& _rotation)
				{
					FTransform::TranslateAround(*m_MetaGear, _center, _rotation);
				}
				void GTransform::TranslateAround(const FVector3& _center, const FVector3& _Angles)
				{
					FTransform::TranslateAround(*m_MetaGear, _center, _Angles);
				}

				void GTransform::Translate(const FVector3& _translation)
				{
					FTransform::Translate(*m_MetaGear, _translation);
				}
				void GTransform::RelativeTranslate(const FVector3& _translation)
				{
					FTransform::RelativeTranslate(*m_MetaGear, _translation);
				}
				void GTransform::Rotate(const FQuaternion& _rotation)
				{
					FTransform::Rotate(*m_MetaGear, _rotation);
				}
				void GTransform::RelativeRotate(const FQuaternion& _rotation)
				{
					FTransform::RelativeRotate(*m_MetaGear, _rotation);
				}

				void GTransform::ApplyScale(const FVector3& _scaling)
				{
					FTransform::ApplyScale(*m_MetaGear, _scaling);
				}
			}
		}
	}
}