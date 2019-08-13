#ifndef _URIGIDBODY_H_
#define _URIGIDBODY_H_

#include <EngineFramework\MetaGear\ParadigmMetaGear.h>
#include <ParadigmTypedef.h>
#include <ParadigmMath.h>
#include <FLayer.h>
#include <IKeyTable.h>
#include <Property.h>

typedef LayerName PhysicsLayer;
typedef Layer PhysicsLayerID;
typedef LayerMask PhysicsLayerMask;

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Force
		{
			METAGEAR_CLASS(UMetaRigidbody)
			{
				METAGEAR_ATTRIBUTES(UMetaRigidbody)

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY - ARCHIVAGE
					//____________________________________	
					void Archive(UArchive& out_archive)  override
					{
						ARCHIVE_MEMBER(UMetaRigidbody, out_archive, 8);

						SERIALIZE_MEMBER(out_archive, m_isKinematic);
						SERIALIZE_MEMBER(out_archive, m_useGravity);
						SERIALIZE_MEMBER(out_archive, m_freezePositionX);
						SERIALIZE_MEMBER(out_archive, m_freezePositionY);
						SERIALIZE_MEMBER(out_archive, m_freezePositionZ);
						SERIALIZE_MEMBER(out_archive, m_freezeRotationX);
						SERIALIZE_MEMBER(out_archive, m_freezeRotationY);
						SERIALIZE_MEMBER(out_archive, m_freezeRotationZ);						
					}

					bool Dearchive(UArchive& out_archive)  override
					{
						SKIP_ARCHIVE_INFO(out_archive);

						DESERIALIZE_MEMBER(out_archive, m_isKinematic);
						DESERIALIZE_MEMBER(out_archive, m_useGravity);
						DESERIALIZE_MEMBER(out_archive, m_freezePositionX);
						DESERIALIZE_MEMBER(out_archive, m_freezePositionY);
						DESERIALIZE_MEMBER(out_archive, m_freezePositionZ);
						DESERIALIZE_MEMBER(out_archive, m_freezeRotationX);
						DESERIALIZE_MEMBER(out_archive, m_freezeRotationY);
						DESERIALIZE_MEMBER(out_archive, m_freezeRotationZ);
						return true;
					}

				public:
					enum EMovingState { IDLE, MOVING };

					float Mass{ 1.f };
					PhysicsLayer PhysicsTag{ "Default" };
					EMovingState MovingState{ IDLE };
					UKeyRegister CorrespondentKey{ INVALID_KEY_REGISTER };
					//UVector3 Gravity{0,-10,0};
					CUSTOM_PROPERTY(bool, useGravity, , );
					CUSTOM_PROPERTY(bool, isKinematic, { return m_isKinematic; }, { if (m_isKinematic != _value){ m_isKinematic = _value; m_outdated = true;}});
					CUSTOM_PROPERTY(bool, freezePositionX, { return m_freezePositionX; }, { if (m_freezePositionX != _value){ m_freezePositionX = _value; m_outdated = true;}} );
					CUSTOM_PROPERTY(bool, freezePositionY, { return m_freezePositionY; }, { if (m_freezePositionY != _value){ m_freezePositionY = _value; m_outdated = true;}} );
					CUSTOM_PROPERTY(bool, freezePositionZ, { return m_freezePositionZ; }, { if (m_freezePositionZ != _value){ m_freezePositionZ = _value; m_outdated = true;}} );
					CUSTOM_PROPERTY(bool, freezeRotationX, { return m_freezeRotationX; }, { if (m_freezeRotationX != _value){ m_freezeRotationX = _value; m_outdated = true;}} );
					CUSTOM_PROPERTY(bool, freezeRotationY, { return m_freezeRotationY; }, { if (m_freezeRotationY != _value){ m_freezeRotationY = _value; m_outdated = true;}} );
					CUSTOM_PROPERTY(bool, freezeRotationZ, { return m_freezeRotationZ; }, { if (m_freezeRotationZ != _value){ m_freezeRotationZ = _value; m_outdated = true;}} );
					CUSTOM_DEFAULT_PROPERTY(bool, outdated);
					CUSTOM_DEFAULT_PROPERTY(bool, useGravityoutdated);

				private:
					bool m_isKinematic{false};//1
					bool m_freezePositionX{false};//2
					bool m_freezePositionY{false};//4
					bool m_freezePositionZ{false};//8
					bool m_freezeRotationX{false};//16
					bool m_freezeRotationY{false};//32
					bool m_freezeRotationZ{false};//64
					bool m_outdated{true};//128
					bool m_useGravity{true};//256
					bool m_useGravityoutdated{true};//256

				//union 
				//{
				//	struct 
				//	{
				//		bits32 m_isKinematic : 1;//1
				//		bits32 m_freezePositionX : 1;//2
				//		bits32 m_freezePositionY : 1;//4
				//		bits32 m_freezePositionZ : 1;//8
				//		bits32 m_freezeRotationX : 1;//16
				//		bits32 m_freezeRotationY : 1;//32
				//		bits32 m_freezeRotationZ : 1;//64
				//		bits32 m_outdated : 1;//128
				//		bits32 m_useGravity : 1;//256
				//		bits32 m_useGravityoutdated : 1;//256
				//		bits32 : 23;
				//	};

				//	bits32 _bytes{0x180};
				//};
			};
			SERIALIZABLE_INSTANCE(UMetaRigidbody)
		}
	}
}
typedef ParadigmEngine::Physics::Force::UMetaRigidbody UMetaRigidbody;

#endif