#ifndef _FPARADIGMENGINE_H_
#define _FPARADIGMENGINE_H_


#include <NativeInterface/Context/FContextInterface.h>
#include <NativeInterface/Graphics/FGraphicsInterface.h>
#include <NativeInterface/Input/FInputInterface.h>
#include <NativeInterface/Physics/FPhysicsInterface.h>

#include <Core/Serialization/FArchiveSupervisor.h>
#include <Core/Multiprograming/FThread.h>
#include <Scene/FSceneSupervisor.h>


#define PARADIGM_LIMITATION_MAX_ENTITY 0xFFF

namespace ParadigmEngine
{
	namespace Resource
	{
		class FResourceSupervisor;
	}

	namespace EngineFramework
	{
		namespace Factory
		{
			class FFactorySupervisor;
		}
		namespace NativeProcessor
		{
			class FProcessorSupervisor;
		}
	}

	class FParadigmEngine
	{		
		public:
			////////////////////////////////////////////////
			// STATIC
			//____________________________________	
			static FParadigmEngine& GetInstance()
			{
				if (!m_Instance)
					m_Instance = new FParadigmEngine();
				return *m_Instance;
			}

		public:
			////////////////////////////////////////////////
			// CONSTRUCTOR - DESTRUCTOR
			//____________________________________	
			FParadigmEngine();
			~FParadigmEngine();

		public:
			////////////////////////////////////////////////
			// PIPELINE
			//____________________________________	
			/** Initialize engine's branches. */
			void Initialize();
			/** Engine update. */
			void Run();

		public:
			////////////////////////////////////////////////
			// FUNCTIONALITY
			//____________________________________	
			FString ApplicationDirectory() const;
			bool Frame(bool _bOnGame = false);

		public:
			////////////////////////////////////////////////
			// DATA
			//____________________________________	
			EngineFramework::Factory::FFactorySupervisor*				Factory;
			EngineFramework::NativeProcessor::FProcessorSupervisor*		Processor;
			FArchiveSupervisor											Archive;
			Resource::FResourceSupervisor*								Resource;
			Core::Multiprograming::FThread 								Multiprograming;
			FContextInterface											Context;
			FGraphicsInterface											Graphics;
			FInputInterface												Input;
			FPhysicsInterface											Physics;
			Core::Time::FTime											Time;
			FSceneSupervisor											Scene;

		private:
			////////////////////////////////////////////////
			// Data
			//____________________________________
			static FParadigmEngine* m_Instance;
	};
}

#define PARADIGM ParadigmEngine::FParadigmEngine::GetInstance()
#define PARADIGM_CONTEXT ParadigmEngine::FParadigmEngine::GetInstance().Context
#define PARADIGM_FACTORY ParadigmEngine::FParadigmEngine::GetInstance().Factory
#define PARADIGM_GRAPHICS ParadigmEngine::FParadigmEngine::GetInstance().Graphics
#define PARADIGM_INPUT ParadigmEngine::FParadigmEngine::GetInstance().Input
#define PARADIGM_PROCESSOR ParadigmEngine::FParadigmEngine::GetInstance().Processor
#define PARADIGM_PHYSICS ParadigmEngine::FParadigmEngine::GetInstance().Physics
#define PARADIGM_RESOURCE ParadigmEngine::FParadigmEngine::GetInstance().Resource
#define PARADIGM_THREAD nullptr
#define PARADIGM_ARCHIVE ParadigmEngine::FParadigmEngine::GetInstance().Archive
#define PARADIGM_SCENE ParadigmEngine::FParadigmEngine::GetInstance().Scene

#define GENERATE_ARCHIVE_CLASS(SerializableClass) ParadigmEngine::FParadigmEngine::GetInstance().Archive.AddClassReplica(SerializableClass)
#define GENERATE_ASSET_ARCHIVE(SerializableClass, Name) ParadigmEngine::FParadigmEngine::GetInstance().Archive.AddAssetReplica(SerializableClass, Name)
#define GENERATE_GEAR_ARCHIVE(SerializableClass, Name) ParadigmEngine::FParadigmEngine::GetInstance().Archive.AddGearReplica(SerializableClass, Name)

#endif