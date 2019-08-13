#ifndef _USHARDSHADER_H_
#define _USHARDSHADER_H_

#include <Resource/UResource.h>

namespace ParadigmEngine
{
	namespace Resource
	{	

		SERIALIZABLE_RESOURCE(UShardShader)
		{			
			public:
				////////////////////////////////////////////////
				// CONSTRUCTOR - DESTRUCTOR
				//____________________________________	
				ASSET_ATTRIBUTES(UShardShader);
				UShardShader(const FString& _resourcePathname, EShaderType _type, FString _entryPoint = "Main");
			
			public:
				////////////////////////////////////////////////
				// FUNCTIONALITY - ARCHIVAGE
				//____________________________________	
				void Archive(UArchive& out_archive)  override
				{
					SERIALIZE_ENUM(EShaderType);

					ARCHIVE_MEMBER(UShardShader, out_archive, 2);
					SERIALIZE_MEMBER(out_archive, Type);
					SERIALIZE_MEMBER(out_archive, EntryPoint);
				}

				bool Dearchive(UArchive& out_archive)  override
				{
					SKIP_ARCHIVE_INFO(out_archive);
					DESERIALIZE_MEMBER(out_archive, Type);
					DESERIALIZE_MEMBER(out_archive, EntryPoint);
					return true;
				}

			public:
				////////////////////////////////////////////////
				// DATA
				//____________________________________					
				/** Shader type (Vertex, Fragment, ...). */
				EShaderType Type{ EShaderType::EShaderType_Unknow };
				FString EntryPoint{ "" };
		};
		SERIALIZABLE_INSTANCE(UShardShader)


		static EShaderType ToEnumEShaderType(FString _extension)
		{
			if (_extension == ".vs" || _extension == ".vert" || _extension == ".vsh" || _extension == ".glsv" || _extension == ".vertex")
				return EShaderType::EShaderType_Vertex;
			else if (_extension == ".fs" || _extension == ".ps" || _extension == ".frag" || _extension == ".fsh" || _extension == ".glsf" || _extension == ".fragment")
				return EShaderType::EShaderType_Pixel;
			else if (_extension == ".gs" || _extension == ".geom" || _extension == ".geo" || _extension == ".geometry")
				return EShaderType::EShaderType_Geometry;
			else if (_extension == ".tcs" || _extension == ".tesc")
				return EShaderType::EShaderType_TessellationControl;
			else if (_extension == ".tes" || _extension == ".tese")
				return EShaderType::EShaderType_TessellationEvaluation;
			else if (_extension == ".cs" || _extension == ".comp" || _extension == ".compute")
				return EShaderType::EShaderType_Compute;
			else
				return EShaderType::EShaderType_Unknow;
		}

	}
}
typedef ParadigmEngine::Resource::UShardShader UShardShader;
typedef KResource KShardShader;
#endif //_FSHARDSHADER_H_