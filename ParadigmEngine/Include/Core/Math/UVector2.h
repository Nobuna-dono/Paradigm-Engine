#ifndef _UVECTOR2_H_
#define _UVECTOR2_H_

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Math
		{
			struct FVector2;
			struct FVector3;
			struct FVector4;

			struct UVector2
			{
				operator FVector2();
				operator FVector3();
				operator FVector4();
				operator float*();

				void operator=(const FVector2& _val);

				float x, y;
			};
		}
	}
}

#endif