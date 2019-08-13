#ifndef _UVECTOR3_H_
#define _UVECTOR3_H_

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			struct FVector2;
			struct FVector3;
			struct FVector4;
			struct FQuaternion;

			/** A simple vector3 structure (x, y, z). */
			struct UVector3
			{
//				UVector3(const FVector3&);
				operator FVector2();
				operator FVector3();
				operator FVector4();
				operator float*();

				void operator=(const FVector3& _val);

				float x{ 0 }, y{ 0 }, z{ 0 };
			};
		}
	}
}

#endif