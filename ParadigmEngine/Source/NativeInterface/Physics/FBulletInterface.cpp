#include <NativeInterface/Physics/FBulletInterface.h>
#include <NativeInterface/Physics/BulletMotionState.h>
#include <EngineFramework/Factory/FMetaEntity.h>
#include <Physics/Force/FRigidbody.h>
#include <Physics/Collision/UCollision.h>
#include <Physics/FTransform.h>
#include <ParadigmException.h>
#include <Physics/Collider.h>
#include <typeinfo>

namespace ParadigmEngine
{
	using namespace Physics;
	using namespace Physics::Force;

	namespace NativeInterface
	{
		namespace Physics
		{
			FBulletInterface::FBulletInterface() : IDynamicPhysicsInterface()
			{
				m_collisionConfiguration = new btDefaultCollisionConfiguration();
				m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
				m_overlappingPairCache = new btDbvtBroadphase();
				m_solver = new btSequentialImpulseConstraintSolver;
				m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);

				gContactAddedCallback = FBulletInterface::EnterCollisionCallback;
				gContactDestroyedCallback = FBulletInterface::DestroyCollisionCallback;

				///	SetGravity({0,0,0});
				SetEarthGravity();



				m_previousUpdate = NOW;
			}

			FBulletInterface::~FBulletInterface()
			{
				//remove the rigidbodies from the dynamics world and delete them
				for (int i = m_dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
				{
					btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
					btRigidBody* body = btRigidBody::upcast(obj);
					if (body && body->getMotionState())
					{
						delete body->getMotionState();
					}
					m_dynamicsWorld->removeCollisionObject(obj);
					delete obj;
				}

				//delete collision shapes
				for (TKeyTable<btCollisionShape*>::Iterator it = m_colliderTable.Begin(); it != m_colliderTable.End(); ++it)
				{
					btCollisionShape* shape = *it;
					*it = 0;
					delete shape;
				}

				//delete dynamics world
				delete m_dynamicsWorld;

				//delete solver
				delete m_solver;

				//delete broadphase
				delete m_overlappingPairCache;

				//delete dispatcher
				delete m_dispatcher;

				delete m_collisionConfiguration;

				m_colliderTable.Clear();

			}

#pragma region Colliders Link Methods

			void FBulletInterface::LinkCollider(UMetaCollider* _col)
			{
				btCollisionShape* shape{nullptr};
				switch (_col->Shape)
				{
					case ParadigmEngine::Physics::Collision::NONE:
					//	shape = new btEmptyShape();
						return;
					case ParadigmEngine::Physics::Collision::BOX:
						shape = new btBoxShape(FNativeConvertor::ToBulletData(FVector3(((UMetaBoxCollider*)_col->ShapeData)->size) / 2));
						break;
					case ParadigmEngine::Physics::Collision::SPHERE:
						shape = new btSphereShape(((USphereCollider*)_col->ShapeData)->radius);
						break;
					case ParadigmEngine::Physics::Collision::CAPSULE:
						shape = new btCapsuleShape(((UMetaCapsuleCollider*)_col->ShapeData)->radius, ((UMetaCapsuleCollider*)_col->ShapeData)->height);
						break;
					case ParadigmEngine::Physics::Collision::CYLINDER:
						shape = new btCylinderShape({ ((UCylindreCollider*)_col->ShapeData)->radius, ((UCylindreCollider*)_col->ShapeData)->height, ((UCylindreCollider*)_col->ShapeData)->radius });
						break;
					case ParadigmEngine::Physics::Collision::CONE:
						shape = new btConeShape(((UConeCollider*)_col->ShapeData)->radius, ((UConeCollider*)_col->ShapeData)->height);
						break;
					case ParadigmEngine::Physics::Collision::MESH:
						//		shape = new btTriangleMeshShape(FNativeConvertor::ToBulletData(((UMeshCollider*)_col->ShapeData)->size / 2));
						THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR("UMeshCollider not yet implemented");
						break;
					default:
						break;
				}
				if (!shape)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("Argument invalid");

				shape->setUserPointer(_col);
				_col->CorrespondentKey = m_colliderTable.Add(shape);
			}
#pragma endregion

#pragma region RigidBodies Methods

			void FBulletInterface::GetChildrensColliders(btCompoundShape* _shape, UMetaEntity* _currentEntity, UMetaTransform* _rgidbody, UVector3& out_centerofmass)
			{
				TArray<UMetaCollider*> colls = _currentEntity->GetGears<UMetaCollider>();
				UMetaTransform* tr = _currentEntity->GetTransform();
				for (uint i = 0; i < colls.Count(); ++i)
				{
					LinkCollider(colls[i]);
					UVector3 relativepos = (FVector3{ tr ? _rgidbody->Position - tr->Position : FVector3::Zero } +colls[i]->RelativePosition)* _currentEntity->GetTransform()->Rotation;
					UQuaternion relativerot = tr ? tr->Rotation / _rgidbody->Rotation : FQuaternion::Identity;

					_shape->addChildShape(FNativeConvertor::ToBulletData(UMetaTransform(relativepos, FQuaternion{ relativerot })), m_colliderTable[colls[i]->CorrespondentKey]);

					UVector3 deltaCenter = (FVector3{ tr->Position } -_rgidbody->Position - FVector3{ out_centerofmass }) / max(1.f, _shape->getNumChildShapes());
					out_centerofmass = FVector3{ out_centerofmass } +deltaCenter;
				}

				auto children = _currentEntity->GetChildrens();
				for (uint i = 0; i < children.Count(); ++i)
					if (!children[i]->GetGear<UMetaRigidbody>())
					{
						GetChildrensColliders(_shape, children[i], _rgidbody, out_centerofmass);
					}
			}


			void FBulletInterface::LinkRigidbody(UMetaRigidbody* _rigidbody)
			{
				//Get transform and, if there'isnt, add one
				UMetaTransform* transPtr = _rigidbody->GearedUnit->GetTransform();
				if (!transPtr)
					transPtr = FMetaEntity::AddGear<UMetaTransform>(_rigidbody->GearedUnit).Pointer;

				//Create motionstate
				btDefaultMotionState* myMotionState = new ParadigmBulletMotionState(_rigidbody, FNativeConvertor::ToBulletData(*transPtr));

				//Getr the colliders
				btCompoundShape* collptr = new btCompoundShape();
				m_colliderTable.Add(collptr);

				UVector3 centerofmass/* = {1000,0,0}= transPtr->Position*/;
				GetChildrensColliders(collptr, _rigidbody->GearedUnit, transPtr, centerofmass);

				float mass = _rigidbody->Mass;
				if (collptr->getNumChildShapes() == 0u)
					mass = 0.f;

				btVector3 localInertia(0, 0, 0);
				if (mass != 0.f)
					collptr->calculateLocalInertia(mass, localInertia);
				else
					transPtr->isStatic = true;

				btScalar* masses = new btScalar[collptr->getNumChildShapes()];
				for (int j = 0; j < collptr->getNumChildShapes(); j++)
				{
					//evenly distribute mass
					masses[j] = mass / collptr->getNumChildShapes();
				}
				collptr->calculatePrincipalAxisTransform(masses, FNativeConvertor::ToBulletData(UMetaTransform{ FVector3 {centerofmass} +transPtr->Position }), localInertia);

				//create bullet's rigidbody
				btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, collptr, localInertia);
				btRigidBody* body = new btRigidBody(rbInfo);
				body->setUserPointer(_rigidbody->GearedUnit);
				body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

				int id = Layers.GetLayer(_rigidbody->PhysicsTag);
				int mask = Layers.GetLayerMask(_rigidbody->PhysicsTag);
				//add the body to the dynamics world
				m_dynamicsWorld->addRigidBody(body, id, mask);

				_rigidbody->CorrespondentKey = m_rigidbodyTable.Add(body);
				if (mass != 0.f)
				{
					//	FRigidbody::SetCenterOfMass(*_rigidbody, { -1000,0,0 });
					FRigidbody::SetCenterOfMass(*_rigidbody, centerofmass);
					FPrint::Print(FVector3{ FRigidbody::GetCenterOfMass(*_rigidbody) });

					if (collptr->getNumChildShapes() > 1)
						FPrint::Print("Multiple colliders dont work well, got a wierd center of mass. Sorries from Lucas B.", ParadigmEngine::Core::Debug::WARNING_LEVEL);
				}
			}

			void FBulletInterface::SetActivationStateRigidbody(UMetaRigidbody*  _rigidbody)
			{
				btRigidBody* body = m_rigidbodyTable[_rigidbody->CorrespondentKey];
				m_dynamicsWorld->removeRigidBody(body);
				m_rigidbodyTable.Remove(_rigidbody->CorrespondentKey);
				delete body;
				body->setActivationState(WANTS_DEACTIVATION);
				//			body->setActivationState(DISABLE_SIMULATION);
			}

			void FBulletInterface::DestroyRigidbody(UMetaRigidbody* _rigidbody)
			{
				btRigidBody* body = m_rigidbodyTable[_rigidbody->CorrespondentKey];
				m_dynamicsWorld->removeRigidBody(body);
				m_rigidbodyTable.Remove(_rigidbody->CorrespondentKey);
				delete body;
			}

			void FBulletInterface::PresetRigidbody(UMetaRigidbody* _rigidbody)
			{
				btRigidBody* body = m_rigidbodyTable[_rigidbody->CorrespondentKey];
				UMetaTransform* transPtr = _rigidbody->GearedUnit->GetGear<UMetaTransform>();
				if (transPtr->bOutdated)
				{
					body->setWorldTransform(FNativeConvertor::ToBulletData(*transPtr));
					transPtr->Updated();
					body->setActivationState(ACTIVE_TAG);
				}

				if (_rigidbody->outdated)
				{
					body->setLinearFactor({ static_cast<btScalar>(!_rigidbody->freezePositionX), static_cast<btScalar>(!_rigidbody->freezePositionY), static_cast<btScalar>(!_rigidbody->freezePositionZ) });
					body->setAngularFactor({ static_cast<btScalar>(!_rigidbody->freezeRotationX), static_cast<btScalar>(!_rigidbody->freezeRotationY), static_cast<btScalar>(!_rigidbody->freezeRotationZ) });

					if (!(_rigidbody->isKinematic &&  body->isKinematicObject() || !_rigidbody->isKinematic && !body->isKinematicObject()))
						body->setCollisionFlags(body->getCollisionFlags() + btCollisionObject::CF_KINEMATIC_OBJECT * (_rigidbody->isKinematic ? 1 : -1));
					if (!(transPtr->isStatic && body->isStaticObject() || !transPtr->isStatic && !body->isStaticObject()))
						body->setCollisionFlags(body->getCollisionFlags() + btCollisionObject::CF_STATIC_OBJECT * (transPtr->isStatic ? 1 : -1));

					//if (_rigidbody->GearedUnit->OnCollisionEnter.ListenerCount() == 0 &&
					//	_rigidbody->GearedUnit->OnCollisionStay.ListenerCount() == 0 &&
					//	_rigidbody->GearedUnit->OnCollisionExit.ListenerCount() == 0)
					//	body->setCollisionFlags(body->getCollisionFlags() & (!btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK));
					//else
					//	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
					_rigidbody->outdated = false;
				}

				if (_rigidbody->useGravityoutdated)
				{
					SetOneGravity(*_rigidbody, _rigidbody->useGravity ? FNativeConvertor::ToParadigmData(m_dynamicsWorld->getGravity()) : FVector3::Zero);
					_rigidbody->useGravityoutdated = false;

				}
			}


			UVector3 FBulletInterface::GetTotalTorque(UMetaRigidbody& _rig)
			{
				return FNativeConvertor::ToParadigmData(m_rigidbodyTable[_rig.CorrespondentKey]->getTotalTorque());
			}

			void FBulletInterface::ApplyTorque(UMetaRigidbody& _rig, const UVector3 _vec)
			{
				m_rigidbodyTable[_rig.CorrespondentKey]->applyTorque(FNativeConvertor::ToBulletData(_vec));
			}

			UVector3 FBulletInterface::GetTotalForce(UMetaRigidbody& _rig)
			{
				return FNativeConvertor::ToParadigmData(m_rigidbodyTable[_rig.CorrespondentKey]->getTotalForce());
			}

			void FBulletInterface::ApplyForce(UMetaRigidbody& _rig, const UVector3 _force, const UVector3 _applicationPosition)
			{
				m_rigidbodyTable[_rig.CorrespondentKey]->applyForce(FNativeConvertor::ToBulletData(_force), FNativeConvertor::ToBulletData(_applicationPosition));
			}

			void FBulletInterface::ClearForces(UMetaRigidbody& _rig)
			{
				m_rigidbodyTable[_rig.CorrespondentKey]->clearForces();
			}

			UVector3	FBulletInterface::GetLinearVelocity(UMetaRigidbody& _rig)
			{
				return 	FNativeConvertor::ToParadigmData(m_rigidbodyTable[_rig.CorrespondentKey]->getLinearVelocity());
			}

			UVector3	FBulletInterface::GetAngularVelocity(UMetaRigidbody& _rig)
			{
				return 	FNativeConvertor::ToParadigmData(m_rigidbodyTable[_rig.CorrespondentKey]->getAngularVelocity());
			}

			void FBulletInterface::SetLinearVelocity(UMetaRigidbody& _rig, const UVector3& _vec)
			{
				m_rigidbodyTable[_rig.CorrespondentKey]->setLinearVelocity(FNativeConvertor::ToBulletData(_vec));
			}

			void FBulletInterface::SetAngularVelocity(UMetaRigidbody& _rig, const UVector3& _vec)
			{
				m_rigidbodyTable[_rig.CorrespondentKey]->setAngularVelocity(FNativeConvertor::ToBulletData(_vec));
			}

			UVector3 FBulletInterface::GetCenterOfMass(UMetaRigidbody& _rig)
			{
				return 	FNativeConvertor::ToParadigmData(m_rigidbodyTable[_rig.CorrespondentKey]->getCenterOfMassPosition());
			}

			void FBulletInterface::SetCenterOfMass(UMetaRigidbody& _rig, const UVector3& _vec)
			{
				m_rigidbodyTable[_rig.CorrespondentKey]->setCenterOfMassTransform(btTransform(btMatrix3x3::getIdentity(), FNativeConvertor::ToBulletData(_vec)));
			}

			void FBulletInterface::SetOneGravity(const UMetaRigidbody& _rig, UVector3 _vec)
			{
				m_rigidbodyTable[_rig.CorrespondentKey]->setGravity(FNativeConvertor::ToBulletData(_vec));
			}

			UVector3 FBulletInterface::GetOneGravity(const UMetaRigidbody& _rig)
			{
				return FNativeConvertor::ToParadigmData(m_rigidbodyTable[_rig.CorrespondentKey]->getGravity());
			}
#pragma endregion

			void FBulletInterface::SetGravity(const FVector3& _vec)
			{
				m_dynamicsWorld->setGravity({ _vec.x, _vec.y, _vec.z });
			}

			void FBulletInterface::DestroyCollider(UMetaCollider* _col)
			{
				btCollisionShape* shp = m_colliderTable[_col->CorrespondentKey];
				m_colliderTable.Remove(_col->CorrespondentKey);
				delete shp;
			}

			void FBulletInterface::Initialize()
			{

			}

			void FBulletInterface::Step()
			{
				m_dynamicsWorld->stepSimulation(TIMELAG(m_previousUpdate) / 1000, 4);
				m_previousUpdate = NOW;
			}

			TArray<ParadigmEngine::Physics::Collision::URayCastHit> FBulletInterface::Raycast(UVector3& _from, UVector3& _to, bool _stopToFirstCollision) const
			{
				TArray<ParadigmEngine::Physics::Collision::URayCastHit> hits;

				btCollisionWorld::RayResultCallback* result;
				if (_stopToFirstCollision)
				{
					btCollisionWorld::ClosestRayResultCallback* result1 = new btCollisionWorld::ClosestRayResultCallback(FNativeConvertor::ToBulletData(_from), FNativeConvertor::ToBulletData(_to));
					m_dynamicsWorld->rayTest(FNativeConvertor::ToBulletData(_from), FNativeConvertor::ToBulletData(_to), *result1);
					if (result1->hasHit())
						hits.Add({ static_cast<EngineFramework::Factory::UMetaEntity*>(result1->m_collisionObject->getUserPointer()),
									 FNativeConvertor::ToParadigmData(result1->m_hitNormalWorld),
									 FNativeConvertor::ToParadigmData(result1->m_hitPointWorld),
									 result1->m_closestHitFraction });
					result = result1;
				}
				else
				{
					btCollisionWorld::AllHitsRayResultCallback* result2 = new btCollisionWorld::AllHitsRayResultCallback(FNativeConvertor::ToBulletData(_from), FNativeConvertor::ToBulletData(_to));
					m_dynamicsWorld->rayTest(FNativeConvertor::ToBulletData(_from), FNativeConvertor::ToBulletData(_to), *result2);

					if (result2->hasHit())
						for (int i = 0; i < result2->m_collisionObjects.size(); ++i)
						{
							hits.Add({ static_cast<EngineFramework::Factory::UMetaEntity*>(result2->m_collisionObject->getUserPointer()),
										 FNativeConvertor::ToParadigmData(result2->m_hitNormalWorld[i]),
										 FNativeConvertor::ToParadigmData(result2->m_hitPointWorld[i]),
										 result2->m_hitFractions[i] });
						}
					result = result2;
				}


				delete result;
				return hits;
			}

			bool FBulletInterface::Raycast(UVector3& _from, UVector3& _to, ParadigmEngine::Physics::Collision::URayCastReport& hit, bool _stopToFirstCollision) const
			{
				hit.hits = Raycast(_from, _to, _stopToFirstCollision);

				bool hasHit = hit.hasHit = hit.hits.Count() > 0;
				return hasHit;
			}

			bool FBulletInterface::EnterCollisionCallback(btManifoldPoint& _cp, const btCollisionObjectWrapper* _colObj0Wrap, int _partId0, int _index0,
														  const btCollisionObjectWrapper* _colObj1Wrap, int _partId1, int _index1)
			{
				EngineFramework::Factory::UMetaEntity* object1 = static_cast<EngineFramework::Factory::UMetaEntity*>(_colObj0Wrap->getCollisionObject()->getUserPointer());
				EngineFramework::Factory::UMetaEntity* object2 = static_cast<EngineFramework::Factory::UMetaEntity*>(_colObj1Wrap->getCollisionObject()->getUserPointer());

				UMetaCollider* coll0 = static_cast<UMetaCollider*>(_colObj0Wrap->getCollisionShape()->getUserPointer());
				UMetaCollider* coll1 = static_cast<UMetaCollider*>(_colObj1Wrap->getCollisionShape()->getUserPointer());

				Collision::UCollision* collision = static_cast<UCollision*>(_cp.m_userPersistentData);
				if (!_cp.getLifeTime())
				{
					collision = new UCollision;
					_cp.m_userPersistentData = collision;
				}

				*collision = { FNativeConvertor::ToParadigmData(_cp) };

				if ((_colObj0Wrap->getCollisionObject()->getCollisionFlags() & btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK) == btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK)
				{
					collision->m_Object1 = coll0;
					collision->m_Object2 = coll1;

					if (_cp.getLifeTime() == 0)
					{
						if (_cp.getAppliedImpulse() == 0.f)
							coll0->OnTriggerEnter(collision);
						coll0->OnCollisionEnter(collision);
					}
					else
					{
						if (_cp.getAppliedImpulse() == 0.f)
							coll0->OnTriggerStay(collision);
						coll0->OnCollisionStay(collision);
					}
				}

				if ((_colObj1Wrap->getCollisionObject()->getCollisionFlags() & btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK) == btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK)
				{
					collision->m_Object1 = coll1;
					collision->m_Object2 = coll0;

					if (_cp.getLifeTime() == 0)
					{
						if (_cp.getAppliedImpulse() == 0.f)
							coll1->OnTriggerEnter(collision);
						coll1->OnCollisionEnter(collision);
					}
					else
					{
						if (_cp.getAppliedImpulse() == 0.f)
							coll1->OnTriggerStay(collision);
						coll1->OnCollisionStay(collision);
					}
				}
				return false;
			}

			bool FBulletInterface::DestroyCollisionCallback(void* usrPtr)
			{
				UCollision* coll = static_cast<UCollision*>(usrPtr);
				coll->m_Object1->OnCollisionExit(coll);
				coll->m_Object2->OnCollisionExit(coll);
				return false;
			}


#pragma region DataConvertion Methods

			btTransform FBulletInterface::FNativeConvertor::ToBulletData(const UMetaTransform& _tra)
			{
				btTransform tempTransform;
				tempTransform.setIdentity();
				tempTransform.setOrigin(ToBulletData(_tra.Position));
				tempTransform.setRotation(ToBulletData(_tra.Rotation));
				return tempTransform;
			}

			btVector3 FBulletInterface::FNativeConvertor::ToBulletData(const FVector3& _vec)
			{
				return { _vec.x, _vec.y, _vec.z };
			}

			btQuaternion FBulletInterface::FNativeConvertor::ToBulletData(const FQuaternion& _quat)
			{
				return { _quat.x, _quat.y, _quat.z, _quat.w };
			}

			btManifoldPoint FBulletInterface::FNativeConvertor::ToBulletData(const UCollision& _coll)
			{
				btManifoldPoint  out(ToBulletData(_coll.m_localPointA), ToBulletData(_coll.m_localPointB), ToBulletData(_coll.m_normalWorldOnB), _coll.m_distance1);
				out.m_positionWorldOnB = ToBulletData(_coll.m_positionWorldOnB);

				out.m_combinedFriction = _coll.m_combinedFriction;
				out.m_combinedRollingFriction = _coll.m_combinedRollingFriction;
				out.m_combinedSpinningFriction = _coll.m_combinedSpinningFriction;
				out.m_combinedRestitution = _coll.m_combinedRestitution;

				out.m_contactPointFlags = _coll.m_contactPointFlags;

				out.m_appliedImpulse = _coll.m_appliedImpulse;
				out.m_appliedImpulseLateral1 = _coll.m_appliedImpulseLateral1;
				out.m_appliedImpulseLateral2 = _coll.m_appliedImpulseLateral2;
				out.m_contactMotion1 = _coll.m_contactMotion1;
				out.m_contactMotion2 = _coll.m_contactMotion2;

				out.m_combinedContactStiffness1 = _coll.m_combinedContactStiffness1;
				out.m_combinedContactDamping1 = _coll.m_combinedContactDamping1;

				out.m_frictionCFM = _coll.m_frictionCFM;
				out.m_lifeTime = _coll.m_lifeTime;

				out.m_lateralFrictionDir1 = ToBulletData(_coll.m_lateralFrictionDir1);
				out.m_lateralFrictionDir2 = ToBulletData(_coll.m_lateralFrictionDir2);
				return out;
			}

			UMetaTransform FBulletInterface::FNativeConvertor::ToParadigmData(const btTransform& _tra)
			{
				UMetaTransform tempTransform;
				tempTransform.Position = FVector3(ToParadigmData(_tra.getOrigin()));
				tempTransform.Rotation = ToParadigmData(_tra.getRotation());
				return tempTransform;
			}

			UVector3 FBulletInterface::FNativeConvertor::ToParadigmData(const btVector3& _vec)
			{
				return { _vec.getX(), _vec.getY(), _vec.getZ() };
			}

			FQuaternion FBulletInterface::FNativeConvertor::ToParadigmData(const btQuaternion& _quat)
			{
				//return FQuaternion{ _quat.getZ(), _quat.getW(), _quat.getX(), -_quat.getY() };
				return FQuaternion{ _quat.getW(), _quat.getX(), _quat.getY(), _quat.getZ() };
			}

			UCollision FBulletInterface::FNativeConvertor::ToParadigmData(const btManifoldPoint& _mani)
			{
				return	{ nullptr,
							nullptr,
							ToParadigmData(_mani.m_localPointA),
							ToParadigmData(_mani.m_localPointB),
							ToParadigmData(_mani.m_positionWorldOnB),
							ToParadigmData(_mani.m_normalWorldOnB),
							_mani.m_distance1,
							_mani.m_combinedFriction,
							_mani.m_combinedRollingFriction,
							_mani.m_combinedSpinningFriction,
							_mani.m_combinedRestitution,
							_mani.m_contactPointFlags,
							_mani.m_appliedImpulse,
							_mani.m_appliedImpulseLateral1,
							_mani.m_appliedImpulseLateral2,
							_mani.m_contactMotion1,
							_mani.m_contactMotion2,
							_mani.m_combinedContactStiffness1,
							_mani.m_combinedContactDamping1,
							_mani.m_frictionCFM,
							_mani.m_lifeTime,
							ToParadigmData(_mani.m_lateralFrictionDir1),
							ToParadigmData(_mani.m_lateralFrictionDir2)
				};
			}
#pragma endregion
		}
	}
}