#ifndef _FMETAMATERIAL_H_
#define _FMETAMATERIAL_H_

#include <TArray.h>
#include <ParadigmMath.h>

#include <Resource/FTexture.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		struct UMetaMaterial
		{
			uint RenderQueue : 16;
			uint PassCount : 15;
			uint bValid : 1;
			KNativeResource kNativeShader;			
		};

		struct UMetaMaterialInfo
		{
			TArray<FString> FloatResources;
			TArray<FString> TextureResources;
			TArray<FString> Vector2Resources;
			TArray<FString> Vector3Resources;
			TArray<FString> Vector4Resources;
		};

		struct UMetaMaterialData
		{
			TArray<std::pair<FString, float>> FloatValues;
			TArray<std::pair<FString, UTexture>> TextureValues;
			TArray<std::pair<FString, UVector2>> Vector2Values;
			TArray<std::pair<FString, UVector3>> Vector3Values;
			TArray<std::pair<FString, UVector4>> Vector4Values;
		};

		class FMetaMaterial
		{			
			public:
				////////////////////////////////////////////////
				// FUNCTIONALITY 
				//_____________________
				static UMetaMaterialInfo GetResourcesInfo(UMetaMaterial& out_material);
				static UMetaMaterialData GetResourcesData(UMetaMaterial& out_material);
				static void SetResourcesData(UMetaMaterial& out_material, const UMetaMaterialData& _matData);

				static bool SetInt(UMetaMaterial& out_material, const FString& _name, int _value);
				static bool SetFloat(UMetaMaterial& out_material, const FString& _name, float _value);
				static bool SetMatrix(UMetaMaterial& out_material, const FString& _name, UMatrix4 _value);
				static bool SetTexture(UMetaMaterial& out_material, const FString& _name, const UTexture& _value);
				static bool SetVector2(UMetaMaterial& out_material, const FString& _name, UVector2 _value);
				static bool SetVector3(UMetaMaterial& out_material, const FString& _name, UVector3 _value);
				static bool SetVector4(UMetaMaterial& out_material, const FString& _name, UVector4 _value);				

				/*static bool SetIntArray(UMetaMaterial& out_material, const FString& _name, const TArray<int>& _value);
				static bool SetFloatArray(UMetaMaterial& out_material, const FString& _name, const TArray<float>& _value);
				static bool SetMatrixArray(UMetaMaterial& out_material, const FString& _name, const TArray<UMatrix4>& _value);
				static bool SetVector2Array(UMetaMaterial& out_material, const FString& _name, const TArray<UVector2>& _value);
				static bool SetVector3Array(UMetaMaterial& out_material, const FString& _name, const TArray<UVector3>& _value);
				static bool SetVector4Array(UMetaMaterial& out_material, const FString& _name, const TArray<UVector4>& _value);*/
				//static bool SetColor(FString _name, UColor);

				/** Only for trivial types. (Don't use with UTexture!) */
				template<typename T>
				static bool SetData(UMetaMaterial& out_material, const FString& _name, T& _value);

				/** Only for trivial types. (Don't use with UTexture!) */
				template<typename T>
				static bool GetData(UMetaMaterial& out_material, const FString& _name, T& out_value);
		};
	}
}
#include <Resource/FMetaMaterial.inl>

typedef ParadigmEngine::Resource::UMetaMaterial UMetaMaterial;
typedef ParadigmEngine::Resource::FMetaMaterial FMetaMaterial;
#endif