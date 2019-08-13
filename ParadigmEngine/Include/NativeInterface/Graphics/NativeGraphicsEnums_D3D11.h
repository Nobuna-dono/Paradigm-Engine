#ifndef _NATIVEGRAPHICSENUM_D3D11_H_
#define _NATIVEGRAPHICSENUM_D3D11_H_

#include <NativeInterface/Graphics/NativeGraphicsEnums.h>
#include <D3D11.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Graphics
		{
			static D3D11_PRIMITIVE_TOPOLOGY NativeConversion(ENativePrimitiveTopology _depthFunc)
			{
				switch (_depthFunc)
				{
					case EPrimitiveTopology_PointList:
						return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
					case EPrimitiveTopology_LineList:
						return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
					case EPrimitiveTopology_LineStrip:
						return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
					case EPrimitiveTopology_LineListAdj:
						return D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ;
					case EPrimitiveTopology_LineStripAdj:
						return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ;
					case EPrimitiveTopology_TriangleList:
						return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
					case EPrimitiveTopology_TriangleStrip:
						return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
					case EPrimitiveTopology_TriangleListAdj:
						return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ;
					case EPrimitiveTopology_TriangleStripAdj:
						return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ;

					default:
						return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
				}
			}

			static D3D11_FILL_MODE NativeConversion(ENativeFillMode _fillmode)
			{
				switch (_fillmode)
				{
					case EFillMode_Wireframe:
						return D3D11_FILL_WIREFRAME;
					default:
						return D3D11_FILL_SOLID;
				}
			}

			static D3D11_CULL_MODE NativeConversion(ENativeCullMode _cullmode)
			{
				switch (_cullmode)
				{
					case ECullMode_Back:
						return D3D11_CULL_BACK;
					case ECullMode_Front:
						return D3D11_CULL_FRONT;
					default:
						return D3D11_CULL_NONE;
				}
			}

			static D3D11_TEXTURE_ADDRESS_MODE NativeConversion(ENativeWrappingMode _wmode)
			{
				switch (_wmode)
				{
					case EWrappingMode_Repeat:
						return D3D11_TEXTURE_ADDRESS_WRAP;
					case EWrappingMode_Mirror:
						return D3D11_TEXTURE_ADDRESS_MIRROR;
					case EWrappingMode_Clamp:
						return D3D11_TEXTURE_ADDRESS_CLAMP;
					case EWrappingMode_Border:
						return D3D11_TEXTURE_ADDRESS_BORDER;
					case EWrappingMode_MirrorOnce:
						return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
					default:
						return D3D11_TEXTURE_ADDRESS_WRAP;
				}
			}

			static D3D11_USAGE NativeConversion(ENativeTextureUsage _usage)
			{
				switch (_usage)
				{
					case ETextureUsage_Default:
						return D3D11_USAGE_DEFAULT;
					case ETextureUsage_Immutable:
						return D3D11_USAGE_IMMUTABLE;
					case ETextureUsage_Dynamic:
						return D3D11_USAGE_DYNAMIC;
					case ETextureUsage_Staging:
						return D3D11_USAGE_STAGING;
					default:
						return D3D11_USAGE_DEFAULT;
				}
			}

			static D3D11_FILTER NativeConversion(ENativeFilteringMode _filtermode)
			{
				switch (_filtermode)
				{
				case EFilteringMode_Point:
					return D3D11_FILTER_MIN_MAG_MIP_POINT;
				case EFilteringMode_Linear:
					return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				case EFilteringMode_Anisotropic:
					return D3D11_FILTER_ANISOTROPIC;
				default:
					return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				}
			}

			static D3D11_COMPARISON_FUNC NativeConversion(ENativeDepthFunc _depthFunc)
			{
				switch (_depthFunc)
				{
					case EDepthFunc_Never:
						return D3D11_COMPARISON_NEVER;
					case EDepthFunc_Less:
						return D3D11_COMPARISON_LESS;
					case EDepthFunc_Equal:
						return D3D11_COMPARISON_EQUAL;
					case EDepthFunc_LessEqual:
						return D3D11_COMPARISON_LESS_EQUAL;
					case EDepthFunc_Greater:
						return D3D11_COMPARISON_GREATER;
					case EDepthFunc_NotEqual:
						return D3D11_COMPARISON_NOT_EQUAL;
					case EDepthFunc_GreaterEqual:
						return D3D11_COMPARISON_GREATER_EQUAL;
					case EDepthFunc_Always:
						return D3D11_COMPARISON_ALWAYS;
					default:
						return D3D11_COMPARISON_LESS;
				}
			}

			static D3D11_BIND_FLAG NativeConversion(ENativeBindFlag _flag)
			{
				switch (_flag)
				{
					case EBindFlag_VertexBuffer:
						return D3D11_BIND_VERTEX_BUFFER;
					case EBindFlag_IndexBuffer:
						return D3D11_BIND_INDEX_BUFFER;
					case EBindFlag_ConstantBuffer:
						return D3D11_BIND_CONSTANT_BUFFER;
					case EBindFlag_Resource:
						return D3D11_BIND_SHADER_RESOURCE;
					case EBindFlag_StreamOutput:
						return D3D11_BIND_STREAM_OUTPUT;
					case EBindFlag_RenderTarget:
						return D3D11_BIND_RENDER_TARGET;
					case EBindFlag_DepthStencil:
						return D3D11_BIND_DEPTH_STENCIL;
					case EBindFlag_UnorderedAccess:
						return D3D11_BIND_UNORDERED_ACCESS;
					default:
						return D3D11_BIND_VERTEX_BUFFER;
				}
			}			
		}
	}
}

#endif