#ifndef _FMATERIAL_H_
#define _FMATERIAL_H_

#include <Resource/FMetaMaterial.h>
#include <Resource/FShader.h>
#include <unordered_map>

namespace ParadigmEngine
{
	namespace Resource
	{
		class FMaterial : public UResource
		{
			public:
				////////////////////////////////////////////////
				// CONSTRUCTOR - DESTRUCTOR 
				//_____________________
				FMaterial() = default;
				FMaterial(const FString& _filename, KShader _kshader);
				FMaterial(KShader _kshader);
				FMaterial(const FString& _filename, UShader& _kshader);
				FMaterial(UShader& _kshader);
		
			public:
				////////////////////////////////////////////////
				// ELEMENT ACCESS 
				//_____________________
				/** Get the meta material. */
				UMetaMaterial& GetMetaData();
				/** Get the meta material. */
				const UMetaMaterial& GetMetaData() const;				
				
				/** Get the shader of the material. */
				UShader& GetShader();
				/** Get the shader of the material. */
				const UShader& GetShader() const;


			public:
				////////////////////////////////////////////////
				// MODIFIER
				//_____________________				
				/** Set the arbitrary render queue value which determine the draw call order arragement. */
				void SetRenderQueue(uint _renderQueue);
				void SetShader(KShader _kshader);
				void SetShader(UShader& _shader);
				void SetShader(const FString& _shader);

				/** return the native shader key. (Allow simpler native purpose as @_GRAPHICS.SetShader(KNativeResource),@_GRAPHICS.SetShaderResources(KNativeResource)...).*/
				operator UKeyRegister();
				void operator=(KShader _kshader);
				void operator=(UShader& _shader);


			public:
				////////////////////////////////////////////////
				// FUNCTIONALITY 
				//_____________________				
				/** Refresh the resources data binding. (Only if you change ?) */
				//void Synchronize();
				bool SetInt(const FString& _name, int _value);
				bool SetFloat(const FString& _name, float _value);
				bool SetMatrix(const FString& _name, UMatrix4 _value);
				bool SetTexture(const FString& _name, const UTexture& _value);
				bool SetVector2(const FString& _name, UVector2 _value);
				bool SetVector3(const FString& _name, UVector3 _value);
				bool SetVector4(const FString& _name, UVector4 _value);

				void Resync();

			private:
				////////////////////////////////////////////////
				// DATA 
				//_____________________
				KShader m_kShader;	
				UMetaMaterial m_Data;
				UMetaMaterialData m_MaterialData;
		};
	}
}

typedef ParadigmEngine::Resource::FMaterial FMaterial;

#endif