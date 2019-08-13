#include <EngineFramework/Factory/FMetaEntity.h>
#include <EngineFramework/Factory/FFactorySupervisor.h>
#include <FParadigmEngine.h>
#include <Physics/FTransform.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace Factory
		{
			void FMetaEntity::CreateMetaEntity(UKeyHandler<UMetaEntity>& out_metaEntity)
			{
				out_metaEntity = PARADIGM_FACTORY->CreateMetaEntity();
			}

			void FMetaEntity::DestroyGears(UMetaEntity* _metaEntity)
			{
				if (_metaEntity)
				{
					for each (auto pair in _metaEntity->Gears)
					{
						for (uint i = 0; i < pair.second.Count(); ++i)
						{
							PARADIGM_FACTORY->DestroyGear(_metaEntity, pair.second[i].Pointer);
						}
					}
					_metaEntity->Gears.clear();
				}
			}

			bool FMetaEntity::AddChild(UMetaEntity* _metaEntity, UMetaEntity* _newChild)
			{
				if (!_newChild || _metaEntity->m_Children.Contains(_newChild))
					return false;

				_metaEntity->m_Children.Add(_newChild);

				if (_newChild->GetParent() != _metaEntity)
					_newChild->m_Parent = _metaEntity;

				UMetaTransform* tr = _newChild->GetTransform();
				if (tr)
				{
					tr->RelativePosition = tr->RelativePosition;
					tr->RelativeRotation = tr->RelativeRotation;
					tr->RelativeScale = tr->RelativeScale;
				}
				OnPositionChanged(_newChild);
				OnRotationChanged(_newChild);
				OnScaleChanged(_newChild);

				return true;
			}

			void FMetaEntity::SetParent(UMetaEntity* _metaEntity, UMetaEntity* _value)
			{
				if (_metaEntity->m_Parent != _value)
				{
					if (!_value)
						_value = &PARADIGM_SCENE.Root;

					AddChild(_value, _metaEntity);
				}
			}

			void FMetaEntity::OnPositionChanged(UMetaEntity* _metaEntity)
			{
				for (uint i = 0; i < _metaEntity->m_Children.Count(); ++i)
				{
					UMetaTransform* tr = _metaEntity->m_Children[i]->GetTransform();
					if (tr)
						tr->RelativePosition = tr->RelativePosition;

					OnPositionChanged(_metaEntity->m_Children[i]);
				}
			}

			void FMetaEntity::OnRotationChanged(UMetaEntity* _metaEntity)
			{
				for (uint i = 0; i < _metaEntity->m_Children.Count(); ++i)
				{
					UMetaTransform* tr = _metaEntity->m_Children[i]->GetTransform();
					if (tr)
						tr->RelativeRotation = tr->RelativeRotation;

					OnRotationChanged(_metaEntity->m_Children[i]);
				}
			}

			void FMetaEntity::OnScaleChanged(UMetaEntity* _metaEntity)
			{
				for (uint i = 0; i < _metaEntity->m_Children.Count(); ++i)
				{
					UMetaTransform* tr = _metaEntity->m_Children[i]->GetTransform();
					if (tr)
						tr->RelativeScale = tr->RelativeScale;

					OnScaleChanged(_metaEntity->m_Children[i]);
				}
			}

			std::ostream& operator<<(std::ostream& _os, const UMetaEntity& _entity)
			{
				_os << _entity.Name;
				return _os;
			}

		}
	}
}