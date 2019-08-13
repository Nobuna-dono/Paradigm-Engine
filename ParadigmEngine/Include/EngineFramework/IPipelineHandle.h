#ifndef _IPIPELINEHANDLE_H_
#define _IPIPELINEHANDLE_H_
#include <ParadigmTypedef.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		enum EPipeline
		{
			NONE			= 0x0,
			INITIALIZE		= 0x1,
			FIXEDUPDATE		= 0x2,
			UPDATE			= 0x4,
			LATEUPDATE		= 0x8,
			DRAW			= 0x10,
			POSTDRAW		= 0x20,
			PREPHYSICS		= 0x40,
			POSTPHYSICS		= 0x80,
			PAUSE			= 0x100,
			TERMINATE		= 0x200
		};

		class IPipelineHandle
		{
			public:
			virtual void Initialize() {};
			virtual void FixedUpdate() {};
			virtual void Update() {};
			virtual void LateUpdate() {};
			virtual void Draw() {};
			virtual void PostDraw() {};
			virtual void PrePhysics() {};
			virtual void PostPhysics() {};
			virtual void Pause() {};
			virtual void Terminate() {};

			public:
			uint enabledPiplines{ (uint)-1 };
		};
	}
}

#endif // !_IPIPELINEHANDLE_H_

