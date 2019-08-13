#include <NativeInterface/Loader/Mesh/FAssimpInterface.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Loader
		{
			namespace Mesh
			{
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// ASSIMP ADDITIONNAL FUNCTIONALITY
				//____________________________________________________________________________________________________________
				aiNode* aiFindNode(aiNode* _rootNode, const FString& _name)
				{
					if (_name == "")
						return nullptr;

					if (_name == _rootNode->mName.data)
						return _rootNode;

					aiNode* node = nullptr;
					for (uint i = 0; i < _rootNode->mNumChildren; ++i)
					{
						node = aiFindNode(_rootNode->mChildren[i], _name);
						if (node)
							return node;
					}

					return nullptr;
				}

				void aiTransformNodeLegacy(aiMatrix4x4& out_transform, const aiNode* _rootNode)
				{
					if (!_rootNode)
						return;
					if (_rootNode->mParent)
					{
						aiTransformNodeLegacy(out_transform, _rootNode->mParent);
						out_transform *= _rootNode->mTransformation;
					}
					else
						out_transform = _rootNode->mTransformation;
				}

				//________________________________________________________________________________________________________________________________________________________________________________________________________________________
				
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// CONSTRUCTOR - DESTRUCTOR
				//____________________________________________________________________________________________________________
				FAssimpInterface::~FAssimpInterface()
				{
					Terminate();
				}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// PIPELINE FUNCTIONALITY
				//____________________________________________________________________________________________________________
				bool FAssimpInterface::Initialize(const FString& _filename, void* _desc)
				{
					m_CurrentFilename = _filename;
					//m_aiScene = m_aiImporter.ReadFile(m_CurrentFiylename, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_FlipUVs | aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder | aiProcess_PreTransformVertices);// | aiProcess_FlipUVs | aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder*/);
					m_aiScene = m_aiImporter.ReadFile(m_CurrentFilename, aiProcess_CalcTangentSpace | 
						aiProcess_GenSmoothNormals | 
						aiProcess_JoinIdenticalVertices | 
						aiProcess_ImproveCacheLocality | 
						aiProcess_LimitBoneWeights | 
						aiProcess_RemoveRedundantMaterials | 
						aiProcess_SplitLargeMeshes | 
						aiProcess_Triangulate | 
						aiProcess_GenUVCoords | 
						aiProcess_SortByPType | 
						aiProcess_FindDegenerates | 
						aiProcess_FindInvalidData | 
						aiProcess_FixInfacingNormals |

						/** Direct3D11 specifics*/
						aiProcess_FlipUVs | 
						aiProcess_MakeLeftHanded | 
						aiProcess_FlipWindingOrder | 
						aiProcess_PreTransformVertices |
						
						aiProcess_OptimizeMeshes |
						0);

					if (m_aiScene)
					{
						m_MeshEntries.Reserve(m_aiScene->mNumMeshes);
						m_Textures.Reserve(m_aiScene->mNumMaterials);
						return true;
					}
					
					FPrint::Print("Failed to load mesh '" + _filename + "'.\n| Error : " + m_aiImporter.GetErrorString(), EParadigmDebugLevel::ERROR_LEVEL);
					return false;
				}

				void FAssimpInterface::Terminate()
				{
					m_MeshEntries.Clear();
					m_Textures.Clear();
				}


				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// ELEMENT ACCESS
				//____________________________________________________________________________________________________________
				uint FAssimpInterface::GetMeshCount()
				{
					return m_aiScene->mNumMeshes;
				}

				uint FAssimpInterface::GetTextureCount()
				{
					return m_aiScene->mNumMaterials;
				}


				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// FUNCTIONALITY
				//____________________________________________________________________________________________________________
				TArray<UModel> FAssimpInterface::BuildModels(TArray<uint>* _materialIndices)
				{
					if (!m_aiScene)
						THROW_PARADIGM_EXCEPTION("Try to work with none initialized mesh loader interface.");
					uint entries = m_aiScene->mNumMeshes;

					TArray<UModel> models;
					models.Reserve(entries);
					
					UModel model(m_CurrentFilename);

					for (uint i = 0; i < entries; ++i)
					{
						if (InitModel(m_aiScene->mMeshes[i], model))
						{
							if (i)
								model.ResourceName = FString::FPathSlicer::Extension(m_CurrentFilename) + "_" + FString::ToString(i);
							if(_materialIndices)
								_materialIndices->Add(m_aiScene->mMeshes[i]->mMaterialIndex);
							models.Add(model);
						}
					}

					models.Compact();

					return models;
				}
				
				void FAssimpInterface::BuildModels(TArray<UModel*>* out_models, TArray<uint>* _materialIndices)
				{
					if (!m_aiScene)
						THROW_PARADIGM_EXCEPTION("Try to work with none initialized mesh loader interface.");

					if (!out_models)
						THROW_PARADIGM_EXCEPTION_ARGUMENT("Null array of referenced model pass as argument.");

					uint entries = out_models->Count();
					
					UModel model(m_CurrentFilename);

					for (uint i = 0; i < entries; ++i)
					{
						if (InitModel(m_aiScene->mMeshes[i], model))
						{
							if (i)
								model.ResourceName = FString::FPathSlicer::Extension(m_CurrentFilename) + "_" + FString::ToString(i);
							if (_materialIndices)
								_materialIndices->Add(m_aiScene->mMeshes[i]->mMaterialIndex);
							*out_models->Get(i) = model;
						}
					}
				}


				TArray<UTexture> FAssimpInterface::BuildTextures(TArray<uint>* _uvsIndex)
				{
					if (!m_aiScene)
						THROW_PARADIGM_EXCEPTION("Try to work with none initialized mesh loader interface.");

					uint entries = m_aiScene->mNumMaterials;

					TArray<UTexture> textures;
					textures.Reserve(entries);

					for (uint i = 0; i < entries; ++i)
					{
						const aiMaterial* pMaterial = m_aiScene->mMaterials[i];

						for (uint i = aiTextureType_DIFFUSE; i < aiTextureType_UNKNOWN + 1; ++i)
							InitTextures(pMaterial, (aiTextureType)i, textures, _uvsIndex);
					}

					return textures;
				}

				void FAssimpInterface::BuildTextures(TArray<UTexture*>* out_textures, TArray<uint>* _uvsIndex)
				{
					if (!m_aiScene)
						THROW_PARADIGM_EXCEPTION("Try to work with none initialized mesh loader interface.");
					
					if (!out_textures)
						THROW_PARADIGM_EXCEPTION_ARGUMENT("Null array of referenced textures pass as argument.");

					uint entries = out_textures->Count();

					TArray<UTexture> textures;
					textures.Reserve(entries);

					for (uint i = 0; i < entries; ++i)
					{
						const aiMaterial* pMaterial = m_aiScene->mMaterials[i];

						for (uint i = aiTextureType_DIFFUSE; i < aiTextureType_UNKNOWN + 1; ++i)
							InitTextures(pMaterial, (aiTextureType)i, textures, _uvsIndex);
					}

					// Experimental
					for (uint i = 0; i < textures.Count(); ++i)					
						*out_textures->Get(i) = textures[i];
				}


				bool FAssimpInterface::InitModel(const aiMesh* _mesh, UModel& out_model)
				{
					TArray<TArray<UVertex>> vertices;
					TArray<uint> Indices;
					uint texureCoordCount= 0;
					const aiVector3D zero(0.f, 0.f, 0.f);
					
					// Get the number of subModel.
					for (; texureCoordCount < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++texureCoordCount)
					{
						if (!_mesh->HasTextureCoords(texureCoordCount))
							break;
						vertices.Add({});
						vertices[texureCoordCount].Reserve(_mesh->mNumVertices);
					}

					// Transform legacy from root.
					aiNode* node = aiFindNode(m_aiScene->mRootNode, _mesh->mName.data);
					aiTransformNodeLegacy(node->mTransformation, node);
					
					aiMatrix4x4 matrixBuffer;
					if (node)
						matrixBuffer = node->mTransformation;

					// Fill SubModels vertex array. 
					for (uint i = 0; i < _mesh->mNumVertices; ++i)
					{
						aiVector3D pPos = matrixBuffer * _mesh->mVertices[i];
						aiVector3D pNormal = _mesh->HasNormals() ? (matrixBuffer *_mesh->mNormals[i]) : zero;
						aiVector3D pTangent = _mesh->HasTangentsAndBitangents() ? (matrixBuffer *_mesh->mTangents[i]) : zero;

						// Foreach texture coords create a new submesh vertices array
						if (texureCoordCount)
						{
							for (uint j = 0; j < texureCoordCount; ++j)
							{
								aiVector3D pTexCoord = _mesh->HasTextureCoords(j) ? _mesh->mTextureCoords[j][i] : zero;

								vertices[j].Add({ { pPos.x, pPos.y, pPos.z },
								{ pNormal.x, pNormal.y, pNormal.z },
								{ pTangent.x, pTangent.y, pTangent.z },
								{ pTexCoord.x, pTexCoord.y } });
							}
						}
						else if(vertices.Count())
						{
							aiVector3D pTexCoord = _mesh->HasTextureCoords(0) ? _mesh->mTextureCoords[0][i] : zero;

							vertices[0].Add({ { pPos.x, pPos.y, pPos.z },
							{ pNormal.x, pNormal.y, pNormal.z },
							{ pTangent.x, pTangent.y, pTangent.z },
							{ pTexCoord.x, pTexCoord.y } });
						}
					}

					// Fill model index array. 
					for (uint i = 0; i < _mesh->mNumFaces; i++)
					{
						const aiFace& face = _mesh->mFaces[i];
						if (face.mNumIndices != 3)
						{
							FPrint::Print("Triangulation Fatal Error.", EParadigmDebugLevel::ERROR_LEVEL);
							return false;
						}
						Indices.Add(face.mIndices[0]);
						Indices.Add(face.mIndices[1]);
						Indices.Add(face.mIndices[2]);
					}
					
					// Move arrays in out_model
					UModel::FNativeModelEntry::Build(out_model, vertices, Indices);

					return true;
				}

				void FAssimpInterface::InitTextures(const aiMaterial* _material, aiTextureType _type, TArray<UTexture>& out_textures, TArray<uint>* _uvsIndex)
				{
					uint textCount = _material->GetTextureCount(_type);

					uint uvIndex;
					aiString path;
					// will be delete by the importer at the end so don't care about free
					aiTextureMapMode* mapmode = new aiTextureMapMode;

					for (uint i = 0; i < textCount; ++i)
					{
						if (_material->GetTexture(_type, i, &path /*path*/, nullptr/* mapping*/, &uvIndex/*uvindex*/, nullptr/*blend*/, nullptr/*operator*/, mapmode/*mapmode*/) == AI_SUCCESS)
						{												
							FString cleanPath(path.data);
							cleanPath.Remove("./");
							UTexture texture(FString::FPathSlicer::Path(m_CurrentFilename) + cleanPath);
							
							if(_uvsIndex)
								_uvsIndex->Add(uvIndex);

							switch(_type)
							{
								case aiTextureType_NORMALS:
									texture.TextureType = UTexture::ETextureType::TextureType_NormalMap;
									break;
								case aiTextureType_LIGHTMAP:
									texture.TextureType = UTexture::ETextureType::TextureType_LightMap;
									break;
								default:
									texture.TextureType = UTexture::ETextureType::TextureType_Default;
									break;
							}

							switch (*mapmode)
							{
								case aiTextureMapMode_Clamp:
									texture.WrappingMode = EWrappingMode::EWrappingMode_Clamp;
									break;
								case aiTextureMapMode_Mirror:
									texture.WrappingMode = EWrappingMode::EWrappingMode_Mirror;
									break;
								default:
									texture.WrappingMode = EWrappingMode::EWrappingMode_Repeat;
									break;
							}

							out_textures.Add(texture);
						}
					}
				}
			}
		}
	}
}