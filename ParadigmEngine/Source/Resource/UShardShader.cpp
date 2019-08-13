#include <Resource/UShardShader.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		UShardShader::UShardShader(const FString& _resourcePathname, EShaderType _type, FString _entryPoint)
			: UResource(_resourcePathname), Type{ _type }, EntryPoint{ _entryPoint }
		{}
	}
}