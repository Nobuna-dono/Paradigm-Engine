#include <EngineFramework\Processor\FCustomBehaviourProcessor.h>
#include <EngineFramework\MetaGear\LowRenderer\FMetaCamera.h>
#include <Include/Scene/CameraMoves.h>
#include <Physics\FTransform.h>
#include <FParadigmEngine.h>

namespace ParadigmEditor
{
	void CameraMoves::LateUpdate()
	{
		ParadigmEngine::EngineFramework::MetaGear::LowRenderer::UMetaCamera* cam = GearedUnit->GetGear<ParadigmEngine::EngineFramework::MetaGear::LowRenderer::UMetaCamera>();
#ifndef _PARADIGM_EDITOR
		if (PARADIGM_CONTEXT->IsFocusOn(cam->DisplayTarget))
#endif
		{
			UMetaTransform* tr = GearedUnit->GetTransform();

			float forward = 0;
			if (PARADIGM_INPUT->IsKeyDown(cam->DisplayTarget, EKeyCode::W))
				forward = 1;
			else if (PARADIGM_INPUT->IsKeyDown(cam->DisplayTarget, EKeyCode::S))
				forward = -1;

			FVector3 velocity = tr->Forward() * forward;

			float right = 0;
			if (PARADIGM_INPUT->IsKeyDown(cam->DisplayTarget, EKeyCode::D))
				right = 1;
			else if (PARADIGM_INPUT->IsKeyDown(cam->DisplayTarget, EKeyCode::A))
				right = -1;
			velocity = velocity + tr->Rightward() * right;

			float speed = m_MovementSpeed;
			if (PARADIGM_INPUT->IsKeyDown(cam->DisplayTarget, EKeyCode::LeftShift))
				speed *= m_SpeedMultiplier;

			tr->Position = tr->Position + (speed * velocity * PARADIGM.Time.GetDeltaTime());

			UAxis axis = PARADIGM_INPUT->GetAxis(cam->DisplayTarget, EAxisCode::Mouse);

			if (PARADIGM_INPUT->IsKeyDown(cam->DisplayTarget, EKeyCode::Mouse_RightClick))
			{
				PARADIGM_INPUT->SetCursorCaptureMode(cam->DisplayTarget, ECursorCaptureMode::MouseCaptureMode_Locked);
				PARADIGM_INPUT->SetActiveCursor(false);

				float turnL = (axis.X - m_MouseBuffer.X) * m_RotationSpeed;// * PARADIGM.Time.GetDeltaTime();
				float LookU = (axis.Y - m_MouseBuffer.Y) * m_RotationSpeed;// * PARADIGM.Time.GetDeltaTime();

				//FPrint::Print("Axis { X : " + FString::ToString(turnL) + "; Y : " + FString::ToString(LookU) + "}");
				m_Rotations = FVector3(LookU, turnL , 0) + m_Rotations;
				tr->Rotation = FQuaternion::FromEulerAngles(m_Rotations);

			}
			else if (PARADIGM_INPUT->IsKeyDown(cam->DisplayTarget, EKeyCode::Mouse_LeftClick))
			{
				float horizontalAngle = cam->FieldOfView * 0.5f * axis.X;
				float verticalAngle = cam->FieldOfView * 0.5f * axis.Y;

				FVector3 direction = cam->GearedUnit->GetTransform()->Forward() * FQuaternion::FromEulerAngles(verticalAngle, horizontalAngle, 0);
				auto result = PARADIGM_PHYSICS.Raycast((UVector3)cam->GearedUnit->GetTransform()->Position, (UVector3)(direction.Normalized() * m_PickingDistance), true);

				if (result.Count())
				{
					UMetaEntity* target = result[0].entity;
				}
			}
//#ifndef _PARADIGM_EDITOR
			else
			{
				PARADIGM_INPUT->SetCursorCaptureMode(cam->DisplayTarget, ECursorCaptureMode::MouseCaptureMode_Free);
				PARADIGM_INPUT->SetActiveCursor(true);
			}
//#endif

			m_MouseBuffer.X = axis.X;
			m_MouseBuffer.Y = axis.Y;
		}
	}
}