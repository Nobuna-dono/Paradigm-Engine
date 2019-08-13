#ifndef _URESOURCE_H_
#define _URESOURCE_H_

#include <NativeInterface/Graphics/NativeGraphicsHandles.h>
#include <NativeInterface/Graphics/NativeGraphicsEnums.h>

#include <Serialization/ParadigmSerialization.h>
#include <Property.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		struct UResource : public virtual IArchivable
		{
			META_SERIALIZABLE_ATTRIBUTES(UResource)

			public:
				////////////////////////////////////////////////
				// CONSTRUCTOR - DESTRUCTOR
				//____________________________________	
				/** Clasic resource constructor. */
				UResource()
					: m_ResourcePath{ "" }, m_ResourceName{ "" }
				{ REGISTER_ARCHIVE_CLASS }
				UResource(const UResource& _other)
				{
					m_ResourcePath = _other.m_ResourcePath;
					m_ResourceName = _other.m_ResourceName;
				}
				UResource(const FString& _resourcePath) 
					: m_ResourcePath{ _resourcePath }, m_ResourceName{ FString::FPathSlicer::Name(_resourcePath, "Resource/") }
				{}

			public:
				virtual void Archive(UArchive& out_archive)  override
				{ 
					ARCHIVE_MEMBER(UResource, out_archive, 0);
				}

				virtual bool Dearchive(UArchive& out_archive)  override
				{ 
					SKIP_ARCHIVE_INFO(out_archive);
					return false;	
				}

			public:
				////////////////////////////////////////////////
				// ELEMENT ACCESS
				//____________________________________	
				CUSTOM_PROPERTY(FString, ResourceName, { return m_ResourceName; }, { m_ResourceName = FString::FPathSlicer::Name(_value , "Resource/"); });
				CUSTOM_GETTER_PROPERTY(FString, ResourcePath, { return m_ResourcePath; });
				CUSTOM_GETTER_PROPERTY(FString, bSynchronized, { return m_bSynchronized; });
				
			protected:
				////////////////////////////////////////////////
				// DATA
				//____________________________________	
				FString m_ResourcePath{ "" };
				FString m_ResourceName{ "" };
				bool m_bSynchronized{ false };
		};
		SERIALIZABLE_INSTANCE(UResource)
	}
}
typedef ParadigmEngine::Resource::UResource UResource;

#define RESOURCE_PROPERTY(Type, Name)\
			 PROPERTY(Type, Name,\
				{ return CONCATENATE(m_, Name); },\
				{ m_bSynchronized = false; CONCATENATE(m_, Name) = _value; });


#define SERIALIZABLE_RESOURCE(ClassName)\
	struct ClassName : UResource


#define ASSET_CONSTRUCTOR(ClassName)\
	public:\
		ClassName() : UResource()\
		{ FParadigmEngine::FParadigmEngine::GetInstance().Archive.AddAssetReplica(this, #ClassName); }


#define ASSET_REPLICATION(ClassName)\
	public:\
		ClassName* Replicate() const override\
		{ return new ClassName(static_cast<const ClassName &>(*this)); }\


#define ASSET_ATTRIBUTES(ClassName)\
		ASSET_CONSTRUCTOR(ClassName);\
		ASSET_REPLICATION(ClassName);


typedef UKeyRegister KNativeResource;
typedef KNativeResource KResource;
#endif