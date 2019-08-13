#ifndef _UTRANSFORM_H_ 
#define _UTRANSFORM_H_

#include <EngineFramework/MetaGear/ParadigmMetaGear.h>
#include <ParadigmMath.h>
#include <Property.h>
#include <atomic>

namespace ParadigmEngine
{
	namespace Physics
	{
		/** Class representing the position,  the orientation and the scale of an object in the scene*/		
		METAGEAR_CLASS(UMetaTransform)// : public UMetaGear
		{
			METAGEAR_ATTRIBUTES(UMetaTransform)

			public:
				//Constructors
				UMetaTransform(const FVector3& _position, const FQuaternion& _rotation = FQuaternion(FQuaternion::Identity), const FVector3& _scale = { 1.f,1.f,1.f });
				UMetaTransform(const UMetaTransform&);

			public:
				//Destructor
				friend class FTransform;

			public:
				////////////////////////////////////////////////
				// FUNCTIONALITY - ARCHIVAGE
				//____________________________________	
				void Archive(UArchive& out_archive)  override
				{
					ARCHIVE_MEMBER(UMetaTransform, out_archive, 3);

					SERIALIZABLE_ATOMIC_MEMBER(UVector3, float, out_archive, m_Position);
					SERIALIZABLE_ATOMIC_MEMBER(UVector3, float, out_archive, m_Scale);
					SERIALIZABLE_ATOMIC_MEMBER(UQuaternion, float, out_archive, m_Rotation);
				}

				bool Dearchive(UArchive& out_archive)  override
				{
					SKIP_ARCHIVE_INFO(out_archive);

					DESERIALIZE_ATOMIC_MEMBER(UVector3, out_archive, Position);
					DESERIALIZE_ATOMIC_MEMBER(UVector3, out_archive, Scale);
					DESERIALIZE_ATOMIC_MEMBER(UQuaternion, out_archive, Rotation);
					return true;
				}

			public:

				/** Returns the forward vector of this*/
				inline FVector3 Forward() const { return FVector3(FVector3::Forward) * m_Rotation; };
				/** Returns the Upward vector of this*/
				inline FVector3 Upward() const { return FVector3(FVector3::Up) * m_Rotation; };
				/** Returns the Rightward vector of this*/
				inline FVector3 Rightward() const { return FVector3(FVector3::Right) * m_Rotation; };

				UMatrix4 ToMatrix() const;

				operator FMatrix4();
				void operator=(const UMetaTransform&);
				bool operator!=(const UMetaTransform&) const;
				bool operator==(const UMetaTransform&) const;

				void Updated();
			public:
				//Property
				CUSTOM_PROPERTY(FVector3, Position, , );
				CUSTOM_PROPERTY(FVector3, RelativePosition, , );

				CUSTOM_PROPERTY(FVector3, Scale, , );
				CUSTOM_PROPERTY(FVector3, RelativeScale, , );

				CUSTOM_PROPERTY(FQuaternion, Rotation, , );
				CUSTOM_PROPERTY(FQuaternion, RelativeRotation, , );

				// will be true for every change on the position
				CUSTOM_GETTER_PROPERTY(bool, bPositionOutdated, { return m_bPositionOutdated; });
				// will be true for every change on the rotation
				CUSTOM_GETTER_PROPERTY(bool, bRotationOutdated, { return m_bRotationOutdated; });
				// will be true for every change on the scale
				CUSTOM_GETTER_PROPERTY(bool, bScaleOutdated, { return m_bScaleOutdated; });
				// will be true for every change
				CUSTOM_GETTER_PROPERTY(bool, bOutdated, { return m_bOutdated; });

				CUSTOM_DEFAULT_PROPERTY(bool, isStatic);
			private:
				//Data
				std::atomic<FVector3> m_Position{ FVector3::Zero };
				std::atomic<FVector3> m_RelativePosition{ FVector3::Zero };

				std::atomic<FVector3> m_Scale{ FVector3::One };
				std::atomic<FVector3> m_RelativeScale{ FVector3::One };

				std::atomic<FQuaternion> m_Rotation{ FQuaternion::Identity };
				std::atomic<FQuaternion> m_RelativeRotation{ FQuaternion::Identity };

				std::atomic_bool m_bPositionOutdated{ false }; // will be true for every change on the position
				std::atomic_bool m_bRotationOutdated{ false }; // will be true for every change on the rotation
				std::atomic_bool m_bScaleOutdated{ false }; // will be true for every change on the scale
				std::atomic_bool m_bOutdated{ false }; // will be true for every change

				std::atomic_bool m_isStatic{ false };
		};
		SERIALIZABLE_INSTANCE(UMetaTransform)
	}
}

typedef ParadigmEngine::Physics::UMetaTransform UMetaTransform;


#endif