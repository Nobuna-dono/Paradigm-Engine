#include "../Include/InspectorField/InspectorIncludes.h"
#include "Include/InspectorField/UInspectorWidget.h"
#include "Core/Serialization/FArchive.h"
#include "Core\Utility\FColor.h"
#include "Include/InspectorField/UVariableField.h"

namespace ParadigmEditor
{
	UGearWidget::UGearWidget(QWidget* _parent, ParadigmEngine::Core::Serialization::UArchive& out_archive)
	{
		m_Box = new QGroupBox(_parent);
		m_Box->setBaseSize(400, 200);
		m_Box->setMinimumWidth(400);
		m_Box->setStyleSheet("background-color: #3F3E3F");

		// Riku Sutato!
		out_archive.LinkArchive(&m_GearArchive);

		//__________________________________________________________
		size_t gearId;
		FString gearName;
		FArchive::Deserialize(out_archive, gearId);
		FArchive::Deserialize(out_archive, gearName);
		// First is Key
		typeCode = m_GearInfo.first = gearId;
		// Second is Name
		m_GearInfo.second = gearName.ToConstChar();	
		
		m_Box->setTitle(m_GearInfo.second);
		m_Layout = new QFormLayout(m_Box);
		QFormLayout* tmp = static_cast<QFormLayout*>(_parent->layout());
		if (tmp)
			tmp->addRow(m_Box);
		
		uint countValues;
		FArchive::Deserialize<uint>(out_archive, countValues);

		for (uint i = 0; i < countValues; ++i)
		{
			//cut out the part that is needed
			CreateVariableField(out_archive);
		}
		
		//Break link
		out_archive.LinkArchive(nullptr);
	};

	UArchive& UGearWidget::GetArchive()
	{
		return m_GearArchive;
	}


	void UGearWidget::CreateVariableField(UArchive& out_archive)
	{
		size_t typeField;
		FString valueName;
		size_t typeCode;
		bool bMustBeDearchive;
		//__________________________________________________________

		FArchive::Deserialize<bool>(out_archive, bMustBeDearchive);
		FArchive::Deserialize<size_t>(out_archive, typeField); // Only for skip #code string name 
		FArchive::Deserialize<FString>(out_archive, valueName);
		FArchive::Deserialize<size_t>(out_archive, typeCode); // In case of Iarchivable value (none fundamental type)
		
		QString name = valueName.ToConstChar();

		UVariableField* Field{nullptr};
		
		//if (typeField == EVariableFieldType::VariableField_Bool)
		if (typeCode == typeid(bool).hash_code())
		{
			bool value;
			FArchive::Deserialize(out_archive, value);
			Field = new UBooleanField(m_Box, name, value);
		}
	//	else if (typeField == EVariableFieldType::VariableField_Integer)
		else if (typeCode == typeid(int).hash_code())
		{
			int value;
			FArchive::Deserialize(out_archive, value);
			Field = new UNumberField(m_Box, name, value);
		}
	//	else if (typeField == EVariableFieldType::VariableField_UnsignedInteger)
		else if (typeCode == typeid(unsigned int).hash_code())
		{
			unsigned int value;
			FArchive::Deserialize(out_archive, value);

			Field = new UNumberField(m_Box, name, value);// Don't not allow negative value
		}
	//	else if (typeField == EVariableFieldType::VariableField_Float)
		else if (typeCode == typeid(float).hash_code())
		{
			float value;
			FArchive::Deserialize(out_archive, value);
			Field = new UNumberField(m_Box, name, value);
		}
	//	else if (typeField == EVariableFieldType::VariableField_String)
		else if (typeCode == typeid(FString).hash_code())
		{
			FString value;
			FArchive::Deserialize(out_archive, value);
			Field = new UStringField(m_Box, name, value.GetData());
		}
		else if (typeCode == typeid(UVector3).hash_code())
		{
			UVector3 value;
			FArchive::Deserialize(out_archive, value);
			Field = new UVectorField(m_Box, name, value.x, value.y, value.z);
		}
		else if (typeCode == typeid(UVector4).hash_code() || typeCode == typeid(UColor).hash_code())
		{
			UVector4 value;
			FArchive::Deserialize(out_archive, value);
			Field = new UVectorField(m_Box, name, value.x, value.y, value.z, value.w);
		}
		else if (typeCode == typeid(UQuaternion).hash_code())
		{
			UQuaternion qvalue;
			FArchive::Deserialize(out_archive, qvalue);
			Field = new UVectorField(m_Box, name, qvalue);
		}
		//else if (typeField == EVariableFieldType::VariableField_Enum)
		else if (PARADIGM_ARCHIVE.IsEnum(typeCode))
		{
			TArray<FString> strValues = PARADIGM_ARCHIVE.GetEnumValues(typeCode);
			std::vector<QString> qtValues;
			
			for (auto it = strValues.Begin(); it != strValues.End(); ++it)
				qtValues.push_back((*it).GetData());

			uint value;
			FArchive::Deserialize(out_archive, value);
			Field = new UEnumField(m_Box, name, qtValues, value);
		}
		else
		{
			UGearWidget* newGear = new UGearWidget(static_cast<QWidget*>(m_Box->parent()), out_archive);
		}

		if (Field)
		{
			Field->SetMustBeDearchived(bMustBeDearchive);
			Field->AddToLayout(m_Layout);
			Field->m_OwnerGear = this;
		}
	}
}