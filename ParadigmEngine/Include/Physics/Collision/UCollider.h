#ifndef _DYNAMICCOLLIDER_
#define _DYNAMICCOLLIDER_
#include <Physics/Collision/UColliderShape.h>
#include <EngineFramework/MetaGear/ParadigmMetaGear.h>
#include <Physics/Collision/UCollision.h>
#include <Core/Dispach/FEvent.h>
#include <Property.h>

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			class UMetaCollider : public  UMetaGear, public virtual IArchivable
			{
				DEFAULT_SERIALIZABLE_CONSTRUCTOR(UMetaCollider)
				META_SERIALIZABLE_ATTRIBUTES(UMetaCollider)
					
				public:
					virtual void Archive(UArchive& out_archive)  override
					{
						ARCHIVE_MEMBER(UMetaCollider, out_archive, 2);
						SERIALIZE_MEMBER(out_archive, RelativePosition);
						SERIALIZE_ENUM(EColliderShape);
						SERIALIZE_DATA_MEMBER(out_archive, m_Shape);
					}

					virtual bool Dearchive(UArchive& out_archive)  override
					{
						SKIP_ARCHIVE_INFO(out_archive);
						DESERIALIZE_MEMBER(out_archive, RelativePosition);
						uint tmp;
						DESERIALIZE_MEMBER(out_archive, tmp);
						Shape = EColliderShape(tmp);
						return false;
					}

				public:
					//Property
					PROPERTY(EColliderShape, Shape, {return m_Shape;}, );

				public:
					//Data
					UColliderShape* ShapeData{nullptr};
					
					UKeyRegister CorrespondentKey{ INVALID_KEY_REGISTER };

					UVector3 RelativePosition{FVector3::Zero};

					FEvent<UCollision*> OnCollisionEnter;
					FEvent<UCollision*> OnCollisionStay;
					FEvent<UCollision*> OnCollisionExit;

					FEvent<UCollision*> OnTriggerEnter;
					FEvent<UCollision*> OnTriggerStay;
					FEvent<UCollision*> OnTriggerExit;
			};
			SERIALIZABLE_INSTANCE(UMetaCollider)

		}
	}
}
#include "UCollider.inl"
#endif // !_DYNAMICCOLLIDER_
