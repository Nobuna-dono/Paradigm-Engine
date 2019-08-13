#ifndef _FRESOURCESUPERVISOR_H_
#define _FRESOURCESUPERVISOR_H_

#include <TKeyTable.h>
#include <Resource/FModel.h>
#include <Resource/FTexture.h>
#include <Resource/UShardShader.h>
#include <Resource/FShader.h>

#include <Serialization/FEnumerator.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		SERIALIZABLE_ENUM(EPrimitiveShape,		
			Cube,
			Cone,
			Cylinder,
			Sphere
		);
		
		class FResourceSupervisor
		{
			public:
				////////////////////////////////////////////////
				// CONSTRUCTOR - DESTRUCTOR
				//____________________________________	
				
				FResourceSupervisor() = default;
				~FResourceSupervisor();

			public:
				////////////////////////////////////////////////
				// PIPELINE FUNCTIONALITY
				//____________________________________	
				/** Load all meta data to rebuild resources tables. */
				bool Initialize();

				/** Save all resource state in meta data file and free memory. */
				bool Terminate();

			public:
				////////////////////////////////////////////////
				// ELEMENT ACCESS - GAME ASSET
				//____________________________________
				/** Load a model from path and return it's key. This function can load multiple mesh and texture. */
				bool LoadModel(const FString& _pathname);
				/** Load a custom model into the resource management. Return it's key. */
				KModel LoadModelFromMemory(UModel& model);
				/** Search a model from path and return it's key. If no found return @INVALID_KEY_REGISTER. */
				KModel ModelKey(const FString& _pathname);
				/** Get model according to the key. */
				UModel& Model(KModel _kModel);
				/** Get model according to the key. */
				bool GetModel(KModel _handle, UModel& out_shard) const;
				/** Get a primitive model. */
				UModel& Model(EPrimitiveShape _shape);

				/** Get model according to the key. */
				const UModel& Model(KModel _kModel) const;
				/** Try to get or load a model according to the _pathname. */
				UModel& Model(const FString& _pathname);
				/** Get the native key of a model according to the key. */
				//KNativeResource NativeModel(KModel _kModel) const;

				/** Load a shardshader from path and return it's key. If failed to load, return @INVALID_KEY_REGISTER. */
				KShardShader LoadShardShader(const FString& _pathname, const FString& _entryPoint = "Main");
				/** Search a shardshader from its path and return is ShardShaderHandle. If no found return @INVALID_KEY_REGISTER. */
				KShardShader ShardShaderKey(const FString& _pathname, const FString& _entryPoint = "Main");
				/** Get shardShader according to the key. */
				UShardShader& ShardShader(KShardShader _kShard);				
				/** Get shardShader according to the key. */
				const UShardShader& ShardShader(KShardShader _kShard) const;
				/** Get shardShader according to the key. */
				bool GetShardShader(KShardShader _handle, UShardShader& out_shard) const;
				/** Try to get or load a model according to the _pathname. */
				UShardShader& ShardShader(const FString& _pathname, const FString& _entryPoint = "Main");


				/** Load a shader from path and return it's key. If failed to load, return @INVALID_KEY_REGISTER. */
				KShader LoadShader(const FString& _pathname);
				/** Search a shader from its path and return is ShaderHandle. If no found return @INVALID_KEY_REGISTER. */
				KShader ShaderKey(const FString& _pathname);
				/** Get Shader according to the key. */
				UShader& Shader(KShader _kShader);
				/** Get Shader according to the key. */
				const UShader& Shader(KShader _kShader) const;
				/** Try to get or load a model according to the _pathname. */
				UShader& Shader(const FString& _pathname);
				/** Create a Shader. */
				KShader CreateShaderKey(const FString& _filename);
				/** Create a Shader. */
				UShader& CreateShader(const FString& _filename);

				/** Load a texture from path and return it's key. If failed to load, return @INVALID_KEY_REGISTER. */
				KTexture LoadTexture(const FString& _pathname);
				/** Search a texture from its path and return is TextureHandle. If no found return @INVALID_KEY_REGISTER. */
				KTexture TextureKey(const FString& _pathname);
				/** Get Texture according to the key. */
				UTexture& Texture(KTexture _kTexture);
				/** Get Texture according to the key. */
				bool GetTexture(KTexture _handle, UTexture& out_texture) const;
				/** Get Texture according to the key. */
				const UTexture& Texture(KTexture _kTexture) const;
				/** Get Texture according to the key. */
				UTexture& Texture(const FString& _pathname);


			public:
				////////////////////////////////////////////////
				// ELEMENT ACCESS - ENGINE ASSET
				//____________________________________
				/*ArchetypeHandle Archetype(const FString& _pathname);
				UArchetype* Archetype(ArchetypeHandle _handle);

				MaterialHandle Material(const FString& _pathname);
				UMetaMaterial* Material(MaterialHandle _handle);

				SceneHandle Scene(const FString& _pathname);
				UScene* Scene(SceneHandle _handle);*/

			private:
				////////////////////////////////////////////////
				// DATA
				//____________________________________
				// [OPTIMIZATION]
				// Work with TKeyMap<U, V> where U = FString filename,  and V = UResource (UModel) and where TKeyMap store a TMap<U, TKeyData<V>>
				
				TKeyTable<UModel> m_Models;
				TKeyTable<UShardShader> m_ShardShaders;
				TKeyTable<UShader> m_Shaders;
				TKeyTable<UTexture> m_Textures;

				/*TKeyTable<UArchetype*> m_Archetypes;
				TKeyTable<UMetaMaterial*> m_Materials;
				TKeyTable<UScene*> m_Scenes;*/

			public:
				////////////////////////////////////////////////
				// INTRA FUNCTIONALITY CLASS
				//____________________________________
				class FResourceProspector
				{
					public:
						template<typename T>
						static UKeyRegister Seek(TKeyTable<T>& _table, FString _pathname)
						{
							int i = 0;
							UKeyRegister key = INVALID_KEY_REGISTER;
							for (TKeyTable<T>::Iterator it = _table.Begin(); it != _table.End(); ++it, ++i)
							{
								if (_pathname == (*it).ResourcePath || _pathname == (*it).ResourceName)
								{
									_table.GetRegister(i, key);
									break;
								}
							}
							return key;
						}
				};

		};

		/*class FResourceSupervisor
		{
			public:
				////////////////////////////////////////////////
				// PIPELINE FUNCTIONALITY
				//____________________________________	
				static bool Initialize(UResourceSupervisor& out_supervisor)
				{
					THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR("");
				}

				static bool Terminate(UResourceSupervisor& out_supervisor)
				{
					THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR("");
				}*/

			//public:
				////////////////////////////////////////////////
				// FUNCTIONALITY
				//____________________________________	
				//ArchetypeHandle CreateArchetype(const FString& _pathname, const FString& _name, GEntity* _original);
				//MaterialHandle CreateMaterial(const FString& _pathname, const FString& _name/*,UMetaMaterial(?)*/);
				//SceneHandler CreateScene(const FString& _pathname, const FString& _name);
				//ShaderHandle CreateShader(const FString& _pathname, const FString& _name);
		//};
	}
}

typedef ParadigmEngine::Resource::EPrimitiveShape EPrimitiveShape;

#endif