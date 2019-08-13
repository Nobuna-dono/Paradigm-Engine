#ifndef _CAMERAMOVES_H_
#define _CAMERAMOVES_H_
#include <EngineFramework\MetaGear\UCustomBehaviourGear.h>
#include <ParadigmMath.h>


namespace ParadigmEditor
{
	class CameraMoves : public ParadigmEngine::UCustomBehaviourGear
	{
	public :
		//Methods
		void LateUpdate() override;
	private :
		//Data
		UVector3 m_Rotations;
		UAxis m_MouseBuffer{0,0};
		float m_RotationSpeed{ 150.f };
		float m_MovementSpeed{ 10.f };
		float m_SpeedMultiplier{ 5.f };
		float m_PickingDistance{ 1000.f };
	};
}

#endif