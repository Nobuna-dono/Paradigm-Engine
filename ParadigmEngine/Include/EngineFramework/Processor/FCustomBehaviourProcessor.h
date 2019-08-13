#ifndef _FCUSTOMBEHAVIOURPROCESSOR_H_
#define _FCUSTOMBEHAVIOURPROCESSOR_H_
//#include <EngineFramework\Processor\TGearProcessor.h>
#include <EngineFramework/MetaGear/UCustomBehaviourGear.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace Processor
		{
			template <typename T>
			class TGearProcessor;

			template <typename T, typename = ParadigmEngine::IfDeriveCustomGear<T>>
			class FCustomBehaviourProcessor : public TGearProcessor<T>
			{
				public:
					static const uint BaseEnabledPipelines{ INITIALIZE | FIXEDUPDATE | UPDATE | LATEUPDATE | DRAW | POSTDRAW | PREPHYSICS | POSTPHYSICS | PAUSE | TERMINATE };
					virtual void InitializeOne(T& _data) override {	_data.Initialize();	};
	
					virtual void UpdateOne(T& _data) override { _data.Update(); };
					virtual void FixedUpdateOne(T& _data) override { _data.FixedUpdate(); };
					virtual void LateUpdateOne(T& _data) override { _data.LateUpdate(); };
	
					virtual void DrawOne(T& _data) override { /*_data.Draw();*/ };
	
					virtual void PrePhysicsOne(T& _data) override { _data.PrePhysics(); };
					virtual void PostPhysicsOne(T& _data) override { _data.PostPhysics(); };
	
					virtual void PauseOne(T& _data) override { _data.Pause(); };
					virtual void TerminateOne(T& _data) override { _data.Terminate(); };
			};
		}
	}
}

using namespace ParadigmEngine::EngineFramework;
template <class T>
class FOverridableCustomProcessor : public ParadigmEngine::EngineFramework::Processor::FCustomBehaviourProcessor<T>
{
	public :	static const uint BaseEnabledPipelines
	{ INITIALIZE | FIXEDUPDATE | UPDATE | LATEUPDATE | DRAW | POSTDRAW | PREPHYSICS | POSTPHYSICS | PAUSE | TERMINATE };
};
/** Use this if you want to change the comportement of your METATYPE's Processor*/
#define GEAR_CUSTOM_PROCESSOR_CLASS(NAME, METATYPE)					\
		typedef FOverridableCustomProcessor<METATYPE> NAME;			\
		template <>													\
		class FOverridableCustomProcessor<METATYPE> : public ParadigmEngine::EngineFramework::Processor::FCustomBehaviourProcessor<METATYPE>
//#include <EngineFramework\Processor\FCustomBehaviourProcessor.inl>
#endif // !_FCUSTOMBEHAVIOURGEAR_H_
