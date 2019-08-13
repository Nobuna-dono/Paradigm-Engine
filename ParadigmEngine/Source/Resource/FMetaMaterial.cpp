#include <Resource/FMetaMaterial.h>
#include <ParadigmCore.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		////////////////////////////////////////////////
		// FUNCTIONALITY 
		//_____________________
		UMetaMaterialInfo FMetaMaterial::GetResourcesInfo(UMetaMaterial& out_material)
		{
			NativeInterface::UShaderResourceHandle& resourceHandle = PARADIGM_GRAPHICS->GetShaderResourceHandle(out_material.kNativeShader);
			UMetaMaterialInfo info;
			for (TArray<NativeInterface::UShaderTextureResource>::Iterator it = resourceHandle.Textures.Begin(); it != resourceHandle.Textures.End(); ++it)			
				info.TextureResources.Add((*it).Name);
			for (TArray<NativeInterface::UShaderDataBlockResource>::Iterator itb = resourceHandle.Data.Begin(); itb != resourceHandle.Data.End(); ++itb)
			{
				for (TArray<NativeInterface::UShaderDataResource>::Iterator it = (*itb).Resources.Begin(); it != (*itb).Resources.End(); ++it)
				{
					if ((*it).Size == sizeof(float))
						info.FloatResources.Add((*it).Name);
					else if ((*it).Size == sizeof(UVector2))
						info.Vector2Resources.Add((*it).Name);
					else if ((*it).Size == sizeof(UVector3))
						info.Vector3Resources.Add((*it).Name);
					else if ((*it).Size == sizeof(UVector4))
						info.Vector4Resources.Add((*it).Name);
					else // Dont take matrix
						continue;
				}
			}
			return info;
		}

		UMetaMaterialData FMetaMaterial::GetResourcesData(UMetaMaterial& out_material)
		{
			NativeInterface::UShaderResourceHandle& resourceHandle = PARADIGM_GRAPHICS->GetShaderResourceHandle(out_material.kNativeShader);
			UMetaMaterialData data;
			for (TArray<NativeInterface::UShaderTextureResource>::Iterator it = resourceHandle.Textures.Begin(); it != resourceHandle.Textures.End(); ++it)			
				data.TextureValues.Add(std::pair<FString, UTexture>((*it).Name, {}));
			
			for (TArray<NativeInterface::UShaderDataBlockResource>::Iterator itb = resourceHandle.Data.Begin(); itb != resourceHandle.Data.End(); ++itb)
			{
				for (TArray<NativeInterface::UShaderDataResource>::Iterator it = (*itb).Resources.Begin(); it != (*itb).Resources.End(); ++it)
				{
					if ((*it).Size == sizeof(float))
						data.FloatValues.Add(std::pair<FString, float>((*it).Name,0));
					else if ((*it).Size == sizeof(UVector2))
						data.Vector2Values.Add(std::pair<FString, UVector2>((*it).Name, {0,0}));
					else if ((*it).Size == sizeof(UVector3))
						data.Vector3Values.Add(std::pair<FString, UVector3>((*it).Name, { 0,0,0 }));
					else if ((*it).Size == sizeof(UVector4))
						data.Vector4Values.Add(std::pair<FString, UVector4>((*it).Name, { 0,0,0,0 }));
					else // Dont take matrix
						continue;
				}
			}
			return data;
		}


		void FMetaMaterial::SetResourcesData(UMetaMaterial& out_material, const UMetaMaterialData& _matData)
		{			
			for (uint i = 0; i < _matData.TextureValues.Count(); ++i)
				SetTexture(out_material, _matData.TextureValues[i].first, _matData.TextureValues[i].second);
			for (uint i = 0; i < _matData.FloatValues.Count(); ++i)
				SetFloat(out_material, _matData.FloatValues[i].first, _matData.FloatValues[i].second);
			for (uint i = 0; i < _matData.Vector2Values.Count(); ++i)
				SetVector2(out_material, _matData.Vector2Values[i].first, _matData.Vector2Values[i].second);
			for (uint i = 0; i < _matData.Vector3Values.Count(); ++i)
				SetVector3(out_material, _matData.Vector3Values[i].first, _matData.Vector3Values[i].second);
			for (uint i = 0; i < _matData.Vector4Values.Count(); ++i)
				SetVector4(out_material, _matData.Vector4Values[i].first, _matData.Vector4Values[i].second);
		}

		bool FMetaMaterial::SetInt(UMetaMaterial& out_material, const FString& _name, int _value)
		{
			return SetData<int>(out_material, _name, _value);
		}

		bool FMetaMaterial::SetFloat(UMetaMaterial& out_material, const FString& _name, float _value)
		{
			return SetData<float>(out_material, _name, _value);
		}

		bool FMetaMaterial::SetMatrix(UMetaMaterial& out_material, const FString& _name, UMatrix4 _value)
		{
			return SetData<UMatrix4>(out_material, _name, _value);
		}

		bool FMetaMaterial::SetTexture(UMetaMaterial& out_material, const FString& _name, const UTexture& _value)
		{
			NativeInterface::UShaderResourceHandle& resourceHandle = PARADIGM_GRAPHICS->GetShaderResourceHandle(out_material.kNativeShader);

			for (TArray<NativeInterface::UShaderTextureResource>::Iterator it = resourceHandle.Textures.Begin(); it != resourceHandle.Textures.End(); ++it)
			{
				if ((*it).Name == _name)
				{
					(*it).bOudated = true;
					(*it).KeysHandle = _value.kNativeTextureHandle;
					return true;
				}
			}
			return false;
		}

		bool FMetaMaterial::SetVector2(UMetaMaterial& out_material, const FString& _name, UVector2 _value)
		{
			return FMetaMaterial::SetData<UVector2>(out_material, _name, _value);
		}

		bool FMetaMaterial::SetVector3(UMetaMaterial& out_material, const FString& _name, UVector3 _value)
		{
			return SetData<UVector3>(out_material, _name, _value);
		}

		bool FMetaMaterial::SetVector4(UMetaMaterial& out_material, const FString& _name, UVector4 _value)
		{
			return SetData<UVector4>(out_material, _name, _value);
		}

	}
}