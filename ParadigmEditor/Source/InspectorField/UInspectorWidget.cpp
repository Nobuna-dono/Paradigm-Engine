#include "Include/InspectorField/UInspectorWidget.h"
#include "Include/InspectorField/InspectorIncludes.h"
#include "FParadigmEngine.h"
#include "EngineFramework/Factory/FFactorySupervisor.h"
#include "GameFramework/GameEntity/GEntity.h"
#include "GameFramework/GameGear/Physics/GCollider.h"
#include "GameFramework/GameGear/Physics/GRigidBody.h"
#include "GameFramework/GameGear/LowRenderer/GMaterialViewver.h"
#include "GameFramework/GameGear/LowRenderer/GCamera.h"
#include "GameFramework/GameGear/LowRenderer/GMeshRender.h"
#include "GameFramework/GameGear/LowRenderer/GMeshShape.h"
#include "Core/Serialization/ParadigmSerialization.h"
#include "Core/Serialization/FArchive.h"


namespace ParadigmEditor
{
	void UInspectorWidget::Construct(QWidget* _parent, UKeyRegister _key)
	{
		m_parent = _parent;
		m_key = _key;
		m_InspectorScrolling = new QScrollArea(_parent);
		//m_InspectorScrolling->setMinimumWidth(475);
		m_InspectorScrolling->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		m_InspectorScrolling->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		_parent->layout()->addWidget(m_InspectorScrolling);
		m_content = new QWidget(_parent);
		m_content->setBaseSize(400, 400);
		m_content->setMinimumWidth(475);
		m_entity = new QFormLayout(m_content);
		m_content->setLayout(m_entity);
		m_content->setStyleSheet("background-color: #2F2E2F;");
		UMetaEntity* metaentity = PARADIGM_FACTORY->GetMetaEntity(_key);
		m_entity->addRow({metaentity->Name.GetData()}, new QCheckBox("isActive",m_content));

		if (metaentity)
		{
			UArchive archive = metaentity->GetArchived();

			uint countGear;
			FArchive::Deserialize<uint>(archive, countGear);			
			for (uint i = 0; i < countGear; ++i)
			{
				UGearWidget* gear = new UGearWidget(m_content, archive);
				gear->m_Inspector = this;
			}
		}
		else
			FPrint::Print("This meta entity was not found in the factory.");
		m_InspectorScrolling->setWidget(m_content);
	}

	void UInspectorWidget::Destroy()
	{
		if (m_InspectorScrolling)
		{
			m_InspectorScrolling->destroyed();
			delete m_InspectorScrolling;
		}
		m_InspectorScrolling = { nullptr };

		//if (content)
		//	delete content;
		m_content = { nullptr };

		//if (entity)
		//	delete entity;
		m_entity = { nullptr };
	}

	void UInspectorWidget::AddGear(const UArchivableData* _data)
	{
		/** Freestyle tryhard =D=) */
		if (m_key == INVALID_KEY_REGISTER)
			return;
		
		GEntity entity = PARADIGM_FACTORY->GetEntity(m_key);
		UArchive archive;
		
		_data->Replica->Archive(archive);
		FMetaEntity::AddGearFromArchive(entity.GetMetaEntity(), _data->Replica);
		
		archive.ResetIndex();
		Destroy();
		Construct(m_parent, m_key);
	}

	void UInspectorWidget::AddGear(EBasicGear _gear)
	{
		if (m_key == INVALID_KEY_REGISTER)
			return;

		GEntity entity = PARADIGM_FACTORY->GetEntity(m_key);
		UArchive archive;
		switch (_gear)
		{
			case COLLIDER:
				entity.AddGear<GCollider>().GetMetaData()->Archive(archive);
				break;
			case RIGIDBODY:
				entity.AddGear<GRigidbody>().GetMetaData()->Archive(archive);
				break;
			case CAMERA:
				entity.AddGear<GCamera>().GetMetaData()->Archive(archive);
				break;
			case MESHRENDER:
				entity.AddGear<GMeshRender>().GetMetaData()->Archive(archive);
				break;
			case MESHSHAPE:
				entity.AddGear<GMeshShape>().GetMetaData()->Archive(archive);
				break;
			case MATERIALVIEWVER:
				entity.AddGear<GMaterialViewver>().GetMetaData()->Archive(archive);
				break;
			default:
				break;
		}
		archive.ResetIndex();
		Destroy();
		Construct(m_parent, m_key);
	//	m_InspectorScrolling->setWidget(nullptr);
	//	{
	//		UGearWidget* gear = new UGearWidget(m_content, archive);
	//		gear->m_Inspector = this;
	//	}
	//	m_InspectorScrolling->setWidget(m_content);
	////	m_InspectorScrolling->adjustSize();
	//	m_content->adjustSize();
	}
}
