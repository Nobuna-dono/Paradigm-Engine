#ifndef _FSHADER_H_
#define _FSHADER_H_

#include <Resource/UShader.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		/** The @UShader's functionality class. */
		class FShader
		{
			public:
				////////////////////////////////////////////////
				// FUNCTIONALITY
				//____________________________________		
				static void SyncResource(UShader& out_shader, bool _brefresh = false);

				/** Add a shard to the shader asset. */
				static void SetShard(UShader& out_shader, EShaderType _shardType, KShardShader _kShard);
				
				/** Add a shard to the shader asset. */
				static void SetShard(UShader& out_shader, const UShardShader& _shard);

				/** Remove a shard to the shader asset. */
				static void RemoveShard(UShader& out_shader, const UShardShader& _shard);
		};
	}
}
typedef ParadigmEngine::Resource::FShader FShader;

#endif //_FSHADER_H_