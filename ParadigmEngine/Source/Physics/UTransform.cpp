#include <Physics/UTransform.h>
#include <EngineFramework/Factory/FMetaEntity.h>

namespace ParadigmEngine
{
	namespace Physics
	{
		UMetaTransform::UMetaTransform(const FVector3& _position, const FQuaternion& _rotation, const FVector3& _scale)
			: m_Position{ _position }, m_Rotation{ _rotation }, m_Scale{ _scale }
		{}

		UMetaTransform::UMetaTransform(const UMetaTransform& _other)
			: m_Position{ _other.Position }, m_Rotation{ _other.Rotation }, m_Scale{ _other.Scale }
		{

		}

		FVector3 UMetaTransform::_GetPosition() const
		{
			return m_Position;
		};

		FVector3 UMetaTransform::_GetRelativePosition() const
		{
			return m_RelativePosition;
		};

		FVector3 UMetaTransform::_GetScale() const
		{
			return m_Scale;
		};
		FVector3 UMetaTransform::_GetRelativeScale() const
		{
			return m_RelativeScale;
		};

		FQuaternion UMetaTransform::_GetRotation() const
		{
			return m_Rotation;
		};
		FQuaternion UMetaTransform::_GetRelativeRotation() const
		{
			return m_RelativeRotation;
		};

		UMatrix4 UMetaTransform::ToMatrix() const
		{
			FMatrix4 mat = FQuaternion(m_Rotation.load()).ToMatrix4();
			mat.Scale(m_Scale.load());

			mat[3] += m_Position.load().x;
			mat[7] += m_Position.load().y;
			mat[11] += m_Position.load().z;

			return *(UMatrix4*)&mat;
		}

		void UMetaTransform::_SetPosition(const FVector3& _in)
		{
			if (m_isStatic)	return;

			if (_in != m_Position)
			{
				if (GearedUnit->GetParent())
				{
					m_Position = _in;
					UMetaTransform* tr = GearedUnit->GetParent()->GetTransform();
					m_RelativePosition = (_in - tr->Position) * tr->Rotation.GetInvert();
				}
				else
					m_RelativePosition = m_Position = _in;

				FMetaEntity::OnPositionChanged(GearedUnit);

				m_bPositionOutdated = true;
				m_bOutdated = true;
			}
		}

		void UMetaTransform::_SetRelativePosition(const FVector3& _in)
		{
			if (m_isStatic)	return;

			if (GearedUnit->GetParent())
			{
				m_RelativePosition = _in;
				UMetaTransform* tr = GearedUnit->GetParent()->GetTransform();
				m_Position = tr->Position + _in * tr->Rotation;
			}
			else
				m_RelativePosition = m_Position = _in;

			FMetaEntity::OnPositionChanged(GearedUnit);

			m_bPositionOutdated = true;
			m_bOutdated = true;
		}

		void UMetaTransform::_SetScale(const FVector3& _in)
		{
			if (m_isStatic)	return;

			if (_in != m_Scale)
			{
				if (GearedUnit->GetParent())
				{
					m_Scale = _in;
					UMetaTransform* tr = GearedUnit->GetParent()->GetTransform();
					m_RelativeScale = _in / tr->Scale;
				}
				else
					m_RelativeScale = m_Scale = _in;

				FMetaEntity::OnScaleChanged(GearedUnit);

				m_bScaleOutdated = true;
				m_bOutdated = true;
			}
		}
		void UMetaTransform::_SetRelativeScale(const FVector3& _in)
		{
			if (m_isStatic)	return;

			if (GearedUnit->GetParent())
			{
				m_RelativeScale = _in;
				UMetaTransform* tr = GearedUnit->GetParent()->GetTransform();
				m_Scale = _in * tr->Scale;
			}
			else
				m_RelativeScale = m_Scale = _in;

			FMetaEntity::OnScaleChanged(GearedUnit);

			m_bScaleOutdated = true;
			m_bOutdated = true;
		}

		void UMetaTransform::_SetRotation(const FQuaternion& _in)
		{
			if (m_isStatic)	return;

			if (_in != m_Rotation)
			{
				if (GearedUnit->GetParent())
				{
					m_Rotation = _in;
					UMetaTransform* tr = GearedUnit->GetParent()->GetTransform();
					m_RelativeRotation = _in / tr->Rotation;
				}
				else
					m_RelativeRotation = m_Rotation = _in;

				FMetaEntity::OnRotationChanged(GearedUnit);

				m_bRotationOutdated = true;
				m_bOutdated = true;
			}
		}

		void UMetaTransform::_SetRelativeRotation(const FQuaternion& _in)
		{
			if (m_isStatic)	return;

			if (GearedUnit->GetParent())
			{
				m_RelativeRotation = _in;
				UMetaTransform* tr = GearedUnit->GetParent()->GetTransform();
				m_Rotation = tr->Rotation * _in;
			}
			else
				m_RelativeRotation = m_Rotation = _in;

			FMetaEntity::OnRotationChanged(GearedUnit);

			m_bRotationOutdated = true;
			m_bOutdated = true;
		}

		UMetaTransform::operator FMatrix4()
		{
			return ToMatrix();
		}

		void UMetaTransform::operator=(const UMetaTransform& _tr)
		{
			_SetPosition(_tr._GetPosition());
			_SetRotation(_tr._GetRotation());
			_SetScale(_tr._GetScale());
		}

		bool UMetaTransform::operator!=(const UMetaTransform& _tr) const
		{
			return Position != _tr.Position ||
				Rotation != _tr.Rotation ||
				Scale != _tr.Scale;
		}

		bool UMetaTransform::operator==(const UMetaTransform& _tr) const
		{
			return (Position == _tr.Position &&
					Rotation == _tr.Rotation &&
					Scale == _tr.Scale);
		}

		void UMetaTransform::Updated()
		{
			m_bPositionOutdated = false;
			m_bRotationOutdated = false;
			m_bScaleOutdated = false;
			m_bOutdated = false;
		}

	}
}