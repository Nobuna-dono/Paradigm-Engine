#ifndef _GRAPHICSINTERFACEATTRIBUTES_H_
#define _GRAPHICSINTERFACEATTRIBUTES_H_

#include <ParadigmException.h>
#include <NativeInterface/Graphics/NativeGraphicsEnums.h>
#include <NativeInterface/Graphics/NativeFormat.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Graphics
		{
			struct UGraphicsCardInfo
			{
				int Memory;
				FString Name;
			};
			
			struct URasterizerDescriptor
			{
				/** Indicates triangles facing the specified direction are not drawn. (see @ENativeCullMode)*/
				ENativeCullMode CullMode { ENativeCullMode::ECullMode_Back };

				/** Determines the fill mode to use when rendering. (see @ENativeFillMode)*/
				ENativeFillMode FillMode { ENativeFillMode::EFillMode_Solid };

				/** Determines if a triangle is front- or back-facing. If this parameter is TRUE, a triangle will be considered front-facing if its vertices are counter-clockwise on the render target and considered back-facing if they are clockwise. */
				bool bFrontCounterClockwise { false };

				/** Multisample antialiasing (MSAA) parameters. */
				bool bMultisampleEnable { true };
			};
			
			struct UNativeDepthStencilDescriptor
			{
				/** A function that compares depth data against existing depth data. (see @EDepthFunc) */
				ENativeDepthFunc DepthFunc{ EDepthFunc_Less };
				
				/** Identify a portion of the depth-stencil buffer for reading stencil data. */
				uint StencilReadMask : 8; 
				/** Identify a portion of the depth - stencil buffer for writing stencil data. */
				uint StencilWriteMask : 8; 
				/** Identify a portion of the depth-stencil buffer that can be modified by depth data. If false, painter algorithm's like. */
				uint bDepthWriteMask : 1; 
				/** Enable depth testing. */
				uint bDepthEnable : 1; 
				/** Enable stencil testing. */
				uint bStencilEnable : 1; 

			};				

			struct UNativeTextureResourceDescriptor
			{
				/** Flags for binding to pipeline stages.The flags can be combined by a logical OR. (see @ENativeBindFlag) */
				ENativeBindFlag BindFlag{ EBindFlag_DepthStencil };

				/** Texture format. */
				ENativeFormat Format{ NAT_FORMAT_R32G32B32A32_FLOAT };
				
				/**	Specifies how a resource will be accessed. (see @EResourceViewDimension)*/
				ENativeTextureDimension TextureDimension;

				/** Texture size. */
				uint Width, Height;

				/** The number of multisamples per pixel. */
				uint MultisampleCount{ 8 };

				/** Value that identifies how the texture is to be read from and written to. */
				ENativeTextureUsage Usage{ ETextureUsage_Default };
			};
		}
	}
}

#endif