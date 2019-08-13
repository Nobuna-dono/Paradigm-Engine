#ifndef _USHADER_H_
#define _USHADER_H_

#include <ParadigmKeyword.h>
#include <Resource/UShardShader.h>
#include <Resource/UResource.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		struct UShader : UResource
		{
			public:
				////////////////////////////////////////////////
				// CONSTRUCTOR - DESTRUCTOR
				//____________________________________	
				ASSET_ATTRIBUTES(UShader);
				UShader(const FString& _resourcePath);
			
			
			public:
				////////////////////////////////////////////////
				// FUNCTIONALITY - ARCHIVAGE
				//____________________________________	
				void Archive(UArchive& out_archive)  override;
				bool Dearchive(UArchive& out_archive)  override;


			public:
				////////////////////////////////////////////////
				// PROPERTY DATA
				//____________________________________		
				RESOURCE_PROPERTY(KShardShader, kShardComputeShader);
				RESOURCE_PROPERTY(KShardShader, kShardControlShader);
				RESOURCE_PROPERTY(KShardShader, kShardEvaluationShader);
				RESOURCE_PROPERTY(KShardShader, kShardPixelShader);
				RESOURCE_PROPERTY(KShardShader, kShardGeometryShader);
				RESOURCE_PROPERTY(KShardShader, kShardVertexShader);
				/** A native resource key containing all shard shader keys and reflected resources (input layout, block buffer, textures, ...).*/
				DEFAULT_READONLY_PROPERTY(KNativeResource, kNativeShaderResources);
				

			public:
				////////////////////////////////////////////////
				// INTRA-FUNCTIONALITY CLASS
				// An Intra-class is a class which allow to manage private data of utilities. (Usefull for native functionnality)
				//____________________________________	
				/** An intra-class which manage the native buffer syncrhonization. */
				class FNativeSynchronizer
				{
					public:
						/** Native synchronization of shader's resources. */
						static void Synchronize(UShader& _shader, bool _brefresh = false);
				};
		};
		SERIALIZABLE_INSTANCE(UShader)
	}
}

typedef ParadigmEngine::Resource::UShader UShader;
typedef KResource KShader;

#endif