#include <GameFramework/GameEntity/GEntity.h>
#include <EngineFramework/Factory/FMetaEntity.h>
#include <GameFramework/GameGear/Physics/GTransform.h>
#include <FParadigmEngine.h>
#include <GameFramework/GameGear/GGear.h>

namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameEntity
		{
			GEntity::GEntity(UMetaEntity* _metaData) : m_MetaEntity{ _metaData }
			{

			}
			GEntity::GEntity(UKeyRegister _metaData) : m_MetaEntity{ PARADIGM_FACTORY->GetMetaEntity(_metaData), _metaData }
			{

			}

			GEntity GEntity::Instanciate(GEntity* _parent, UVector3 _position, UQuaternion _rotation, UVector3 _Scale)
			{
				auto handler = PARADIGM_FACTORY->CreateMetaEntity();
				GEntity out(handler.Register);
				out.m_MetaEntity = handler;
				//instanciate core gears
				GTransform tr = out.AddGear<GTransform>();
				tr.Position = _position;
				tr.Rotation = _rotation;
				tr.Scale = _Scale;

				FMetaEntity::SetParent(handler.Pointer, _parent ? _parent->GetMetaEntity() : nullptr);
				return out;
			}

			//void GEntity::AddGear(IArchivable* _original)
			//{
			//	GameFramework::GameGear::GGear<UMetaGear> metaGear{ (UMetaGear*)_original };
			//	//AddGear(metaGear);
			//}
			

			bool GEntity::Destroy(const GEntity* _original)
			{
				return PARADIGM_FACTORY->DestroyEntity(_original->GetMetaKey());
			}

			//GTransform GEntity::GetTransform() const
			//{
			//	return GetGear<GTransform>();
			//}

			GEntity GEntity::GetChild(FString _name)
			{
				return m_MetaEntity.Pointer->GetChild(_name);
			}

			GEntity GEntity::GetChild(uint _index)
			{
				return m_MetaEntity.Pointer->GetChild(_index);
			}

			TArray<GEntity> GEntity::GetChildrens()
			{
			//	return *(TArray<GEntity>*)&m_MetaEntity.Pointer->GetChildrens();

				sizeof(GEntity) == sizeof(UMetaEntity*);


				TArray<GEntity> out;
				TArray<UMetaEntity*>& in = m_MetaEntity.Pointer->GetChildrens();
				for(uint i = 0; i < in.Count(); ++i )
					out.Add(in[i]);
				return out;
			}

			GEntity GEntity::GetParent()
			{
				return m_MetaEntity.Pointer->GetParent();
			}

			bool GEntity::AddChild(GEntity _newChild)
			{
				return FMetaEntity::AddChild(m_MetaEntity.Pointer, _newChild);
			}

			void GEntity::SetParent(GEntity _newParent)
			{
				return FMetaEntity::SetParent(m_MetaEntity.Pointer, _newParent);
			}

			UMetaEntity* GEntity::GetMetaEntity() 
			{
				return m_MetaEntity.Pointer;
			}

			UKeyRegister GEntity::GetMetaKey() const
			{
				return m_MetaEntity.Register;
			}

			GEntity::operator UMetaEntity*()
			{
				return m_MetaEntity.Pointer;
			}
		}
	}
}
