#ifndef _NATIVEGRAPHICSHANDLES_H_
#define _NATIVEGRAPHICSHANDLES_H_

#include <ParadigmMath.h>
#include <IKeyTable.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Graphics
		{
			enum ENativeVertexType
			{
				EVertexType_Position,
				EVertexType_PositionNormal,
				EVertexType_PositionUv,
				EVertexType_PositionNormalUv,
				EVertexType_PositionNormalTangentUv,
				EVertexType_Anchor,
			};

			struct UNativeVertex_Position
			{
				UVector3 Position{ 0.f,0.f,0.f };				
			};

			struct UNativeVertex_PositionNormal
			{
				UVector3 Position{ 0.f,0.f,0.f };
				UVector3 Normal{ 0.f,0.f,0.f };
			};

			struct UNativeVertex_PositionUv
			{
				UVector3 Position{ 0.f,0.f,0.f };
				UVector2 TextureCoord{ 0,0 };
			};

			struct UNativeVertex_PositionNormalUv
			{
				UVector3 Position{ 0.f,0.f,0.f };
				UVector3 Normal{ 0.f,0.f,0.f };
				UVector2 TextureCoord{ 0,0 };
			};

			struct UNativeVertex
			{
				UVector3 Position{ 0.f,0.f,0.f };
				UVector3 Normal{ 0.f,0.f,0.f };
				UVector3 Tangent{ 0.f,0.f,0.f };
				UVector2 TextureCoord{ 0,0 };
			};
			
			struct UNativeVertex_Anchor
			{
				UVector3 AnchorPosition{ 0.f,0.f,0.f };
				UVector2 Dimension{ 0.f,0.f };
				float Opacity{ 1.f };
				int ZOrder{ 0 };
			};

			struct UNativeModelBuffer
			{
				/** A key toward the model's element buffer. */
				UKeyRegister kElementBuffer{ INVALID_KEY_REGISTER };
				/** A key toward the model's vertex buffer. */
				UKeyRegister kVerticesBuffer{ INVALID_KEY_REGISTER };
			};

			struct UNativeTextureResource
			{
				/** A key toward the native texture resource. */
				UKeyRegister kResourceView{ INVALID_KEY_REGISTER };
				/** A key toward the native texture sampler resource. */
				UKeyRegister kSamplerState{ INVALID_KEY_REGISTER };
			};
		}
	}
}

typedef ParadigmEngine::NativeInterface::Graphics::UNativeVertex UVertex;
typedef ParadigmEngine::NativeInterface::Graphics::UNativeModelBuffer UNativeModelBuffer;
typedef ParadigmEngine::NativeInterface::Graphics::UNativeTextureResource UNativeTextureResource;
#endif // _UNATIVEVERTEX_H_