#include <Resource/FResourceSupervisor.h>
#include <NativeInterface/Loader/Mesh/FMeshLoaderInterface.h>
#include <Core/RAII/FFileHandle.h>



namespace ParadigmEngine
{
	namespace Resource
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ELEMENT ACCESS - GAME ASSET
		//____________________________________________________________________________________________________________

		FResourceSupervisor::~FResourceSupervisor()
		{
			Terminate();
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// PIPELINE FUNCTIONALITY
		//____________________________________________________________________________________________________________
		bool FResourceSupervisor::Initialize()
		{
			// load the default shader texture and primitive.
			try
			{
				Texture("Resource/Texture/null.dds");
				Model("Resource/Model/Primitive/Cube.fbx");
				Model("Resource/Model/Primitive/Cone.fbx");
				Model("Resource/Model/Primitive/Cylinder.fbx");
				Model("Resource/Model/Primitive/Sphere.fbx");
			}
			PARADIGM_CATCH_EXCEPTION

			return true;
		}

		bool FResourceSupervisor::Terminate()
		{
			/** Archive Meta Data*/

			m_Models.Clear();
			m_ShardShaders.Clear();
			m_Shaders.Clear();
			m_Textures.Clear();

			return true;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// MODEL
		//____________________________________________________________________________________________________________
		bool FResourceSupervisor::LoadModel(const FString& _filename)
		{
			if (!_filename.Count())
				return INVALID_KEY_REGISTER;
			FString cleanPath = _filename;
			cleanPath.Remove("./");

			KModel kmodel = FResourceProspector::Seek(m_Models, _filename);

			if (kmodel == INVALID_KEY_REGISTER)
			{
				FMeshLoaderInterface loader = PARADIGM_NATIVE_MESH_LOADER;

				if (!loader->Initialize(cleanPath))
					return false;

				TArray<uint> materialIndices;
				TArray<UModel>& models = loader->BuildModels(&materialIndices);
				for (uint i = 0; i < models.Count(); ++i)
				{
					if (!i)
						kmodel = m_Models.Add(models[i]);
					else
						m_Models.Add(models[i]);
				}

				TArray<uint> uvsIndex;
				TArray<UTexture>& textures = loader->BuildTextures(&uvsIndex);
				for (uint i = 0; i < textures.Count(); ++i)
					m_Textures.Add(textures[i]);

				/////////////////////////////////////////
				// Try to build a mesh from material indices and uvsIndex
				//__________________________________
			}

			return true;
		}

		KModel FResourceSupervisor::LoadModelFromMemory(UModel& model)
		{
			return m_Models.Add(model);
		}

		KModel FResourceSupervisor::ModelKey(const FString& _filename)
		{
			if (!_filename.Count())
				return INVALID_KEY_REGISTER;
			uint i = 0;

			UKeyRegister key = FResourceProspector::Seek(m_Models, _filename);

			// If not found, try to load.
			if (key == INVALID_KEY_REGISTER)
			{
				if (LoadModel(_filename)) // if successfully load, get
					return ModelKey(_filename);
				else
					return key;
			}

			// Synchronize the model
			FModel::SyncResource(m_Models[key], false);
			return key;
		}

		UModel& FResourceSupervisor::Model(KModel _handle)
		{
			if (m_Models.Contains(_handle))
				return m_Models[_handle];
			THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid or corrupted KModel pass as argument.");
		}

		bool FResourceSupervisor::GetModel(KModel _handle, UModel& out_shard) const
		{
			if (m_Models.Contains(_handle))
				out_shard = m_Models[_handle];
			else return false;
			return true;
		}

		UModel& FResourceSupervisor::Model(EPrimitiveShape _shape)
		{
			return Model("Resource/Model/Primitive/" + FENUMERATOR(EPrimitiveShape)::ToString(_shape) + ".fbx");
		}

		const UModel& FResourceSupervisor::Model(KModel _handle) const
		{
			if (m_Models.Contains(_handle))
				return m_Models[_handle];
			THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid or corrupted KModel pass as argument.");
		}

		UModel& FResourceSupervisor::Model(const FString& _filename)
		{
			return Model(ModelKey(_filename));
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// SHARDSHADER
		//____________________________________________________________________________________________________________
		KShardShader FResourceSupervisor::LoadShardShader(const FString& _filename, const FString& _entryPoint)
		{
			if (!_filename.Count())
				return INVALID_KEY_REGISTER;

			bool success;
			FFileHandle(_filename, EFileOpenMode::Read, success);
			if (!success)
				return INVALID_KEY_REGISTER;

			UKeyRegister key = FResourceProspector::Seek(m_ShardShaders, _filename);
			
			if (key == INVALID_KEY_REGISTER)
				key = m_ShardShaders.Add({ _filename , ToEnumEShaderType(FString::FPathSlicer::Extension(_filename, true)), _entryPoint });

			return key;
		}

		KShardShader FResourceSupervisor::ShardShaderKey(const FString& _filename, const FString& _entryPoint)
		{
			if (!_filename.Count())
				return INVALID_KEY_REGISTER;

			uint i = 0;
			UKeyRegister key = FResourceProspector::Seek(m_ShardShaders, _filename);

			if (key == INVALID_KEY_REGISTER)
				return LoadShardShader(_filename, _entryPoint);

			return key;
		}

		UShardShader& FResourceSupervisor::ShardShader(KShardShader _handle)
		{
			if (m_ShardShaders.Contains(_handle))
				return m_ShardShaders[_handle];
			THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid or corrupted KShardShader pass as argument.");
		}

		const UShardShader& FResourceSupervisor::ShardShader(KShardShader _handle) const
		{
			if (m_ShardShaders.Contains(_handle))
				return m_ShardShaders[_handle];
			THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid or corrupted KShardShader pass as argument.");
		}

		bool FResourceSupervisor::GetShardShader(KShardShader _handle, UShardShader& out_shard) const
		{			
			if (m_ShardShaders.Contains(_handle))
				out_shard = m_ShardShaders[_handle];
			else
				return false;			
			return true;
		}

		UShardShader& FResourceSupervisor::ShardShader(const FString& _pathname, const FString& _entryPoint)
		{
			return ShardShader(ShardShaderKey(_pathname, _entryPoint));
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// SHADER
		//____________________________________________________________________________________________________________
		KShader FResourceSupervisor::LoadShader(const FString& _filename)
		{
			if (!_filename.Count())
				return INVALID_KEY_REGISTER;

			bool success;
			FFileHandle FileHandle(_filename, EFileOpenMode::Read, success);
			if (!success)
				return INVALID_KEY_REGISTER;
			
			UKeyRegister key = FResourceProspector::Seek(m_Shaders, _filename);
			if(key == INVALID_KEY_REGISTER)						
				key = m_Shaders.Add({ _filename });

			FString data = FileHandle.ToString();
			// Dearchive data to extract and rebuild the shader			
			THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR("");

			return key;
		}

		KShader FResourceSupervisor::ShaderKey(const FString& _filename)
		{
			if (!_filename.Count())
				return INVALID_KEY_REGISTER;

			uint i = 0;
			UKeyRegister key = FResourceProspector::Seek(m_Shaders, _filename);

			if (key == INVALID_KEY_REGISTER)
			{
				key = LoadShader(_filename);
				if (key == INVALID_KEY_REGISTER)
					key = CreateShaderKey(_filename);
			}

			return key;
		}

		UShader& FResourceSupervisor::Shader(KShader _kShader)
		{
			if (m_Shaders.Contains(_kShader))
				return m_Shaders[_kShader];
			THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid or corrupted KShader pass as argument.");
		}

		const UShader& FResourceSupervisor::Shader(KShader _kShader) const
		{
			if (m_Shaders.Contains(_kShader))
				return m_Shaders[_kShader];
			THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid or corrupted KShader pass as argument.");
		}
		
		UShader& FResourceSupervisor::Shader(const FString& _pathname)
		{
			return Shader(ShaderKey(_pathname));
		}

		KShader FResourceSupervisor::CreateShaderKey(const FString& _filename)
		{
			if (!_filename.Count())
				return INVALID_KEY_REGISTER;

			UKeyRegister key = FResourceProspector::Seek(m_Shaders, _filename);
			if (key == INVALID_KEY_REGISTER)			
				key = m_Shaders.Add({_filename});
			
			return key;
		}

		UShader& FResourceSupervisor::CreateShader(const FString& _filename)
		{
			return Shader(CreateShaderKey(_filename));
		}



		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// TEXTURE
		//____________________________________________________________________________________________________________
		KTexture FResourceSupervisor::LoadTexture(const FString& _filename)
		{
			if (!_filename.Count())
				return INVALID_KEY_REGISTER;

			bool success = false;
			FFileHandle FileHandle(_filename, EFileOpenMode::Read, success);
			if (!success)
				return INVALID_KEY_REGISTER;
			
			KTexture key = FResourceProspector::Seek(m_Textures, _filename);
			
			if(key == INVALID_KEY_REGISTER)
				key = m_Textures.Add({ _filename });
			
			return key;
		}

		KTexture FResourceSupervisor::TextureKey(const FString& _filename)
		{
			if (!_filename.Count())
				return INVALID_KEY_REGISTER;

			uint i = 0;
			UKeyRegister key = FResourceProspector::Seek(m_Textures, _filename);

			if (key == INVALID_KEY_REGISTER)
			{
				key = LoadTexture(_filename);
				if (key == INVALID_KEY_REGISTER)
					return key;
			}

			// Native Sync
			 UTexture::FNativeSynchronizer::Synchronize(m_Textures[key]);

			return key;
		}

		UTexture& FResourceSupervisor::Texture(KTexture _handle) 
		{
			if (m_Textures.Contains(_handle))
				return m_Textures[_handle];
			THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid or corrupted KTexture pass as argument.");
		}

		bool FResourceSupervisor::GetTexture(KTexture _handle, UTexture& out_texture) const
		{
			if (m_Textures.Contains(_handle))
				out_texture = m_Textures[_handle];
			else return false;
			return true;
		}

		const UTexture& FResourceSupervisor::Texture(KTexture _handle) const
		{
			if (m_Textures.Contains(_handle))
				return m_Textures[_handle];
			THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid or corrupted KTexture pass as argument.");
		}

		UTexture& FResourceSupervisor::Texture(const FString& _pathname)
		{
			return Texture(TextureKey(_pathname));
		}

	}
}