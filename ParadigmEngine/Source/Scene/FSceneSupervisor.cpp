#include <Scene/FSceneSupervisor.h>
#include <FParadigmEngine.h>
#include <EngineFramework/Factory/FFactorySupervisor.h>

namespace ParadigmEngine
{
	namespace Scene
	{
		void FSceneSupervisor::LoadScene(FString _path)
		{
			PARADIGM_FACTORY->Clear();

		}

		void FSceneSupervisor::AsyncLoadScene(FString _path)
		{
			PARADIGM_FACTORY->Clear();
			//multithread->AddToQueue(LoadScene(_path));
		}

		void FSceneSupervisor::SaveScene(FString _path)
		{

			
		}
	}
}