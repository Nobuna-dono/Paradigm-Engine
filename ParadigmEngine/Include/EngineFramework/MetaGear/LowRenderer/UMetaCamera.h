#ifndef _UMETACAMERA_H_
#define _UMETACAMERA_H_

#include <NativeInterface/Graphics/NativeGraphicsEnums.h>
#include <EngineFramework/MetaGear/ParadigmMetaGear.h>
#include <Core/Math/UVector4.h>
#include <FLayer.h>
#include <FColor.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace MetaGear
		{
			namespace LowRenderer
			{
				METAGEAR_CLASS(UMetaCamera)
				{
					METAGEAR_ATTRIBUTES(UMetaCamera)
					
					public:
							////////////////////////////////////////////////
							// FUNCTIONALITY - ARCHIVAGE
							//____________________________________	
							void Archive(UArchive& out_archive)  override
							{							
								SERIALIZE_ENUM(EClearFlag);
								SERIALIZE_ENUM(EProjection);
								SERIALIZE_ENUM(ETargetViewport);

								ARCHIVE_MEMBER(UMetaCamera, out_archive, 8);
								SERIALIZE_MEMBER(out_archive, ClearFlag);
								SERIALIZE_MEMBER(out_archive, ClearColor);
								SERIALIZE_MEMBER(out_archive, Projection);
								SERIALIZE_MEMBER(out_archive, FieldOfView);
								SERIALIZE_MEMBER(out_archive, Near);
								SERIALIZE_MEMBER(out_archive, Far);
								SERIALIZE_MEMBER(out_archive, Depth);
								SERIALIZE_MEMBER(out_archive, DisplayTarget);
							}

							bool Dearchive(UArchive& out_archive)  override
							{
								SKIP_ARCHIVE_INFO(out_archive);
								DESERIALIZE_MEMBER(out_archive, ClearFlag);
								DESERIALIZE_MEMBER(out_archive, ClearColor);
								DESERIALIZE_MEMBER(out_archive, Projection);
								DESERIALIZE_MEMBER(out_archive, FieldOfView);
								DESERIALIZE_MEMBER(out_archive, Near);
								DESERIALIZE_MEMBER(out_archive, Far);
								DESERIALIZE_MEMBER(out_archive, Depth);
								DESERIALIZE_MEMBER(out_archive, DisplayTarget);
								return true;
							}


						public:
							////////////////////////////////////////////////
							// ENUMS
							//____________________________________	
							
							/** No clear. */
							/** Clear the render with a solid color. */
							/** Clear the render with the skybox. */
							/** Only clear the depth buffer. */
						
							SERIALIZABLE_ENUM(EClearFlag,
								None,
								Color,
								Skybox,
								DepthOnly
							)

							SERIALIZABLE_ENUM(EProjection,						
								Perspective,
								Orthographic
							)

						public:
							////////////////////////////////////////////////
							// DATA 
							//____________________________________	
							/** How the camera clears the background. */
							EClearFlag ClearFlag;
							UColor ClearColor{ UColor::ParadigmDarkGray };
							/** Mode of projection (Perspective, Orthographic). */
							EProjection Projection{ Perspective };
							/** This is used to render parts of the scene selectively. */
							Layer CullingMask{0x0};

							float FieldOfView{ PI * 0.5f };
							float Near{ .1f };
							float Far{ 1000.f };
							float Depth{ -1 };
						
							ETargetViewport DisplayTarget;
							//URenderTexture UTargetTexture;
				};
				SERIALIZABLE_INSTANCE(UMetaCamera)
			}
		}
	}
}

typedef ParadigmEngine::EngineFramework::MetaGear::LowRenderer::UMetaCamera::EClearFlag EClearFlag;
typedef ParadigmEngine::EngineFramework::MetaGear::LowRenderer::UMetaCamera::EProjection EProjection;
typedef ParadigmEngine::EngineFramework::MetaGear::LowRenderer::UMetaCamera UMetaCamera;

#endif