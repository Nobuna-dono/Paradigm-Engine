#include <EngineFramework/NativeProcessor/FProcessorSupervisor.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace NativeProcessor
		{
			void FProcessorSupervisor::Initialize()
			{
				for (std::unordered_map<GearID, UProcessor*>::iterator it = m_Processors.begin(); it != m_Processors.end(); ++it)
				{
					if ((*it).second->enabledPiplines & INITIALIZE)
					{
						(*it).second->CaptureData();
						(*it).second->Initialize();
					}
				}
			}

			void FProcessorSupervisor::FixedUpdate()
			{
				for (std::unordered_map<GearID, UProcessor*>::iterator it = m_Processors.begin(); it != m_Processors.end(); ++it)
				{
					if ((*it).second->enabledPiplines & FIXEDUPDATE)
					{
						(*it).second->CaptureData();
						(*it).second->FixedUpdate();
					}
				}
			}

			void FProcessorSupervisor::Update()
			{
				for (std::unordered_map<GearID, UProcessor*>::iterator it = m_Processors.begin(); it != m_Processors.end(); ++it)
				{
					if ((*it).second->enabledPiplines & (UPDATE | INITIALIZE))
					{
						(*it).second->CaptureData();
						(*it).second->Update();
					}
				}
			}

			void FProcessorSupervisor::LateUpdate()
			{
				for (std::unordered_map<GearID, UProcessor*>::iterator it = m_Processors.begin(); it != m_Processors.end(); ++it)
				{
					if ((*it).second->enabledPiplines & LATEUPDATE)
					{
						(*it).second->CaptureData();
						(*it).second->LateUpdate();
					}
				}
			}

			void FProcessorSupervisor::Pause()
			{
				for (std::unordered_map<GearID, UProcessor*>::iterator it = m_Processors.begin(); it != m_Processors.end(); ++it)
				{
					if ((*it).second->enabledPiplines & PAUSE)
					{
						(*it).second->CaptureData();
						(*it).second->Pause();
					}
				}
			}

			void FProcessorSupervisor::Terminate()
			{
				for (std::unordered_map<GearID, UProcessor*>::iterator it = m_Processors.begin(); it != m_Processors.end(); ++it)
				{
					if ((*it).second->enabledPiplines & TERMINATE)
					{
						(*it).second->CaptureData();
						(*it).second->Terminate();
					}
				}
			}

			void FProcessorSupervisor::Draw()
			{
				for (std::unordered_map<GearID, UProcessor*>::iterator it = m_Processors.begin(); it != m_Processors.end(); ++it)
				{
					if ((*it).second->enabledPiplines & DRAW)
					{
						(*it).second->CaptureData();
						(*it).second->Draw();
					}
				}
			}

			void FProcessorSupervisor::PostDraw()
			{
				for (std::unordered_map<GearID, UProcessor*>::iterator it = m_Processors.begin(); it != m_Processors.end(); ++it)
				{
					if ((*it).second->enabledPiplines & POSTDRAW)
					{
						(*it).second->CaptureData();
						(*it).second->PostDraw();
					}
				}
			}

			void FProcessorSupervisor::PrePhysics()
			{
				for (std::unordered_map<GearID, UProcessor*>::iterator it = m_Processors.begin(); it != m_Processors.end(); ++it)
				{
					if ((*it).second->enabledPiplines & PREPHYSICS)
					{
						(*it).second->CaptureData();
						(*it).second->PrePhysics();
					}
				}
			}

			void FProcessorSupervisor::PostPhysics()
			{
				for (std::unordered_map<GearID, UProcessor*>::iterator it = m_Processors.begin(); it != m_Processors.end(); ++it)
				{
					if ((*it).second->enabledPiplines & POSTPHYSICS)
					{
						(*it).second->CaptureData();
						(*it).second->PostPhysics();
					}
				}
			}
		}
	}
}