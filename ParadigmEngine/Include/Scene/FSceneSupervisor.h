#ifndef _FSCENESUPERVISOR_H_
#define _FSCENESUPERVISOR_H_
#include <EngineFramework/Factory/UMetaEntity.h>

namespace ParadigmEngine
{
	namespace Scene
	{
		class FSceneSupervisor
		{
		public:

			void LoadScene(FString _path);
			void AsyncLoadScene(FString _path);
			void SaveScene(FString _path);

			UMetaEntity Root;
		private:
			FString CurrentSceneName;
			//SkySphere
		};
	}
	typedef Scene::FSceneSupervisor FSceneSupervisor;
}

#endif // !_FSCENESUPERVISOR_H_
