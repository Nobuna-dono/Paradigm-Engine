#include <Resource/FMaterial.h>
#include <ParadigmCore.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		////////////////////////////////////////////////
		// CONSTRUCTOR - DESTRUCTOR 
		//_____________________
		FMaterial::FMaterial(const FString& _Filename, KShader _kshader)
			: UResource(_Filename)
		{
			FShader::SyncResource(PARADIGM_RESOURCE->Shader(_kshader));
			SetShader(_kshader);
		}

		FMaterial::FMaterial(KShader _kshader)
			: UResource()
		{
			FShader::SyncResource(PARADIGM_RESOURCE->Shader(_kshader));
			SetShader(_kshader);
		}

		FMaterial::FMaterial(const FString& _filename, UShader& _shader)
			: UResource()
		{
			FShader::SyncResource(_shader);
			SetShader(_shader.ResourceName);
		}

		FMaterial::FMaterial(UShader& _shader)
			: UResource()
		{
			FShader::SyncResource(_shader);
			SetShader(_shader);
		}


		////////////////////////////////////////////////
		// ELEMENT ACCESS 
		//_____________________
		UMetaMaterial& FMaterial::GetMetaData()
		{
			return m_Data;
		}
		const UMetaMaterial& FMaterial::GetMetaData() const
		{
			return m_Data;
		}

		/*void FMaterial::Synchronize()
		{
			FMetaMaterial::SetResourcesData(m_Data, m_MaterialData);
		}	*/	

		UShader& FMaterial::GetShader()
		{
			return PARADIGM_RESOURCE->Shader(m_kShader);
		}

		const UShader& FMaterial::GetShader() const
		{
			return PARADIGM_RESOURCE->Shader(m_kShader);
		}

		////////////////////////////////////////////////
		// MODIFIER
		//_____________________
		void FMaterial::SetShader(KShader _kshader)
		{
			try
			{
				// check keyValidity
				UShader& shader = PARADIGM_RESOURCE->Shader(_kshader);
				m_Data.kNativeShader = shader.kNativeShaderResources;
				m_Data.RenderQueue = 2000;
				m_kShader = _kshader;
				//PARADIGM_GRAPHICS->GetShaderResourceHandle(shader.kNativeShaderResources);
				m_MaterialData = FMetaMaterial::GetResourcesData(m_Data);
			}
			catch (const ParadigmException&)
			{
				THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid kShader pass to init material's shader.");
			}
		}

		void FMaterial::SetShader(UShader& _shader)
		{
			try
			{
				m_Data.kNativeShader = _shader.kNativeShaderResources;
				m_Data.RenderQueue = 2000;
				m_kShader = PARADIGM_RESOURCE->ShaderKey(_shader.ResourceName);
				//PARADIGM_GRAPHICS->GetShaderResourceHandle(_shader.kNativeShaderResources);
				m_MaterialData = FMetaMaterial::GetResourcesData(m_Data);
			}
			catch (const ParadigmException&)
			{
				THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid kShader pass to init material's shader.");
			}
		}

		void FMaterial::SetShader(const FString& _shader)
		{
			SetShader(PARADIGM_RESOURCE->ShaderKey(_shader));				
		}

		void FMaterial::SetRenderQueue(uint _renderQueue)
		{
			m_Data.RenderQueue = _renderQueue;
		}

		void FMaterial::operator=(KShader _kshader)
		{
			FShader::SyncResource(PARADIGM_RESOURCE->Shader(_kshader));
			SetShader(_kshader);
		}
		
		void FMaterial::operator=(UShader& _shader)
		{
			FShader::SyncResource(_shader);
			SetShader(_shader);
		}

		FMaterial::operator UKeyRegister()
		{
			return m_Data.kNativeShader;
		}


		////////////////////////////////////////////////
		// FUNCTIONALITY 
		//_____________________		
		bool FMaterial::SetInt(const FString& _name, int _value)
		{
			if (FMetaMaterial::SetInt(m_Data, _name, _value))
			{
				for (TArray<std::pair<FString, float>>::Iterator it = m_MaterialData.FloatValues.Begin(); it != m_MaterialData.FloatValues.End(); ++it)
				{
					if ((*it).first == _name)
					{
						(*it).second = (float)_value;
						return true;
					}
				}
				FPrint::Print("What a funny behaviour... Native resource find but incomplete material?", EParadigmDebugLevel::ERROR_LEVEL);
			}
			return false;
		}
		bool FMaterial::SetFloat(const FString& _name, float _value)
		{
			if (FMetaMaterial::SetFloat(m_Data, _name, _value))
			{
				for (TArray<std::pair<FString, float>>::Iterator it = m_MaterialData.FloatValues.Begin(); it != m_MaterialData.FloatValues.End(); ++it)
				{
					if ((*it).first == _name)
					{
						(*it).second = _value;
						return true;
					}
				}
				FPrint::Print("What a funny behaviour... Native resource find but incomplete material?", EParadigmDebugLevel::ERROR_LEVEL);
			}
			return false;
		}
				
		bool FMaterial::SetMatrix(const FString& _name, UMatrix4 _value)
		{
			/** Dont need to store value for derefered binding. */
			return FMetaMaterial::SetMatrix(m_Data, _name, _value);
		}

		bool FMaterial::SetTexture(const FString& _name, const UTexture& _value)
		{
			/** Check if valid texture. */
			if (FMetaMaterial::SetTexture(m_Data, _name, _value))
			{
				for (TArray<std::pair<FString, UTexture>>::Iterator it = m_MaterialData.TextureValues.Begin(); it != m_MaterialData.TextureValues.End(); ++it)
				{
					if ((*it).first == _name)
					{
						(*it).second = _value;
						return true;
					}
				}
			}
			return false;
		}

		bool FMaterial::SetVector2(const FString& _name, UVector2 _value)
		{
			if (FMetaMaterial::SetVector2(m_Data, _name, _value))
			{
				for (TArray<std::pair<FString, UVector2>>::Iterator it = m_MaterialData.Vector2Values.Begin(); it != m_MaterialData.Vector2Values.End(); ++it)
				{
					if ((*it).first == _name)
					{
						(*it).second = _value;
						return true;
					}
				}
				FPrint::Print("What a funny behaviour... Native resource find but incomplete material?", EParadigmDebugLevel::ERROR_LEVEL);
			}
			return false;
		}

		bool FMaterial::SetVector3(const FString& _name, UVector3 _value)
		{
			if (FMetaMaterial::SetVector3(m_Data, _name, _value))
			{
				for (TArray<std::pair<FString, UVector3>>::Iterator it = m_MaterialData.Vector3Values.Begin(); it != m_MaterialData.Vector3Values.End(); ++it)
				{
					if ((*it).first == _name)
					{
						(*it).second = _value;
						return true;
					}
				}
				FPrint::Print("What a funny behaviour... Native resource find but incomplete material?", EParadigmDebugLevel::ERROR_LEVEL);
			}
			return false;
		}

		bool FMaterial::SetVector4(const FString& _name, UVector4 _value)
		{
			if (FMetaMaterial::SetVector4(m_Data, _name, _value))
			{
				for (TArray<std::pair<FString, UVector4>>::Iterator it = m_MaterialData.Vector4Values.Begin(); it != m_MaterialData.Vector4Values.End(); ++it)
				{
					if ((*it).first == _name)
					{
						(*it).second = _value;
						return true;
					}
				}
				FPrint::Print("What a funny behaviour... Native resource find but incomplete material?", EParadigmDebugLevel::ERROR_LEVEL);
			}
			return false;
		}

		void FMaterial::Resync()
		{
			FShader::SyncResource(PARADIGM_RESOURCE->Shader(m_kShader), true);
		}

	}
}
