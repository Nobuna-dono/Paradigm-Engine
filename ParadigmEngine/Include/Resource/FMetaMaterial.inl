////////////////////////////////////////////////////////////////////////////////////////////////
// _FMETAMATERIAL_H_'s inline file
//________________________________________________________________________

namespace ParadigmEngine
{
	namespace Resource
	{
		template<typename T>
		bool FMetaMaterial::SetData(UMetaMaterial& out_material, const FString& _name, T& _value)
		{
			NativeInterface::UShaderResourceHandle& resourceHandle = FParadigmEngine::GetInstance().Graphics->GetShaderResourceHandle(out_material.kNativeShader);

			bool bSuccess = false;

			for (TArray<NativeInterface::UShaderDataBlockResource>::Iterator itBlock = resourceHandle.Data.Begin(); itBlock != resourceHandle.Data.End(); ++itBlock)
			{
				for (TArray<NativeInterface::UShaderDataResource>::Iterator it = (*itBlock).Resources.Begin(); it != (*itBlock).Resources.End(); ++it)
				{
					if ((*it).Name == _name)
					{
						if ((*it).Size == sizeof(T))
						{
							memmove((*it).Data, &_value, sizeof(T));
							bSuccess = true;
							continue;
						}
						bSuccess = false;
					}
				}
			}
			return bSuccess;
		}

		template<typename T>
		bool FMetaMaterial::GetData(UMetaMaterial& out_material, const FString& _name, T& out_value)
		{
			NativeInterface::UShaderResourceHandle& resourceHandle = FParadigmEngine::GetInstance().Graphics->GetShaderResourceHandle(out_material.kNativeShader);

			for (TArray<NativeInterface::UShaderDataBlockResource>::Iterator itBlock = resourceHandle.Data.Begin(); itBlock != resourceHandle.Data.End(); ++itBlock)
			{
				for (TArray<NativeInterface::UShaderDataResource>::Iterator it = (*itBlock).Resources.Begin(); it != (*itBlock).Resources.End(); ++it)
				{
					if ((*it).Name == _name)
					{
						if ((*it).Size == sizeof(T))
						{
							out_value = *((T*)(*it).Data);
							return true;
						}
						return false;
					}
				}
			}
			return false;
		}
	}
}