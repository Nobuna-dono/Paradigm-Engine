#ifndef _UQUATERNION_H_
#define _UQUATERNION_H_

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			struct FVector4;
			struct FQuaternion;
			class FMatrix4;

			struct UQuaternion
			{
				operator FQuaternion();

				void operator=(const FQuaternion& _val);

				float w, x, y, z;
			};
		}
	}
}
typedef ParadigmEngine::Core::Math::UQuaternion UQuaternion;

#endif