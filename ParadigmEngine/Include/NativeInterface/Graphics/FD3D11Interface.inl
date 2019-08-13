////////////////////////////////////////////////////////////////////////////////////////////////
// _IKEYTABLE_H_'s inline file
//________________________________________________________________________

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Graphics
		{
			template<typename T>
			UKeyRegister FD3D11Interface::SeekExistingShader(T& _tableToProspect, FString _uniqueShaderName)
			{
				uint i = 0;
				UKeyRegister key = INVALID_KEY_REGISTER;

				for (T::Iterator it = _tableToProspect.Begin(); it != _tableToProspect.End(); ++it)
				{
					if ((*it).first == _uniqueShaderName)
					{
						if (_tableToProspect.GetRegister(i, key))
							break;
					}
					i++;
				}
				return key;
			}

			template<typename T>
			UKeyRegister FD3D11Interface::TryRecycleShaderResource(T& _tableToProspect, FString _uniqueShaderName, ENativeShaderType _shaderType, UShaderResourceHandle& out_resourceHandle)
			{
				UKeyRegister key = INVALID_KEY_REGISTER;
				bool bSet = false;
				if ((key = SeekExistingShader(_tableToProspect, _uniqueShaderName)) != INVALID_KEY_REGISTER)
				{
					for (TKeyTable<UShaderResourceHandle>::Iterator it = m_InterfaceData.ShaderInterface.ShaderResources.Begin(); it != m_InterfaceData.ShaderInterface.ShaderResources.End(); ++it)
					{
						for (TArray<UShaderDataBlockResource>::Iterator itData = (*it).Data.Begin(); itData != (*it).Data.End(); ++itData)
						{
							if ((*itData).ShaderType == _shaderType)
							{
								bSet = true;
								out_resourceHandle.Data.Add(*itData);
							}
						}
						for (TArray<UShaderTextureResource>::Iterator itData = (*it).Textures.Begin(); itData != (*it).Textures.End(); ++itData)
						{
							if ((*itData).ShaderType == _shaderType)
							{
								bSet = true;
								out_resourceHandle.Textures.Add(*itData);
							}
						}
						if (bSet)
							break;
					}
				}
				return key;
			}


			template<typename T>
			void FD3D11Interface::ClearNativeShaderKeyTable(T& _table)
			{
				for (T::Iterator it = _table.Begin(); it != _table.End(); ++it)
				{
					if ((*it).second)
					{
						(*it).second->Release();
						(*it).second = nullptr;
					}
				}
				_table.Clear();
			}


			template<typename T>
			void FD3D11Interface::ClearNativeKeyTable(T& _table)
			{
				for (T::Iterator it = _table.Begin(); it != _table.End(); ++it)
				{
					if (*it)
					{
						(*it)->Release();
						*it = nullptr;
					}
				}
				_table.Clear();
			}
		}
	}
}
