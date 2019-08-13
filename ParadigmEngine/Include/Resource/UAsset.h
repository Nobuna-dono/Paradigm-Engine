#ifndef _UASSET_H_
#define _UASSET_H_

#include <Resource/UResource.h>

namespace ParadigmEngine
{
	namespace Resource
	{

		struct UAsset : UResource
		{
			public:
				////////////////////////////////////////////////
				// CONSTRUCTOR - DESTRUCTOR
				//____________________________________	

				UAsset() = default;
				/** Classic asset constructor. */
				UAsset(const FString& _assetDest, const FString& _assetName)
					: UResource(_assetDest), m_ResourceName{ _assetName } {}


			public:
				////////////////////////////////////////////////
				// ELEMENT ACCESS
				//____________________________________	
				/** Return the Name of the asset. */
				const FString& ResourceName const
				{
					return m_ResourceName;
				}

			private:
				////////////////////////////////////////////////
				// DATA
				//____________________________________	
				FString m_ResourceName;
		};

	}
}
typedef ParadigmEngine::Resource::UAsset UAsset;
typedef KResource KAsset;

#endif

////___________________________________________________________________________
//// Engine Assets
////___________________________________________________________________________	
//typedef AssetHandle ArchetypeHandle;
//class UArchetype : public UAsset
//{
//public:
//	// Constructor - Destructor
//	UArchetype(const FString& _assetDest, const FString& _assetName, GEntity* _original = nullptr);
//	~UArchetype() = default;

//private:
//	// Data
//	GEntity* m_Entity{ nullptr };
//};

///** True body defined into Low Renderer namespace. */
//typedef AssetHandle MaterialHandle;
//class UMetaMaterial : public UAsset
//{
//public:
//	// Constructor - Destructor
//	UMetaMaterial(const FString& _assetDest, const FString& _assetName, GEntity* _original = nullptr);
//	~UMetaMaterial() = default;

//private:
//	// Data
//	ShaderHandle m_Shader;
//	//TArray<UDynamicShaderResource*> m_Resources;
//};

//typedef AssetHandle SceneHandle;
//class UScene : public UAsset
//{
//public:
//	// Constructor - Destructor
//	UArchetype(const FString& _assetDest, const FString& _assetName,

//public:
//	// Virtual Methods
//	/** Don't need this shit OAo) */
//	void SyncResource() override;

//private:
//	// Data
//	// ProcessorArray...
//	UArchetype m_Root;
//};