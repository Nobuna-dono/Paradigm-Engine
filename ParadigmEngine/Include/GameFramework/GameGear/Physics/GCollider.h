#ifndef _GDYNAMICCOLLIDER_H_
#define _GDYNAMICCOLLIDER_H_
#include <Physics/Collision/UCollider.h>
#include <GameFramework/GameGear/GGear.h>
#include <Core/Dispach/FEvent.h>

namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear
		{
			namespace Physics
			{
				GEAR_CLASS(GCollider,UMetaCollider)
				{
					public:			
						//Constructor
						GCollider(UMetaEntity* _metaEntity) : GGear(_metaEntity) {}
						GCollider(UMetaCollider* _metaGear) : GGear(_metaGear) 
						{
							OnCollisionEnter.Subscribe(&FEvent<UCollision*>::Invoke, &_metaGear->OnCollisionEnter);
							OnCollisionStay.Subscribe(&FEvent<UCollision*>::Invoke, &_metaGear->OnCollisionStay);
							OnCollisionExit.Subscribe(&FEvent<UCollision*>::Invoke, &_metaGear->OnCollisionExit);

							OnTriggerEnter.Subscribe(&FEvent<UCollision*>::Invoke, &_metaGear->OnTriggerEnter);
							OnTriggerStay.Subscribe(&FEvent<UCollision*>::Invoke, &_metaGear->OnTriggerStay);
							OnTriggerExit.Subscribe(&FEvent<UCollision*>::Invoke, &_metaGear->OnTriggerExit);

						}

						PROPERTY(EColliderShape, Shape, { return m_MetaGear->Shape; }, { m_MetaGear->Shape = _value; });
						CUSTOM_GETTER_PROPERTY(UColliderShape*, ShapeData, { return m_MetaGear->ShapeData; });
						CUSTOM_PROPERTY(FVector3, RelativePosition, { return m_MetaGear->RelativePosition; }, { m_MetaGear->RelativePosition = _value; });

					public:
						FEvent<UCollision*> OnCollisionEnter;
						FEvent<UCollision*> OnCollisionStay;
						FEvent<UCollision*> OnCollisionExit;

						FEvent<UCollision*> OnTriggerEnter;
						FEvent<UCollision*> OnTriggerStay;
						FEvent<UCollision*> OnTriggerExit;
				};
			}
		}
	}
}

typedef ParadigmEngine::GameFramework::GameGear::Physics::GCollider GCollider;
#endif // !_GDYNAMICCOLLIDER_H_
