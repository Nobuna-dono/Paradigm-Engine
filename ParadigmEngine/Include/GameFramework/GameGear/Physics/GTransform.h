#ifndef _GTRANSFORM_H_
#define _GTRANSFORM_H_

#include <GameFramework/GameGear/GGear.h>
#include <Physics/FTransform.h>
#include <Property.h>

namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear
		{
			namespace Physics
			{
				GEAR_CLASS(GTransform, UMetaTransform)
				{
					GEAR_CLASS_CONSTRUCTOR(GTransform, UMetaTransform);

				public:
					//Methods
					/** Returns the forward vector of this*/
					FVector3 Forward() const;
					/** Returns the Upward vector of this*/
					FVector3 Upward() const;
					/** Returns the Rightward vector of this*/
					FVector3 Rightward() const;

				public:
					//Methods 
					/** Orbit around a specified point and rotation*/
					void RotateAround(const FVector3& _center, const FQuaternion& _rotation);

					/** Orbit around a specified point and rotation*/
					inline void RotateAround(const FVector3& _center, const FVector3& _Angles);

					/** Orbit around a specified point and rotation but without change the orientation (circular translation)*/
					void TranslateAround(const FVector3& _center, const FQuaternion& _rotation);
					/** Orbit around a specified point and rotation but without change the orientation (circular translation)*/
					inline void TranslateAround(const FVector3& _center, const FVector3& _Angles);

					/** Move strait in the direction specified*/
					void Translate(const FVector3& _translation);
					/** Move strait in the direction specified*/
					void RelativeTranslate(const FVector3& _translation);
					/** Rotate by the spaecified rotation*/
					void Rotate(const FQuaternion& _rotation);
					/** Rotate by the spaecified rotation*/
					void RelativeRotate(const FQuaternion& _rotation);

					void ApplyScale(const FVector3& _scaling);

				public:
					//Property
					CUSTOM_PROPERTY(FVector3, Position, { return m_MetaGear->Position; }, { m_MetaGear->Position = _value; });
					CUSTOM_PROPERTY(FVector3, RelativePosition, { return m_MetaGear->RelativePosition; }, { m_MetaGear->RelativePosition = _value; });

					CUSTOM_PROPERTY(FVector3, Scale, { return m_MetaGear->Scale; }, { m_MetaGear->Scale = _value; });
					CUSTOM_PROPERTY(FVector3, RelativeScale, { return m_MetaGear->RelativeScale; }, { m_MetaGear->RelativeScale = _value; });

					CUSTOM_PROPERTY(FQuaternion, Rotation, { return m_MetaGear->Rotation; }, { m_MetaGear->Rotation = _value; });
					CUSTOM_PROPERTY(FQuaternion, RelativeRotation, { return m_MetaGear->RelativeRotation; }, { m_MetaGear->RelativeRotation = _value; });

					// will be true for every change on the position
					CUSTOM_GETTER_PROPERTY(bool, bPositionOutdated, { return m_MetaGear->bPositionOutdated; });
					// will be true for every change on the rotation
					CUSTOM_GETTER_PROPERTY(bool, bRotationOutdated, { return m_MetaGear->bRotationOutdated; });
					// will be true for every change on the scale
					CUSTOM_GETTER_PROPERTY(bool, bScaleOutdated, { return m_MetaGear->bScaleOutdated; });
					// will be true for every change
					CUSTOM_GETTER_PROPERTY(bool, bOutdated, { return m_MetaGear->bOutdated; });
				};

			}
		}
	}
}

typedef ParadigmEngine::GameFramework::GameGear::Physics::GTransform GTransform;
#endif // !_GTRANSFORM_H_
