#pragma once
#ifndef _FTRANSFORM_H_ 
#define _FTRANSFORM_H_
#include "../Shortcut/ParadigmMath.h"
#include <Physics/UTransform.h>


namespace ParadigmEngine
{
	namespace Physics
	{
			/** Class representing the position,  the orientation and the scale of an object in the scene*/
			class FTransform
			{
				public:
				//Methods 
				/** Orbit around a specified point and rotation*/
				static void RotateAround(UMetaTransform& _tr, const FVector3& _center, const FQuaternion& _rotation);

				/** Orbit around a specified point and rotation*/
				static inline void RotateAround(UMetaTransform& _tr, const FVector3& _center, const FVector3& _Angles) { RotateAround(_tr, _center, FQuaternion::FromEulerAngles(_Angles)); };

				/** Orbit around a specified point and rotation but without change the orientation (circular translation)*/
				static void TranslateAround(UMetaTransform& _tr, const FVector3& _center, const FQuaternion& _rotation);
				/** Orbit around a specified point and rotation but without change the orientation (circular translation)*/
				static inline void TranslateAround(UMetaTransform& _tr, const FVector3& _center, const FVector3& _Angles) { TranslateAround(_tr, _center, FQuaternion::FromEulerAngles(_Angles)); };

				/** Move strait in the direction specified*/
				static void Translate(UMetaTransform& _tr, const FVector3& _translation);
				/** Move strait in the direction specified*/
				static void RelativeTranslate(UMetaTransform& _tr, const FVector3& _translation);
				/** Rotate by the spaecified rotation*/
				static void Rotate(UMetaTransform& _tr, const FQuaternion& _rotation);
				/** Rotate by the spaecified rotation*/
				static void RelativeRotate(UMetaTransform& _tr, const FQuaternion& _rotation);

				static void ApplyScale(UMetaTransform& _tr, const FVector3& _scaling);
			};
			//	ostream& operator<<(ostream& _os,const FTransform& _tr);
	}
}

typedef ParadigmEngine::Physics::FTransform FTransform;

#endif