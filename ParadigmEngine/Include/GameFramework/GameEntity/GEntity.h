#ifndef _GOBJECT_H_
#define _GOBJECT_H_

#include <ParadigmMath.h>
#include <EngineFramework/Factory/FMetaEntity.h>
#include <Serialization\ParadigmSerialization.h>

namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear 
		{
			namespace Physics
			{
				class GTransform;
			}
		}

		namespace GameEntity
		{
			class GEntity
			{
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________	
					GEntity(UMetaEntity*);
					GEntity(UKeyRegister);
					~GEntity() = default;

				public:
					////////////////////////////////////////////////
					// STATIC FUNCTIONALITY
					//____________________________________	
					/** Create a new GEntity and copy the one in parameter if it is not nullptr*/
					static GEntity Instanciate(GEntity* _parent = nullptr, UVector3 _position = FVector3::Zero, UQuaternion _rotation = FQuaternion::Identity, UVector3 _Scale = FVector3::One);
					/** Destroy an entity and all his gears*/
					static bool Destroy(const GEntity*);

				public:
					////////////////////////////////////////////////
					// Gears FUNCTIONALITY
					//____________________________________	
					template <typename GearT>
					GearT AddGear(GearT* _original = nullptr);

					//void AddGear(IArchivable* _original);

					/** Returns a gear of the specified type if there is one, 
						else return an invalid gear.*/
					template <typename GearT>
					GearT GetGear() const;
					
					//GTransform GetTransform() const;

					/** Returns an array of gears of the specified type if there is one,
					else return an empty array.*/
					template <typename GearT>
					TArray<GearT> GetGears() const;

					template <typename GearT>
					bool RemoveGear(GearT* _original = nullptr);

					////////////////////////////////////////////////
					// Hierarchy FUNCTIONALITY
					//____________________________________	

					/** Returns a child with the specified name*/
					GEntity GetChild(FString _name);
					/** Returns a child with the specified index*/
					GEntity GetChild(uint _index);

					/** Returns a child that contain a gear of the specified type*/
					template<typename GearT>
					GEntity GetChild();

					/** Returns a reference to the array of children*/
					TArray<GEntity> GetChildrens();

					/** Returns the parent*/
					GEntity GetParent();

					bool AddChild(GEntity _newChild);

					/** Change the parent entity if nullptr set to Root*/
					void SetParent(GEntity _newParent);

					////////////////////////////////////////////////
					// Others FUNCTIONALITY
					//____________________________________	
					/** Returns the meta type class*/
					UMetaEntity* GetMetaEntity();

					/** Returns the key of the meta type class*/
					UKeyRegister GetMetaKey() const;

					operator UMetaEntity*();

				private:
					////////////////////////////////////////////////
					// DATA
					//____________________________________	
					UKeyHandler<UMetaEntity> m_MetaEntity;
			};
		}
	}
}
#include "GEntity.inl"

typedef ParadigmEngine::GameFramework::GameEntity::GEntity GEntity;

#endif // !_GOBJECT_H_
