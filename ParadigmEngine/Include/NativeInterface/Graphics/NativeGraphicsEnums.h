#ifndef _NATIVEGRAPHICSENUM_H_
#define _NATIVEGRAPHICSENUM_H_

#include <NativeInterface/NativeInterfaceEnums.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Graphics
		{
			////////////////////////////////////////////////
			// RENDER ENUM
			//____________________________________				
			enum ENativeClearFlag
			{
				EClearFlag_Depth = 0x1L,
				EClearFlag_Stencil = 0x2L,
			};
			
			/** Draw primitive topology mode. */
			SERIALIZABLE_ENUM(ENativePrimitiveTopology,			
				EPrimitiveTopology_PointList,
				EPrimitiveTopology_LineList,
				EPrimitiveTopology_LineStrip,
				EPrimitiveTopology_LineListAdj,
				EPrimitiveTopology_LineStripAdj,
				EPrimitiveTopology_TriangleList ,
				EPrimitiveTopology_TriangleStrip,
				EPrimitiveTopology_TriangleListAdj,
				EPrimitiveTopology_TriangleStripAdj,
			);

			/** Draw fill mode. */
			enum ENativeFillMode
			{
				EFillMode_Wireframe,
				EFillMode_Solid,
			};

			/** Cull Mode. */
			enum ENativeCullMode
			{
				ECullMode_None = 1,
				ECullMode_Front = 2,
				ECullMode_Back = 3,
			};

			/** A function that compares depth data against existing depth data. */
			enum ENativeDepthFunc
			{
				/** Never pass the comparison. */
				EDepthFunc_Never,
				/** If the source data is less than the destination data, the comparison passes. */
				EDepthFunc_Less,
				/** If the source data is equal to the destination data, the comparison passes. */
				EDepthFunc_Equal,
				/** If the source data is less than or equal to the destination data, the comparison passes. */
				EDepthFunc_LessEqual,
				/** If the source data is greater than the destination data, the comparison passes. */
				EDepthFunc_Greater,
				/** If the source data is not equal to the destination data, the comparison passes. */
				EDepthFunc_NotEqual,
				/** If the source data is greater than or equal to the destination data, the comparison passes. */
				EDepthFunc_GreaterEqual,
				/** Always pass the comparison. */
				EDepthFunc_Always
			};

			enum ENativeBindFlag
			{
				EBindFlag_VertexBuffer,
				EBindFlag_IndexBuffer,
				EBindFlag_ConstantBuffer,
				EBindFlag_Resource,
				EBindFlag_StreamOutput,
				EBindFlag_RenderTarget,
				EBindFlag_DepthStencil,
				EBindFlag_UnorderedAccess
			};

			////////////////////////////////////////////////
			// TEXTURES ENUM
			//____________________________________	
			/** Texture dimension. */
			enum ENativeTextureDimension
			{
				ETextureDimension_Unknow = 0,
				ETextureDimension_1D = 1,
				ETextureDimension_1DArray = 2,
				ETextureDimension_2D = 3,
				ETextureDimension_2DArray = 4,
			};

			/** Texture usage. */
			enum ENativeTextureUsage
			{
				ETextureUsage_Default = 0,
				ETextureUsage_Immutable = 1,
				ETextureUsage_Dynamic = 2,
				ETextureUsage_Staging = 3
			};

			/* Texture filtering mode. */
			SERIALIZABLE_ENUM(ENativeFilteringMode,			
				EFilteringMode_Point, 
				EFilteringMode_Linear, 
				EFilteringMode_Anisotropic
			);

			/* Texture filtering mode. */
			SERIALIZABLE_ENUM(ENativeWrappingMode,			
				EWrappingMode_Repeat,
				EWrappingMode_Mirror,
				EWrappingMode_Clamp,
				EWrappingMode_Border,
				EWrappingMode_MirrorOnce
			);

			/** Dimension of the texture according to the shader. */
			enum ENativeTextureDimensionView
			{
				ETextureDimensionType_Unknow = 0,
				ETextureDimensionType_1D = 2,
				ETextureDimensionType_1DArray = 3,
				ETextureDimensionType_2D,
				ETextureDimensionType_2DArray,
				ETextureDimensionType_2DMultisample,
				ETextureDimensionType_2DMultisampleArray,
				ETextureDimensionType_3D,
				ETextureDimensionType_Cubemap
			};

			
			////////////////////////////////////////////////
			// SHADER ENUM
			//____________________________________	
			namespace Shader
			{
				/** Shader type. */
				SERIALIZABLE_ENUM(ENativeShaderType,				
					EShaderType_Unknow,
					EShaderType_Vertex,
					EShaderType_Pixel,
					EShaderType_Geometry,
					EShaderType_TessellationControl,
					EShaderType_TessellationEvaluation,
					EShaderType_Compute,
					EShaderType_Program
				);
			}
		}
	}
}

typedef ParadigmEngine::NativeInterface::Graphics::ENativeTextureDimensionView ENativeTextureDimensionView;
typedef ENativeTextureDimensionView ETextureDimensionView;

typedef ParadigmEngine::NativeInterface::Graphics::ENativeFilteringMode ENativeFilteringMode;
typedef ENativeFilteringMode EFilteringMode;
typedef ParadigmEngine::NativeInterface::Graphics::ENUMERATOR_TYPE(ENativeFilteringMode) ENUMERATOR_TYPE(EFilteringMode);

typedef ParadigmEngine::NativeInterface::Graphics::ENativeWrappingMode ENativeWrappingMode;
typedef ENativeWrappingMode EWrappingMode;
typedef ParadigmEngine::NativeInterface::Graphics::ENUMERATOR_TYPE(ENativeWrappingMode) ENUMERATOR_TYPE(EWrappingMode);

typedef ParadigmEngine::NativeInterface::Graphics::ENativePrimitiveTopology ENativePrimitiveTopology;
typedef ENativePrimitiveTopology EPrimitiveTopology;
typedef ParadigmEngine::NativeInterface::Graphics::ENUMERATOR_TYPE(ENativePrimitiveTopology) ENUMERATOR_TYPE(EPrimitiveTopology);

typedef ParadigmEngine::NativeInterface::Graphics::Shader::ENativeShaderType ENativeShaderType;
typedef ENativeShaderType EShaderType;
typedef ParadigmEngine::NativeInterface::Graphics::Shader::ENUMERATOR_TYPE(ENativeShaderType) ENUMERATOR_TYPE(EShaderType);

#endif