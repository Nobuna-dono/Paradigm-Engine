#ifndef _UCUSTOMBEHAVIOURGEAR_H_
#define _UCUSTOMBEHAVIOURGEAR_H_
#include <EngineFramework/MetaGear/ParadigmMetaGear.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace MetaGear
		{
			class UCustomBehaviourGear : public UMetaGear
			{
				public:
					virtual void Initialize() {};
					virtual void Update() {};
					virtual void FixedUpdate() {};
					virtual void LateUpdate() {};
					virtual void PrePhysics() {};
					virtual void PostPhysics() {};
					virtual void Pause() {};
					virtual void Terminate() {};
			};
		}
	}
	typedef EngineFramework::MetaGear::UCustomBehaviourGear UCustomBehaviourGear;
	template <class T>
	using IfDeriveCustomGear = std::enable_if_t<std::is_base_of<UCustomBehaviourGear, T>::value>;
}


#endif // !_UCUSTOMBEHAVIOURGEAR_H_
