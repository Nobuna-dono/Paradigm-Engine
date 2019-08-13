#ifndef _UARCHIVE_H_
#define _UARCHIVE_H_

#include <FString.h>
#include <Property.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Serialization
		{
			class UArchive
			{
				//#define MAX_DATA_SIZE 1024
				//#define PACKAGE_SIGNATURE 0x26083995
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR
					//_____________________
					UArchive();
					UArchive(const UArchive& _other);
					UArchive(UArchive&& _other);

					UArchive operator=(const UArchive& _other);

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//_____________________
					/** Reset index and clear all the data. To use for recycling the archive. */
					void Clear();

					/** Reset index (Deserialize method will start from the begining). */
					void ResetIndex();

					/** Reset index (De/Serialize method will start from the begining). */
					bool IsValid();

					/** Link an archive to another one. Each time the index of this archive move forward, 
					the linked archive will get the values of the data pass over.*/
					void LinkArchive(UArchive* _archiveToLink)
					{
						m_LinkedArchive = _archiveToLink;
					}
					
				public:
					////////////////////////////////////////////////
					// DATA
					//_____________________
					/** A string which contains the serialized data. */
					FString Data;

					CUSTOM_PROPERTY(uint, Index,
					{ return m_Index; },
					{
						if (m_LinkedArchive)
						{
							m_LinkedArchive->Data += Data.Substring((uint64)m_Index, (uint64)_value);
							m_LinkedArchive->Index = m_LinkedArchive->Index  + (_value - m_Index);
						}
						m_Index = _value;
						if (_value < 1)
							m_Index = 1;
					});


				private:
					////////////////////////////////////////////////
					// DATA
					//_____________________
					uint m_Index;		
					UArchive* m_LinkedArchive{nullptr};
			};
			
			class IArchivable// : public FCloneable
			{
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//_____________________
					IArchivable() = default;
					~IArchivable() = default;

					//typedef IArchivable MetaType;

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//_____________________
					/** The method which allow to save the state of a data in an archive.
					Here, a sample of how must be implement this methods :
					bool Archive(UArchive& _toArchive) override {
					SERIALIZE_CLASS_ID(out_archive);
					SERIALIZE_NUMBER_ELEMENT(out_archive, 2);
					SERIALIZE_MEMBER(out_archive, Data.X);
					SERIALIZE_MEMBER(out_archive, Data.Y);
					...
					return true; } */
					virtual void Archive(UArchive& out_archive) {};
					
					/** The method which allow to rebuild a data from an archive.
					Here, a sample of how must be implement this methods :
					bool Dearchive(UArchive& _toArchive) override {
						SKIP_CLASS_ID(out_archive);
						SKIP_NUMBER_ELEMENT(out_archive);
						DESERIALIZE_MEMBER(out_archive, Data.X);
						DESERIALIZE_MEMBER(out_archive, Data.Y);
						...
						return true; } */
					virtual bool Dearchive(UArchive& _toArchive) { return false; };
					virtual IArchivable* Replicate() const { return nullptr; };

				protected:
					struct UMetaData
					{
						FString Name;
						void* Data;
						bool operator==(const UMetaData& _data) const
						{
							return Name == _data.Name;
						}
					};
			};

			template<typename T>
			class IMetaArchivable : public virtual IArchivable
			{
				typedef T MetaType;
			};


			struct UAssetFile : public UArchive
			{};
		}
	}
}
template<typename T>
using IMetaArchivable = ParadigmEngine::Core::Serialization::IMetaArchivable<T>;
typedef ParadigmEngine::Core::Serialization::IArchivable IArchivable;
typedef ParadigmEngine::Core::Serialization::UArchive UArchive;

#endif